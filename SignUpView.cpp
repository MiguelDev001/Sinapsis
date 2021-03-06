/************************************************//**
 * \file    SignUpView.cpp
 * \brief   Here are defined all methods from SignUpView class
***************************************************/

/**************************************************/
// Libraries

#include <SFML/Graphics.hpp>

#include "RoundedRectangle.h"

#include "Button.h"
#include "MainView.h"
#include "Settings.h"
#include "SlideableMenu.h"
#include "StorageController.h"
#include "SignUpView.h"
#include "TextField.h"
#include "WrappableText.h"

/**************************************************/
// Dev libraries
#ifdef _DEBUG
	#include "Console.h"
#endif

/**************************************************/
// Namespaces

using namespace sf;

/**************************************************/
// Private

/*****************************/
// Medoths

void SignUpView::loop()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		this->selectedTextField = NULL;
	}
	
	for (TextField* field : this->textFields)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && field->isMouseOver())
			this->selectedTextField = field;
	}

	for (SlideableMenu* avatar : this->t1Avatars)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && avatar->isMouseOver())
			this->selectedTextField = avatar->getTextFieldPtr();
	}

	for (SlideableMenu* avatar : this->t2Avatars)
	{
		if (Mouse::isButtonPressed(Mouse::Left) && avatar->isMouseOver())
			this->selectedTextField = avatar->getTextFieldPtr();
	}

	if (this->drawables.find("zaddPlayer") != this->drawables.end() && static_cast<Button*>(this->drawables["zaddPlayer"])->isClicked())
	{
		int
			x = (this->t1Avatars.size() % 2 == 0) ? (int)this->x + (this->width * 1 / 20) : (int)this->x + (this->width / 5) + 60,
			y = ((this->t1Avatars.size() / 2) * 170) + 130,
			bX = (this->t1Avatars.size() % 2 == 0) ? (int)this->x + (this->width / 5) + 60 : (int)this->x + (this->width * 1 / 20);

		if (this->t1Avatars.size() + 1 < 6)
		{
			static_cast<Button*>(this->drawables["zaddPlayer"])->setX(bX + 40);
			if (this->t1Avatars.size() % 2 != 0)
				static_cast<Button*>(this->drawables["zaddPlayer"])->setY(y + 250);
		}
		else
		{
			this->drawables.erase("zaddPlayer");
		}

		this->drawables["smT1" + to_string(this->t1Avatars.size() + 1)] = new SlideableMenu(this->parent, x, y, 320, 200, this->avatarsFilesNames, "resources\\images\\avatars\\", true);
		this->t1Avatars.push_back(static_cast<SlideableMenu*>(this->drawables["smT1" + to_string(this->t1Avatars.size() + 1)]));
	}

	if (this->drawables.find("zaddPlayer2") != this->drawables.end() && static_cast<Button*>(this->drawables["zaddPlayer2"])->isClicked())
	{
		int
			x = (this->t2Avatars.size() % 2 == 0) ? (int)this->x + (this->width * 11 / 20) + 40 : (int)this->x + (this->width * 4 / 5) - 20,
			y = ((this->t2Avatars.size() / 2) * 170) + 130,
			bX = (this->t2Avatars.size() % 2 == 0) ? (int)this->x + (this->width * 4 / 5) - 50 : (int)this->x + (this->width * 11 / 20);

		if (this->t2Avatars.size() + 7 < 12)
		{
			static_cast<Button*>(this->drawables["zaddPlayer2"])->setX(bX + 80);
			if (this->t2Avatars.size() % 2 != 0)
				static_cast<Button*>(this->drawables["zaddPlayer2"])->setY(y + 250);
		}
		else
		{
			this->drawables.erase("zaddPlayer2");
		}

		this->drawables["smT2" + to_string(this->t2Avatars.size() + 1)] = new SlideableMenu(this->parent, x, y, 320, 200, this->avatarsFilesNames, "resources\\images\\avatars\\", true);
		this->t2Avatars.push_back(static_cast<SlideableMenu*>(this->drawables["smT2" + to_string(this->t2Avatars.size() + 1)]));
	}

	if (static_cast <Button*> (this->drawables["playButton"])->isClicked())
	{
		this->isDone = true;
	}
};

/**************************************************/
// Public

/*****************************/
// Constructor

SignUpView::SignUpView(RenderWindow* parent, int x, int y, int height, int width) : MainView(parent, x, y, height, width)
{
	this->isDone = false;
	this->initDrawables();
};

/*****************************/
// Getters and setters methods

bool SignUpView::getIsDone() { return this->isDone; };
void SignUpView::setIsDone(bool isDone) { this->isDone = isDone; };

map<string, vector<map<string, string>>> SignUpView::getData()
{
	map<string, vector<map<string, string>>> res = map<string, vector<map<string, string>>>();
	vector<map<string, string>> players = vector<map<string, string>>();

	res["names"] = { {{ "team1", this->textFields[0]->getText() }, { "team2", this->textFields[1]->getText() }} };

	for (SlideableMenu* avatar : this->t1Avatars)
	{
		players.push_back(avatar->getData());
	}
	res["team1Players"] = players;
	players.clear();

	for (SlideableMenu* avatar : this->t2Avatars)
	{
		players.push_back(avatar->getData());
	}
	res["team2Players"] = players;

	return res;
};

/*****************************/
// Medoths

