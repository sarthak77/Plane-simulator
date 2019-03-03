#include "tree.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Tree::Tree(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;



 int n=40;//n triangles
	float r=.7 ;
	float theta=(2*pi)/n;
    float height=3;
    float xtr=-1; 
    float ytr=1; 
	GLfloat g_vertex_buffer_data[9*n];
	GLfloat a_vertex_buffer_data[9*n];
	//1st triangle
	g_vertex_buffer_data[0]=r+xtr;
	g_vertex_buffer_data[1]=0+ytr;
	g_vertex_buffer_data[2]=height;
	
	g_vertex_buffer_data[3]=r+xtr;
	g_vertex_buffer_data[4]=0+ytr;
	g_vertex_buffer_data[5]=0;
	
	g_vertex_buffer_data[6]=r*cos(theta)+xtr;
	g_vertex_buffer_data[7]=r*sin(theta)+ytr;
	g_vertex_buffer_data[8]=0;
/////////////////////////////////////////////////
    a_vertex_buffer_data[0]=r*cos(theta)+xtr;
	a_vertex_buffer_data[1]=r*sin(theta)+ytr;
	a_vertex_buffer_data[2]=0;
	
	a_vertex_buffer_data[3]=r+xtr;
	a_vertex_buffer_data[4]=0+ytr;
	a_vertex_buffer_data[5]=height;
	
	a_vertex_buffer_data[6]=r*cos(theta)+xtr;
	a_vertex_buffer_data[7]=r*sin(theta)+ytr;
	a_vertex_buffer_data[8]=height;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6]-xtr;
	prev[1]=g_vertex_buffer_data[7]-ytr;

    float prev2[2];
	prev2[0]=a_vertex_buffer_data[6]-xtr;
	prev2[1]=a_vertex_buffer_data[7]-ytr;

	for(int i=1;i<n;i++)
	{
		g_vertex_buffer_data[9*i]=prev2[0]+xtr;
		g_vertex_buffer_data[9*i+1]=prev2[1]+ytr;
		g_vertex_buffer_data[9*i+2]=height;
		
		g_vertex_buffer_data[9*i+3]=prev[0]+xtr;
		g_vertex_buffer_data[9*i+4]=prev[1]+ytr;
		g_vertex_buffer_data[9*i+5]=0;
		
		g_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta)+xtr;
		g_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta)+ytr;
		g_vertex_buffer_data[9*i+8]=0;

		prev[0]=g_vertex_buffer_data[9*i+6]-xtr;
		prev[1]=g_vertex_buffer_data[9*i+7]-ytr;
///////////////////////////////////////////////////////
        a_vertex_buffer_data[9*i]=g_vertex_buffer_data[9*i+6];
		a_vertex_buffer_data[9*i+1]=g_vertex_buffer_data[9*i+7];
		a_vertex_buffer_data[9*i+2]=0;
		
		a_vertex_buffer_data[9*i+3]=prev2[0]+xtr;
		a_vertex_buffer_data[9*i+4]=prev2[1]+ytr;
		a_vertex_buffer_data[9*i+5]=height;
		
		a_vertex_buffer_data[9*i+6]=prev2[0]*cos(theta)-prev2[1]*sin(theta)+xtr;
		a_vertex_buffer_data[9*i+7]=prev2[0]*sin(theta)+prev2[1]*cos(theta)+ytr;
		a_vertex_buffer_data[9*i+8]=height;

		prev2[0]=a_vertex_buffer_data[9*i+6]-xtr;
		prev2[1]=a_vertex_buffer_data[9*i+7]-ytr;
	}

    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);


float a=.2;//variable parameter
height=2;
float zz=4;//controls height from ground
GLfloat gg_vertex_buffer_data[9*n];
	GLfloat aa_vertex_buffer_data[9*n];
	//1st triangle
	gg_vertex_buffer_data[0]=r;
	gg_vertex_buffer_data[2]=0+zz;
	gg_vertex_buffer_data[1]=height;
	
	gg_vertex_buffer_data[3]=r;
	gg_vertex_buffer_data[5]=0+zz;
	gg_vertex_buffer_data[4]=0;
	
	gg_vertex_buffer_data[6]=r*cos(theta);
	gg_vertex_buffer_data[8]=r*sin(theta)+zz;
	gg_vertex_buffer_data[7]=0;
/////////////////////////////////////////////////
    aa_vertex_buffer_data[0]=r*cos(theta);
	aa_vertex_buffer_data[2]=r*sin(theta)+zz;
	aa_vertex_buffer_data[1]=0;
	
	aa_vertex_buffer_data[3]=r;
	aa_vertex_buffer_data[5]=0+zz;
	aa_vertex_buffer_data[4]=height;
	
	aa_vertex_buffer_data[6]=r*cos(theta);
	aa_vertex_buffer_data[8]=r*sin(theta)+zz;
	aa_vertex_buffer_data[7]=height;

	float prev3[2];
	prev3[0]=gg_vertex_buffer_data[6];
	prev3[1]=gg_vertex_buffer_data[8]-zz;

    float prev4[2];
	prev4[0]=aa_vertex_buffer_data[6];
	prev4[1]=aa_vertex_buffer_data[8]-zz;

	for(int i=1;i<n;i++)
	{
		gg_vertex_buffer_data[9*i]=prev4[0];
		gg_vertex_buffer_data[9*i+2]=prev4[1]+zz;
		gg_vertex_buffer_data[9*i+1]=height;
		
		gg_vertex_buffer_data[9*i+3]=prev3[0];
		gg_vertex_buffer_data[9*i+5]=prev3[1]+zz;
		gg_vertex_buffer_data[9*i+4]=0;
		
		gg_vertex_buffer_data[9*i+6]=prev3[0]*cos(theta)-prev3[1]*sin(theta);
		gg_vertex_buffer_data[9*i+8]=prev3[0]*sin(theta)+prev3[1]*cos(theta)+zz;
		gg_vertex_buffer_data[9*i+7]=0;

		prev3[0]=gg_vertex_buffer_data[9*i+6]+a;
		prev3[1]=gg_vertex_buffer_data[9*i+8]+a-zz;
///////////////////////////////////////////////////////
        aa_vertex_buffer_data[9*i]=gg_vertex_buffer_data[9*i+6];
		aa_vertex_buffer_data[9*i+2]=gg_vertex_buffer_data[9*i+7]+zz;
		aa_vertex_buffer_data[9*i+1]=0;
		
		aa_vertex_buffer_data[9*i+3]=prev4[0];
		aa_vertex_buffer_data[9*i+5]=prev4[1]+zz;
		aa_vertex_buffer_data[9*i+4]=height;
		
		aa_vertex_buffer_data[9*i+6]=prev4[0]*cos(theta)-prev4[1]*sin(theta);
		aa_vertex_buffer_data[9*i+8]=prev4[0]*sin(theta)+prev4[1]*cos(theta)+zz;
		aa_vertex_buffer_data[9*i+7]=height;

		prev4[0]=aa_vertex_buffer_data[9*i+6]+a;
		prev4[1]=aa_vertex_buffer_data[9*i+8]+a-zz;
	}

    this->object3 = create3DObject(GL_TRIANGLES, n*3, gg_vertex_buffer_data, COLOR_DDGREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, n*3, aa_vertex_buffer_data, COLOR_DGREEN, GL_FILL);





}

void Tree::draw(glm::mat4 VP) {
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

void Tree::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Tree::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

