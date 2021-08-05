/************************************************//**
 * \file    SlideableMenu.cpp
 * \brief   Here are defined all methods from SlideableMenu class
***************************************************/

/**************************************************/
// Libraries

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Button.h"
#include "SlideableMenu.h"
#include "Settings.h"
#include "WrappableText.h"

/**************************************************/
// Dev libraries
#ifdef _DEBUG
	#include "Console.h"
#endif

/**************************************************/
// Namespaces

using namespace std;
using namespace sf;

/**************************************************/
// Private

/*****************************/
// Medoths

void SlideableMenu::loop()
{
	if (static_cast<Button*>(this->drawables["backButton"])->isClicked())
	{
		this->animation.isChangingOption = true;
		this->animation.direction = AnimationData::Direction::LEFT;

		if (--(this->actualOption) < 0)
		{
			if ((this->actualSection)-- == this->options.begin())
			{
				this->actualSection = --(this->options.end());
			}

			this->actualOption = this->actualSection->second.size() - 1;
		}

		this->drawables["prevOptionButton"] = this->drawables["optionButton"];
		this->loadOption();
	}
	else if (static_cast<Button*>(this->drawables["nextButton"])->isClicked())
	{
		this->animation.isChangingOption = true;
		this->animation.direction = AnimationData::Direction::RIGHT;

		if (++(this->actualOption) >= this->actualSection->second.size())
		{
			if (++(this->actualSection) == this->options.end())
			{
				this->actualSection = this->options.begin();
			}

			this->actualOption = 0;
		}

		this->drawables["prevOptionButton"] = this->drawables["optionButton"];
		this->loadOption();
	}
	else if (static_cast<Button*>(this->drawables["nextButton"])->isClicked())
	{

	}

	if (this->animation.isChangingOption)
	{
		changeOption();
	}
};

/**************************************************/
// Public

/**************************************************/
// Constructor

SlideableMenu::SlideableMenu(RenderWindow* parent, int x, int y, int height, int width, map<string, vector<string>> options) : UIElement(parent, x, y, height, width)
{
	vector<Image> tempImages = {
		Image(),
		Image(),
		Image(),
		Image()
	};

	this->options = options;
	this->actualSection = this->options.begin();
	this->actualOption = 0;
	this->icon = new Texture();

	if (!tempImages[0].loadFromFile("resources\\images\\buttons\\arrow.png") || !tempImages[1].loadFromFile("resources\\images\\buttons\\arrow-hover.png"))
	{
		#ifdef _DEBUG
				Console().debug("Error loading image", "There was an error loading arrow.png or arrow-hover.png", __LINE__, __FILE__, Console::Message_Type::ERR);
		#endif
	}
	else
	{
		tempImages[2] = tempImages[0];
		tempImages[3] = tempImages[1];
		tempImages[2].flipHorizontally();
		tempImages[3].flipHorizontally();
	}

	this->arrowImages = tempImages;

	this->initDrawables();
};

/*****************************/
// Getters and setters methods

/*****************************/
// Medoths

void SlideableMenu::changeOption()
{
	if (this->animation.gap < MAX_GAP )
	{
		int 
			prevX,
			prevOpacity,
			newX,
			newOpacity;
		this->animation.gap++;

		newX = static_cast<Button*>(this->drawables["optionButton"])->getX();
		newOpacity = this->animation.gap * (255 / MAX_GAP);
		prevX = static_cast<Button*>(this->drawables["prevOptionButton"])->getX();
		prevOpacity = 255 - this->animation.gap * (255 / MAX_GAP);

		if (this->animation.direction == AnimationData::Direction::LEFT)
		{
			// Move the new option from right to center
			newX--;

			if (this->animation.gap == 1) {
				newX += MAX_GAP;
			}

			// Move the previous option from center to left
			prevX--;
		}
		else
		{
			// Move the new option from left to center
			newX++;

			if (this->animation.gap == 1) {
				newX -= MAX_GAP;
			}

			// Move the previous option from center to right
			prevX++;
		}

		static_cast<Button*>(this->drawables["optionButton"])->setX(newX);
		static_cast<Button*>(this->drawables["optionButton"])->setOpacity(newOpacity);
		static_cast<Button*>(this->drawables["prevOptionButton"])->setX(prevX);
		static_cast<Button*>(this->drawables["prevOptionButton"])->setOpacity(prevOpacity);
	}
	else
	{
		this->animation.isChangingOption = false;
		this->animation.gap = 0;
	}
};

void SlideableMenu::initDrawables()
{
	const Vector2f CENTER = Vector2f((float)(this->x + (this->width / 2)), (float)(this->y + (this->height / 2)));
	CircleShape* circle = new CircleShape();

	this->loadOption();

	circle->setRadius(50);
	circle->setFillColor(APP_COLORS().GRAY);
	circle->setPosition((float) (CENTER.x - 50), (float) (this->y + 55 + 37.5));

	this->drawables["backButton"] = new Button(this->parent, (int)this->x, (int)this->y + 55 + 50, 75, 26, arrowImages[0], arrowImages[1]);
	this->drawables["bg"] = circle;
	this->drawables["nextButton"] = new Button(this->parent, (int)(this->x + this->width - 26), (int)this->y + 55 + 50, 75, 26, arrowImages[2], arrowImages[3]);
};

void SlideableMenu::loadOption()
{
	Image image;
	Sprite* sprite;
	const Vector2f CENTER = Vector2f((float)(this->x + (this->width / 2)), (float)(this->y + (this->height / 2)));
	float rescaleFactor;
	string realText = this->actualSection->second[this->actualOption];
	realText[0] = toupper(realText[0]);

	if (!image.loadFromFile("resources\\images\\" + this->actualSection->second[this->actualOption] + ".png"))
	{
		#ifdef _DEBUG
				Console().debug("Error loading image", "There was an error loading menu image", __LINE__, __FILE__, Console::Message_Type::ERR);
		#endif

	}
	rescaleFactor = 120 / (float)image.getSize().y;

	// Convert from image -> texture
	this->icon->loadFromImage(image);
	this->icon->setSmooth(true);

	this->drawables["sectionText"] = new WrappableText(this->parent, (int)this->x + (this->width / 5), this->y, 50, (int)(this->width * 3) / 5, this->actualSection->first, PADDING, WrappableText::Style::SUBTITLE, WrappableText::TextAlign::CENTER, APP_COLORS().GRAY_LIGHT, APP_COLORS().PRIMARY);
	this->drawables["optionButton"] = new Button(this->parent, (int)(CENTER.x - (this->icon->getSize().x * rescaleFactor / 2)), (int)(this->y + 82.5), 120, this->icon->getSize().x * rescaleFactor, image, image);
	this->drawables["optionText"] = new WrappableText(this->parent, (int)this->x + (this->width / 5), this->y + 55 + 75 + +55 + 25, 50, (int)(this->width * 3) / 5, realText, PADDING, WrappableText::Style::BODY, WrappableText::TextAlign::CENTER, APP_COLORS().SECONDARY_DARK);
};
