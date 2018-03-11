#include "Element.h"
#include "Display.h"

Element::Element()
{
	DOMparent = NULL;
	Init();
}


Element::Element(spElement _parent) : DOMparent(_parent)
{
	Init();
}

void Element::Init()
{
	position = Vector2(0.0, 0.0);
	type = "default";

	width = 0.0;
	height = 0.0;

	pWidth = new ValueType();
	pHeight = new ValueType();
	pMargin = new Side4();
	pPadding = new Side4();

	pDisplay = new Display(this, "inline");
}

int Element::getIndex()
{
	int index = 0;
	for each (spElement _e in DOMparent->children)
	{
		if (_e == this)
			break;

		index++;
	}

	return index;
}

Element::~Element()
{
}



