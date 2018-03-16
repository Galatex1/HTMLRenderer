#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include "vector2.h"
#include <cairo.h>
#include <vector>
#include "Color.h"
//#include "Renderer.h"
#include "Functionbuf.h"
#include "SmartPointers.h"
#include "StrFunction.h"
#include "windows.h"



using namespace std;
using namespace HTMLParser;

class Renderer;

void doLog(std::string const& value);

class Debug : private virtual functionbuf, public std::ostream 
{
public:
	static Debug console;

	//Default Constructor
	Debug() : functionbuf(&doLog), std::ostream(static_cast<std::streambuf*>(this)) {
		this->flags(std::ios_base::unitbuf);
	};

	Debug(Renderer* rend/*cairo_t * _cr, double size, Color color, Vector2 pos*/): functionbuf(&doLog), std::ostream(static_cast<std::streambuf*>(this))
	{
		this->flags(std::ios_base::unitbuf);
		//cr = _cr;
		//font_size = size;
		//text_color = color;
		//position = pos;
		//last_line = position.y;
		p = rend;
		console = *this;
	}

	Debug(const Debug& d) : functionbuf(d.d_function), std::ostream(static_cast<std::streambuf*>(this))
	{

	}

	Debug& operator=(Debug& d)
	{
		return d;
	}

	Debug* setCairo(cairo_t * _cr);
	Debug* setHWnd(HWND _hWnd);
	Debug* setFontSize(double size);
	Debug* setTextColor(Color color);
	Debug* setPosition(Vector2 pos);
	Debug* setWidth(double _width = 200.0);
	Debug* setHeight(double _height = 200.0);

	void update();

	void log(std::string const& message);

	void renderMessages();

	void newLine();

	bool isInitialized() { return (cr ? true : false); };

	//Deconstructor
	~Debug() {};

private:
	HWND hWnd;
	cairo_t *cr;
	Renderer * p;
	double width;
	double height;
	double font_size;
	Color text_color;
	Vector2 position;
	Vector2 last_line;
	vector<string> messages;
	
};





#endif

