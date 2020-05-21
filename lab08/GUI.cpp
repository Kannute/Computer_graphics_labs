#include "GUI.h"

MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(300, 100), wxDefaultSize);

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer(wxVERTICAL);

	panelSizer->SetMinSize(wxSize(200, -1));
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	loadImgButton = new wxButton(this, wxID_ANY, wxT("Wczytaj Obrazek"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(loadImgButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	censorButton = new wxButton(this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(censorButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	erodeButton = new wxButton(this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(erodeButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	animeCheck = new wxCheckBox(this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(animeCheck, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);


	panelSizer->Add(bSizer4, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("test"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer7->Add(m_staticText1, 0, wxALL, 5);


	panelSizer->Add(bSizer7, 1, wxEXPAND, 5);


	mainSizer->Add(panelSizer, 0, wxEXPAND, 5);

	m_panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
	m_panel3->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
	m_panel3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	mainSizer->Add(m_panel3, 1, wxEXPAND, 5);


	this->SetSizer(mainSizer);
	this->Layout();

	this->Centre(wxBOTH);

	
	this->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame::WindowSizeChanged));
	this->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame::WindowUpdate));
	loadImgButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::LoadImgClick), NULL, this);
	censorButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::CensorClick), NULL, this);
	erodeButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::ErodeClick), NULL, this);
	animeCheck->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame::AnimeCheck), NULL, this);
}

MyFrame::~MyFrame()
{
	this->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame::WindowSizeChanged));
	this->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame::WindowUpdate));
	loadImgButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::LoadImgClick), NULL, this);
	censorButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::CensorClick), NULL, this);
	erodeButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::ErodeClick), NULL, this);
	animeCheck->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame::AnimeCheck), NULL, this);

}