void SignUpView::changeSelectedTextField(String input)
{
	if (this->selectedTextField != NULL)
	{
		if (input == '\b')
			this->selectedTextField->setText(this->selectedTextField->getText().substr(0, this->selectedTextField->getText().size() - 1));
		else
			this->selectedTextField->setText(this->selectedTextField->getText() + input);
	}
};


void SignUpView::initDrawables()
{
	Sprite
		* bgSprite = new Sprite(),
		* addPlayerSprite = new Sprite(),
		* addPlayerSprite2 = new Sprite(),
		* vsSprite = new Sprite();
	
	Vector2f
		logoScale;

	this->bg = new Texture();
	this->addPlayer = new Texture();
	this->vs = new Texture();

	if (!this->bg->loadFromFile("resources\\images\\bg.png") || !this->addPlayer->loadFromFile("resources\\images\\add.png") || !this->vs->loadFromFile("resources\\images\\vs.png"))
	{
		#ifdef _DEBUG
				Console().debug("Error loading image", "There was an error loading logo.png or bg.png", __LINE__, __FILE__, Console::Message_Type::ERR);
		#endif
	}

	logoScale = Vector2f((float)(this->addPlayer->getSize().x * 0.45) / this->width, (float)(this->addPlayer->getSize().x * 0.45) / this->width);

	this->avatarsFilesNames["avatars"] = StorageController::getFilesNames(AVATARS_PATH);

	// Convert bg.png (from image -> texture -> sprite) to draw on canvas
	this->bg->setSmooth(true);
	bgSprite->setTexture(*(this->bg));
	bgSprite->setScale((float)this->width / this->bg->getSize().x, (float)this->height / this->bg->getSize().y);

	// Convert vs.png (from image -> texture -> sprite) to draw on canvas
	this->vs->setSmooth(true);
	vsSprite->setScale(logoScale);
	vsSprite->setTexture(*(this->vs));
	vsSprite->setPosition((float)(this->width / 2) - (this->vs->getSize().x * (logoScale.x / 2.f)), (float)(this->height / 2) - (this->vs->getSize().x * (logoScale.x / 2.f)));

	// Convert add.png (from image -> texture -> sprite) to draw on canvas
	this->addPlayer->setSmooth(true);
	addPlayerSprite->setScale(logoScale);
	addPlayerSprite->setTexture(*(this->addPlayer));
	addPlayerSprite->setPosition((float)this->x + (this->width / 5) + 100, (float)this->y + 108);

	addPlayerSprite2->setScale(logoScale);
	addPlayerSprite2->setTexture(*(this->addPlayer));
	addPlayerSprite2->setPosition((float)this->x + (this->width * 4 / 5) + 20, (float)this->y + 108);

	this->drawables["title"] = new WrappableText(this->parent, (int)this->x + (this->width / 2) - (int)(this->width * 2) / 10, 15, 55, (int)(this->width * 2) / 5, "Registro de Jugadores", PADDING, WrappableText::Style::TITLE, WrappableText::TextAlign::CENTER, APP_COLORS().GRAY_LIGHT, APP_COLORS().PRIMARY);
	
	this->drawables["team1"] = new TextField(this->parent, (int)this->x + (this->width * 1 / 20) - 20, 65, 50, (int)(this->width * 2) / 5, "Equipo 1", PADDING, WrappableText::Style::TITLE, WrappableText::TextAlign::LEFT, APP_COLORS().ACCENT, APP_COLORS().ACCENT);
	this->drawables["team2"] = new TextField(this->parent, (int)this->x + (this->width * 19 / 20) - (this->width * 2) / 5 + 20, 65, 50, (int)(this->width * 2) / 5, "Equipo 2", PADDING, WrappableText::Style::TITLE, WrappableText::TextAlign::RIGHT, APP_COLORS().ACCENT, APP_COLORS().ACCENT);
	
	this->drawables["smT11"] = new SlideableMenu(this->parent, (int)this->x + (this->width * 1 / 20), this->y + 130, 320, 200, this->avatarsFilesNames, "resources\\images\\avatars\\", true);
	this->drawables["zaddPlayer"] = new Button(this->parent, (int)this->x + (this->width / 5) + 100, (int)this->y + 130, 120, 120, this->addPlayer->copyToImage(), this->addPlayer->copyToImage());

	this->drawables["smT21"] = new SlideableMenu(this->parent, (int)this->x + (this->width * 11 / 20) + 40, this->y + 130, 320, 200, this->avatarsFilesNames, "resources\\images\\avatars\\", true);
	this->drawables["zaddPlayer2"] = new Button(this->parent, (int)this->x + (this->width * 4 / 5) + 20, (int)this->y + 130, 120, 120, this->addPlayer->copyToImage(), this->addPlayer->copyToImage());

	this->drawables["playButton"] = new Button(this->parent, (int)this->x + (this->width / 2) - 60, (int)(this->height * 4 / 5) + 50, 60, 120, "Jugar", APP_COLORS().GRAY_LIGHT, APP_COLORS().ACCENT, APP_COLORS().BLACK);

	this->drawables["bg"] = bgSprite;
	this->drawables["vs"] = vsSprite;

	this->textFields.push_back(static_cast<TextField*>(this->drawables["team1"]));
	this->textFields.push_back(static_cast<TextField*>(this->drawables["team2"]));
	this->t1Avatars.push_back(static_cast<SlideableMenu*>(this->drawables["smT11"]));
	this->t2Avatars.push_back(static_cast<SlideableMenu*>(this->drawables["smT21"]));
};
