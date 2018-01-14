#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <cairo.h>
#include <string>
#include <map>

#include "ref_counter.h"
#include "Debug.h"

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
	Display(spElement _parent, string _type): Property("display",_parent), type(_type) {};

	//Deconstructor
	~Display() {};

	void setProperty();
	void setPreInline();
	void setPostInline();
	void setPreBlock();
	void setPostBlock();
	void setText();
	void preChildRender();
	void postChildRender();
	bool isInline() {if( type.find("inline") != std::string::npos) return true; return false; };



private:
	string type;
};




#endif
