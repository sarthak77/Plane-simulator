/*Y AND Z INTERCHANGED TO ALIGN THE PLANE*/
#include "plane.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Plane::Plane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
	this->local_axis = glm::mat4(1.0f);
	this->rotangle=.5;
    this->speed = .2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    

	//body
    int n=40;//n triangles
	float r=.7 ;
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

    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_BLACK, GL_FILL);


	//front cone
    height=height/3;
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

    this->object3 = create3DObject(GL_TRIANGLES, n*3, b_vertex_buffer_data, COLOR_DBLACK, GL_FILL);


	//wings
    int wl=1;
    float wb=2.5;
    static const GLfloat c_vertex_buffer_data[]={

        r,1,0,
        r,2+wl,0,
        r+wb,2+wl,0,

        -r,1,0,
        -r,2+wl,0,
        -r-wb,2+wl,0,

		r,4,0,
        r,4+wl,0,
        r+wb,4+wl,0,

        -r,4,0,
        -r,4+wl,0,
        -r-wb,4+wl,0,

		0,1,r,
		0,4+wl,r,
		0,4+wl,r+wb/2,

    };
    this->object4 = create3DObject(GL_TRIANGLES, 5*3, c_vertex_buffer_data, COLOR_BLACK, GL_FILL);


	//back cone
	height=-1;
	int d=6;
    //cone
    GLfloat bb_vertex_buffer_data[9*n];
	//1st triangle
	bb_vertex_buffer_data[0]=0;
	bb_vertex_buffer_data[2]=0;
	bb_vertex_buffer_data[1]=-height+d;
	
	bb_vertex_buffer_data[3]=r;
	bb_vertex_buffer_data[5]=0;
	bb_vertex_buffer_data[4]=0+d;
	
	bb_vertex_buffer_data[6]=r*cos(theta);
	bb_vertex_buffer_data[8]=r*sin(theta);
	bb_vertex_buffer_data[7]=0+d;

	float prev4[2];
	prev4[0]=bb_vertex_buffer_data[6];
	prev4[1]=bb_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		bb_vertex_buffer_data[9*i]=0;
		bb_vertex_buffer_data[9*i+2]=0;
		bb_vertex_buffer_data[9*i+1]=-height+d;
		
		bb_vertex_buffer_data[9*i+3]=prev4[0];
		bb_vertex_buffer_data[9*i+5]=prev4[1];
		bb_vertex_buffer_data[9*i+4]=0+d;
		
		bb_vertex_buffer_data[9*i+6]=prev4[0]*cos(theta)-prev4[1]*sin(theta);
		bb_vertex_buffer_data[9*i+8]=prev4[0]*sin(theta)+prev4[1]*cos(theta);
		bb_vertex_buffer_data[9*i+7]=0+d;

		prev4[0]=bb_vertex_buffer_data[9*i+6];
		prev4[1]=bb_vertex_buffer_data[9*i+8];
	}

    this->object5 = create3DObject(GL_TRIANGLES, n*3, bb_vertex_buffer_data, COLOR_RED, GL_FILL);


	//side engine
	int a=2*r;
	int b=3;
	r=.3 ;
    height=2;
	GLfloat gg_vertex_buffer_data[9*n];
	GLfloat aa_vertex_buffer_data[9*n];
	//1st triangle
	gg_vertex_buffer_data[0]=r+a;
	gg_vertex_buffer_data[2]=0;
	gg_vertex_buffer_data[1]=height+b;
	
	gg_vertex_buffer_data[3]=r+a;
	gg_vertex_buffer_data[4]=0+b;
	gg_vertex_buffer_data[5]=0;
	
	gg_vertex_buffer_data[6]=r*cos(theta)+a;
	gg_vertex_buffer_data[8]=r*sin(theta);
	gg_vertex_buffer_data[7]=0+b;
/////////////////////////////////////////////////
    aa_vertex_buffer_data[0]=r*cos(theta)+a;
	aa_vertex_buffer_data[2]=r*sin(theta);
	aa_vertex_buffer_data[1]=0+b;
	
	aa_vertex_buffer_data[3]=r+a;
	aa_vertex_buffer_data[5]=0;
	aa_vertex_buffer_data[4]=height+b;
	
	aa_vertex_buffer_data[6]=r*cos(theta)+a;
	aa_vertex_buffer_data[8]=r*sin(theta);
	aa_vertex_buffer_data[7]=height+b;

	float prev5[2];
	prev5[0]=gg_vertex_buffer_data[6]-a;
	prev5[1]=gg_vertex_buffer_data[8];

    float prev6[2];
	prev6[0]=aa_vertex_buffer_data[6]-a;
	prev6[1]=aa_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		gg_vertex_buffer_data[9*i]=prev6[0]+a;
		gg_vertex_buffer_data[9*i+2]=prev6[1];
		gg_vertex_buffer_data[9*i+1]=height+b;
		
		gg_vertex_buffer_data[9*i+3]=prev5[0]+a;
		gg_vertex_buffer_data[9*i+5]=prev5[1];
		gg_vertex_buffer_data[9*i+4]=0+b;
		
		gg_vertex_buffer_data[9*i+6]=prev5[0]*cos(theta)-prev5[1]*sin(theta)+a;
		gg_vertex_buffer_data[9*i+8]=prev5[0]*sin(theta)+prev5[1]*cos(theta);
		gg_vertex_buffer_data[9*i+7]=0+b;

		prev5[0]=gg_vertex_buffer_data[9*i+6]-a;
		prev5[1]=gg_vertex_buffer_data[9*i+8];
