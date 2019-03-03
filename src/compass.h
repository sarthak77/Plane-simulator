#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z,color_t color,int flag);
    glm::vec3 position;
    glm::mat4 local_axis;

    float angle;
    float rotation;
    float rotangle;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 a);
    void tick(float angle);
    double speed;
    int flag;
    color_t color;

    void left();
    void right();
    void forward();
    void backward();
    void pitchup();
    void pitchdown();
    void tiltright(float angle);
    void tiltleft(float angle);
    glm::vec3 axis(int axe);
    
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // COMPASS_H
