/************************************************//**
 * \file    Settings.h
 * \brief	This file contains the data about the app
***************************************************/

#pragma once

/**************************************************/
// Libraries
#include <iostream>
#include <SFML/Graphics.hpp>

/**************************************************/
// Namespaces
using namespace std;
using namespace sf;

/**************************************************/
// Constants

const string APP_TITLE = "100 Mexicanos dijeron";
const float PADDING = 10;
const float BORDER_RADIUS = 12;

/**************************************************/
// Classes

class APP_COLORS {
	public:
		const Color
			PRIMARY = Color(67, 97, 238),
			SECONDARY = Color(76, 201, 240),
			SECONDARY_DARK = Color(72, 149, 239),
			ACCENT = Color(247, 37, 133),
			GRAY = Color(229, 229, 229),
			GRAY_LIGHT = Color(242, 242, 242),
			BLACK = Color(25, 25, 25);
};
