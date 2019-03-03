#include "main.h"

#ifndef MBALOON_H
#define MBALOON_H


class Mbaloon {
public:
    Mbaloon() {}
    Mbaloon(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 velocity;
    glm::vec3 acc;
    glm::mat4 local_axis;
    float speed;
    float rotation;
    void draw(glm::mat4 VP,float x,float y,float z,glm::vec3 dir);
    void set_position(float x, float y,float z);
    void tick(int up);
    bounding_box_t bounding_box();

private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // MBALOON_H
