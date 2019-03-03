#include "powerup.h"
#include "main.h"

Powerup::Powerup(float x, float y, float z,int flag) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->flag = flag;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -2.0f,-2.0f,-2.0f, // triangle 2 : begin
        -2.0f,-2.0f, 2.0f,
        -2.0f, 2.0f, 2.0f, // triangle 2 : end
        2.0f, 2.0f,-2.0f, // triangle 2 : begin
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f,-2.0f, // triangle 2 : end
        2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,
        2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        -2.0f,-2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        -2.0f,-2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f,-2.0f,
        2.0f,-2.0f,-2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f,-2.0f,
        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f,-2.0f,
        -2.0f, 2.0f, 2.0f,
        2.0f, 2.0f, 2.0f,
        -2.0f, 2.0f, 2.0f,
        2.0f,-2.0f, 2.0f,


        //plus sign
        .5,2,2.01,
        -.5,2,2.01,
        -.5,-2,2.01,

        .5,2,2.01,
        .5,-2,2.01,
        -.5,-2,2.01,

        2,.5,2.01,
        2,-.5,2.01,
        -2,-.5,2.01,

        2,.5,2.01,
        -2,.5,2.01,
        -2,-.5,2.01,


        //fuel sign
        //upper
        1,1.5,2.01,
        -1,1.5,2.01,
        1,-1,2.01,
        
        1,-1,2.01,
        -1,-1,2.01,
        -1,1.5,2.01,

        //lower
        1.5,-1,2.01,
        -1.5,-1,2.01,
        1.5,-1.5,2.01,

        1.5,-1.5,2.01,
        -1.5,-1.5,2.01,
        -1.5,-1,2.01,

        //center
        0.5,.75,2.02,
        0.5,0,2.02,
        -0.5,.75,2.02,

        0.5,0,2.02,
        -0.5,0,2.02,
        -0.5,.75,2.02
        
        
            };

    color_t color;
    if(this->flag==0)
        color=COLOR_WHITE;
    else
        color=COLOR_DBLACK;
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data+12*9, COLOR_FIRE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data+16*9, COLOR_FIRE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+20*9, COLOR_DBLACK, GL_FILL);

}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+glm::vec3(0,0,1));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->flag==0)
    draw3DObject(this->object1);
    else
    {
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    }
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

