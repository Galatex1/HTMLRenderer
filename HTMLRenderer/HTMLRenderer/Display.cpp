#include "Display.h"
#include "Property.h"
#include "Element.h"


void Display::setProperty() {


	/*Debug::console << "elem type: " << owner->type << endl;*/
	if (owner->type == "text")
		setText();
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

};

void Display::setPreInline() {

	double height = 20.0;
	double width = 0.0;

	for each (spElement child in owner->children)
	{
		height = child->height > height ? child->height : height;
		width += child->width;
	}

	owner->width = width;
	owner->height = height;
	
};

void Display::setText() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];
	Vector2 previous_element = previous->position;

	if (previous != owner)
		owner->position = previous_element + Vector2(0, previous->height);
	else
		owner->position = parent->position;

	parent->height += owner->height;

	Debug::console << "text parent height: " << parent->height << endl;

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

	parent->height += owner->height;
	owner->width = parent->width;
	//parent->height = 30;
	//Debug::console << parent->type <<" width: " << parent->width << ",          " << owner->type << " position: " << owner->position.x << ", " << owner->position.y<< endl;

};


