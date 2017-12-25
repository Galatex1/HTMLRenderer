#include "Display.h"
#include "Element.h"

void Display::setProperty() {

	if (isInline())
		setInline();
	else
		setBlock();

};

void Display::setInline() {

	double height = 0;
	double width = 0;

	for each (spElement child in parent->children)
	{
		height = child->height > height ? child->height : height;
		width += child->width;
	}

};

void Display::setBlock() {

	double height = 0;
	double width = parent->width;

	for each (spElement child in parent->children)
	{
		height += child->height;
	}

};
