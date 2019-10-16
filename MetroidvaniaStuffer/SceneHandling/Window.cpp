//
//  Window.cpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#include "Window.hpp"

///Initialices the window
Window::Window(const std::string& windowName)
//TODO: Make WindowSize a custmizable feature
:window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar)
{
    //TODO: Make VSyncEnabled a customizable feature
    window.setVerticalSyncEnabled(true);
}

///  Updates the window on each frame
void Window::update()
{
    sf::Event event;
    
    /// Check if close the window was triggered
    if(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

/// Clears the screen to an uniform color
void Window::beginDraw()
{
    window.clear(sf::Color::White);
}

/// Set everything is need to be draw on the window
void Window::draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}

/// Display what has been drawed
void Window::endDraw()
{
    window.display();
}

bool Window::isOpen() const
{
    return window.isOpen();
}

sf::Vector2u Window::getCenter() const
{
    sf::Vector2u size = window.getSize();
    
    return sf::Vector2u(size.x / 2, size.y / 2);
}

