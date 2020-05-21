#include <wx/dc.h>
#include <memory>
#include "vecmat.h"
#include "ChartClass.h"


ChartClass::ChartClass(std::shared_ptr<ConfigClass> c, int w, int h) : _w(w), _h(h) {
	cfg = std::move(c);
	x_step = 200;
}

void ChartClass::Set_Range()
{
	double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
	double x, y, step;
	int i;

	xmin = cfg->Get_x_start();
	xmax = cfg->Get_x_stop();

	step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
	x = cfg->Get_x_start();

	for (i = 0; i <= x_step; i++)
	{
		y = GetFunctionValue(x);
		if (y > ymax) ymax = y;
		if (y < ymin) ymin = y;
		x = x + step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}


double ChartClass::GetFunctionValue(double x)
{
	if (cfg->Get_F_type() == 1) return x * x;
	if (cfg->Get_F_type() == 2) return 0.5*exp(4 * x - 3 * x*x);
	return x + sin(x*4.0);
}

void ChartClass::Draw(wxDC *dc, int _w, int _h)
{
	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, _w - 20, _h - 20);
	dc->SetClippingRegion(wxRect(10, 10, _w - 20, _h - 20));
	dc->SetPen(wxPen(RGB(0, 0, 255)));

	Matrix T;

	if (!cfg->RotateScreenCenter())
		T = Translation(cfg->Get_dX(), cfg->Get_dY()) * Rotation(cfg->Get_Alpha()) * Scale();
	else
		T = Rotation(cfg->Get_Alpha()) * Translation(cfg->Get_dX(), cfg->Get_dY()) * Scale();

	Axis(dc, T);

	dc->SetPen(wxPen(RGB(0, 255, 0)));

	double step = (x_max - x_min) / x_step;

	for (double i = x_min; i < x_max; i += step)
		Line2d(T, dc, i, GetFunctionValue(i), i + step, GetFunctionValue(i + step));

}

void ChartClass::Line2d( Matrix t, wxDC *dc, double x1, double y1, double x2, double y2) 
{
	Vector startPoint, endPoint;
	startPoint.Set(x1, y1);
	endPoint.Set(x2, y2);
	startPoint = t * startPoint;
	endPoint = t * endPoint;
	dc->DrawLine(startPoint.GetX(), _h - startPoint.GetY(), endPoint.GetX(), _h - endPoint.GetY());
}



double ChartClass::Get_Y_min()
{
	Set_Range();
	return y_min;
}

double ChartClass::Get_Y_max()
{
	Set_Range();
	return y_max;
}

Matrix ChartClass::Translation(double dx, double dy)
{
	Matrix X;
	X.data[0][0] = 1.0;
	X.data[1][1] = 1.0;
	X.data[0][2] = dx;
	X.data[1][2] = -dy;
	return X;
}

Matrix ChartClass::Rotation(double alpha) 
{
	double x, y;

	if (!cfg->RotateScreenCenter()) 
	{
		Matrix tmp = Scale();
		x = tmp.data[0][2];
		y = tmp.data[1][2];
	}
	else 
	{
		x = _w / 2.0;
		y = _h / 2.0;		
	}

	Matrix R;
	double cosinus = cos(alpha * M_PI / 180);
	double sinus = sin(alpha * M_PI / 180);
	R.data[0][0] = cosinus;
	R.data[0][1] = -sinus;
	R.data[1][0] = sinus;
	R.data[1][1] = cosinus;
	R.data[0][2] = x * (1 - cosinus) + y * sinus;
	R.data[1][2] = -x * sinus + y * (1 - cosinus);
	return R;
}

Matrix ChartClass::Scale() 
{
	Matrix S;
	S.data[0][0] = (_w - 20.0) / (cfg->Get_x1() - cfg->Get_x0());
	S.data[1][1] = (_h - 20.0) / (cfg->Get_y1() - cfg->Get_y0());
	S.data[0][2] = 10.0 - S.data[0][0] * cfg->Get_x0();
	S.data[1][2] = 10.0 - S.data[1][1] * cfg->Get_y0();
	return S;
}

void ChartClass::Axis(wxDC * dc, Matrix t)
{
	Line2d(t, dc, cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0);
	Line2d(t, dc, 0, Get_Y_min(), 0, Get_Y_max());

	Line2d(t, dc, x_max, 0, x_max - 0.05, 0.05);
	Line2d(t, dc, x_max, 0, x_max - 0.05, -0.05);
	Line2d(t, dc, 0, y_max, 0.05, y_max - 0.05);
	Line2d(t, dc, 0, y_max, -0.05, y_max - 0.05);

	double dy = 1 + int((cfg->Get_y1() - cfg->Get_y0()) / 10);

	Vector coordinates;
	for (double i = x_min; i <= x_max; i += 0.5)
	{
		Line2d(t, dc, i, -0.05, i, 0.05);
		coordinates.Set(i - 0.1, -0.1);
		coordinates = t * coordinates;
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coordinates.GetX() + 0.2, _h - coordinates.GetY(), cfg->Get_Alpha());
	}

	for (double i = y_min; i <= y_max; i += dy)
	{
		Line2d(t, dc, -0.05, i, 0.05, i);
		coordinates.Set(0.1, i);
		coordinates = t * coordinates;
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coordinates.GetX(), _h - coordinates.GetY() - 0.2, cfg->Get_Alpha());
	}
}