#pragma once
#pragma once

#ifndef VISIBILITY_H
#define VISIBILITY_H

#include <cairo.h>
#include <string>
#include <map>

#include "Property.h"

using namespace std;


class Visibility : public Property
{
public:
	//Default Constructor
	Visibility(spElement _parent, string _type) : Property("display", _parent), type(_type) {};

	//Deconstructor
	~Visibility() {};

	void setProperty() {};



private:
	string type;
};




#endif