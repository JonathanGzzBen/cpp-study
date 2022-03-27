#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>
#include <ui_implementation/main_frame_implementation.h>

#endif

#include "ui/wx_gui.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    auto frame = new MainFrameImplementation();
    frame->Show(true);
    return true;
}
