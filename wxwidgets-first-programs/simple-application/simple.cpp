#include "simple.h"

#include <wx/defs.h>
#include <wx/gdicmn.h>

Simple::Simple(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) {
  Centre();
}
