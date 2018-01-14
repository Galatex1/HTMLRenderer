#include "Property.h"
#include "Element.h"

Property::Property(string _name, spElement _parent) : name(_name), owner(_parent) {
	owner->props.push_back(this);
}