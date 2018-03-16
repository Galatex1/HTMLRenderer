#include "Renderer.h"
#include "Debug.h"
#include "CairoSurface.h"
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
	cairo_stroke(cr);
}

void Renderer::text(cairo_t* cr, string text, double x, double y, double size, Color fill, cairo_font_slant_t slant, cairo_font_weight_t weight)
{
	cairo_select_font_face(cr, "Sans", slant, weight);
	cairo_set_font_size(cr, size);
	cairo_set_source_rgba(cr, fill.r, fill.g, fill.b, fill.a);

	cairo_text_extents_t extents;
	cairo_text_extents(cr, text.c_str(), &extents);

	cairo_move_to(cr, x, y + size - 2);

	cairo_show_text(cr, text.c_str());


	///* draw helping lines */
	//cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
	//cairo_set_line_width(cr, 2.0);
	//cairo_arc(cr, x, y, 4.0, 0, 2 * M_PI);
	//cairo_fill(cr);
	//cairo_move_to(cr, x, y);
	//cairo_rel_line_to(cr, 0, -extents.height);
	//cairo_rel_line_to(cr, extents.width, 0);
	//cairo_rel_line_to(cr, extents.x_bearing, -extents.y_bearing);
	//cairo_stroke(cr);

	//cairo_fill(cr);
}

void Renderer::calculate(cairo_t * cr, spElement _el)
{
	int i = 0;

	for each (spElement el in _el->children)
	{
		el->position = Vector2(0.0, 0.0);
		el->width = el->pWidth->value;
		el->height = el->pHeight->value;

		if (el->type == "text")
		{
			text(cr);
			cairo_text_extents_t extents;
			cairo_text_extents(cr, el->text.c_str(), &extents);
			el->width = extents.width;
			el->height = extents.height;
		}

		el->allPreChildRender();

		if (el->children.size() > 0)
			calculate(cr, el);

		el->allPostChildRender();

		i++;
	}
}

void Renderer::renderDOM(cairo_t * cr, spElement _el)
{
	int i = 0;

	if (_el->type == "document")
	{
		roundedRectangle(cr,
			_el->getPos().x,
			_el->getPos().y,
			_el->width,
			_el->height,
			_el->pBackgroundColor,
			0.0,
			_el->pBorderSize->x(),
			_el->pBorderColor
		);
	}

	for each (spElement el in _el->children)
	{
		if (el->type != "text")
		{
			if (el->type == "input")
			{
				if(el->input == "text")
					roundedRectangle(cr,
						el->getPos().x,
						el->getPos().y,
						el->width,
						el->height,
						Color(255, 255, 255, 1.0),
						0.0,
						0.7,
						Color(0, 0, 0, 1.0)
					);
				else if (el->input == "checkbox")
				{
					/*int SIZE = 10;
					el->width = el->width > SIZE ? el->width : SIZE;
					el->height = el->height > SIZE ? el->height : SIZE;*/

					roundedRectangle(cr,
						el->getPos().x,
						el->getPos().y,
						el->width,
						el->height,
						Color(0.9215686274509804, 0.9215686274509804, 0.9215686274509804, 1.0),
						2.0,
						0.1,
						Color(0, 0, 0, 1.0)
						);
				}
			}
			else if (el->type == "button")
			{
				roundedGradiantRectangle(cr,
					el->getPos().x,
					el->getPos().y,
					el->width,
					el->height,
					Color(255, 255, 255, 1.0),
					3.0,
					1,
					Color(112, 112, 112, 1.0)
				);
			}
			else
			{
				roundedRectangle(cr,
					el->getPos().x,
					el->getPos().y,
					el->width,
					el->height,
					el->pBackgroundColor,
					0.0,
					el->pBorderSize->x(),
					el->pBorderColor
				);
			}
		}
		else
		{
			text(cr, el->text, el->getPos().x, el->getPos().y,13.0,el->pColor);
		}

		if (el->children.size() > 0)
			renderDOM(cr, el);

		i++;
	}
}

void Renderer::doRender(cairo_t * cr, spElement DOM)
{
	calculate(cr, DOM);
	renderDOM(cr, DOM);
}

//void Renderer::draw_gradient(cairo_t *cr, double width)
//{
//	cairo_pattern_t *pat;
//	pat = cairo_pattern_create_linear(20.0, 260.0, 20.0, 360.0);
//
//	cairo_pattern_add_color_stop_rgb(pat, 0, 0.9490196078431373, 0.9490196078431373, 0.9490196078431373);
//	cairo_pattern_add_color_stop_rgb(pat, 0.5, 0.9215686274509804, 0.9215686274509804, 0.9215686274509804);
//	cairo_pattern_add_color_stop_rgb(pat, 0.500000000000001, 0.8666666666666667, 0.8666666666666667, 0.8666666666666667);
//	cairo_pattern_add_color_stop_rgb(pat, 1, 0.8117647058823529, 0.8117647058823529, 0.8117647058823529);
//
//	cairo_rectangle(cr, 20, 260, width, width);
//	cairo_set_source(cr, pat);
//	cairo_fill(cr);
//
//	cairo_pattern_destroy(pat);
//}

void Renderer::roundedGradiantRectangle(cairo_t * cr, double x, double y, double width, double height, Color fill, double _radius, double border, Color borderColor, double aspect)
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

    //cairo_surface_t* sur1 = cairo_surface_create_for_rectangle(CSurface::surface, x, y, width, height);

	cairo_pattern_t *pat;
	
	pat = cairo_pattern_create_linear( y+height/2.0, x, y+height/2.0, x+width);
	//pat = cairo_pattern_create_for_surface(sur1);

	//Debug::console << "Height: " << height << ",   ";

	//cairo_patte

	double WinWidth = CSurface::WindowRect.right - CSurface::WindowRect.left;
	double WinHeight = CSurface::WindowRect.bottom - CSurface::WindowRect.top;

	double scaleH = (height+58) / height;

	
	cairo_matrix_t matrix;
	cairo_get_matrix(cr, &matrix);
	//cairo_matrix_init_scale(&matrix, 1, 1);
	cairo_matrix_init_translate(&matrix, 0, -y + (height/2) );

	cairo_pattern_set_matrix(pat, &matrix);

	//Debug::console << " -y: " << -y << ", ScaleH: " << scaleH << endl;

	cairo_pattern_set_extend(pat, CAIRO_EXTEND_PAD);


	//cairo_pattern_add_color_stop_rgb(pat, 0, 0.9490196078431373, 0.9490196078431373, 0.9490196078431373);
	//cairo_pattern_add_color_stop_rgb(pat, 0.5, 0.9215686274509804, 0.9215686274509804, 0.9215686274509804);
	//cairo_pattern_add_color_stop_rgb(pat, 0.6, 0.8666666666666667, 0.8666666666666667, 0.8666666666666667);
	cairo_pattern_add_color_stop_rgb(pat, 1, 0.8117647058823529, 0.8117647058823529, 0.8117647058823529);

	cairo_set_source(cr, pat);
	cairo_fill_preserve(cr);
	cairo_pattern_destroy(pat);

	cairo_set_source_rgba(cr, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	cairo_set_line_width(cr, border);
	cairo_stroke(cr);

	//Debug::console << "x: " << x << ", y: " << y << ", h: " << height << ", w: " << width << ", winHeight: " <<WinHeight << endl;
}

//0.8117647058823529
