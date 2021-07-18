/************************************************//**
 * \file    Button.h
***************************************************/

#pragma once

/**************************************************/
// Libraries

#include "UIElement.h"

/**************************************************/
/**
 * Button class
 */
class Button : public UIElement
{
    private:

    protected:
        /********************/
        // Variables

        /********************/
        // Methods

        /**
         * \brief Creates the button's background, etc, but doesn`t show it until render.
         */
        void draw();

    public:
        /********************/
        // Constructor

        /**
         * Button Constructor.
         *
         * \param width The desired width for the window.
         * \param height The desired height for the window.
         */
        Button(int width, int height);

        /********************/
        // Getters and setters methods

        /********************/
        // Methods

        /**
         * \brief Prints the button on screen.
         */
        void render();
};
