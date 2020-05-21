#ifndef __GUIMyFrame__
#define __GUIMyFrame__

#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include <wx/msgdlg.h>
#include <math.h>
#include "GUI.h"
#include "CImg.h"
#include "FreeImage.h"



class GUIMyFrame : public MyFrame
{
protected:
	//Handler zmiany rozmiarow okna
	void WindowSizeChanged(wxSizeEvent& event);

	//Update okna
	void WindowUpdate(wxUpdateUIEvent& event);

	//Wczytanie obrazu i skopiowanie go do zmiennych wxImage
	void LoadImgClick(wxCommandEvent& event);

	//Ocenzurowanie strusia
	void CensorClick(wxCommandEvent& event);

	//Zardzewienie strusia
	void ErodeClick(wxCommandEvent& event);

	//Ustawienie flagi animacji w zale¿noœci czy checkbox jest zaznaczony
	void AnimeCheck(wxCommandEvent& event);
public:
	
	GUIMyFrame(wxWindow* parent);

	// Obraz
	wxImage image;
	wxImage source_image;

	// Rozmiary okna
	int window_width;
	int window_height;

	// Flaga zaznaczenia checkboxa animacji
	bool animation;

	// Maska gaussa potrzebna do wykonania animacji
	cimg_library::CImg<float> mask;

	// obraz FreeImage
	FIBITMAP *bmp;
	FIBITMAP* bitmap_free;

	// Flaga wczytania obrazka
	bool test;

	// Metoda update'ujaca obraz, gdy zostanie wykonana akcja
	void Repaint();
};

#endif 

