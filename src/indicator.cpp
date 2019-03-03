/*Y AND Z INTERCHANGED TO ALIGN THE Indicator*/
#include "indicator.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Indicator::Indicator(float x, float y, float z,color_t color,int flag,double l3) {
    this->position = glm::vec3(x, y, z);
	this->local_axis = glm::mat4(1.0f);
	this->rotangle=.5;
    this->speed = .1;
    this->flag=flag;
    this->color=color;
    this->l3=l3;


    int l,b;
    l=12;
    b=3;

    static const GLfloat vertex_buffer_data[] = {
        0,0,0,
        l,0,0,
        l,0,b,

        l,0,b,
        0,0,0,
        0,0,b
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);

    int b2,l2;
    int xpad,ypad;
    xpad=1;
    ypad=1;
    // l2=this->l3;
    b2=1;
    GLfloat a_vertex_buffer_data[] = {
        xpad,0.1,ypad,
        xpad,0.1,ypad+b2,
        xpad+this->l3,0.1,ypad,

        xpad+this->l3,0.1,ypad+b2,
        xpad,0.1,ypad+b2,
        xpad+this->l3,0.1,ypad

    };

    this->object2 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, this->color, GL_FILL);

}

void Indicator::draw(glm::mat4 VP) {

    float d=.25;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale=glm::scale(glm::vec3(d,d,d));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    //glm::mat4 rotate2    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->local_axis*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

int b2,l2;
    int xpad,ypad;
    xpad=1;
    ypad=1;
    // l2=this->l3;
    b2=1;
    GLfloat a_vertex_buffer_data[] = {
        xpad,0.1,ypad,
        xpad,0.1,ypad+b2,
        xpad+this->l3,0.1,ypad,

        xpad+this->l3,0.1,ypad+b2,
        xpad,0.1,ypad+b2,
        xpad+this->l3,0.1,ypad

    };

    this->object2 = create3DObject(GL_TRIANGLES, 2*3, a_vertex_buffer_data, this->color, GL_FILL);


    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Indicator::set_position(glm::vec3 a) {
    this->position = a;
}

void Indicator::tick() {
    //this->position.z -= speed;
	//if(this->position.z<0.5)
	//    this->position.z=0.5;

}

void Indicator::right()//rotation about global y
{
    glm::mat4 rotate_y = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y -= this->speed;
    this->local_axis = this->local_axis*rotate_y;

}

void Indicator::left()
{
    glm::mat4 rotate_y = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y += this->speed;
    this->local_axis = this->local_axis*rotate_y;
}

void Indicator::forward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position -= length;
}

void Indicator::backward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position += length;
}

void Indicator::pitchdown()//rotate about x
{
    glm::mat4 rotate_x = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}

void Indicator::pitchup()
{
    glm::mat4 rotate_x = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}


void Indicator::tiltright()//rotation about z axis
{
    glm::mat4 rotate_z = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

void Indicator::tiltleft()
{
    glm::mat4 rotate_z = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

glm::vec3 Indicator::axis(int axe)
{
	return(glm::vec3(this->local_axis[axe][0],this->local_axis[axe][1],this->local_axis[axe][2]));
}