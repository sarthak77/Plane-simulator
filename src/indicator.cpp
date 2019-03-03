#include "indicator.h"
#include "main.h"

Indicator::Indicator(float x, float y, float z,color_t color, int flag) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->flag=flag;
    
    speed = 1;
    
    int l,b,l2,b2;
    int xpad,ypad;
    xpad=1;
    ypad=1;
    l=12;
    b=3;
    l2=10;
    b2=1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0,0,0,
        l,0,0,
        l,0,b,

        l,0,b,
        0,0,0,
        0,0,b
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);

    static const GLfloat a_vertex_buffer_data[] = {
        xpad,0,ypad,
        xpad,0,ypad+b2,
        xpad+l2,0,ypad,

        xpad+l2,0,ypad+b2,
        xpad,0,ypad+b2,
        xpad+l2,0,ypad

    };

    this->object2 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, color, GL_FILL);

}

void Indicator::draw(glm::mat4 VP,glm::vec3 pos) {
    this->position=pos;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Indicator::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Indicator::tick(int length) {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

