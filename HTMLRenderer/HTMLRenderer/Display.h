#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <cairo.h>
#include <string>
#include <map>

#include "Property.h"

using namespace std;

enum DisplayType
{
	INLINE,
	BLOCK,
	FLEX,
	INLINE_BLOCK,
	INLINE_FLEX,
	INLINE_TABLE,
	LIST_ITEM,
	RUN_IN,
	TABLE,
	TABLE_CAPTION,
	TABLE_COLUMN_GROUP,
	TABLE_HEADER_GROUP,
	TABLE_FOOTER_GROUP,
	TABLE_ROW_GROUP,
	TABLE_CELL,
	TABLE_COLUMN,
	TABLE_ROW,
	NONE,
	INITIAL,
	INHERIT


};

class Display : public Property
{
public:
	//Default Constructor
	Display(spElement _parent,DisplayType _type): Property("display",_parent), type(_type) {};

	//Deconstructor
	~Display() {};

	void setProperty();
	void setInline();
	void setBlock();
	bool isInline() { if (type == 0 || (type > 2 && type < 6)) return true; return false; };



private:
	DisplayType type;
};




#endif
