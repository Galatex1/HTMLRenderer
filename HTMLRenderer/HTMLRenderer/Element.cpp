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

	pBorderSize = new Side4();

	pDisplay = new Display(this, "inline");
}

void Element::allProperties() {
	for each (spProperty prop in props)
	{
		prop->setProperty();
	}
}

void Element::allPostChildRender() {
	for each (spProperty prop in props)
	{
		prop->postChildRender();
	}
}

void Element::allPreChildRender() {
	for each (spProperty prop in props)
	{
		prop->preChildRender();
	}
}

spElement Element::getAbsoluteSizedParent() {

	spElement ASParent = DOMparent;

	while (ASParent && ASParent->isInline())
	{
		ASParent = ASParent->DOMparent;
	}

	return ASParent ? ASParent : this;
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

Vector2 Element::getPos() {
	if (DOMparent)
		return position + DOMparent->getPos();
	else
		return position;
}

Element::~Element()
{
}



