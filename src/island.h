#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
};

#endif // ISLAND_H
