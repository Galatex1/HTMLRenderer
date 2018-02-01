#pragma once

#ifndef RENDERER_H
#define RENDERER_H


#include <cairo.h>
#include <string>
#include <vector>


#include "vector2.h"
#include "Color.h"
#include "Element.h"
#include "SmartPointers.h"

using namespace std;
using namespace HTMLParser;

#define M_PI 3.14

class Aspect
{
	Aspect() {};

	public:
		static double CIRCLE;
		static double SQUARE;
		static double NORMAL;
};

class Renderer
{

public:

	//Default Constructor
	Renderer();

	//Deconstructor
	~Renderer();

	//Params: cairo_t* cr, double x, double y, double width, double height, Color fill, double radius, double aspect (Aspect::    CIRCLE, SQUARE, NORMAL), double border, Color borderColor
	void roundedRectangle(cairo_t* cr, double x = 0.0, double y = 0.0, double width = 0.0, double height = 0.0, Color fill = Color(0,0,0,0.0), double _radius = 10.0, double border = 0.0, Color borderColor = Color(0, 0, 0, 1.0), double aspect = Aspect::NORMAL);
	
	void text(cairo_t* cr, string text = "", double x = 0.0, double y = 0.0, double size = 13.0, Color fill = Color(0, 0, 0, 1.0), cairo_font_slant_t slant = CAIRO_FONT_SLANT_NORMAL, cairo_font_weight_t weight = CAIRO_FONT_WEIGHT_NORMAL);

	void calculate(cairo_t * cr, spElement DOM);

	void renderDOM(cairo_t * cr, spElement DOM);

	void doRender(cairo_t * cr, spElement DOM);


private:

};

class Rectangle
{
public:
	//Default Constructor
	Rectangle();

	//Deconstructor
	~Rectangle();
private:
	double x;
	double y;
	double width;
	double height;
	double radius;
	double aspect;
	Color fill;
	double border;
	Color borderColor;
};




#endif
