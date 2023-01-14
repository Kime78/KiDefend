#pragma once

#include "game_object.hpp"
#include "turret.hpp"

class IButton : public GameObject {
protected:
    sf::Vector2i scale; 
public: 
    static std::array<sf::Texture, 10>* textures;
    static sf::Event* event;
    static sf::Font* text_font;
    virtual void on_click() = 0;
    bool is_clicked();
};

class ShopButton : public IButton {
public:
    TurretType shop_for;
    int price;
    static bool* dragging;
    static int* game_money;
    static GameObject* ptr_to_turr;
    ShopButton(sf::Texture texture, sf::Vector2f position, sf::Vector2i scale, TurretType shop_for, float price);
    void on_click();
    void draw() override;
    void update() override;
};