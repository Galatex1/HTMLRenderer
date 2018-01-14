#include "Loader.h"


Loader::Loader(string _path, double width, double height)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(((_path).c_str()));

	document =  new Element();
	document->position = Vector2((double)GetSystemMetrics(SM_CXSIZEFRAME), (double)GetSystemMetrics(SM_CYCAPTION));

	doc.append_child("document");
	doc.child("document").append_move(doc.child("body"));

	document->width = width;
	document->height = height;
	document->type = "document";

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
			//Debug::console << child.name() << "   ";

		if (child.name() != "" || (child.type() == pugi::node_pcdata && child.text().as_string() != ""))
		{
			std::string name = child.name();
			
			spElement el = new Element(parent /*, types[child.name()], child.text().as_string(), child.attribute("id").as_string(), child.attribute("class").as_string()*/);

			el->type = name;

			if (child.type() == pugi::node_pcdata)
			{
				el->type = "text";
				//Debug::console << "This is" << el->type << "node : " << child.text().as_string() << endl;
				el->text = child.text().as_string();
			}


			Vector2 position = Vector2(0, 0);

			el->position = Vector2(0, 0);
			


			if (parent != NULL)
			{
					parent->addChild(el);
			}

			if (size_t n = std::distance(child.children().begin(), child.children().end()) > 0)
				createElement(child, el);

			

			pugi::xml_attribute attr = child.attribute("border");
			if (attr)
			{

			}
		}
	}
}

void Loader::applyAttrStyles(pugi::xml_node element)
{

	/*for (pugi::xml_attribute attr : element.attributes())
	{
		std::string name = attr.name();
		if (name == "color")
			Text->setColor(Html::colors[attr.as_string()]);
		else if (name == "background")
			Background->setColor(Html::colors[attr.as_string()]);
		else if (name == "margin")
			Margin = attr.as_int();
		else if (name == "padding")
			Padding = attr.as_int();
		else if (name == "style")
		{

		}
		else if (name == "top")
		{
			//Background->setPosition(0, attr.as_int());
			Margin.y = attr.as_int();
		}
		else if (name == "left")
		{
			//Background->setPosition(attr.as_int(), 0);
			Margin.x = attr.as_int();
		}
		else if (name == "border")
		{
			//Margin.x += attr.as_int();
			//Margin.y += attr.as_int();
			//Background->createBorder(attr.as_int(), Color::Black, 0);
		}
	}*/
}


Loader::~Loader()
{
}
