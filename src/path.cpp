#include "path.hpp"
#include "utility.hpp"
#include <cmath>

void Path::move_in_path(Enemy& obj, float speed) {
    float angle = angle_between(path.front(), obj.getPosition());

    float vx = speed * cos(angle);
    float vy = speed * sin(angle);

    bool cond1 = obj.getPosition().x > path.front().x - 1 && obj.getPosition().x < path.front().x + 1;
    bool cond2 = obj.getPosition().y > path.front().y - 1 && obj.getPosition().y < path.front().y + 1;
    if(cond1) {
        vx = 0;
    }
    if(cond2) {
        vy = 0;
    }
    if(cond1 && cond2) {
        path.pop();
        float angle = angle_between(path.front(), obj.getPosition());
        obj.setRotation(0);
        obj.rotate(angle * (180.0/M_PI));
    }
    obj.setPosition(obj.getPosition().x + vx, obj.getPosition().y + vy);
}