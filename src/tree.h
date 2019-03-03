#include "main.h"

#ifndef TREE_H
#define TREE_H


class Tree {
public:
    Tree() {}
    Tree(float x, float y, float z);
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
};

#endif // TREE_H
