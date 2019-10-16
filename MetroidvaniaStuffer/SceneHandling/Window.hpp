//
//  Window.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/1/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>
class Window
{
public:
    Window(const std::string& windowName);
    
    void update();
    
    void beginDraw();
    void draw(const sf::Drawable& drawable);
    void endDraw();
    
    sf::Vector2u getCenter() const;
    
    bool isOpen() const;
    
private:
    sf::RenderWindow window;
};
#endif /* Window_hpp */
