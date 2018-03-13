#pragma once

#ifndef CAIRO_SURFACE_H
#define CAIRO_SURFACE_H

#include <cairo.h>
#include <cairo-win32.h>

class CSurface
{
public:

	static cairo_surface_t* surface;
	static cairo_t* cr;

};




#endif // CAIRO_SURFACE
