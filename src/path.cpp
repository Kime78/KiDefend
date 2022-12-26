#include "path.hpp"
#include "utility.hpp"
#include <cmath>

void Path::move_in_path(Enemy& obj) {
    float angle = angle_between(path[obj.path_indx], obj.getPosition());

    float vx = obj.speed * cos(angle);
    float vy = obj.speed * sin(angle);

    bool cond1 = obj.getPosition().x > path[obj.path_indx].x - 1 && obj.getPosition().x < path[obj.path_indx].x + 1;
    bool cond2 = obj.getPosition().y > path[obj.path_indx].y - 1 && obj.getPosition().y < path[obj.path_indx].y + 1;
    if(cond1) {
        vx = 0;
    }
    if(cond2) {
        vy = 0;
    }
    if(cond1 && cond2) {
        obj.path_indx++;
        float angle = angle_between(path[obj.path_indx], obj.getPosition());
        obj.setRotation(0);
        obj.rotate(angle * (180.0/PI));
    }
    obj.setPosition(obj.getPosition().x + vx, obj.getPosition().y + vy);
}