#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/utils.h>
#include <wx/wx.h>
#include <wx/wxcrt.h>
#include <wx/wxcrtvararg.h>

int main() {
  // wxPuts
  wxPuts(wxT("A wxWidgets console application"));

  // wxString
  wxString str1{wxT("Linux")};
  wxString str2{wxT("operating")};
  wxString str3{wxT("system")};
  auto combined_str{str1 + wxT(" ") + str2 + wxT(" ") + str3};
  wxPuts(combined_str);

  // Printf
  int flowers{21};
  wxString flowers_message;
  flowers_message.Printf(wxT("There are %d red roses."), flowers);
  wxPuts(flowers_message);

  // Format
  wxString flowers_message_initialized_with_format{
      wxString::Format(wxT("There are %d red roses."), flowers)};
  wxPuts(flowers_message_initialized_with_format);

  // Utility functions
  // wxShell(wxT("ls -l"));
  // wxShell("ls -l");

  wxPuts(wxGetHomeDir());
  wxPuts(wxGetOsDescription());
  wxPuts(wxGetUserName());
  wxPuts(wxGetFullHostName());

  long mem = wxGetFreeMemory().ToLong();

  wxPrintf(wxT("Memory: %ld\n"), mem);

  // Time & Date
  wxDateTime now = wxDateTime::Now();
  wxString date1 = now.Format();
  wxString date2 = now.Format(wxT("%X"));
  wxString date3 = now.Format(wxT("%x"));

  wxPuts(date1);
  wxPuts(date2);
  wxPuts(date3);

  // date span
  wxDateSpan span(0, 1);
  wxDateTime then {now.Add(span)};
  wxPuts(then.Format("%B %d %Y"));
}
