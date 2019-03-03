/*Y AND Z INTERCHANGED TO ALIGN THE Compass*/
#include "compass.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Compass::Compass(float x, float y, float z,color_t color,int flag) {
    this->position = glm::vec3(x, y, z);
	this->local_axis = glm::mat4(1.0f);
	this->rotangle=.5;
    this->speed = .1;
    this->flag=flag;
    this->color=color;
    this->angle=0;

 int n=200;//n triangles
	float r=5 ;
	float theta=(2*pi)/n;

	GLfloat g_vertex_buffer_data[9*n];
	GLfloat tg_vertex_buffer_data[9*n];

	//1st triangle
	g_vertex_buffer_data[0]=0;
	g_vertex_buffer_data[1]=0;
	g_vertex_buffer_data[2]=0;
	
	g_vertex_buffer_data[3]=r;
	g_vertex_buffer_data[4]=0;
	g_vertex_buffer_data[5]=0;
	
	g_vertex_buffer_data[6]=r*cos(theta);
	g_vertex_buffer_data[7]=r*sin(theta);
	g_vertex_buffer_data[8]=0;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6];
	prev[1]=g_vertex_buffer_data[7];

    int i;
	for(i=1;i<n;i++)
	{
		g_vertex_buffer_data[9*i]=0;
		g_vertex_buffer_data[9*i+1]=0;
		g_vertex_buffer_data[9*i+2]=0;
		
		g_vertex_buffer_data[9*i+3]=prev[0];
		g_vertex_buffer_data[9*i+4]=prev[1];
		g_vertex_buffer_data[9*i+5]=0;
		
		g_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		g_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		g_vertex_buffer_data[9*i+8]=0;

		prev[0]=g_vertex_buffer_data[9*i+6];
		prev[1]=g_vertex_buffer_data[9*i+7];
        
	}
    for(int i=0;i<n*9;i++)
    {
        if(i%3==0)
            tg_vertex_buffer_data[i]=g_vertex_buffer_data[i];
        if(i%3==1)
            tg_vertex_buffer_data[i]=g_vertex_buffer_data[i+1];
        if(i%3==2)
            tg_vertex_buffer_data[i]=g_vertex_buffer_data[i-1];
    }
    this->object1 = create3DObject(GL_TRIANGLES, n*3, tg_vertex_buffer_data, COLOR_BLACK, GL_FILL);

	
	GLfloat vertex_buffer_data[9*n];
	GLfloat tvertex_buffer_data[9*n];

    r=4;
    //1st triangle
	vertex_buffer_data[0]=0;
	vertex_buffer_data[1]=0;
	vertex_buffer_data[2]=0;
	
	vertex_buffer_data[3]=r;
	vertex_buffer_data[4]=0;
	vertex_buffer_data[5]=0;
	
	vertex_buffer_data[6]=r*cos(theta);
	vertex_buffer_data[7]=r*sin(theta);
	vertex_buffer_data[8]=0;

	
	prev[0]=vertex_buffer_data[6];
	prev[1]=vertex_buffer_data[7];

    i;
	for(i=1;i<n;i++)
	{
		vertex_buffer_data[9*i]=0;
		vertex_buffer_data[9*i+1]=0;
		vertex_buffer_data[9*i+2]=0;
		
		vertex_buffer_data[9*i+3]=prev[0];
		vertex_buffer_data[9*i+4]=prev[1];
		vertex_buffer_data[9*i+5]=0;
		
		vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		vertex_buffer_data[9*i+8]=0;

		prev[0]=vertex_buffer_data[9*i+6];
		prev[1]=vertex_buffer_data[9*i+7];
        
	}
    for(int i=0;i<n*9;i++)
    {
        if(i%3==0)
            tvertex_buffer_data[i]=vertex_buffer_data[i];
        if(i%3==1)
            tvertex_buffer_data[i]=vertex_buffer_data[i+1]+.1;
        if(i%3==2)
            tvertex_buffer_data[i]=vertex_buffer_data[i-1];
    }
    this->object2 = create3DObject(GL_TRIANGLES, n*3, tvertex_buffer_data, COLOR_DBLACK, GL_FILL);

    float al,ah;
    al=1;
    ah=4;
	GLfloat aavertex_buffer_data[]={

        -al/2,0.2,0,
        al/2,0.2,0,
        0,0.2,ah

    };

    this->object3 = create3DObject(GL_TRIANGLES, 1*3, aavertex_buffer_data, color, GL_FILL);

   
}

