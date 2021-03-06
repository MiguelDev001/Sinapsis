/************************************************//**
 * \file    SignUpView.h
***************************************************/

#pragma once

/**************************************************/
// Libraries

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "MainView.h"
#include "SlideableMenu.h"
#include "TextField.h"

/**************************************************/
// Namespaces

using namespace std;
using namespace sf;

/**************************************************/
/**
 * SignUpView class
 */
class SignUpView : public MainView
{
    private:
        /********************/
        // Methods
        void loop() override;

    protected:
        /********************/
        // Variables

        Texture
            * bg,
            * addPlayer,
            * addPlayer2,
            * vs;

        TextField* selectedTextField;
        vector<TextField*> textFields;
        vector<SlideableMenu*>
            t1Avatars,
            t2Avatars;
        map<string, vector<string>> avatarsFilesNames;
        bool isDone;

        /********************/
        // Methods

    public:
        /********************/
        // Constructor

        SignUpView(RenderWindow* parent, int x, int y, int height, int width);

        /********************/
        // Getters and setters methods

        bool getIsDone();
        void setIsDone(bool isDone);

        map<string, vector<map<string, string>>> getData();

        /********************/
        // Methods

        void changeSelectedTextField(String input);

        /**
         * \brief Prints the ui on the canvas (doesn't show it on screen).
         */
        void initDrawables();
};
