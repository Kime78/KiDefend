#pragma once

#include "game_object.hpp"


class IButton : protected GameObject {
protected:
    sf::Vector2i scale; 
public: 
    static sf::RenderWindow* window;
    virtual void on_click() = 0;
    bool is_clicked();
};

class ShopButton : public IButton {
public:
    ShopButton(sf::Texture texture, sf::Vector2f position, sf::Vector2i scale);
    void on_click();
};