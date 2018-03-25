#ifndef VST_AB_SWITCH_STRINGTEXTEDIT_H
#define VST_AB_SWITCH_STRINGTEXTEDIT_H

#include <vstgui4/vstgui/lib/iviewlistener.h>
#include <vstgui4/vstgui/lib/controls/ctextedit.h>

namespace pongasoft {
namespace VST {

using namespace VSTGUI;

/**
 * This class lives in the controller and will be assigned the view (CTextEdit) when the UI part of the plugin
 * is shown. In other words this class outlives the view (UI can be opened and closed). Once the view is assigned,
 * it gets initialized with the text (fText) and registers listeners to handle
 * lifecycle (IViewListenerAdapter::viewWillDelete) and changes (IControlListener::valueChanged).
 */
class StringTextEdit : VSTGUI::IControlListener, VSTGUI::IViewListenerAdapter
{
public:
  explicit StringTextEdit(UTF8String const& pText);
  ~StringTextEdit() override;

  inline const UTF8String &getText() const { return fText; }
  void setText (const UTF8String& pTxt);

  void assignTextEdit(CTextEdit *pTextEdit);

private:
  // called when the value of the control changes
  void valueChanged(CControl *pControl) override;

  // called when the view will be deleted (UI closed)
  void viewWillDelete(CView *view) override;

private:
  UTF8String fText;
  CTextEdit *fTextEdit;

};

}
}

#endif //VST_AB_SWITCH_STRINGTEXTEDIT_H
