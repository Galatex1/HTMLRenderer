#include "Debug.h"
#include "Renderer.h"

Debug Debug::console;
//ofunctionstream Debug::Console;

void doLog(std::string const& value) {

	vector<string> lines = split(value, "\n", true);
	
	for each (string line in lines)
	{
		Debug::console.log(line);
	}

}

Debug * Debug::setCairo(cairo_t * _cr)
{
	cr = _cr;
	return this;
}

Debug * Debug::setHWnd(HWND _hWnd)
{
	hWnd = _hWnd;
	return this;
}

Debug * Debug::setFontSize(double size)
{
	font_size = size;
	return this;
}

Debug * Debug::setTextColor(Color _color)
{
	text_color = _color;
	return this;
}

Debug * Debug::setPosition(Vector2 pos)
{
	position = pos;
	return this;
}

Debug * Debug::setWidth(double _width)
{
	width = _width;
	return this;
}

Debug * Debug::setHeight(double _height)
{
	height = _height;
	return this;
}

void Debug::update()
{
	p->roundedRectangle(cr, position.x, position.y - 20, width - 40, 20, Color(50, 50, 50, 1), 7);
	p->text(cr, "Console", position.x + 4, position.y - 16, 16.0, Color(255, 255, 255, 1));
	last_line = Vector2(0.0, 0.0);

	renderMessages();
}

void Debug::log(std::string const & message) {

	messages.push_back(message);
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);	
}


void Debug::renderMessages()
{
	p->roundedRectangle(cr, position.x, position.y - 20, width - 40, 20, Color(50, 50, 50, 1), 7);
	p->text(cr, "Console", position.x + 4, position.y - 16, 16.0, Color(255, 255, 255, 1));
	for each (string message in messages)
	{
		p->text(cr, "", 0.0, 0.0, font_size);

		cairo_text_extents_t extents;

		cairo_text_extents(cr, message.c_str(), &extents);

		if (message == "\n")
		{
			newLine();
		}
		else
		{
			if (last_line.x + extents.x_advance > width)
				newLine();

			message += " ";

			p->text(cr, message, position.x + last_line.x, position.y + last_line.y, font_size, text_color);

			last_line.x += extents.width;
		}
	}
}

void Debug::newLine() {

	double y = last_line.y + font_size + 3.0;
	last_line.y = y;
	last_line.x = 0.0;
}
