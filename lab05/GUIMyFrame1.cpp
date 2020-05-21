#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
	
		wxClientDC dcClient(WxPanel);
		wxBufferedDC dcBuffer(&dcClient);

		int width, height;
		WxPanel->GetSize(&width, &height);

		dcBuffer.SetBackground(wxBrush(RGB(255, 255, 255)));
		dcBuffer.Clear();
		dcBuffer.SetClippingRegion(wxRect(0, 0, width, height));

		//macierz translacji o wektor
		Matrix4 translation; 
		translation.data[0][0] = 1.0;
		translation.data[1][1] = 1.0;
		translation.data[2][2] = 1.0;
		translation.data[3][3] = 1.0;
		translation.data[0][3] = (WxSB_TranslationX->GetValue() -100.0) / 50.0;
		translation.data[1][3] = -(WxSB_TranslationY->GetValue() -100.0) / 50.0;
		translation.data[2][3] = (WxSB_TranslationZ->GetValue() -100.0) / 50.0 + 2.0;

		//zmienne cosinus i sinus zale�ne od warto�ci obrotu wzgl�dem osi X
		double cosinus = cos(WxSB_RotateX->GetValue() * M_PI / 180);
		double sinus = sin(WxSB_RotateX->GetValue() * M_PI / 180);

		//macierz rotacji wok� osi X
		Matrix4 rotationX;
		rotationX.data[0][0] = 1.0;
		rotationX.data[1][1] = cosinus;
		rotationX.data[1][2] = -sinus;
		rotationX.data[2][1] = sinus;
		rotationX.data[2][2] = cosinus;
		rotationX.data[3][3] = 1.0;

		//(...), wzgl�dem osi Y
		cosinus = cos(WxSB_RotateY->GetValue() * M_PI / 180);
		sinus = sin(WxSB_RotateY->GetValue() * M_PI / 180);

		//macierz rotacji wok� osi Y
		Matrix4 rotationY;
		rotationY.data[0][0] = cosinus;
		rotationY.data[0][2] = sinus;
		rotationY.data[2][0] = -sinus;
		rotationY.data[2][2] = cosinus;
		rotationY.data[1][1] = 1;
		rotationY.data[3][3] = 1;

		//(...), wzgl�dem osi Z
		cosinus = cos(WxSB_RotateZ->GetValue() * M_PI / 180);
		sinus = sin(WxSB_RotateZ->GetValue() * M_PI / 180);

		//macierz rotacji wok� osi Z
		Matrix4 rotationZ;
		rotationZ.data[0][0] = cosinus;
		rotationZ.data[0][1] = -sinus;
		rotationZ.data[1][0] = sinus;
		rotationZ.data[1][1] = cosinus;
		rotationZ.data[2][2] = 1.0;
		rotationZ.data[3][3] = 1.0;

		//pe�na rotacja
		Matrix4 rotation = rotationX * rotationY * rotationZ;
		
		//macierz skali
		Matrix4 scale;
		scale.data[0][0] = WxSB_ScaleX->GetValue()/100.0;
		scale.data[1][1] = WxSB_ScaleY->GetValue()/100.0;
		scale.data[2][2] = WxSB_ScaleZ->GetValue()/100.0;
		scale.data[3][3] = 1.0;

		//macierz pe�nej transformacji
		Matrix4 transformation = translation * rotation * scale;
 		
		//macierz wyznaczaj�ca �rodek 
		Matrix4 center;
		center.data[0][0] = 1.0;
		center.data[1][1] = 1.0;
		center.data[2][2] = 1.0;
		center.data[0][3] = 0.5;
		center.data[1][3] = 0.5;
		
		

		//p�tla rysuj�ca lini�, dla ka�dego segmentu pliku *.geo przechowywanego w wektorze data
		for (Segment &elem : data) 
		{
			//wektory zawierajace po�o�enie pocz�tku i ko�ca rysowanej linii
			Vector4 begin, end;

			//ustawiam warto�ci x, y, z dla wektora pocz�tkowego 
			begin.Set(elem.begin.x, elem.begin.y, elem.begin.z);

			//transformuj� wektor o odpowiedni� warto��
			begin = transformation * begin;

			//analogicznie dla wektora ko�cowego
			end.Set(elem.end.x, elem.end.y, elem.end.z);
			end = transformation * end;

			//ustawiam kolor linii w zale�no�ci od koloru okre�lonego aktualnym segmencie
			dcBuffer.SetPen(wxPen(RGB(elem.color.R, elem.color.G, elem.color.B)));

			//je�eli warto�� Z wektora jest mniejsza od 0, przyjmuj�, �e jest minimalna
			if (begin.GetZ() < 0)
				begin.Set(begin.GetX(), begin.GetY(), 1.0e-005);
			if (end.GetZ() < 0)
				end.Set(begin.GetX(), begin.GetY(), 1.0e-005);

			//je�eli jest inaczej, wektory s� odpowiednio modyfikowane oraz wypo�rodkowywane
			//nast�pnie rysowana jest linia
			if (begin.GetZ() > 0 && end.GetZ() > 0) 
			{
				begin.Set(begin.GetX() / begin.GetZ(), begin.GetY() / begin.GetZ(), begin.GetZ());
				begin = center * begin;

				end.Set(end.GetX() / end.GetZ(), end.GetY() / end.GetZ(), end.GetZ());
				end = center * end;

				dcBuffer.DrawLine(begin.GetX() * width, begin.GetY() * height, end.GetX() * width, end.GetY() * height);
			}
		}
}
