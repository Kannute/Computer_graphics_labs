#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.ConvertToGreyscale();
	
	// TO DO: Konwersja do skali szarosci    
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Blur(5);
 // TO DO: Rozmywanie obrazu (blur)
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Mirror();
 // TO DO: Odbicie lustrzane
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	//Img_Cpy.Clear();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
	
 // TO DO: Zamiana kolorow 
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Clear();
	Img_Cpy = Img_Org.Scale(320, 420);
 // TO DO: Zmiana rozmiarow do 320x240
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Rotate(M_PI * 30 / 180, wxPoint(Img_Org.GetHeight(), Img_Org.GetWidth()));
 // TO DO: Obrot o 30 stopni
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
 // TO DO: Przesuniecie Hue o 180 stopni
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
 // TO DO: Ustawienie maski obrazu
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	
	//Nie mia�em pomys�u jak to zrobi�
}

 // TO DO: Pionowa maska Prewitta


void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	int rozmiar;
	unsigned char *c;

	Img_Cpy = Img_Org.Copy();
	rozmiar = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	c = Img_Cpy.GetData();

	for (int i = 0; i < rozmiar; i++)
	{
		if (c[i] < 128)
			c[i] = 0;
		else
			c[i] = 255;
	}
		
 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
}


void GUIMyFrame1::Contrast(int value)
{
	int rozmiar;
	int val;
	unsigned char *c;	
	float k;


	Img_Cpy = Img_Org.Copy();
	rozmiar = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	c = Img_Cpy.GetData();
	k = (value + 100) / (100.001 - value);

	for (int i = 0; i < rozmiar; i++)
	{
		val = (c[i] - 255.0 / 2) * c[i]+ 255.0 / 2;

		if (val > 255)
			val = 255;

		if (val < 0)
			val = 0;

		c[i] = val;
	}
	
}
 // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100


void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	int val;
	int rozmiar;
	unsigned char *c;

	rozmiar = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	Img_Cpy = Img_Org.Copy();
	c = Img_Cpy.GetData();

	for (int i = 0; i < rozmiar; i++)
	{
		val = c[i] + value;

		if (val > 255)
			val = 255;

		if (val < 0)
			val = 0;

		c[i] = val;
	}
 // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
}