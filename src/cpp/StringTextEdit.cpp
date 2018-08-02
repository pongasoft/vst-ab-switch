#include "StringTextEdit.h"
#include <pongasoft/logging/logging.h>

namespace pongasoft {
namespace VST {
namespace ABSwitch {

using namespace VSTGUI;

//------------------------------------------------------------------------
// StringTextEditView::registerParameters
//------------------------------------------------------------------------
void StringTextEditView::registerParameters()
{
  if(fParamCxMgr)
  {
    auto paramID = static_cast<ParamID>(getTag());

    if(fParamCxMgr->existsSer(paramID))
    {
      fLabel = registerSerParam<UTF8StringSerializer>(static_cast<ParamID>(getTag()));
      if(fLabel)
      {
        setText(fLabel->getValue());
      }
    }
    else
    {
      if(fLabel)
        unregisterParam(fLabel->getParamID());
      fLabel = nullptr;
    }
  }
}

//------------------------------------------------------------------------
// StringTextEditView::registerParameters
//------------------------------------------------------------------------
void StringTextEditView::valueChanged()
{
  CTextEdit::valueChanged();
  if(fLabel)
  {
    fLabel->setValue(getText());
  }
}

//------------------------------------------------------------------------
// StringTextEditView::registerParameters
//------------------------------------------------------------------------
void StringTextEditView::setTag(int32_t val)
{
  CTextEdit::setTag(val);
  registerParameters();
}

//------------------------------------------------------------------------
// StringTextEditView::onParameterChange
//------------------------------------------------------------------------
void StringTextEditView::onParameterChange(ParamID iParamID)
{
  if(fLabel && fLabel->getParamID() == iParamID)
  {
    setText(fLabel->getValue());
  }

  CustomViewAdapter::onParameterChange(iParamID);
}

StringTextEditView::Creator __gStringTextEditCreator("pongasoft::StringTextEdit", "pongasoft - String Text Edit");
}
}
}