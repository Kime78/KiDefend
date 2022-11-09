#include "path.hpp"
#include <cmath>

void Path::move_in_path(Enemy& obj, float speed) {
    float dx = path.front().x - obj.sprite.getPosition().x;
    float dy = path.front().y - obj.sprite.getPosition().y;

    float angle = atan2(dy, dx);

    float vx = speed * cos(angle);
    float vy = speed * sin(angle);

    bool cond1 = obj.sprite.getPosition().x > path.front().x - 1 && obj.sprite.getPosition().x < path.front().x + 1;
    bool cond2 = obj.sprite.getPosition().y > path.front().y - 1 && obj.sprite.getPosition().y < path.front().y + 1;
    if(cond1) {
        vx = 0;
    }
    if(cond2) {
        vy = 0;
    }
    if(cond1 && cond2) {
        path.pop();
        float dx = path.front().x - obj.sprite.getPosition().x;
        float dy = path.front().y - obj.sprite.getPosition().y;
        float angle = atan2(dy, dx);
        obj.sprite.setRotation(0);
        obj.sprite.rotate(angle * (180.0/3.141592653589793238463));
    }
    obj.sprite.setPosition(obj.sprite.getPosition().x + vx, obj.sprite.getPosition().y + vy);
}