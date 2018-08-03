#ifndef VST_AB_SWITCH_STRINGTEXTEDIT_H
#define VST_AB_SWITCH_STRINGTEXTEDIT_H

#include <vstgui4/vstgui/lib/controls/ctextedit.h>
#include <pongasoft/VST/GUI/Views/CustomView.h>
#include "ABSwitchPlugin.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

using namespace VSTGUI;
using namespace GUI::Views;

class StringTextEditView : public CustomViewAdapter<CTextEdit>
{
public:
  explicit StringTextEditView(const CRect &iSize) : CustomViewAdapter(iSize, nullptr, -1)
  {}

  void setTag(int32_t val) override;

  void registerParameters() override;

  void valueChanged() override;

  void onParameterChange(ParamID iParamID) override;

  CLASS_METHODS_NOCOPY(StringTextEditView, CustomViewAdapter<CTextEdit>)

protected:
  GUISerParameterSPtr<UTF8String> fLabel;

public:
  class Creator : public TCustomViewCreator<StringTextEditView>
  {
    public:
    explicit Creator(char const *iViewName = nullptr, char const *iDisplayName = nullptr) :
      TCustomViewCreator(iViewName, iDisplayName, VSTGUI::UIViewCreator::kCTextEdit)
    {
    }
  };
};

}
}
}

#endif //VST_AB_SWITCH_STRINGTEXTEDIT_H
