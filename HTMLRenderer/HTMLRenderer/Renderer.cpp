#include "Renderer.h"
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

	cairo_move_to(cr, x, y + extents.height);
	cairo_show_text(cr, text.c_str());
	//cairo_fill(cr);
}

void Renderer::renderDOM(cairo_t * cr, spElement _el)
{
	int i = 0;

	for each (spElement el in _el->children)
	{
		el->position = Vector2(0.0, 0.0);
		el->width = 0.0;
		el->height = 0.0;
		Vector2 position;
		if (i > 0)
		{
			if ( el->pDisplay->isInline())
			{
				position = _el->children[i - 1]->position + Vector2(_el->children[i - 1]->width, 0) + Vector2(el->pMargin->x(), el->pMargin->y());
				
				if (position.x + el->width > _el->width)
					position = Vector2(0, el->DOMparent->children[i - 1]->position.y) + Vector2(0, el->DOMparent->children[i - 1]->height) + Vector2(el->pMargin->x(), el->pMargin->y());

			}
			else
				position = _el->children[i - 1]->position + Vector2(0, _el->children[i - 1]->height) + Vector2(el->pMargin->x(), el->pMargin->y());

		}
		else
		{
					position = Vector2(el->pMargin->pLeft->value, el->pMargin->pTop->value) + Vector2(el->DOMparent->pPadding->pLeft->value, el->DOMparent->pPadding->pTop->value);
		}


		el->position = position;

		if (size_t n = std::distance(el->children.begin(), el->children.end()) > 0)
			renderDOM(cr, el);


		srand(time(NULL));

		if (el->text != "")
		{
			cairo_text_extents_t extents;
			text(cr, el->text, el->position.x, el->position.y);
			cairo_text_extents(cr, el->text.c_str(), &extents);

			el->width += extents.width;
			el->height += extents.height;
		} 


		if (!el->pDisplay->isInline())
		{
			_el->height += el->height;

		}
		else
		{

			if (position.x + el->width > _el->width)
			{
				_el->height += el->height;
			}
			else
			{
				_el->width = el->width;
			}

		}

		if(el->type != Html::TEXT)
			roundedRectangle(cr, 
							el->position.x, 
							el->position.y, 
							el->width,
							el->height,
							Color(rand() % 255, rand()%255, rand() % 255, 0.5),
							0.0,
							1.0
							);
		else
			roundedRectangle(cr,
				el->position.x,
				el->position.y,
				el->width,
				el->height,
				Color(rand() % 255, rand() % 255, rand() % 255, 0.0),
				0.0,
				0.0
			);



		i++;
	}
}


