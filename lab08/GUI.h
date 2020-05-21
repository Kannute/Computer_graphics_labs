#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/frame.h>

class MyFrame : public wxFrame
{
private:

protected:
	wxButton* loadImgButton;
	wxButton* censorButton;
	wxButton* erodeButton;
	wxCheckBox* animeCheck;
	wxStaticText* m_staticText1;
	wxPanel* m_panel3;

	virtual void WindowSizeChanged(wxSizeEvent& event) { event.Skip(); }
	virtual void WindowUpdate(wxUpdateUIEvent& event) { event.Skip(); }
	virtual void LoadImgClick(wxCommandEvent& event) { event.Skip(); }
	virtual void CensorClick(wxCommandEvent& event) { event.Skip(); }
	virtual void ErodeClick(wxCommandEvent& event) { event.Skip(); }
	virtual void AnimeCheck(wxCommandEvent& event) { event.Skip(); }


public:

	MyFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1025, 575), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame();

};

#endif 
