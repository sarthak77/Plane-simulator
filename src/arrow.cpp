#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        2.0f,-1.0f,2.0f,
        2.0f,-1.0f,-2.0f,
        -2.0f,-1.0f,2.0f,

        -2.0f,-1.0f,-2.0f,
        -2.0f,-1.0f,2.0f,
        2.0f,-1.0f,-2.0f,
///////////////////////////////////////////
        -2.0f,-1.0f,-2.0f,
        -2.0f,-1.0f,2.0f,
        0.0f,-2.0f,0.0f,

        -2.0f,-1.0f,-2.0f,
        2.0f,-1.0f,-2.0f,
        0.0f,-2.0f,0.0f,

        2.0f,-1.0f,2.0f,
        -2.0f,-1.0f,2.0f,
        0.0f,-2.0f,0.0f,

        2.0f,-1.0f,-2.0f,
        2.0f,-1.0f,2.0f,
        0.0f,-2.0f,0.0f
    };
    GLfloat a_vertex_buffer_data[18*9];

    int size=2;
    for(int i=0;i<18*9;i++)
    {
        int temp;
        if(i%3==0)
            a_vertex_buffer_data[i]=size*vertex_buffer_data[i];
        if(i%3==1)
        {
            temp=vertex_buffer_data[i];
            a_vertex_buffer_data[i]=size*vertex_buffer_data[i+1];
        }
        if(i%3==2)
            a_vertex_buffer_data[i]=size*temp;
    }


    this->object = create3DObject(GL_TRIANGLES, (12+6)*3, a_vertex_buffer_data, color, GL_FILL);

}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick() {
    //this->position.x -= speed;
}