///////////////////////////////////////////////////////
        aa_vertex_buffer_data[9*i]=gg_vertex_buffer_data[9*i+6];
		aa_vertex_buffer_data[9*i+2]=gg_vertex_buffer_data[9*i+8];
		aa_vertex_buffer_data[9*i+1]=0+b;
		
		aa_vertex_buffer_data[9*i+3]=prev6[0]+a;
		aa_vertex_buffer_data[9*i+5]=prev6[1];
		aa_vertex_buffer_data[9*i+4]=height+b;
		
		aa_vertex_buffer_data[9*i+6]=prev6[0]*cos(theta)-prev6[1]*sin(theta)+a;
		aa_vertex_buffer_data[9*i+8]=prev6[0]*sin(theta)+prev6[1]*cos(theta);
		aa_vertex_buffer_data[9*i+7]=height+b;

		prev6[0]=aa_vertex_buffer_data[9*i+6]-a;
		prev6[1]=aa_vertex_buffer_data[9*i+8];
	}

    this->object6 = create3DObject(GL_TRIANGLES, n*3, gg_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, n*3, aa_vertex_buffer_data, COLOR_DBLACK, GL_FILL);


//side engine
	a=-4*r;
	b=3;
	r=.3 ;
    height=2;
	GLfloat ggg_vertex_buffer_data[9*n];
	GLfloat aaa_vertex_buffer_data[9*n];
	//1st triangle
	ggg_vertex_buffer_data[0]=r+a;
	ggg_vertex_buffer_data[2]=0;
	ggg_vertex_buffer_data[1]=height+b;
	
	ggg_vertex_buffer_data[3]=r+a;
	ggg_vertex_buffer_data[4]=0+b;
	ggg_vertex_buffer_data[5]=0;
	
	ggg_vertex_buffer_data[6]=r*cos(theta)+a;
	ggg_vertex_buffer_data[8]=r*sin(theta);
	ggg_vertex_buffer_data[7]=0+b;
/////////////////////////////////////////////////
    aaa_vertex_buffer_data[0]=r*cos(theta)+a;
	aaa_vertex_buffer_data[2]=r*sin(theta);
	aaa_vertex_buffer_data[1]=0+b;
	
	aaa_vertex_buffer_data[3]=r+a;
	aaa_vertex_buffer_data[5]=0;
	aaa_vertex_buffer_data[4]=height+b;
	
	aaa_vertex_buffer_data[6]=r*cos(theta)+a;
	aaa_vertex_buffer_data[8]=r*sin(theta);
	aaa_vertex_buffer_data[7]=height+b;

	float prev7[2];
	prev7[0]=ggg_vertex_buffer_data[6]-a;
	prev7[1]=ggg_vertex_buffer_data[8];

    float prev8[2];
	prev8[0]=aaa_vertex_buffer_data[6]-a;
	prev8[1]=aaa_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		ggg_vertex_buffer_data[9*i]=prev8[0]+a;
		ggg_vertex_buffer_data[9*i+2]=prev8[1];
		ggg_vertex_buffer_data[9*i+1]=height+b;
		
		ggg_vertex_buffer_data[9*i+3]=prev7[0]+a;
		ggg_vertex_buffer_data[9*i+5]=prev7[1];
		ggg_vertex_buffer_data[9*i+4]=0+b;
		
		ggg_vertex_buffer_data[9*i+6]=prev7[0]*cos(theta)-prev7[1]*sin(theta)+a;
		ggg_vertex_buffer_data[9*i+8]=prev7[0]*sin(theta)+prev7[1]*cos(theta);
		ggg_vertex_buffer_data[9*i+7]=0+b;

		prev7[0]=ggg_vertex_buffer_data[9*i+6]-a;
		prev7[1]=ggg_vertex_buffer_data[9*i+8];
