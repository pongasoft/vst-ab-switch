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
  if(!fParamCxMgr || getTag() < 0)
    return;

  auto paramID = static_cast<ParamID>(getTag());

  fLabel = registerSerParam<UTF8String>(paramID);
  if(fLabel)
  {
    setText(fLabel->getValue());
  }
  else
  {
    unregisterParam(paramID);
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