#include "ring.h"
#include "main.h"

#define pi 3.14159265358979323846264338327950288

Ring::Ring(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed=0.05;
    speedup = 0.1;
    speeddown = 0.025;
    

    int n=40;//n triangles
	float r=5 ;
	float theta=(2*pi)/n;
    int height=1;

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

    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_DBLACK, GL_FILL);


}

void Ring::draw(glm::mat4 VP) {
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
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

//x is forward coming out of screen
void Ring::tick(int up) {
    //this->rotation += speed;
    //this->position.x += speed;
    
}


bounding_box_t Ring::bounding_box() {
    float x = this->position.x;
	float y= this->position.y;
    float w = .3;//r
	float h = .3;//r
    bounding_box_t bbox = { x,y,2*w,2*h };
    return bbox;
}