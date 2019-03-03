#include "main.h"

#ifndef INDICATOR_H
#define INDICATOR_H


class Indicator {
public:
    Indicator() {}
    Indicator(float x, float y, float z,color_t color,int flag);
    glm::vec3 position;
    float rotation;
    float flag;
    void draw(glm::mat4 VP,glm::vec3 pos);
    void set_position(float x, float y,float z);
    void tick(int length);
    double speed;
private:
    VAO *object1;
    VAO *object2;
};

#endif // INDICATOR_H
