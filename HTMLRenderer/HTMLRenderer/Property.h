#pragma once

#ifndef PROPERTY_H
#define PROPERTY_H


#include <cairo.h>
#include <string>
#include <map>
#include <memory>
#include "SmartPointers.h"



using namespace std;

class Property : public ref_counter
{
public:
	//Default Constructor
	Property(string _name, spElement _parent);

	//Deconstructor
	~Property() {};

	virtual void setProperty() = 0;
	virtual void preChildRender() {};
	virtual void postChildRender() {};

protected:
	string name;
	spElement owner;
};

#endif
