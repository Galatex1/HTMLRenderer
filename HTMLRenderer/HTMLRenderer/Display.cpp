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
	else if (type == "inline")
		setPreInline();
	else if (type == "block")
		setPreBlock();
	else if (type == "list-item")
		setPreListItem();
	else
		setPreBlock();

};
void Display::postChildRender()
{
	if (owner->type == "text")
	{
	//	setText();
	}
	else if (type == "inline")
		setPostInline();
	else if (type == "block")
		setPostBlock();
	else if (type == "list-item")
		setPostListItem();
	else
		setPostBlock();
};

void Display::setText() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];
	Vector2 previous_element = previous->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());

	Vector2 element_margin = Vector2(owner->pMargin->x(), owner->pMargin->y());

	

	if (previous != owner)
		if (previous->isInline())
		{
			owner->position = previous_element + Vector2(previous->width, 0);

			int maxWidth = owner->getAbsoluteSizedParent()->width;
			if (owner->position.x + owner->width > maxWidth)
			{
				owner->position = Vector2(parent_padding.x, 0) + element_margin + Vector2(0, previous_element.y + previous->height);				
			}
			
		}		
		else
		{
			owner->position = previous_element + Vector2(0, previous->height);
		}
	else
		owner->position = parent_padding + element_margin;

	parent->height += owner->height + parent_padding.y * 2 + element_margin.y*2;

};

void Display::setPreBlock() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	double width = parent->width;

	owner->pPadding->pLeft = owner->pPadding->pLeft->value > 1.0 ? owner->pPadding->pLeft : new ValueType(3, "px");
	owner->pPadding->pRight = owner->pPadding->pRight->value > 1.0 ? owner->pPadding->pRight : new ValueType(3, "px");
	owner->pPadding->pTop = owner->pPadding->pTop->value > 1.0 ? owner->pPadding->pTop : new ValueType(3, "px");
	owner->pPadding->pBottom = owner->pPadding->pBottom->value > 1.0 ? owner->pPadding->pBottom : new ValueType(3, "px");

	owner->position = Vector2(0.0, 0.0);

	Vector2 parent_position = parent->position;
	Vector2 position = owner->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());
	Vector2 element_margin = Vector2(owner->pMargin->x(), owner->pMargin->y());
	double padding_height = parent->pPadding->pTop->value + parent->pPadding->pBottom->value;
	double padding_width = parent->pPadding->pLeft->value + parent->pPadding->pRight->value;
	Vector2 previous_element = previous->position;

	if(previous != owner)
		owner->position = Vector2( parent_padding.x, previous_element.y + previous->height)  + element_margin;
	else
		owner->position = parent_padding + element_margin;

	owner->width = parent->width - (padding_width);

};

void Display::setPostBlock() {

	spElement parent = owner->DOMparent;
	double padding_height = parent->pPadding->pTop->value + parent->pPadding->pBottom->value;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	parent->height += owner->height + (previous == owner ? padding_height : 0) ;
}

void Display::setPreInline() {

	spElement parent = owner->DOMparent;
	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	owner->pPadding->pLeft = owner->pPadding->pLeft->value > 1.0 ? owner->pPadding->pLeft : new ValueType(3, "px");
	owner->pPadding->pRight = owner->pPadding->pRight->value > 1.0 ? owner->pPadding->pRight : new ValueType(3, "px");
	owner->pPadding->pTop = owner->pPadding->pTop->value > 1.0 ? owner->pPadding->pTop : new ValueType(3, "px");
	owner->pPadding->pBottom = owner->pPadding->pBottom->value > 1.0 ? owner->pPadding->pBottom : new ValueType(3, "px");


	Vector2 parent_position = parent->position;
	Vector2 position = owner->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());
	Vector2 element_margin = Vector2(owner->pMargin->x(), owner->pMargin->y());
	double padding_height = parent->pPadding->pTop->value + parent->pPadding->pBottom->value;
	double padding_width = parent->pPadding->pLeft->value + parent->pPadding->pRight->value;

	Vector2 previous_margin = Vector2(previous->pPadding->x(), previous->pPadding->y());
	Vector2 previous_element = previous->position;

	if (previous != owner)
		if (previous->isInline())
		{
			owner->position = Vector2(previous->width + previous_element.x + element_margin.x, previous_element.y + element_margin.y);			
		}
		else
			owner->position = parent_padding + element_margin + Vector2(0, previous->position.y+previous->height);
	else
		owner->position = parent_padding + element_margin;

};

void Display::setPostInline() {

	double height = 0.0;
	double width = 0.0;

	spElement parent = owner->DOMparent;

	double parent_padding_height = parent->pPadding->pTop->value + parent->pPadding->pBottom->value;
	double parent_padding_width = parent->pPadding->pLeft->value + parent->pPadding->pRight->value;

	double padding_height = owner->pPadding->pTop->value + owner->pPadding->pBottom->value;
	double padding_width = owner->pPadding->pLeft->value + owner->pPadding->pRight->value;


	spElement previous = parent->children[owner->getIndex() > 0 ? (owner->getIndex() - 1) : 0];

	owner->pPadding->pLeft = owner->pPadding->pLeft->value > 1.0 ? owner->pPadding->pLeft : new ValueType(3, "px");
	owner->pPadding->pRight = owner->pPadding->pRight->value > 1.0 ? owner->pPadding->pRight : new ValueType(3, "px");
	owner->pPadding->pTop = owner->pPadding->pTop->value > 1.0 ? owner->pPadding->pTop : new ValueType(3, "px");
	owner->pPadding->pBottom = owner->pPadding->pBottom->value > 1.0 ? owner->pPadding->pBottom : new ValueType(3, "px");


	Vector2 parent_position = parent->position;
	Vector2 parent_padding = Vector2(parent->pPadding->x(), parent->pPadding->y());
	Vector2 element_margin = Vector2(owner->pMargin->x(), owner->pMargin->y());

	Vector2 previous_margin = Vector2(previous->pPadding->x(), previous->pPadding->y());
	Vector2 previous_element = previous->position;


	for each (spElement child in owner->children)
	{
		//height = child->height > height ? child->height : height;
		width += child->width;
	}

	if(previous == owner)
		parent->height += owner->height + parent_padding_height + element_margin.y;

	if (!owner->hasChildren())
	{
		owner->height += padding_height;
	}

	owner->width = (width > owner->width ? width : owner->width) + padding_width;
	//owner->height = height;
	if(parent->isInline())
		parent->width += width;


	int maxWidth = owner->getAbsoluteSizedParent()->width;
	if (owner->position.x + owner->width > maxWidth)
	{
		owner->position = Vector2(parent_padding.x, 0) + element_margin + Vector2(0, previous_element.y + previous->height);
		parent->height += owner->height + element_margin.y;
	}
	else if (previous->height < owner->height)
		parent->height += owner->height - previous->height;

	//parent->width += width;
	//parent->height += owner->height;
}

void Display::setPreListItem() {
	owner->pMargin->pLeft = new ValueType(10, "px");
	setPreBlock();
}

void Display::setPostListItem() {
	setPostBlock();
}


