#include "Debug.h"
#include "Renderer.h"

Debug Debug::console;
//ofunctionstream Debug::Console;

void doLog(std::string const& value) {

	vector<string> lines = split(value, "\n", true);
	
	for each (string line in lines)
	{
		if (line == "\n")
			Debug::console.newLine();
		else
			Debug::console.log(line);
	}

}

void Debug::setParameters(cairo_t * _cr, double size, Color color, Vector2 pos, double _width, double _height)
{
	cr = _cr;
	font_size = size;
	text_color = color;
	position = pos;
	last_line = Vector2(0.0, 0.0);
	width = _width;
	height = _height;
	p->roundedRectangle(cr, position.x, position.y - 20, width - 40, 20, Color(50, 50, 50, 1), 7);
	p->text(cr, "Console", position.x+4, position.y - 16, 16.0, Color(255,255,255,1));
}

void Debug::log(std::string const & message) {

	/*double y = last_line + font_size + 3.0;
	last_line = y;*/

	p->text(cr, "", 0.0, 0.0, font_size);

	cairo_text_extents_t extents;
	cairo_text_extents(cr, message.c_str(), &extents);


	if (last_line.x + extents.x_advance > width)
		newLine();

	p->text(cr, message, position.x + last_line.x, position.y + last_line.y, font_size);



	last_line.x += extents.width;

}

void Debug::newLine() {

	double y = last_line.y + font_size + 3.0;
	last_line.y = y;
	last_line.x = 0.0;
}
