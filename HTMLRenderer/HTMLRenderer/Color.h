#pragma once

#ifndef COLOR_H
#define COLOR_H

#include "ColorEnum.h"

class Color
{
public:

	//static std::map<std::string, Color > colors;


	Color();
	Color(double _r, double _g, double _b, double _a) : r(_r), g(_g), b(_b), a(_a) {};
	Color(int _r, int _g, int _b, double _a) {
		r = (double)_r / 255.0;
		g = (double)_g / 255.0;
		b = (double)_b / 255.0;
		a = _a;
	};
	Color(unsigned int rgba) {

		r = rgba >> 24;
		g = (rgba >> 16) & 0xFF;
		b = (rgba >> 8) & 0xFF;
		a = rgba & 0xFF;

		/*r = _r;
		g = _b;
		b = _g;
		a = _a;*/

		r = abs((double)r / 255.0);
		g = abs((double)g / 255.0);
		b = abs((double)b / 255.0);
		a = abs((double)a / 255.0);
	}

	~Color();

	double r;
	double g;
	double b;
	double a;

}; 

//static Color::colors = std::map<std::string, Color >({ { "aliceblue", Color::AliceBlue },
//{ "antiquewhite", Color::AntiqueWhite },
//{ "aqua", Color::Aqua },
//{ "aquamarine", Color::Aquamarine },
//{ "azure", Color::Azure },
//{ "beige", Color::Beige },
//{ "bisque", Color::Bisque },
//{ "black", Color::Black },
//{ "blanchedalmond", Color::BlanchedAlmond },
//{ "blue", Color::Blue },
//{ "blueviolet", Color::BlueViolet },
//{ "brown", Color::Brown },
//{ "burlywood", Color::BurlyWood },
//{ "cadetblue", Color::CadetBlue },
//{ "chartreuse", Color::Chartreuse },
//{ "chocolate", Color::Chocolate },
//{ "coral", Color::Coral },
//{ "cornflowerblue", Color::CornflowerBlue },
//{ "cornsilk", Color::Cornsilk },
//{ "crimson", Color::Crimson },
//{ "cyan", Color::Cyan },
//{ "darkblue", Color::DarkBlue },
//{ "darkcyan", Color::DarkCyan },
//{ "darkgoldenrod", Color::DarkGoldenrod },
//{ "darkgray", Color::DarkGray },
//{ "darkgreen", Color::DarkGreen },
//{ "darkkhaki", Color::DarkKhaki },
//{ "darkmagenta", Color::DarkMagenta },
//{ "darkolivegreen", Color::DarkOliveGreen },
//{ "darkorange", Color::DarkOrange },
//{ "darkorchid", Color::DarkOrchid },
//{ "darkred", Color::DarkRed },
//{ "darksalmon", Color::DarkSalmon },
//{ "darkseagreen", Color::DarkSeaGreen },
//{ "darkslateblue", Color::DarkSlateBlue },
//{ "darkslategray", Color::DarkSlateGray },
//{ "darkturquoise", Color::DarkTurquoise },
//{ "darkviolet", Color::DarkViolet },
//{ "deeppink", Color::DeepPink },
//{ "deepskyblue", Color::DeepSkyBlue },
//{ "dimgray", Color::DimGray },
//{ "dodgerblue", Color::DodgerBlue },
//{ "firebrick", Color::Firebrick },
//{ "floralwhite", Color::FloralWhite },
//{ "forestgreen", Color::ForestGreen },
//{ "fuchsia", Color::Fuchsia },
//{ "gainsboro", Color::Gainsboro },
//{ "ghostwhite", Color::GhostWhite },
//{ "gold", Color::Gold },
//{ "goldenrod", Color::Goldenrod },
//{ "gray", Color::Gray },
//{ "green", Color::Green },
//{ "greenyellow", Color::GreenYellow },
//{ "honeydew", Color::Honeydew },
//{ "hotpink", Color::HotPink },
//{ "indianred", Color::IndianRed },
//{ "indigo", Color::Indigo },
//{ "ivory", Color::Ivory },
//{ "khaki", Color::Khaki },
//{ "lavender", Color::Lavender },
//{ "lavenderblush", Color::LavenderBlush },
//{ "lawngreen", Color::LawnGreen },
//{ "lemonchiffon", Color::LemonChiffon },
//{ "lightblue", Color::LightBlue },
//{ "lightcoral", Color::LightCoral },
//{ "lightcyan", Color::LightCyan },
//{ "lightgoldenrodyellow", Color::LightGoldenrodYellow },
//{ "lightgray", Color::LightGray },
//{ "lightgreen", Color::LightGreen },
//{ "lightpink", Color::LightPink },
//{ "lightsalmon", Color::LightSalmon },
//{ "lightseagreen", Color::LightSeaGreen },
//{ "lightskyblue", Color::LightSkyBlue },
//{ "lightslategray", Color::LightSlateGray },
//{ "lightsteelblue", Color::LightSteelBlue },
//{ "lightyellow", Color::LightYellow },
//{ "lime", Color::Lime },
//{ "limegreen", Color::LimeGreen },
//{ "linen", Color::Linen },
//{ "magenta", Color::Magenta },
//{ "maroon", Color::Maroon },
//{ "mediumaquamarine", Color::MediumAquamarine },
//{ "mediumblue", Color::MediumBlue },
//{ "mediumorchid", Color::MediumOrchid },
//{ "mediumpurple", Color::MediumPurple },
//{ "mediumseagreen", Color::MediumSeaGreen },
//{ "mediumslateblue", Color::MediumSlateBlue },
//{ "mediumspringgreen", Color::MediumSpringGreen },
//{ "mediumturquoise", Color::MediumTurquoise },
//{ "mediumvioletred", Color::MediumVioletRed },
//{ "midnightblue", Color::MidnightBlue },
//{ "mintcream", Color::MintCream },
//{ "mistyrose", Color::MistyRose },
//{ "moccasin", Color::Moccasin },
//{ "navajowhite", Color::NavajoWhite },
//{ "navy", Color::Navy },
//{ "oldlace", Color::OldLace },
//{ "olive", Color::Olive },
//{ "olivedrab", Color::OliveDrab },
//{ "orange", Color::Orange },
//{ "orangered", Color::OrangeRed },
//{ "orchid", Color::Orchid },
//{ "palegoldenrod", Color::PaleGoldenrod },
//{ "palegreen", Color::PaleGreen },
//{ "paleturquoise", Color::PaleTurquoise },
//{ "palevioletred", Color::PaleVioletRed },
//{ "papayawhip", Color::PapayaWhip },
//{ "peachpuff", Color::PeachPuff },
//{ "peru", Color::Peru },
//{ "pink", Color::Pink },
//{ "plum", Color::Plum },
//{ "powderblue", Color::PowderBlue },
//{ "purple", Color::Purple },
//{ "red", Color::Red },
//{ "rosybrown", Color::RosyBrown },
//{ "royalblue", Color::RoyalBlue },
//{ "saddlebrown", Color::SaddleBrown },
//{ "salmon", Color::Salmon },
//{ "sandybrown", Color::SandyBrown },
//{ "seagreen", Color::SeaGreen },
//{ "seashell", Color::SeaShell },
//{ "sienna", Color::Sienna },
//{ "silver", Color::Silver },
//{ "skyblue", Color::SkyBlue },
//{ "slateblue", Color::SlateBlue },
//{ "slategray", Color::SlateGray },
//{ "snow", Color::Snow },
//{ "springgreen", Color::SpringGreen },
//{ "steelblue", Color::SteelBlue },
//{ "tan", Color::Tan },
//{ "teal", Color::Teal },
//{ "thistle", Color::Thistle },
//{ "tomato", Color::Tomato },
//{ "turquoise", Color::Turquoise },
//{ "violet", Color::Violet },
//{ "wheat", Color::Wheat },
//{ "white", Color::White },
//{ "whitesmoke", Color::WhiteSmoke },
//{ "yellow", Color::Yellow },
//{ "yellowgreen", Color::YellowGreen } });

#endif
