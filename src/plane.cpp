/*Y AND Z INTERCHANGED TO ALIGN THE PLANE*/
#include "plane.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Plane::Plane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
	this->local_axis = glm::mat4(1.0f);
	this->rotangle=.5;
    this->speed = .1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    int n=40;//n triangles
	float r=1 ;
	float theta=(2*pi)/n;
    int height=6;

	GLfloat g_vertex_buffer_data[9*n];
	GLfloat a_vertex_buffer_data[9*n];
	
	//1st triangle
	g_vertex_buffer_data[0]=r;
	g_vertex_buffer_data[2]=0;
	g_vertex_buffer_data[1]=height;
	
	g_vertex_buffer_data[3]=r;
	g_vertex_buffer_data[4]=0;
	g_vertex_buffer_data[5]=0;
	
	g_vertex_buffer_data[6]=r*cos(theta);
	g_vertex_buffer_data[8]=r*sin(theta);
	g_vertex_buffer_data[7]=0;
/////////////////////////////////////////////////
    a_vertex_buffer_data[0]=r*cos(theta);
	a_vertex_buffer_data[2]=r*sin(theta);
	a_vertex_buffer_data[1]=0;
	
	a_vertex_buffer_data[3]=r;
	a_vertex_buffer_data[5]=0;
	a_vertex_buffer_data[4]=height;
	
	a_vertex_buffer_data[6]=r*cos(theta);
	a_vertex_buffer_data[8]=r*sin(theta);
	a_vertex_buffer_data[7]=height;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6];
	prev[1]=g_vertex_buffer_data[8];

    float prev2[2];
	prev2[0]=a_vertex_buffer_data[6];
	prev2[1]=a_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		g_vertex_buffer_data[9*i]=prev2[0];
		g_vertex_buffer_data[9*i+2]=prev2[1];
		g_vertex_buffer_data[9*i+1]=height;
		
		g_vertex_buffer_data[9*i+3]=prev[0];
		g_vertex_buffer_data[9*i+5]=prev[1];
		g_vertex_buffer_data[9*i+4]=0;
		
		g_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		g_vertex_buffer_data[9*i+8]=prev[0]*sin(theta)+prev[1]*cos(theta);
		g_vertex_buffer_data[9*i+7]=0;

		prev[0]=g_vertex_buffer_data[9*i+6];
		prev[1]=g_vertex_buffer_data[9*i+8];
///////////////////////////////////////////////////////
        a_vertex_buffer_data[9*i]=g_vertex_buffer_data[9*i+6];
		a_vertex_buffer_data[9*i+2]=g_vertex_buffer_data[9*i+8];
		a_vertex_buffer_data[9*i+1]=0;
		
		a_vertex_buffer_data[9*i+3]=prev2[0];
		a_vertex_buffer_data[9*i+5]=prev2[1];
		a_vertex_buffer_data[9*i+4]=height;
		
		a_vertex_buffer_data[9*i+6]=prev2[0]*cos(theta)-prev2[1]*sin(theta);
		a_vertex_buffer_data[9*i+8]=prev2[0]*sin(theta)+prev2[1]*cos(theta);
		a_vertex_buffer_data[9*i+7]=height;

		prev2[0]=a_vertex_buffer_data[9*i+6];
		prev2[1]=a_vertex_buffer_data[9*i+8];
	}

    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_GOLDEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_GOLDEN, GL_FILL);


    height=height/2;
    //cone
    GLfloat b_vertex_buffer_data[9*n];
	//1st triangle
	b_vertex_buffer_data[0]=0;
	b_vertex_buffer_data[2]=0;
	b_vertex_buffer_data[1]=-height;
	
	b_vertex_buffer_data[3]=r;
	b_vertex_buffer_data[5]=0;
	b_vertex_buffer_data[4]=0;
	
	b_vertex_buffer_data[6]=r*cos(theta);
	b_vertex_buffer_data[8]=r*sin(theta);
	b_vertex_buffer_data[7]=0;

	float prev3[2];
	prev3[0]=b_vertex_buffer_data[6];
	prev3[1]=b_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		b_vertex_buffer_data[9*i]=0;
		b_vertex_buffer_data[9*i+2]=0;
		b_vertex_buffer_data[9*i+1]=-height;
		
		b_vertex_buffer_data[9*i+3]=prev3[0];
		b_vertex_buffer_data[9*i+5]=prev3[1];
		b_vertex_buffer_data[9*i+4]=0;
		
		b_vertex_buffer_data[9*i+6]=prev3[0]*cos(theta)-prev3[1]*sin(theta);
		b_vertex_buffer_data[9*i+8]=prev3[0]*sin(theta)+prev3[1]*cos(theta);
		b_vertex_buffer_data[9*i+7]=0;

		prev3[0]=b_vertex_buffer_data[9*i+6];
		prev3[1]=b_vertex_buffer_data[9*i+8];
	}

    this->object3 = create3DObject(GL_TRIANGLES, n*3, b_vertex_buffer_data, COLOR_GOLDEN, GL_FILL);

    int wl=4;
    int wb=2;
    static const GLfloat c_vertex_buffer_data[]={

        r,2,0,
        r,2+wl,0,
        r+wb,2+wl,0,
        -r,2,0,
        -r,2+wl,0,
        -r-wb,2+wl,0,

		0,2,r,
		0,2+wl,r,
		0,2+wl,r+wb


    };
    this->object4 = create3DObject(GL_TRIANGLES, 3*3, c_vertex_buffer_data, COLOR_RED, GL_FILL);


}

void Plane::draw(glm::mat4 VP) {
	//std::cout <<this->local_axis[0][0] << " ";
	//std::cout <<this->local_axis[0][1] << " ";
	//std::cout <<this->local_axis[0][2] << "\n";

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    //glm::mat4 rotate2    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->local_axis);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
    this->position.z -= speed;
	if(this->position.z<0.5)
	    this->position.z=0.5;

}

void Plane::right()//rotation about global y
{
    glm::mat4 rotate_y = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y -= this->speed;
    this->local_axis = this->local_axis*rotate_y;

}

void Plane::left()
{
    glm::mat4 rotate_y = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[2][0],this->local_axis[2][1],this->local_axis[2][2]));
    //this->rotation.y += this->speed;
    this->local_axis = this->local_axis*rotate_y;
}

void Plane::forward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position -= length;
}

void Plane::backward()//translation in z
{
    float mag = glm::length(glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    glm::vec3 length = glm::vec3(this->local_axis[1][0]*this->speed/mag,this->local_axis[1][1]*this->speed/mag,this->local_axis[1][2]*this->speed/mag);
    this->position += length;
}

void Plane::pitchdown()//rotate about x
{
    glm::mat4 rotate_x = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}

void Plane::pitchup()
{
    glm::mat4 rotate_x = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[0][0],this->local_axis[0][1],this->local_axis[0][2]));
    this->local_axis = rotate_x*this->local_axis;
}


void Plane::tiltright()//rotation about z axis
{
    glm::mat4 rotate_z = glm::rotate((float)(this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

void Plane::tiltleft()
{
    glm::mat4 rotate_z = glm::rotate((float)(-this->rotangle*pi/180.0f),glm::vec3(this->local_axis[1][0],this->local_axis[1][1],this->local_axis[1][2]));
    this->local_axis = rotate_z*this->local_axis;
}

glm::vec3 Plane::axis(int axe)
{
	return(glm::vec3(this->local_axis[axe][0],this->local_axis[axe][1],this->local_axis[axe][2]));
}