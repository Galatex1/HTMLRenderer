#pragma once

#ifndef ELEMENT_H
#define ELEMENT_H

#include <cairo.h>
#include <string>
#include <vector>
#include <memory>  

#include "Color.h"
#include "Display.h"
#include "vector2.h"
#include "ref_counter.h"
#include "SmartPointers.h"

using namespace std;
using namespace HTMLParser;

#define M_PI 3.14

enum class  Html {
	ROW,
	B,
	BODY,
	BR,
	BUTTON,
	CENTER,
	DIV,
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
	HR,
	I,
	IMG,
	RADIO,
	CHECKBOX,
	LI,
	OL,
	OPTION,
	P,
	S,
	SELECT,
	SPAN,
	SUB,
	SUP,
	TABLE,
	TD,
	TH,
	TR,
	U,
	UL,
	RADIOS,
	CHECKBOXES,
	INPUT,
	TEXT 
};


class ValueType : public ref_counter
{
public:
	ValueType() : value(0.0), type("px") {};
	ValueType(double _value, string _type) : value(_value), type(_type) {};
	~ValueType() {};
	
	double value;
	string type;

};



class Side4 : public ref_counter
{

public:
	Side4() { 
		pTop = new ValueType();
		pLeft = new ValueType();
		pRight = new ValueType();
		pBottom = new ValueType();
	};
	Side4(spValueType _top, spValueType _left, spValueType _right, spValueType _bottom ) : pTop(_top), pLeft(_left), pRight(_right), pBottom(_bottom) {};

	~Side4(){};

	double x() { return pLeft->value - pRight->value; };
	double y() { return pTop->value - pBottom->value; };

	spValueType pTop;
	spValueType pLeft;
	spValueType pRight;
	spValueType pBottom;
};



class Element : public ref_counter
{
public:
	//Default Constructor
	Element();
	Element(spElement _parent);
	void Init();

	bool isInline() { return pDisplay->isInline(); };
	void addChild(spElement e) { children.push_back(e); e->DOMparent = this;};
	spElement getLastChild() { return children.back(); };
	void allProperties() {
		for each (spProperty prop in props)
		{
			prop->setProperty();
		}
	};
	void allPostChildRender() {
		for each (spProperty prop in props)
		{
			prop->postChildRender();
		}
	};
	void allPreChildRender() {
		for each (spProperty prop in props)
		{
			prop->preChildRender();
		}
	};


	int getIndex();



	//Deconstructor
	~Element();
	
	string type;
	spElement DOMparent;
	vector<spElement> children;

	Vector2 position;

	double width;
	double height;

	spValueType pWidth;
	spValueType pHeight;
	spSide4 pMargin;
	spSide4 pPadding;

	string text;

	vector<spProperty> props;
	spDisplay pDisplay;
};
#endif
