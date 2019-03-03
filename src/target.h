#include "main.h"

#ifndef TARGET_H
#define TARGET_H


class Target {
public:
    Target() {}
    Target(float x, float y, float z,color_t color,int flag,double l3);
    glm::vec3 position;
    glm::mat4 local_axis;

    float rotation;
    double l3;
    float rotangle;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 a);
    void tick();
    double speed;
    int flag;
    color_t color;

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
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // TARGET_H
