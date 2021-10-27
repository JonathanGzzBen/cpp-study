#include "main.h"

#include <wx/app.h>
#include <wx/wx.h>

#include "simple.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Simple *simple = new Simple(wxT("Simple"));
    simple->Show(true);
    delete simple;
    return true;
}
