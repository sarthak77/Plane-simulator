#include "enemybase.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Enemybase::Enemybase(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    //this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

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
        1.0f,-1.0f, 1.0f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

	GLfloat a_vertex_buffer_data[12*3*3];
    for(int i=0;i<12*3*3;i++)
    {
        if(i%3==0)
            a_vertex_buffer_data[i]=vertex_buffer_data[i]-3;
        else
            a_vertex_buffer_data[i]=vertex_buffer_data[i];

    }
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, a_vertex_buffer_data, color, GL_FILL);

    GLfloat b_vertex_buffer_data[12*3*3];
    for(int i=0;i<12*3*3;i++)
    {
        if(i%3==0)
            b_vertex_buffer_data[i]=vertex_buffer_data[i]+3;
        else
            b_vertex_buffer_data[i]=vertex_buffer_data[i];

    }
    this->object3 = create3DObject(GL_TRIANGLES, 12*3, b_vertex_buffer_data, color, GL_FILL);

    GLfloat c_vertex_buffer_data[12*3*3];
    for(int i=0;i<12*3*3;i++)
    {
        if(i%3==1)
            c_vertex_buffer_data[i]=vertex_buffer_data[i]-3;
        else
            c_vertex_buffer_data[i]=vertex_buffer_data[i];

    }
    this->object4 = create3DObject(GL_TRIANGLES, 12*3, c_vertex_buffer_data, color, GL_FILL);

    GLfloat d_vertex_buffer_data[12*3*3];
    for(int i=0;i<12*3*3;i++)
    {
        if(i%3==1)
            d_vertex_buffer_data[i]=vertex_buffer_data[i]+3;
        else
            d_vertex_buffer_data[i]=vertex_buffer_data[i];

    }
    this->object5 = create3DObject(GL_TRIANGLES, 12*3, d_vertex_buffer_data, color, GL_FILL);

}

void Enemybase::draw(glm::mat4 VP) {
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
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

void Enemybase::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemybase::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

