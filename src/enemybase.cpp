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



//body
    int n=40;//n triangles
	float r=6 ;
	float r2=1 ;
	float theta=(2*pi)/n;
    int height=1;
	GLfloat g_vertex_buffer_data[9*n];
	GLfloat aa_vertex_buffer_data[9*n];
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
    aa_vertex_buffer_data[0]=r*cos(theta);
	aa_vertex_buffer_data[1]=r*sin(theta);
	aa_vertex_buffer_data[2]=0;
	
	aa_vertex_buffer_data[3]=r2;
	aa_vertex_buffer_data[4]=0;
	aa_vertex_buffer_data[5]=height;
	
	aa_vertex_buffer_data[6]=r2*cos(theta);
	aa_vertex_buffer_data[7]=r2*sin(theta);
	aa_vertex_buffer_data[8]=height;

	float prev[2];
	prev[0]=g_vertex_buffer_data[6];
	prev[1]=g_vertex_buffer_data[7];

    float prev2[2];
	prev2[0]=aa_vertex_buffer_data[6];
	prev2[1]=aa_vertex_buffer_data[7];

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
        aa_vertex_buffer_data[9*i]=g_vertex_buffer_data[9*i+6];
		aa_vertex_buffer_data[9*i+1]=g_vertex_buffer_data[9*i+7];
		aa_vertex_buffer_data[9*i+2]=0;
		
		aa_vertex_buffer_data[9*i+3]=prev2[0];
		aa_vertex_buffer_data[9*i+4]=prev2[1];
		aa_vertex_buffer_data[9*i+5]=height;
		
		aa_vertex_buffer_data[9*i+6]=prev2[0]*cos(theta)-prev2[1]*sin(theta);
		aa_vertex_buffer_data[9*i+7]=prev2[0]*sin(theta)+prev2[1]*cos(theta);
		aa_vertex_buffer_data[9*i+8]=height;

		prev2[0]=aa_vertex_buffer_data[9*i+6];
		prev2[1]=aa_vertex_buffer_data[9*i+7];
	}

    this->object6 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_DBLACK, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, n*3, aa_vertex_buffer_data, COLOR_BLACK, GL_FILL);




}

void Enemybase::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale=glm::scale(glm::vec3(1,1,4));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
}

void Enemybase::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemybase::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

