#include "para.h"
#include "main.h"
#define pi 3.14159265358979323846264338327950288

Para::Para(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
	this->rotation = -90;



	int n=40;//n triangles
	float r=.7 ;
	float theta=(2*pi)/n;
	float height=6;
	float xtr=-1; 
	float ytr=1; 
	float a=1;
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

		prev[0]=a+g_vertex_buffer_data[9*i+6]-xtr;
		prev[1]=a+g_vertex_buffer_data[9*i+7]-ytr;
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

		prev2[0]=a+a_vertex_buffer_data[9*i+6]-xtr;
		prev2[1]=a+a_vertex_buffer_data[9*i+7]-ytr;
	}

	this->object1 = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_BROWN, GL_FILL);
	this->object2 = create3DObject(GL_TRIANGLES, n*3, a_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);



	GLfloat gg_vertex_buffer_data[9*n];
	GLfloat aa_vertex_buffer_data[9*n];

	height=10;
	xtr=-3;
	ytr=3;
	float ztr=18;
	//1st triangle
	gg_vertex_buffer_data[0]=r+xtr;
	gg_vertex_buffer_data[2]=0+ytr;
	gg_vertex_buffer_data[1]=height+ztr;

	gg_vertex_buffer_data[3]=r+xtr;
	gg_vertex_buffer_data[5]=0+ytr;
	gg_vertex_buffer_data[4]=0+ztr;

	gg_vertex_buffer_data[6]=r*cos(theta)+xtr;
	gg_vertex_buffer_data[8]=r*sin(theta)+ytr;
	gg_vertex_buffer_data[7]=0+ztr;
	/////////////////////////////////////////////////
	aa_vertex_buffer_data[0]=r*cos(theta)+xtr;
	aa_vertex_buffer_data[2]=r*sin(theta)+ytr;
	aa_vertex_buffer_data[1]=0+ztr;

	aa_vertex_buffer_data[3]=r+xtr;
	aa_vertex_buffer_data[5]=0+ytr;
	aa_vertex_buffer_data[4]=height+ztr;

	aa_vertex_buffer_data[6]=r*cos(theta)+xtr;
	aa_vertex_buffer_data[8]=r*sin(theta)+ytr;
	aa_vertex_buffer_data[7]=height+ztr;

	float prev1[2];
	prev1[0]=gg_vertex_buffer_data[6]-xtr;
	prev1[1]=gg_vertex_buffer_data[8]-ytr;

	float prev3[2];
	prev3[0]=aa_vertex_buffer_data[6]-xtr;
	prev3[1]=aa_vertex_buffer_data[8]-ytr;

	for(int i=1;i<n;i++)
	{
		gg_vertex_buffer_data[9*i]=prev3[0]+xtr;
		gg_vertex_buffer_data[9*i+2]=prev3[1]+ytr;
		gg_vertex_buffer_data[9*i+1]=height+ztr;

		gg_vertex_buffer_data[9*i+3]=prev1[0]+xtr;
		gg_vertex_buffer_data[9*i+5]=prev1[1]+ytr;
		gg_vertex_buffer_data[9*i+4]=0+ztr;

		gg_vertex_buffer_data[9*i+6]=prev1[0]*cos(theta)-prev1[1]*sin(theta)+xtr;
		gg_vertex_buffer_data[9*i+8]=prev1[0]*sin(theta)+prev1[1]*cos(theta)+ytr;
		gg_vertex_buffer_data[9*i+7]=0+ztr;

		prev1[0]=gg_vertex_buffer_data[9*i+6]-xtr;
		prev1[1]=gg_vertex_buffer_data[9*i+8]-ytr;
		///////////////////////////////////////////////////////
		aa_vertex_buffer_data[9*i]=gg_vertex_buffer_data[9*i+6];
		aa_vertex_buffer_data[9*i+2]=gg_vertex_buffer_data[9*i+8];
		aa_vertex_buffer_data[9*i+1]=0+ztr;

		aa_vertex_buffer_data[9*i+3]=prev3[0]+xtr;
		aa_vertex_buffer_data[9*i+5]=prev3[1]+ytr;
		aa_vertex_buffer_data[9*i+4]=height+ztr;

		aa_vertex_buffer_data[9*i+6]=prev3[0]*cos(theta)-prev3[1]*sin(theta)+xtr;
		aa_vertex_buffer_data[9*i+8]=prev3[0]*sin(theta)+prev3[1]*cos(theta)+ytr;
		aa_vertex_buffer_data[9*i+7]=height+ztr;

		prev3[0]=aa_vertex_buffer_data[9*i+6]-xtr;
		prev3[1]=aa_vertex_buffer_data[9*i+8]-ytr;
	}

	this->object3 = create3DObject(GL_TRIANGLES, n*3, gg_vertex_buffer_data, COLOR_BROWN, GL_FILL);
	this->object4 = create3DObject(GL_TRIANGLES, n*3, aa_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);

	xtr=-10;
	GLfloat ggg_vertex_buffer_data[9*n];
	GLfloat aaa_vertex_buffer_data[9*n];

	ggg_vertex_buffer_data[0]=r+xtr;
	ggg_vertex_buffer_data[2]=0+ytr;
	ggg_vertex_buffer_data[1]=height+ztr;

	ggg_vertex_buffer_data[3]=r+xtr;
	ggg_vertex_buffer_data[5]=0+ytr;
	ggg_vertex_buffer_data[4]=0+ztr;

	ggg_vertex_buffer_data[6]=r*cos(theta)+xtr;
	ggg_vertex_buffer_data[8]=r*sin(theta)+ytr;
	ggg_vertex_buffer_data[7]=0+ztr;
	/////////////////////////////////////////////////
	aaa_vertex_buffer_data[0]=r*cos(theta)+xtr;
	aaa_vertex_buffer_data[2]=r*sin(theta)+ytr;
	aaa_vertex_buffer_data[1]=0+ztr;

	aaa_vertex_buffer_data[3]=r+xtr;
	aaa_vertex_buffer_data[5]=0+ytr;
	aaa_vertex_buffer_data[4]=height+ztr;

	aaa_vertex_buffer_data[6]=r*cos(theta)+xtr;
	aaa_vertex_buffer_data[8]=r*sin(theta)+ytr;
	aaa_vertex_buffer_data[7]=height+ztr;

	float prev5[2];
	prev5[0]=ggg_vertex_buffer_data[6]-xtr;
	prev5[1]=ggg_vertex_buffer_data[8]-ytr;

	float prev4[2];
	prev4[0]=aaa_vertex_buffer_data[6]-xtr;
	prev4[1]=aaa_vertex_buffer_data[8]-ytr;

	for(int i=1;i<n;i++)
	{
		ggg_vertex_buffer_data[9*i]=prev4[0]+xtr;
		ggg_vertex_buffer_data[9*i+2]=prev4[1]+ytr;
		ggg_vertex_buffer_data[9*i+1]=height+ztr;

		ggg_vertex_buffer_data[9*i+3]=prev5[0]+xtr;
		ggg_vertex_buffer_data[9*i+5]=prev5[1]+ytr;
		ggg_vertex_buffer_data[9*i+4]=0+ztr;

		ggg_vertex_buffer_data[9*i+6]=prev5[0]*cos(theta)-prev5[1]*sin(theta)+xtr;
		ggg_vertex_buffer_data[9*i+8]=prev5[0]*sin(theta)+prev5[1]*cos(theta)+ytr;
		ggg_vertex_buffer_data[9*i+7]=0+ztr;

		prev5[0]=ggg_vertex_buffer_data[9*i+6]-xtr;
		prev5[1]=ggg_vertex_buffer_data[9*i+8]-ytr;
		///////////////////////////////////////////////////////
		aaa_vertex_buffer_data[9*i]=ggg_vertex_buffer_data[9*i+6];
		aaa_vertex_buffer_data[9*i+2]=ggg_vertex_buffer_data[9*i+8];
		aaa_vertex_buffer_data[9*i+1]=0+ztr;

		aaa_vertex_buffer_data[9*i+3]=prev4[0]+xtr;
		aaa_vertex_buffer_data[9*i+5]=prev4[1]+ytr;
		aaa_vertex_buffer_data[9*i+4]=height+ztr;

		aaa_vertex_buffer_data[9*i+6]=prev4[0]*cos(theta)-prev4[1]*sin(theta)+xtr;
		aaa_vertex_buffer_data[9*i+8]=prev4[0]*sin(theta)+prev4[1]*cos(theta)+ytr;
		aaa_vertex_buffer_data[9*i+7]=height+ztr;

		prev4[0]=aaa_vertex_buffer_data[9*i+6]-xtr;
		prev4[1]=aaa_vertex_buffer_data[9*i+8]-ytr;
	}

	this->object5 = create3DObject(GL_TRIANGLES, n*3, ggg_vertex_buffer_data, COLOR_BROWN, GL_FILL);
	this->object6 = create3DObject(GL_TRIANGLES, n*3, aaa_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);





	GLfloat vertex_buffer_data[] = {
		//face
		0,0,0,//extreme ends are 4 and -4
		0,-.4,0,
		-.4,0,0,

		0,-.4,0,
		-.4,0,0,
		-.4,-.4,0,

		//glares
		-.4,-.2,0,
		-.4,-.35,0,
		-.25,-.2,0,

		-.25,-.35,0,
		-.4,-.35,0,
		-.25,-.2,0,


		//hair

		-.4,-.4,0,
		0,-.4,0,
		0,-.5,0,

		-.4,-.4,0,
		-.4,-.5,0,
		-.5,-.5,0,

		-.4,-.4,0,
		-.4,-.5,0,
		0,-.5,0,

		.1,-.5,0,
		0,-.5,0,
		0,-.1,0,

		0,-.1,0,
		.1,-.5,0,
		.1,-.1,0,

		0,0,0,
		0,-.1,0,
		.1,-.1,0,

		//rocket
		0,0,0,
		.1,-.1,0,
		.2,0,0,

		0,0,0,
		0,.5,0,
		.2,0,0,//

		.2,.5,0,//
		0,0,0,
		.2,0,0,

		//lower body

		0,.4,0,
		0,0,0,
		-.3,.4,0,

		-.3,.4,0,
		0,0,0,
		-.3,0,0,

		//shoes

		0,.4,0,
		0,.5,0,
		-0.4,.5,0,

		-.3,.5,0,
		0,.4,0,
		-.3,.4,0,

		-.3,.4,0,
		-.3,.5,0,
		-.4,.5,0
	};

	for(int i=0;i<18*9;i++)
	{
		vertex_buffer_data[i]*=7;
		if(i%3==0)
		{
			vertex_buffer_data[i]-=5;
		}
		if(i%3==1)
		{
			vertex_buffer_data[i]+=30;
		}
		if(i%3==2)
		{
			vertex_buffer_data[i]+=3;
		}

	}
	this->object7 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_SKIN, GL_FILL);
	this->object12 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+2*9, COLOR_BLACK, GL_FILL);
	this->object8 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data+4*9, COLOR_BROWN, GL_FILL);
	this->object9 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data+10*9, COLOR_BLACK, GL_FILL);
	this->object10 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+13*9, COLOR_BLUE, GL_FILL);
	this->object11 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data+15*9, COLOR_RED, GL_FILL);


	GLfloat aaaa_vertex_buffer_data[] = {
		0,.5,0,
		.2,.5,0,
		.1,.25,0,

		0,.5,0,
		.2,.5,0,
		.1,.75,0


	} ;

	for(int i=0;i<18*9;i++)
	{
		aaaa_vertex_buffer_data[i]*=5;
		if(i%3==0)
		{
			aaaa_vertex_buffer_data[i]-=5;
		}
		if(i%3==1)
		{
			aaaa_vertex_buffer_data[i]+=30;
		}
		if(i%3==2)
		{
			aaaa_vertex_buffer_data[i]+=3;
		}
	}
	this->object13 = create3DObject(GL_TRIANGLES, 2*3, aaaa_vertex_buffer_data, COLOR_FIRE, GL_FILL);


	GLfloat gggg_vertex_buffer_data[9*n];

	//1st triangle
	gggg_vertex_buffer_data[0]=0;
	gggg_vertex_buffer_data[1]=0;
	gggg_vertex_buffer_data[2]=0;

	gggg_vertex_buffer_data[3]=r;
	gggg_vertex_buffer_data[4]=0;
	gggg_vertex_buffer_data[5]=0;

	gggg_vertex_buffer_data[6]=r*cos(theta);
	gggg_vertex_buffer_data[7]=r*sin(theta);
	gggg_vertex_buffer_data[8]=0;

	float prev6[2];
	prev6[0]=gggg_vertex_buffer_data[6];
	prev6[1]=gggg_vertex_buffer_data[7];

	for(int i=1;i<n;i++)
	{
		gggg_vertex_buffer_data[9*i]=0;
		gggg_vertex_buffer_data[9*i+1]=0;
		gggg_vertex_buffer_data[9*i+2]=0;

		gggg_vertex_buffer_data[9*i+3]=prev6[0];
		gggg_vertex_buffer_data[9*i+4]=prev6[1];
		gggg_vertex_buffer_data[9*i+5]=0;

		gggg_vertex_buffer_data[9*i+6]=prev6[0]*cos(theta)-prev6[1]*sin(theta);
		gggg_vertex_buffer_data[9*i+7]=prev6[0]*sin(theta)+prev6[1]*cos(theta);
		gggg_vertex_buffer_data[9*i+8]=0;

		prev6[0]=gggg_vertex_buffer_data[9*i+6];
		prev6[1]=gggg_vertex_buffer_data[9*i+7];
	}

	for(int i=0;i<n*9;i++)
	{
		gggg_vertex_buffer_data[i]*=12;
		if(i%3==0)
		{
			gggg_vertex_buffer_data[i]-=7;
		}
		if(i%3==1)
		{
			gggg_vertex_buffer_data[i]+=8;
		}
		if(i%3==2)
		{
			gggg_vertex_buffer_data[i]+=3;
		}
	}
	this->object14 = create3DObject(GL_TRIANGLES, n*3, gggg_vertex_buffer_data, COLOR_VOLCANO, GL_FILL);



}

void Para::draw(glm::mat4 VP) {
	float d=.3;
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 scale = glm::scale(glm::vec3(d,d,d));
	glm::mat4 translate = glm::translate (this->position+glm::vec3(0,0,50));    // glTranslatef
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
	draw3DObject(this->object8);
	draw3DObject(this->object9);
	draw3DObject(this->object10);
	draw3DObject(this->object11);
	draw3DObject(this->object12);
	draw3DObject(this->object13);
	draw3DObject(this->object14);
}

void Para::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

void Para::tick() {
	// this->rotation += 1;
}

