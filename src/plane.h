#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 local_axis;

    float rotation;
    float rotangle;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

    void left();
    void right();
    void forward();
    void backward();
    void pitchup();
    void pitchdown();
    void tiltright();
    void tiltleft();
    glm::vec3 axis(int axe);
    
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
    VAO *object10;
    VAO *object11;
};

#endif // PLANE_H
