#include "Renderer.h"
#include "Debug.h"
#include <ctime>

double Aspect::CIRCLE = 0.5;
double Aspect::SQUARE = 0;
double Aspect::NORMAL = 1.0;


Color::Color()
{
}

Color::~Color()
{
} 


Renderer::Renderer()
{
	srand((unsigned)time(NULL));
}

Renderer::~Renderer()
{

}

void Renderer::roundedRectangle(cairo_t * cr, double x, double y, double width, double height, Color fill, double _radius, double border, Color borderColor, double aspect)
{
	/* a custom shape that could be wrapped in a function */
	double corner_radius = _radius;/*height / _radius;   /* and corner curvature radius */

	double radius = aspect > 0 ? aspect == Aspect::CIRCLE ? width > height ? height / 2 : width / 2 : corner_radius / aspect : 0;
	double degrees = M_PI / 180.0;
	cairo_new_sub_path(cr);
	cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);

	cairo_set_source_rgba(cr, fill.r, fill.g, fill.b, fill.a);
	cairo_fill_preserve(cr);
	cairo_set_source_rgba(cr, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	cairo_set_line_width(cr, border);
	cairo_stroke(cr);
}

void Renderer::text(cairo_t* cr, string text, double x, double y, double size, cairo_font_slant_t slant, cairo_font_weight_t weight)
{
	cairo_select_font_face(cr, "Sans", slant, weight);
	cairo_set_font_size(cr, size);

	cairo_text_extents_t extents;
	cairo_text_extents(cr, text.c_str(), &extents);

	cairo_move_to(cr, x, y + extents.y_advance);

	cairo_show_text(cr, text.c_str());
	//cairo_fill(cr);
}

void Renderer::calculate(cairo_t * cr, spElement _el)
{
	int i = 0;

	//Debug::console << _el->height << ": ";
	//Debug::console << _el->width << endl;

	for each (spElement el in _el->children)
	{
		el->position = Vector2(0.0, 0.0);
		el->width = 0.0;
		el->height = 0.0;

		if (el->type == "text")
		{
			text(cr);
			cairo_text_extents_t extents;
			cairo_text_extents(cr, el->text.c_str(), &extents);
			el->width = extents.width;
			el->height = extents.height;
		}

		el->allPreChildRender();

		if (size_t n = std::distance(el->children.begin(), el->children.end()) > 0)
			calculate(cr, el);

		el->allPostChildRender();

		el->allProperties();

		i++;
	}
}

void Renderer::renderDOM(cairo_t * cr, spElement _el)
{
	int i = 0;

	for each (spElement el in _el->children)
	{
		//el->allProperties();

		Debug::console << "rendering " << el->type << ", position: (" << el->position.x << ", " << el->position.y << "), width: " << el->width << ", height: " << el->height << endl;

		if (el->type != "text")
		{
			roundedRectangle(cr,
				el->position.x,
				el->position.y,
				el->width,
				el->height,
				Color(255,125,0, 0.1),
				0.0,
				0.0
			);
		}
		else
		{
			text(cr, el->text, el->position.x, el->position.y);
		}

		if (size_t n = std::distance(el->children.begin(), el->children.end()) > 0)
			renderDOM(cr, el);

		i++;
	}
}

void Renderer::doRender(cairo_t * cr, spElement DOM)
{
	calculate(cr, DOM);
	renderDOM(cr, DOM);
}


