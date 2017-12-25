#pragma once

#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color();
	Color(double _r, double _g, double _b, double _a) : r(_r), g(_g), b(_b), a(_a) {};
	Color(int _r, int _g, int _b, double _a) {
		r = (double)_r / 255.0;
		g = (double)_g / 255.0;
		b = (double)_b / 255.0;
		a = _a;
	};
	~Color();

	double r;
	double g;
	double b;
	double a;

}; 
#endif
