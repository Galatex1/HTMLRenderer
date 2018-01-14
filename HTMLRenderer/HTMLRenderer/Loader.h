#pragma once
#include <pugixml.hpp>
#include <string>
#include "Element.h"
#include "stdafx.h"

using namespace std;

class Loader
{
public:
	Loader(string _path, double width, double height);
	~Loader();

	void Loader::createElement(pugi::xml_node element, spElement parent);
	void applyAttrStyles(pugi::xml_node element);

	spElement document;
};

