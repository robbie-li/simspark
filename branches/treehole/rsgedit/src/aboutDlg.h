// -*- C++ -*- generated by wxGlade 0.4.1 on Sun Feb 18 14:55:33 2007

#include <wx/wx.h>
#include <wx/image.h>

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

// begin wxGlade: ::dependencies
// end wxGlade


class aboutDlg: public wxDialog {
public:
    // begin wxGlade: aboutDlg::ids
    // end wxGlade

    aboutDlg(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: aboutDlg::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: aboutDlg::attributes
    wxStaticBitmap* mBitmap;
    wxStaticText* label_1;
    wxButton* button_1;
    // end wxGlade
}; // wxGlade: end class


#endif // ABOUTDLG_H