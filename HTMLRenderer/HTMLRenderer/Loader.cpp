#include "Loader.h"
#include "Color.h"
#include <algorithm>


Loader::Loader(string _path, double width, double height)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(((_path).c_str()), 116U | pugi::parse_trim_pcdata);

	document =  new Element();
	document->position = Vector2((double)GetSystemMetrics(SM_CXSIZEFRAME), (double)GetSystemMetrics(SM_CYCAPTION));

	doc.append_child("document");
	doc.child("document").append_move(doc.child("body"));

	document->width = width;
	document->height = height;
	document->type = "document";
	document->pDisplay->setType("block");
	document->pPadding->twoVals(10, 50);
	document->pColor = Color(0.0, 0.0, 0.0, 1.0);
	document->pBackgroundColor = Color(1.0, 1.0, 1.0, 1.0);

	//doc.save_file("indexGenerated.xml");
	
	createElement(doc.child("document")/*doc.child("body")*/, document);

	double size = 0;

	//body->render();

}


void Loader::createElement(pugi::xml_node element, spElement parent)
{
	//Debug::console << element.name() << " ";
	for (pugi::xml_node child : element.children())
	{

		if (child.name() != "" || (child.type() == pugi::node_pcdata && child.text().as_string() != ""))
		{
			std::string name = child.name();
			
			spElement el = new Element(parent /*, types[child.name()], child.text().as_string(), child.attribute("id").as_string(), child.attribute("class").as_string()*/);

			el->type = name;
			el->pColor = parent->pColor;
			

			if (child.type() == pugi::node_pcdata)
			{
				el->type = "text";
				//Debug::console << "This is" << el->type << "node : " << child.text().as_string() << endl;
				el->text = child.text().as_string();
				replaceAll(el->text, "\n", "");
			}
			else
			{
				el->pDisplay->setType("block");

				applyAttrStyles(child, el);

				/*el->pPadding->pLeft = new ValueType(20, "px");
				el->pPadding->pTop = new ValueType(7, "px");
				el->pPadding->x = 20;*/
				//el->pPadding->twoVals(10, 10);
			}

			//Debug::console << "This is " << el->type << " node : " << el->text << " Parent: " << parent->type << endl;


			Vector2 position = Vector2(0, 0);

			el->position = Vector2(0, 0);
			


			if (parent != NULL)
			{
					parent->addChild(el);
			}

			if (size_t n = std::distance(child.children().begin(), child.children().end()) > 0)
				createElement(child, el);

		}
	}
}

void Loader::applyAttrStyles(pugi::xml_node element, spElement DOMelement)
{

	for (pugi::xml_attribute attr : element.attributes())
	{
		std::string name = attr.name();
		if (name == "color")
		{
			string clrs = attr.as_string();
			std::transform(clrs.begin(), clrs.end(), clrs.begin(), ::toupper);
			int colr = GetColorsValue(clrs.c_str());
			Color clr = Color(colr);
			DOMelement->pColor = clr;
		}	
		else if (name == "background")
		{
			string clrs = attr.as_string();
			std::transform(clrs.begin(), clrs.end(), clrs.begin(), ::toupper);
			int colr = GetColorsValue(clrs.c_str());
			Color clr = Color(colr);
			DOMelement->pBackgroundColor = clr;
		}	
		else if (name == "margin")
		{	
			DOMelement->pMargin = new Side4(new ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"));
		}
		else if (name == "padding")
		{	
			DOMelement->pPadding = new Side4(new ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"), new  ValueType(attr.as_int(), "px"));
		}
		else if (name == "style")
		{

		}
		else if (name == "top")
		{
			//Background->setPosition(0, attr.as_int());
			//Margin.y = attr.as_int();
		}
		else if (name == "left")
		{
			//Background->setPosition(attr.as_int(), 0);
			//Margin.x = attr.as_int();
		}
		else if (name == "border")
		{
			//Margin.x += attr.as_int();
			//Margin.y += attr.as_int();
			//Background->createBorder(attr.as_int(), Color::Black, 0);
			DOMelement->pBorderSize = new Side4(attr.as_int(), "px");
			DOMelement->pBorderColor = Colors::BLACK;
		}
	}
}


Loader::~Loader()
{
}
