//
// Created by jonat on 26-Mar-22.
//

#ifndef WXFORMBUILDER_TESTS_MAIN_FRAME_IMPLEMENTATION_H
#define WXFORMBUILDER_TESTS_MAIN_FRAME_IMPLEMENTATION_H


#include <wx/event.h>
#include <ui/wx_gui.h>

class MainFrameImplementation : public MainFrame {
protected:
    void ShowHelloDialog(wxCommandEvent &event) override;

public:
    MainFrameImplementation(wxWindow *parent = NULL);

    ~MainFrameImplementation() = default;
};


#endif //WXFORMBUILDER_TESTS_MAIN_FRAME_IMPLEMENTATION_H
