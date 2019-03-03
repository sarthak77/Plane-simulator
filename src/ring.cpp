#include "ring.h"
#include "main.h"

#define pi 3.14159265358979323846264338327950288

Ring::Ring(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed=0.05;
    speedup = 0.1;
    speeddown = 0.025;
    

    int n=100;//n triangles
	float r=.5 ;
	float theta=(2*pi)/n;

	GLfloat g_vertex_buffer_data[9*n];

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
    this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, color, GL_FILL);

	
	GLfloat vertex_buffer_data[9*n];

    r=0.4;
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
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);



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