void Compass::draw(glm::mat4 VP) {

    float d=.15;
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

    draw3DObject(this->object1);
    draw3DObject(this->object2);


    float al,ah;
    float theta=-this->angle;
    al=1;
    ah=4;
	GLfloat aavertex_buffer_data[]={

        //(-al/2)*cos(theta),0.2,(-al/2)*sin(theta),
        //(al/2)*cos(theta),0.2,(al/2)*sin(theta),
        //(-ah)*sin(theta),0.2,ah*sin(theta)

         -al/2,0.2,0,
        al/2,0.2,0,
        0,0.2,ah

    };
    glm::mat4 temp(1.0f);
//////////////////////////////////////////////////////////////
    temp[0][0]=aavertex_buffer_data[0];
    temp[0][1]=aavertex_buffer_data[1];
    temp[0][2]=aavertex_buffer_data[2];
    temp[1][0]=aavertex_buffer_data[3];
    temp[1][1]=aavertex_buffer_data[4];
    temp[1][2]=aavertex_buffer_data[5];
    temp[2][0]=aavertex_buffer_data[6];
    temp[2][1]=aavertex_buffer_data[7];
    temp[2][2]=aavertex_buffer_data[8];


    glm::mat4 rotate_z = glm::rotate((float)(theta),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    temp = rotate_z*temp;

    aavertex_buffer_data[0]=temp[0][0];
    //aavertex_buffer_data[1]=temp[0][1];
    aavertex_buffer_data[2]=temp[0][2];
    aavertex_buffer_data[3]=temp[1][0];
    //aavertex_buffer_data[4]=temp[1][1];
    aavertex_buffer_data[5]=temp[1][2];
    aavertex_buffer_data[6]=temp[2][0];
    //aavertex_buffer_data[7]=temp[2][1];
    aavertex_buffer_data[8]=temp[2][2];


    this->object3 = create3DObject(GL_TRIANGLES, 1*3, aavertex_buffer_data, color, GL_FILL);
    draw3DObject(this->object3);
}

void Compass::set_position(glm::vec3 a) {
    this->position = a;
}

void Compass::tick(float angle) {
    
    //glm::mat4 rotate_y = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    //this->local_axis = rotate_y*this->local_axis;
}

void Compass::right()//rotation about global y
{
    glm::mat4 rotate_y = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y -= this->speed;
    this->local_axis = this->local_axis*rotate_y;

}

void Compass::left()
{
    glm::mat4 rotate_y = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y += this->speed;
    this->local_axis = this->local_axis*rotate_y;
}

void Compass::forward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position -= length;
}

void Compass::backward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position += length;
}

void Compass::pitchdown()//rotate about x
{
    glm::mat4 rotate_x = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}

void Compass::pitchup()
{
    glm::mat4 rotate_x = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}


void Compass::tiltright(float angle)//rotation about z axis
{
//    glm::mat4 rotate_z = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::mat4 rotate_z = glm::rotate((float)(angle),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

void Compass::tiltleft(float angle)
{
//    glm::mat4 rotate_z = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::mat4 rotate_z = glm::rotate((float)(-angle),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

glm::vec3 Compass::axis(int axe)
{
	return(glm::vec3(this->local_axis[axe][0],this->local_axis[axe][1],this->local_axis[axe][2]));
}