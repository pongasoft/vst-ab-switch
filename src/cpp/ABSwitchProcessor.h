#ifndef VST_AB_SWITCH_ABSWITCHPROCESSOR_H
#define VST_AB_SWITCH_ABSWITCHPROCESSOR_H

#include <public.sdk/source/vst/vstaudioeffect.h>
#include <atomic>

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {

enum class ESwitchState
{
  kSwitchStateUnknown, kA, kB
};

template<typename T>
inline ESwitchState ESwitchStateFromValue(T value)
{
  return value > 0 ? ESwitchState::kB : ESwitchState::kA;
}

class ABSwitchProcessor : public AudioEffect
{
public:
  struct State
  {
    ESwitchState fSwitchState;
    bool fSoften;
  };

  /**
   * Thread safe and lock free queue containing at most one element. Calling push multiple times is safe and simply
   * replaces the value in the queue if there is already one. The intended usage is the UI thread calling "push" (in XProcessor::setState)
   * and the processor thread calling pop at the beginning of process. If multiple pushes happen before process is called
   * it is fine because the processor will get the latest version.
   */
  template<typename T>
  class SingleElementQueue
  {
  public:
    SingleElementQueue() : fSingleElement{nullptr}
    {}

    ~SingleElementQueue()
    {
      delete fSingleElement.exchange(nullptr);
    }


    bool pop(T &oElement)
    {
      auto element = fSingleElement.exchange(nullptr);
      if(element)
      {
        oElement = *element;
        delete element;
        return true;
      }

      return false;
    };

    void push(T const &iElement)
    {
      delete fSingleElement.exchange(new T(iElement));
    }


  private:
    std::atomic<T *> fSingleElement;
  };

  /**
   * Thread safe and lock free atomic value. The intended usage is the processor calling set when the state is updated.
   * Then the UI thread will eventually call get (in XProcessor::getState). If the processor updates its state
   * multiple times before getState is called it is fine as getState will only get the latest value. get is also safe
   * to be called multiple times and will always return the most up to date version.
   */
  template<typename T>
  class AtomicValue
  {
  public:
    explicit AtomicValue(T const &iValue) : fValue{iValue}, fNewValue{nullptr}
    {}

    ~AtomicValue()
    {
      delete fNewValue.exchange(nullptr);
    }

    const T &get()
    {
      auto state = fNewValue.exchange(nullptr);
      if(state)
      {
        fValue = *state;
        delete state;
      }

      return fValue;
    };

    void set(T const &iState)
    {
      delete fNewValue.exchange(new T(iState));
    }


  private:
    T fValue;
    std::atomic<T *> fNewValue;
  };

public:
  ABSwitchProcessor();

  ~ABSwitchProcessor() override;

  /** Called at first after constructor */
  tresult PLUGIN_API initialize(FUnknown *context) override;

  /** Called at the end before destructor */
  tresult PLUGIN_API terminate() override;

  /** Switch the Plug-in on/off */
  tresult PLUGIN_API setActive(TBool state) override;

  /** Here we go...the process call */
  tresult PLUGIN_API process(ProcessData &data) override;

  /** Asks if a given sample size is supported see \ref SymbolicSampleSizes. */
  tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize) override;

  /** Restore the state (ex: after loading preset or project) */
  tresult PLUGIN_API setState(IBStream *state) override;

  /** Called to save the state (before saving a preset or project) */
  tresult PLUGIN_API getState(IBStream *state) override;

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this Plug-in
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/) { return (IAudioProcessor *) new ABSwitchProcessor(); }

  tresult PLUGIN_API setupProcessing(ProcessSetup &setup) override;


protected:
  /**
   * Processes the parameters that have changed since the last call to process
   *
   * @param inputParameterChanges
   */
  void processParameters(IParameterChanges &inputParameterChanges);

  /**
   * Processes inputs (step 2 always called after processing the parameters)
   *
   * @param inputParameterChanges
   */
  tresult processInputs(ProcessData &data);

  /**
   * Handles inputs when cross fade needs to happen
   */
  tresult processCrossFade(ProcessData &data);

  /**
   * Handles inputs when it is just a copy
   */
  tresult processCopy(ProcessData &data);

private:
  bool fAudioOn;

  State fState;
  State fPreviousState;

  SingleElementQueue<State> fStateUpdate;
  AtomicValue<State> fLatestState;
};

}
}

#endif //VST_AB_SWITCH_ABSWITCHPROCESSOR_H
