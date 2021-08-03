/************************************************//**
 * \file    MainGameView.cpp
 * \brief   Here are defined all methods from MainGameView class
***************************************************/

/**************************************************/
// Libraries

#include <SFML/Graphics.hpp>

#include "RoundedRectangle.h"

#include "Button.h"
#include "MainGameView.h"
#include "Settings.h"
#include "SlideableMenu.h"
#include "StorageController.h"
#include "UIElement.h"

/**************************************************/
// Dev libraries
#ifdef _DEBUG
#include "Console.h"
#endif

/**************************************************/
// Namespaces

using namespace sf;

/**************************************************/
// Public

/*****************************/
// Constructor

MainGameView::MainGameView(RenderWindow* parent, int x, int y, int height, int width) : UIElement(parent, x, y, height, width)
{
	options["Modo de juego"] = StorageController::findGameModes();
	this->logo = new Texture();
	this->bg = new Texture();

	this->initDrawables();
};

/*****************************/
// Getters and setters methods

/*****************************/
// Medoths

void MainGameView::initDrawables()
{
	Sprite
		* bgSprite = new Sprite(),
		* logoSprite = new Sprite();
	Vector2f logoScale;

	if (!logo->loadFromFile("resources\\images\\logo.png") || !bg->loadFromFile("resources\\images\\bg.png"))
	{
#ifdef _DEBUG
		Console().debug("Error loading image", "There was an error loading logo.png or bg.png", __LINE__, __FILE__, Console::Message_Type::ERR);
#endif
	}

	logoScale = Vector2f((float)(logo->getSize().x * 0.7) / this->width, (float)(logo->getSize().x * 0.7) / this->width);

	// Convert bg.png (from image -> texture -> sprite) to draw on canvas
	bg->setSmooth(true);
	bgSprite->setTexture(*bg);
	bgSprite->setScale((float)this->width / bg->getSize().x, (float)this->height / bg->getSize().y);

	this->drawables["bg"] = bgSprite;

	// Convert logo.png (from image -> texture -> sprite) to draw on canvas
	logo->setSmooth(true);
	logoSprite->setScale(logoScale);
	logoSprite->setTexture(*logo);
	logoSprite->setPosition((float)(this->width / 2) - (logo->getSize().x * (logoScale.x / 2.f)), (float)this->height / 15);

	this->drawables["logoImage"] = logoSprite;

	this->drawables["mainMenu"] = new SlideableMenu(this->parent, (int)(this->width / 2) - (400 / 2), (int)(this->height * (1 + 0.1)) / 2, 40, 400, this->options);
};