///////////////////////////////////////////////////////
        aaa_vertex_buffer_data[9*i]=ggg_vertex_buffer_data[9*i+6];
		aaa_vertex_buffer_data[9*i+2]=ggg_vertex_buffer_data[9*i+8];
		aaa_vertex_buffer_data[9*i+1]=0+b;
		
		aaa_vertex_buffer_data[9*i+3]=prev8[0]+a;
		aaa_vertex_buffer_data[9*i+5]=prev8[1];
		aaa_vertex_buffer_data[9*i+4]=height+b;
		
		aaa_vertex_buffer_data[9*i+6]=prev8[0]*cos(theta)-prev8[1]*sin(theta)+a;
		aaa_vertex_buffer_data[9*i+8]=prev8[0]*sin(theta)+prev8[1]*cos(theta);
		aaa_vertex_buffer_data[9*i+7]=height+b;

		prev8[0]=aaa_vertex_buffer_data[9*i+6]-a;
		prev8[1]=aaa_vertex_buffer_data[9*i+8];
	}

    this->object8 = create3DObject(GL_TRIANGLES, n*3, ggg_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, n*3, aaa_vertex_buffer_data, COLOR_DBLACK, GL_FILL);




//side cone
	height=-1;
	d=5;
    //cone
    GLfloat bbb_vertex_buffer_data[9*n];
	//1st triangle
	bbb_vertex_buffer_data[0]=0+a;
	bbb_vertex_buffer_data[2]=0;
	bbb_vertex_buffer_data[1]=-height+d;
	
	bbb_vertex_buffer_data[3]=r+a;
	bbb_vertex_buffer_data[5]=0;
	bbb_vertex_buffer_data[4]=0+d;
	
	bbb_vertex_buffer_data[6]=r*cos(theta)+a;
	bbb_vertex_buffer_data[8]=r*sin(theta);
	bbb_vertex_buffer_data[7]=0+d;

	float prev9[2];
	prev9[0]=bbb_vertex_buffer_data[6]-a;
	prev9[1]=bbb_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		bbb_vertex_buffer_data[9*i]=0+a;
		bbb_vertex_buffer_data[9*i+2]=0;
		bbb_vertex_buffer_data[9*i+1]=-height+d;
		
		bbb_vertex_buffer_data[9*i+3]=prev9[0]+a;
		bbb_vertex_buffer_data[9*i+5]=prev9[1];
		bbb_vertex_buffer_data[9*i+4]=0+d;
		
		bbb_vertex_buffer_data[9*i+6]=prev9[0]*cos(theta)-prev9[1]*sin(theta)+a;
		bbb_vertex_buffer_data[9*i+8]=prev9[0]*sin(theta)+prev9[1]*cos(theta);
		bbb_vertex_buffer_data[9*i+7]=0+d;

		prev9[0]=bbb_vertex_buffer_data[9*i+6]-a;
		prev9[1]=bbb_vertex_buffer_data[9*i+8];
	}

    this->object10 = create3DObject(GL_TRIANGLES, n*3, bbb_vertex_buffer_data, COLOR_RED, GL_FILL);


//side cone
	height=-1;
	d=5;
	a=5*r;
    //cone
    GLfloat bbbb_vertex_buffer_data[9*n];
	//1st triangle
	bbbb_vertex_buffer_data[0]=0+a;
	bbbb_vertex_buffer_data[2]=0;
	bbbb_vertex_buffer_data[1]=-height+d;
	
	bbbb_vertex_buffer_data[3]=r+a;
	bbbb_vertex_buffer_data[5]=0;
	bbbb_vertex_buffer_data[4]=0+d;
	
	bbbb_vertex_buffer_data[6]=r*cos(theta)+a;
	bbbb_vertex_buffer_data[8]=r*sin(theta);
	bbbb_vertex_buffer_data[7]=0+d;

	float prev10[2];
	prev10[0]=bbbb_vertex_buffer_data[6]-a;
	prev10[1]=bbbb_vertex_buffer_data[8];

	for(int i=1;i<n;i++)
	{
		bbbb_vertex_buffer_data[9*i]=0+a;
		bbbb_vertex_buffer_data[9*i+2]=0;
		bbbb_vertex_buffer_data[9*i+1]=-height+d;
		
		bbbb_vertex_buffer_data[9*i+3]=prev10[0]+a;
		bbbb_vertex_buffer_data[9*i+5]=prev10[1];
		bbbb_vertex_buffer_data[9*i+4]=0+d;
		
		bbbb_vertex_buffer_data[9*i+6]=prev10[0]*cos(theta)-prev10[1]*sin(theta)+a;
		bbbb_vertex_buffer_data[9*i+8]=prev10[0]*sin(theta)+prev10[1]*cos(theta);
		bbbb_vertex_buffer_data[9*i+7]=0+d;

		prev10[0]=bbbb_vertex_buffer_data[9*i+6]-a;
		prev10[1]=bbbb_vertex_buffer_data[9*i+8];
	}

    this->object11 = create3DObject(GL_TRIANGLES, n*3, bbbb_vertex_buffer_data, COLOR_RED, GL_FILL);




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
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
    draw3DObject(this->object10);
    draw3DObject(this->object11);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
    this->position.z -= speed/2;
	// if(this->position.z<0.5)
	    // this->position.z=0.5;

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