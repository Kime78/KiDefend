#include "button.hpp"
#include <iostream>
std::array<sf::Texture, 10>* IButton::textures = nullptr;
sf::Font* IButton::text_font = nullptr;
sf::Event* IButton::event = nullptr;
bool* ShopButton::dragging = nullptr;
int* ShopButton::game_money = nullptr;
GameObject* ShopButton::ptr_to_turr = nullptr;

ShopButton::ShopButton(sf::Texture& texture, sf::Vector2f position, sf::Vector2i scale, TurretType shop_for, int price) {
    this->scale = scale;
    this->setPosition(position);
    this->setTexture(texture);
    this->price = price;
    this->shop_for = shop_for;
    text.setFont(*text_font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(25);
    text.setPosition(position + sf::Vector2f(120, 20));
    text.setString("$ " + std::to_string(price));
}

bool IButton::is_clicked() {
    if(event) {
        if(event->type == sf::Event::MouseButtonPressed) {
            if (event->mouseButton.button == sf::Mouse::Left) {
                return this->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window));
            }
        }
    }
    return 0;
}

void ShopButton::on_click() {
     if(*game_money >= price) { //turret cost maw    
        objects->add(std::make_unique<Turret>(shop_for, (sf::Vector2f)sf::Mouse::getPosition(*window)));
        ptr_to_turr = objects->vec().back().get();
        *game_money -= price;
        *dragging = 1;
    }
}

void ShopButton::update() {
    if(this->is_clicked()) {
        this->on_click();
    }
}

void ShopButton::draw() {
    window->draw(*this);
    window->draw(text);

}