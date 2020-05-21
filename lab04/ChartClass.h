#pragma once
#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
private:
	std::shared_ptr<ConfigClass> cfg;
	int _w, _h;
	int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
	double x_min, x_max; // zakres zmiennej x
	double y_min, y_max; // zakres wartosci przyjmowanych przez funkcje
	double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji

	void Line2d( Matrix t, wxDC *dc, double x1, double y1, double x2, double y2);


	Matrix Translation(double dx, double dy);
	Matrix Rotation(double alpha);
	Matrix Scale();

	void Axis(wxDC *dc, Matrix t);

	

public:
	ChartClass(std::shared_ptr<ConfigClass> c, int w = 600, int h = 400);
	void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
	double Get_Y_min(); // zwraca y_min
	double Get_Y_max(); // zwraca y_max
	void Draw(wxDC *dc, int _w, int _h);  // rysuje wykres

};

#endif