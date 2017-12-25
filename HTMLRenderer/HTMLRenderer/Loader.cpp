#include "Loader.h"


Loader::Loader(string _path, double width, double height)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(((_path).c_str()));

	body =  new Element();
	body->position = Vector2((double)GetSystemMetrics(SM_CXSIZEFRAME), (double)GetSystemMetrics(SM_CYCAPTION));


	createElement(doc.child("body"), body);

	double size = 0;


	for (spElement el : body->children)
	{
		size += el->height;
		if (el->width > width)
			body->width = el->width;
	}

	if (size > height)
		body->height = size;

	//body->render();

}


void Loader::createElement(pugi::xml_node element, spElement parent)
{
	for (pugi::xml_node child : element.children())
	{
		if (child.name() != "" || (child.type() == pugi::node_pcdata && child.text().as_string() != ""))
		{
			std::string name = child.name();
			spElement el;
			if (name == "img")
				el = new Element(parent /*, types[child.name()], child.attribute("src").as_string(), child.attribute("id").as_string(), child.attribute("class").as_string()*/);
			else
				el = new Element(parent /*, types[child.name()], child.text().as_string(), child.attribute("id").as_string(), child.attribute("class").as_string()*/);

			if (child.type() == pugi::node_pcdata)
				el->type = Html::TEXT;

			Vector2 position = Vector2(0, 0);

			el->position = position;
			el->text = child.text().as_string();


			if (parent != NULL)
			{
				if (el->isInline() && !parent->isInline() /*&& parent->Type != TR && parent->Type != LI*/)
				{
					if (parent->children.size()>0 /*&& parent->getLastChild()->Type == 0*/)
					{
						parent->getLastChild()->addChild(el);

					}
					else
					{
						spElement row = new Element(parent/*, 0*/);

						parent->addChild(row);

						row->addChild(el);

					}

				}
				else
				{
					parent->addChild(el);
				}

				if (child.text().as_string() != "")
				{

				}
			}

			//el->applyAttrStyles(child);

			if (size_t n = std::distance(child.children().begin(), child.children().end()) > 0)
				createElement(child, el);

			
			/*Vector2 size = el->calculateSize();
			el->height(size.y);
			el->width(size.x);
			if (el->Parent->Type == ROW)
			{
				size = el->Parent->calculateSize();
				el->Parent->height(size.y);
				el->Parent->width(size.x);
			}*/


			pugi::xml_attribute attr = child.attribute("border");
			if (attr)
			{
				/*el->Margin.x += attr.as_int();
				el->Margin.y += attr.as_int();*/
				//el->Background->createBorder(attr.as_int(), Color::Black, 0);
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
