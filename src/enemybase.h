#include "main.h"

#ifndef ENEMYBASE_H
#define ENEMYBASE_H


class Enemybase {
public:
    Enemybase() {}
    Enemybase(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // ENEMYBASE_H
