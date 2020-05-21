#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

//funckje pomocnicze
double MakeGridPoint(int N, float d[100][3], double x, double y);
void MakeMap(double **siatka, unsigned char *data, double MAX, double MIN, int MappingType);


void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.SetBackground(*wxWHITE_BRUSH);
 memDC.Clear();
    
 // demo.....
 memDC.SetPen(*wxBLACK_PEN);
 memDC.SetBrush(*wxTRANSPARENT_BRUSH);


 //wyznaczanie najmniejszej i najwiekszej wartosci
 double MIN = d[0][2];
 double MAX = d[0][2];

 for (int i = 0; i < N; i++) 
 {
	 if (d[i][2] < MIN)
		 MIN = d[i][2];
	 if (d[i][2] > MAX)
		 MAX = d[i][2];
 }
 
 //interpolacja funkcji do regularnej siatki Sheparda
 double** grid = new double*[500];

 for (int i = 0; i < 500; i++)
	 grid[i] = new double[500];

 
 for (int x = 0; x < 500; x++)
	 for (int y = 0; y < 500; y++)	
		 grid[y][x] = MakeGridPoint(N, d, static_cast<double>(x)/100.0 - 2.5, static_cast<double>(y)/100.0 - 2.5);
	


 //Rysowanie mapy barwnej
 unsigned char* data = new unsigned char[500 * 500 * 3];

 if (MappingType) 
 {
	 MakeMap(grid, data, MAX, MIN, MappingType);
	 wxImage tmp(500, 500, data);
	 wxBitmap tmp2(tmp);
	 memDC.DrawBitmap(tmp2, 0, 0);
 }

 //Rysowanie poziomic w zaleznoœci od ich liczby
 if (Contour) 
 {
	 memDC.SetPen(*wxBLACK);
	 memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	 for (int level = 0; level < NoLevels; level++) 
	 {
		 double thresholdPoint = MIN + (level + 1) * (MAX - MIN) / (NoLevels + 1.0f);

		 for (int x = 0; x < 500; ++x) 
		 {
			 for (int y = 0; y < 500; ++y) 
			 {
				 if (grid[y][x] > thresholdPoint) 
				 {
					 for (int i = -1; i <= 1; i++)
					 {
						 for (int j = -1; j <= 1; j++) 
						 {
							 if (i != 0 && j != 0 && (y + i >= 0) && (y + i < 500) && (y + j >= 0) &&
								 (x + j < 500) && (grid[y + i][x + j] < thresholdPoint)) 
							 {
								 memDC.DrawPoint(y, x);
							 }
						 }
					 }
				 }
			 }
		 }
	 }
 }

 //Rysowanie punktow
 if (ShowPoints) 
 {
	 memDC.SetPen(*wxBLACK);
	 memDC.SetBrush(*wxTRANSPARENT_BRUSH);

	 for (int i = 0; i < N; ++i) 
	 {
		 const int x = (d[i][0] + 2.5) * 100;
		 const int y = (2.5 - d[i][1]) * 100;
		 memDC.DrawLine(x, y + 3, x, y - 3);
		 memDC.DrawLine(x - 3, y, x + 3, y);
	 }
 }

 //Czyszczenie
 for (int i = 0; i < 500; i++)
	 delete[] grid[i];

 delete[] grid;

    
     
}


double MakeGridPoint(int N, float d[100][3], double x, double y)
{
	double a = 0.0, b = 0.0, c = 0.0;

	for (int i = 0; i < N; i++) 
	{
		c = 1. / std::abs((x - d[i][0])*(x - d[i][0]) + (y - d[i][1])*(y - d[i][1]));
		a += c * d[i][2];
		b += c;
	}

	return a / b;
}

void MakeMap(double **grid, unsigned char *data, double MAX, double MIN, int MappingType)
{
	for (int x = 0; x < 500; x++) {
		for (int y = 0; y < 500; y++) {
			if (1 == MappingType) {
				float color = ((grid[x][y] - MIN) / (MAX - MIN) - 0.5) * 2;
				data[y * 500 * 3 + x * 3 + 0] = 127 - 127 * color;
				data[y * 500 * 3 + x * 3 + 1] = 0;
				data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
			}
			else if (2 == MappingType) {
				float color = ((grid[x][y] - MIN) / (MAX - MIN) - 0.5) * 2;
				data[y * 500 * 3 + x * 3 + 0] = color < 0 ? 255 * std::abs(color) : 0;
				data[y * 500 * 3 + x * 3 + 1] = 255 - 255 * std::abs(color);
				data[y * 500 * 3 + x * 3 + 2] = color > 0 ? 255 * std::abs(color) : 0;
			}
			else if (MappingType == 3) {
				float color = ((grid[x][y] - MIN) / (MAX - MIN) - 0.5) * 2;
				data[y * 500 * 3 + x * 3 + 0] = 127 + 127 * color;
				data[y * 500 * 3 + x * 3 + 1] = 127 + 127 * color;
				data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
			}
		}
	}
	
}