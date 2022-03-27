#include "main_frame_implementation.h"

#include <wx/msgdlg.h>

MainFrameImplementation::MainFrameImplementation(wxWindow *parent) : MainFrame(parent) {}

void MainFrameImplementation::ShowHelloDialog(wxCommandEvent &event) {
    wxMessageBox(wxT("Hello"));
}
