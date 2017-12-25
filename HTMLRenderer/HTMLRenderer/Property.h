#pragma once

#ifndef PROPERTY_H
#define PROPERTY_H


#include <cairo.h>
#include <string>
#include <map>
#include <memory>
#include "ref_counter.h"


using namespace std;

class Element;
typedef intrusive_ptr<Element> spElement;

class Property
{
public:
	//Default Constructor
	Property() {};
	Property(string _name, spElement _parent) : name(_name), parent(_parent) {};

	//Deconstructor
	~Property() {};

	virtual void setProperty(){};
	virtual bool isInline() { return false; };


protected:
	string name;
	spElement parent;
};




#endif
