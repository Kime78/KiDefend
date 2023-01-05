#include "path.hpp"
#include "utility.hpp"
#include <cmath>

void Path::move_in_path(Enemy& obj) {
    float angle = angle_between(path[obj.get_path_indx()], obj.getPosition());

    float vx = obj.get_speed() * cos(angle);
    float vy = obj.get_speed() * sin(angle);

    bool cond1 = obj.getPosition().x > path[obj.get_path_indx()].x - 5 && obj.getPosition().x < path[obj.get_path_indx()].x + 5;
    bool cond2 = obj.getPosition().y > path[obj.get_path_indx()].y - 5 && obj.getPosition().y < path[obj.get_path_indx()].y + 5;
    if(cond1) {
        vx = 0;
    }
    if(cond2) {
        vy = 0;
    }
    if(cond1 && cond2) {
        obj.set_path_indx(obj.get_path_indx() + 1);
        float angle = angle_between(path[obj.get_path_indx()], obj.getPosition());
    }
    obj.setPosition(obj.getPosition().x + vx, obj.getPosition().y + vy);
}