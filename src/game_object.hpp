#pragma once
#include <SFML/Graphics.hpp> 

class GameObjectContainer;

class GameObject : public sf::Sprite  {
public:
    static sf::RenderWindow* window;
    static GameObjectContainer* objects;
    virtual ~GameObject() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
};

class GameObjectContainer {
public:
    void add(std::unique_ptr<GameObject> obj) {
        objects.push_back(std::move(obj));
    }

    void remove(GameObject* obj) {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (it->get() == obj) {
                objects.erase(it);
                break;
            }
        }
    }

    void iterate(std::function<void(GameObject&)> func) {
        for (auto& obj : objects) {
            if(obj != nullptr)
                func(*obj);
        }
    }

    std::vector<std::unique_ptr<GameObject>>& vec() {
        return objects;
    }

private:
    std::vector<std::unique_ptr<GameObject>> objects;
};