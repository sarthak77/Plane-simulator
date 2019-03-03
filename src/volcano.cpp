#include "volcano.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

//body
    int n=40;//n triangles
	float r=4 ;
	float r2=1 ;
	float theta=(2*pi)/n;
    int height=6;
	GLfloat g_vertex_buffer_data[9*n];
	GLfloat a_vertex_buffer_data[9*n];
	//1st triangle
	g_vertex_buffer_data[0]=r2;
	g_vertex_buffer_data[1]=0;
	g_vertex_buffer_data[2]=height;
	
	g_vertex_buffer_data[3]=r;
	g_vertex_buffer_data[4]=0;
	g_vertex_buffer_data[5]=0;
	
	g_vertex_buffer_data[6]=r*cos(theta);
	g_vertex_buffer_data[7]=r*sin(theta);
	g_vertex_buffer_data[8]=0;
/////////////////////////////////////////////////
    a_vertex_buffer_data[0]=r*cos(theta);
	a_vertex_buffer_data[1]=r*sin(theta);
	a_vertex_buffer_data[2]=0;
	
	a_vertex_buffer_data[3]=r2;
	a_vertex_buffer_data[4]=0;
	a_vertex_buffer_data[5]=height;
	
	a_vertex_buffer_data[6]=r2*cos(theta);
	a_vertex_buffer_data[7]=r2*sin(theta);
	a_vertex_buffer_data[8]=height;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6];
	prev[1]=g_vertex_buffer_data[7];

    float prev2[2];
	prev2[0]=a_vertex_buffer_data[6];
	prev2[1]=a_vertex_buffer_data[7];

	for(int i=1;i<n;i++)
	{
		g_vertex_buffer_data[9*i]=prev2[0];
		g_vertex_buffer_data[9*i+1]=prev2[1];
		g_vertex_buffer_data[9*i+2]=height;
		
		g_vertex_buffer_data[9*i+3]=prev[0];
		g_vertex_buffer_data[9*i+4]=prev[1];
		g_vertex_buffer_data[9*i+5]=0;
		
		g_vertex_buffer_data[9*i+6]=prev[0]*cos(theta)-prev[1]*sin(theta);
		g_vertex_buffer_data[9*i+7]=prev[0]*sin(theta)+prev[1]*cos(theta);
		g_vertex_buffer_data[9*i+8]=0;

		prev[0]=g_vertex_buffer_data[9*i+6];
		prev[1]=g_vertex_buffer_data[9*i+7];
///////////////////////////////////////////////////////
        a_vertex_buffer_data[9*i]=g_vertex_buffer_data[9*i+6];
		a_vertex_buffer_data[9*i+1]=g_vertex_buffer_data[9*i+7];
		a_vertex_buffer_data[9*i+2]=0;
		
		a_vertex_buffer_data[9*i+3]=prev2[0];
		a_vertex_buffer_data[9*i+4]=prev2[1];
		a_vertex_buffer_data[9*i+5]=height;
		
		a_vertex_buffer_data[9*i+6]=prev2[0]*cos(theta)-prev2[1]*sin(theta);
		a_vertex_buffer_data[9*i+7]=prev2[0]*sin(theta)+prev2[1]*cos(theta);
		a_vertex_buffer_data[9*i+8]=height;

		prev2[0]=a_vertex_buffer_data[9*i+6];
		prev2[1]=a_vertex_buffer_data[9*i+7];
	}

    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);

	GLfloat vertex_buffer_data[9*n];

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

    int i;
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
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_FIRE, GL_FILL);



}

void Volcano::draw(glm::mat4 VP) {
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
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

