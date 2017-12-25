#include "Element.h"
#include "Display.h"

Element::Element()
{
	DOMparent = NULL;

	position = Vector2(0.0, 0.0);
	type = Html::ROW;

	width = 0.0;
	height = 0.0;

	pWidth = new ValueType();
	pHeight = new ValueType();
	pMargin = new Side4();
	pPadding = new Side4();

	pDisplay = new Display(DOMparent,DisplayType::INLINE);
	//pDisplay->setProperty();
}


Element::Element(spElement _parent) : DOMparent(_parent)
{
	position = Vector2(0.0, 0.0);
	type = Html::ROW;

	width = 0.0;
	height = 0.0;

	pWidth = new ValueType();
	pHeight = new ValueType();
	pMargin = new Side4();
	pPadding = new Side4();

	pDisplay = new Display(DOMparent, DisplayType::INLINE);
	pDisplay->setProperty();
}

Element::~Element()
{
}



