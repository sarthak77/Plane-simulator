#include "boat.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Boat::Boat(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

	static const GLfloat g_vertex_buffer_data[]={

        2,0,4,
        2,0,-4,
        -2,0,4,

        -2,0,4,
        -2,0,-4,
        2,0,-4,
/////////////////////////
        2,0,4,
        2,0,-4,
        4,2,4,

        2,0,-4,/////////not///
        4,2,4,
        4,2,-4,

        -2,0,4,
        -2,0,-4,
        -4,2,4,

        -2,0,-4,////////not////
        -4,2,4,
        -4,2,-4,
//////////////////////////
        4,2,4,
        2,0,4,
        0,2,6,

        -4,2,4,
        -2,0,4,
        0,2,6,

        4,2,-4,
        2,0,-4,
        0,2,-6,

        -4,2,-4,
        -2,0,-4,
        0,2,-6,
//////////////////////////
        2,0,4,
        -2,0,4,
        0,2,6,

        2,0,-4,
        -2,0,-4,
        0,2,-6,
    };

	GLfloat a_vertex_buffer_data[12*9];
    for(int i=0;i<12*9;i++)
    {
        int temp;
        if(i%3==0)
            a_vertex_buffer_data[i]=g_vertex_buffer_data[i];
        if(i%3==1)
        {
            temp=g_vertex_buffer_data[i];
            a_vertex_buffer_data[i]=g_vertex_buffer_data[i+1];
        }
        if(i%3==2)
            a_vertex_buffer_data[i]=temp;
        
    }
	
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, a_vertex_buffer_data+2*9, COLOR_DBLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 4*3, a_vertex_buffer_data+6*9, COLOR_DBLACK, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data+10*9, COLOR_DBLACK, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
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
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

