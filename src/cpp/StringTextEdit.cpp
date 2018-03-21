#include "StringTextEdit.h"
#include "logging/loguru.hpp"

namespace pongasoft {
namespace VST {

using namespace VSTGUI;

///////////////////////////////////////////
// StringTextEdit::StringTextEdit
///////////////////////////////////////////
StringTextEdit::StringTextEdit(UTF8String const& pText):
  IControlListener(),
  IViewListenerAdapter(),
  fTextEdit(nullptr),
  fText(pText)
{
  DLOG_F(INFO, "StringTextEdit::StringTextEdit(%s)", fText.data());
}

///////////////////////////////////////////
// StringTextEdit::StringTextEdit//////////////////////////////////
StringTextEdit::~StringTextEdit()
{
  DLOG_F(INFO, "StringTextEdit::~StringTextEdit()");
}

///////////////////////////////////////////
// StringTextEdit::assignTextEdit
///////////////////////////////////////////
void StringTextEdit::assignTextEdit(CTextEdit *pTextEdit)
{
  DCHECK_NOTNULL_F(pTextEdit, "assignTextEdit should not receive null pointer");

  if(fTextEdit != nullptr)
  {
    fTextEdit->unregisterViewListener(this);
    fTextEdit->unregisterControlListener(this);
  }

  DLOG_F(INFO, "StringTextEdit::assignTextEdit(%i)", pTextEdit->getTag());

  fTextEdit = pTextEdit;
  fTextEdit->setText(fText);
  fTextEdit->registerControlListener(this);
  fTextEdit->registerViewListener(this);
}

///////////////////////////////////////////
// StringTextEdit::viewWillDelete
///////////////////////////////////////////
void StringTextEdit::viewWillDelete(CView *view)
{
  DCHECK_EQ_F(view, fTextEdit, "should be called with the same object!");

  DLOG_F(INFO, "StringTextEdit::viewWillDelete(%i)", fTextEdit->getTag());

  fTextEdit->unregisterViewListener(this);
  fTextEdit->unregisterControlListener(this);
  fTextEdit = nullptr;
}

///////////////////////////////////////////
// StringTextEdit::valueChanged
///////////////////////////////////////////
void StringTextEdit::valueChanged(CControl *pControl)
{
  DCHECK_EQ_F(pControl, fTextEdit, "should be called with the same object!");
  DLOG_F(INFO, "StringTextEdit::valueChanged(%i)", fTextEdit->getTag());
  fText = fTextEdit->getText();
}

///////////////////////////////////////////
// StringTextEdit::setText
///////////////////////////////////////////
void StringTextEdit::setText(const UTF8String &pTxt)
{
  fText = pTxt;
  if(fTextEdit != nullptr)
    fTextEdit->setText(pTxt);
}


}
}