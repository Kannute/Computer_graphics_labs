#include "GUIMyFrame.h"

#define PI 3.1415

GUIMyFrame::GUIMyFrame(wxWindow* parent)
	:
	MyFrame(parent)
{
	source_image = wxImage(800, 533);
	image = source_image.Copy();
	animation = false;
	test = false;
	mask = cimg_library::CImg<float>::CImg(source_image.GetWidth(), source_image.GetHeight(), 1, 1);
}

void GUIMyFrame::WindowSizeChanged(wxSizeEvent& event)
{
	window_width = event.GetSize().GetWidth();
	window_height = event.GetSize().GetHeight();
	Repaint();
}

void GUIMyFrame::WindowUpdate(wxUpdateUIEvent& event)
{	
	Repaint();
}

void GUIMyFrame::LoadImgClick(wxCommandEvent& event)
{
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("JPEG file (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK) 
	{
		if (!source_image.LoadFile(WxOpenFileDialog.GetPath())) 
		{
			wxMessageBox(_("Cannot open a file"));
		}
		else 
		{
			// wyczytuje obraz dla wximage i freeimage, ustawiam flage wczytania obrazka na true
			source_image.LoadFile(WxOpenFileDialog.GetPath());
			bmp = FreeImage_Load(FIF_JPEG, WxOpenFileDialog.GetPath(), JPEG_DEFAULT);
			test = true;

			// kopiuje do image
			image = source_image.Copy();

			// Update
			Repaint();
		}
	}
}

void GUIMyFrame::CensorClick(wxCommandEvent& event)
{
	cimg_library::CImg<unsigned char> c_image(image.GetWidth(), image.GetHeight(), 1, 3);

	// Konwersja wximage do cimage
	for (int i = 0; i < image.GetWidth(); i++)
	{
		for (int j = 0; j < image.GetHeight(); j++)
		{
			c_image(i, j, 0) = source_image.GetRed(i, j);
			c_image(i, j, 1) = source_image.GetGreen(i, j);
			c_image(i, j, 2) = source_image.GetBlue(i, j);
		}
	}

	// Ocenzurowanie
	c_image.blur(5);

	// Update obrazu
	image = source_image.Copy();

	//Konwersja cimage do wximage
	for (int i = 450; i < 580; i++) 
	{
		for (int j = 15; j < 100; j++)
		{
			int red = image.GetRed(i, j)*c_image(i, j, 1, 1) / 255.0;
			int green = image.GetGreen(i, j)*c_image(i, j, 1, 1) / 255.0;
			int blue = image.GetBlue(i, j)*c_image(i, j, 1, 1) / 255.0;
			image.SetRGB(i, j, c_image(i, j, 0), c_image(i, j, 1), c_image(i, j, 2));
		}
	}

	// Update
	Repaint();
}

void GUIMyFrame::ErodeClick(wxCommandEvent& event)
{
	//Wszystko analogicznie do CensorClick
	cimg_library::CImg<unsigned char> c_image(source_image.GetWidth(), source_image.GetHeight(), 1, 3);

	
	for (int i = 0; i < source_image.GetWidth(); i++)
	{
		for (int j = 0; j < source_image.GetHeight(); j++)
		{
			c_image(i, j, 0) = source_image.GetRed(i, j);
			c_image(i, j, 1) = source_image.GetGreen(i, j);
			c_image(i, j, 2) = source_image.GetBlue(i, j);
		}
	}

	
	c_image.erode(5);
	
	image = source_image.Copy();

	for (int i = 0; i < image.GetWidth(); i++) 
	{
		for (int j = 0; j < image.GetHeight(); j++) 
		{
			int red = image.GetRed(i, j)*c_image(i, j, 1, 1) / 255.0;
			int green = image.GetGreen(i, j)*c_image(i, j, 1, 1) / 255.0;
			int blue = image.GetBlue(i, j)*c_image(i, j, 1, 1) / 255.0;
			image.SetRGB(i, j, c_image(i, j, 0), c_image(i, j, 1), c_image(i, j, 2));
		}
	}
	
	Repaint();
}

void GUIMyFrame::AnimeCheck(wxCommandEvent& event)
{
	//Ustawienie flagi animacji
	animation ? animation = false : animation = true;
	image = source_image.Copy();
}


void GUIMyFrame::Repaint()
{
	// Pobranie kontekstu okna
	wxClientDC dc(m_panel3);
	// Zmiana rozmiaru
	m_panel3->SetSize(window_width - 215, window_height - 45);

	//String do wypisania informacji o obrazie
	
	wxString Label;
	//jezeli obraz zostal wczytany
	if (test) 
	{
		Label = "Rozmiar obrazka: ";
		Label = Label + std::to_string(source_image.GetWidth()) + "*" + std::to_string(source_image.GetHeight());
		Label = Label + "\n";

		int bpp = FreeImage_GetBPP(bmp);
		bitmap_free = FreeImage_Allocate(source_image.GetWidth(), source_image.GetHeight(), bpp);
		bitmap_free = bmp;

		FITAG *tag = NULL;
		FIMETADATA *mdhandle = NULL;

		//Wpisywanie informacji o obrazie do Label
		Label = Label + "EXIF Info:\n";
		mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, bitmap_free, &tag);
		if (mdhandle) 
		{			
			do
			{
				const char *value = FreeImage_TagToString(FIMD_EXIF_MAIN, tag);
				if (FreeImage_GetTagValue(tag))
				{
					Label = Label + FreeImage_GetTagKey(tag) + ": " + value + "\n";
				}
			} while (FreeImage_FindNextMetadata(mdhandle, &tag));

			FreeImage_FindCloseMetadata(mdhandle);
		}
	}
	//wypisywanie infromacji na temat obrazu
	m_staticText1->SetLabel(Label);


	// Je¿eli checkbox animacji jest true
	if (animation) 
	{

		// Katowy krok rok animacji
		static int krok;
		krok > 180 ? krok = -180 : krok += 30;

		// Gaussian
		int x = source_image.GetWidth() / 2 + 300 * cos(krok * PI / 180.0);
		int y = source_image.GetHeight() / 2 - 100 * sin(krok * PI / 180.0);
		int* spectrum = new int(1);
		mask.draw_gaussian(x, y, 100.0, spectrum);
		delete spectrum;

		// Zresetowanie obrazu
		image = source_image.Copy();

		unsigned char *image_data = image.GetData();

		for (int i = 0; i < source_image.GetHeight(); i++) 
		{
			for (int j = 0; j < source_image.GetWidth(); j++) 
			{
				image_data[i * source_image.GetWidth() * 3 + 3 * j + 0] = image_data[i * source_image.GetWidth() * 3 + 3 * j + 0] * mask(j, i);
				image_data[i * source_image.GetWidth() * 3 + 3 * j + 1] = image_data[i * source_image.GetWidth() * 3 + 3 * j + 1] * mask(j, i);
				image_data[i * source_image.GetWidth() * 3 + 3 * j + 2] = image_data[i * source_image.GetWidth() * 3 + 3 * j + 2] * mask(j, i);
			}
		}
	}

	// Tymczasowy obraz
	wxImage image_temp = image.Scale(window_width - 215, window_height - 45);

	// Tworzy tymczasowa bitmape na podstawie image_temp
	wxBitmap bitmap(image_temp);

	// Rysuje 
	dc.DrawBitmap(bitmap, 0, 0, true);
}