#include "Display.h"
#include "Property.h"
#include "Element.h"


void Display::setProperty() {

	if (owner->type == "text")
	{
		//setText();
	}
	else
		if (isInline())
		{

			//setInline();
		}
		else
		{
			//setBlock();
		}

};

void Display::preChildRender()
{
	if (owner->type == "text")
		setText();
	else
		if (isInline())
		{

			setPreInline();
		}
		else
		{
			setPreBlock();
		}

};
void Display::postChildRender()
{
	if(owner->type != "text")
		if (isInline())
		{
			setPostInline();
		}
		else
		{
			setPostBlock();
		}
};

void Display::setText() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];
	Vector2 previous_element = previous->position;

	

	if (previous != owner)
		if(previous->isInline())
			owner->position = previous_element + Vector2(previous->width,0);
		else
			owner->position = previous_element + Vector2(0, previous->height);
	else
		owner->position = parent->position;

	parent->height += owner->height;

};

void Display::setPreBlock() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	double width = parent->width;

	owner->position = Vector2(0.0, 0.0);

	Vector2 parent_position = parent->position;
	Vector2 position = owner->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());
	Vector2 previous_element = previous->position;

	if(previous != owner)
		owner->position = Vector2(parent->position.x , previous_element.y + previous->height);
	else
		owner->position = parent->position;

	owner->width = parent->width;

};

void Display::setPostBlock() {

	spElement parent = owner->DOMparent;
	parent->height += owner->height;
}

void Display::setPreInline() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	owner->position = Vector2(0.0, 0.0);

	Vector2 parent_position = parent->position;
	Vector2 position = owner->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());
	Vector2 previous_element = previous->position;

	if (previous != owner)
			owner->position = Vector2(previous->width + previous_element.x, previous_element.y);
	else
		owner->position = parent->position;

};

void Display::setPostInline() {

	double height = 0.0;
	double width = 0.0;

	spElement parent = owner->DOMparent;


	for each (spElement child in owner->children)
	{
		height = child->height > height ? child->height : height;
		width += child->width;
	}

	owner->width = width;
	owner->height = height;
	parent->width = width;
	//parent->width += width;
	//parent->height += owner->height;
}


