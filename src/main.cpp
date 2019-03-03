#include "main.h"
#include "timer.h"
#include "plane.h"
#include "indicator.h"
#include "powerup.h"
#include "arrow.h"
#include "island.h"
#include "water.h"
#include "ring.h"
#include "baloon.h"
#include "mbaloon.h"
#include "enemybase.h"
#include "boat.h"
#include "volcano.h"
#define GLM_ENABLE_EXPERIMENTAL
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
 * Customizable functions *
 **************************/

Plane plane1;
Water pani;
Arrow arr;

Indicator ind1,ind2,ind3,ind4;
vector<Island> vector_i;
vector<Baloon> vector_bal;
vector<Mbaloon> vector_mbal;
vector<Powerup> vector_pu;
vector<Ring> vector_ring;
vector<Volcano> vector_v;
vector<Enemybase> vector_eb;
vector<bool>dead;
vector<Boat> vector_boat;
vector<pair<int,int>> ebcor;

//enemybal
vector<Mbaloon> vector_enemybal;
vector<bool> enemyspawn;
Timer emt(2);
int enemyno=0;


//baloon
vector<bool> boon;
vector<bool> spawn;
int balno=-1;
bool bpress=false;
int maxbal=50;
Timer bt(2);

//mbaloon
vector<bool> mboon;
vector<bool> mspawn;
int mbalno=-1;
bool mbpress=false;
int mmaxbal=50;
Timer mbt(2);


int camview=3;
glm::vec3 tempeye = glm::vec3(50,50,60);//for tower view

double speed=100;
double altitude=100;
double fuel=100;
double health=100;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

float stop;   
float sbottom;   
float sleft;
float sright;   

Timer t60(1.0 / 60);
Timer t(1);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	if(camview==0)//plane view
	{
		target = glm::vec3(plane1.position.x, plane1.position.y,plane1.position.z);
		int d=20;
		glm::vec3 temp=glm::vec3(d*plane1.local_axis[1][0],d*plane1.local_axis[1][1],d*plane1.local_axis[1][2]);
		eye=target+temp;

		d=23;
		temp=glm::vec3(d*plane1.local_axis[1][0],d*plane1.local_axis[1][1],d*plane1.local_axis[1][2]);
		eye-=temp;
		target-=temp;
		up = glm::vec3(0,0,1);
	}
	else if(camview==1)//tower
	{
		double dist=glm::length(plane1.position-tempeye);
		//cout << dist << "\n\n";
		if(dist>100)
		{
			eye = glm::vec3(50+plane1.position.x,50+plane1.position.y,60);
			tempeye=eye;
		}
		else
			eye=tempeye;

		target = glm::vec3(plane1.position.x, plane1.position.y,plane1.position.z);
		up = glm::vec3(0,0,1);
	}
	else if (camview==2)//top
	{
		eye  = glm::vec3(plane1.position.x, plane1.position.y, plane1.position.z+40);
		target = glm::vec3 (plane1.position.x,plane1.position.y,plane1.position.z);
		up = glm::vec3 (0, -1, 0);
	}
	else if (camview==3)//back
	{
		target = glm::vec3(plane1.position.x, plane1.position.y,plane1.position.z);
		int d=20;
		glm::vec3 temp=glm::vec3(d*plane1.local_axis[1][0],d*plane1.local_axis[1][1],d*plane1.local_axis[1][2]);
		eye=target+temp;
		eye.z+=5;
		up = glm::vec3(0,0,1);
	}




	Matrices.view = glm::lookAt(eye,target,up);


	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	plane1.draw(VP);
	pani.draw(VP);
	arr.draw(VP);

	if(camview==3)
	{
		//speed   
		ind1.draw(VP,glm::vec3(plane1.position.x,plane1.position.y,plane1.position.z));
		
		//health
		ind2.draw(VP,glm::vec3(stop,sright,plane1.position.z));
		
		//fuel
		//ind3.draw(VP);
		
		//height
		//ind4.draw(VP);
	}

	for(int i=0;i<vector_i.size();i++)
		vector_i[i].draw(VP);

	for(int i=0;i<vector_v.size();i++)
		vector_v[i].draw(VP);

	for(int i=0;i<vector_eb.size();i++)
		vector_eb[i].draw(VP);

	for(int i=0;i<vector_boat.size();i++)
		vector_boat[i].draw(VP);

	for(int i=0;i<vector_pu.size();i++)
		vector_pu[i].draw(VP);

	for(int i=0;i<vector_ring.size();i++)
		vector_ring[i].draw(VP);

	//baloons
	if(bpress && boon[balno])
	{
		if(spawn[balno])
		{
			vector_bal[balno].draw(VP,plane1.position.x,plane1.position.y,plane1.position.z-1);//1=radius
			spawn[balno]=false;
		}
		else
		{
			vector_bal[balno].draw(VP,vector_bal[balno].position.x,vector_bal[balno].position.y,vector_bal[balno].position.z);
		}
	}
	//mbaloons
	if(mbpress && mboon[mbalno])
	{
		if(mspawn[mbalno])
		{
			vector_mbal[mbalno].draw(VP,plane1.position.x,plane1.position.y,plane1.position.z-1);//1=radius
			mspawn[mbalno]=false;
		}
		else
		{
			vector_mbal[mbalno].draw(VP,vector_mbal[mbalno].position.x,vector_mbal[mbalno].position.y,vector_mbal[mbalno].position.z);
		}
	}


	//enemies throwing rockets
	for(int i=enemyno*100;i<enemyno*100+100;i++)
	{
		if(enemyspawn[i] && emt.processTick())
		{
			//setting arrow
			arr.position=vector_eb[enemyno].position;
			arr.position.z=plane1.position.z;

			vector_enemybal[i].draw(VP,vector_eb[enemyno].position.x,vector_eb[enemyno].position.y,0);
			vector_enemybal[i+1].draw(VP,vector_eb[enemyno].position.x+12,vector_eb[enemyno].position.y+12,0);
			enemyspawn[i]=false;
		}
		else if(!enemyspawn[i])
		{
			vector_enemybal[i].draw(VP,vector_enemybal[i].position.x,vector_enemybal[i].position.y,vector_enemybal[i].position.z);
			vector_enemybal[i+1].draw(VP,vector_enemybal[i+1].position.x,vector_enemybal[i+1].position.y,vector_enemybal[i+1].position.z);

			//velocity
			vector_enemybal[i].velocity=plane1.position-vector_enemybal[i].position;
			float len=glm::length(vector_enemybal[i].velocity)/10;
			vector_enemybal[i].velocity/=len;

			vector_enemybal[i+1].velocity=plane1.position-vector_enemybal[i+1].position;
			len=glm::length(vector_enemybal[i+1].velocity)/10;
			vector_enemybal[i+1].velocity/=len;

		}
		i++;
	}
}

void tick_input(GLFWwindow *window) {
	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int up  = glfwGetKey(window, GLFW_KEY_UP);
	int down  = glfwGetKey(window, GLFW_KEY_DOWN);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int space = glfwGetKey(window, GLFW_KEY_SPACE);

	int w = glfwGetKey(window, GLFW_KEY_W);
	int s = glfwGetKey(window, GLFW_KEY_S);
	int d = glfwGetKey(window, GLFW_KEY_D);
	int a = glfwGetKey(window, GLFW_KEY_A);
	int v = glfwGetKey(window, GLFW_KEY_V);
	int b = glfwGetKey(window, GLFW_KEY_B);
	int g = glfwGetKey(window, GLFW_KEY_G);


	if (left) {
		plane1.left();
	}
	if(right)
	{
		plane1.right();
	}
	if(up)
	{
		plane1.forward();
	}
	if(down)
	{
		plane1.backward();
	}
	if(w)
	{
		plane1.pitchup();
	}
	if(s)
	{
		plane1.pitchdown();
	}
	if(d)
	{
		plane1.tiltright();
	}
	if(a)
	{
		plane1.tiltleft();
	}
	if(v && t.processTick())
	{
		camview++;
		camview=camview%4;
	}
	if(space)
	{
		plane1.position.z+=.3;
		if(plane1.position.z>60)
			plane1.position.z=60;
	}
	if(b && bt.processTick()){
		bpress=true;
		if(balno<maxbal-1)
		{
			balno++;
			boon[balno]=true;
			spawn[balno]=true;
		}
	}
	if(g && mbt.processTick()){
		mbpress=true;
		if(mbalno<mmaxbal-1)
		{
			mbalno++;
			mboon[mbalno]=true;
			mspawn[mbalno]=true;
		}
	}
}

void tick_elements() {
	plane1.tick();
	arr.tick();

	ind1.tick(5);
	ind2.tick(5);
	ind3.tick(5);
	ind4.tick(5);
	//camera_rotation_angle += 1;

	//water ballons
	if(bpress && boon[balno] && !spawn[balno])
		vector_bal[balno].tick(0);

	//water ballons
	if(mbpress && mboon[mbalno] && !mspawn[mbalno])
		vector_mbal[mbalno].tick(0);

	for(int i=0;i<vector_enemybal.size();i++)
	{
		vector_enemybal[i].tick(0);
	}
}

void collide(){

	//volcano
	for(int i=0;i<vector_v.size();i++)
	{
		if(colision(plane1.position,vector_v[i].position,7))
			cout << "wddede\n\n";
	}

	if(plane1.position.z<.5)
		quit(window);

	//powerup
	for(int i=0;i<vector_pu.size();i++)
	{
		if(colision(plane1.position,vector_pu[i].position,2))
		{
			if(vector_pu[i].flag==0)
				health+=10;
			else
				fuel+=10;

			if(fuel>100)
				fuel=100;
			if(health>100)
				health=100;

			auto it=vector_pu.begin();
			vector_pu.erase(it+i);
		}
	}

	//boats
	for(int i=0;i<vector_boat.size();i++)
	{
		if(colision(vector_bal[balno].position,vector_boat[i].position,4) || colision(vector_mbal[mbalno].position,vector_boat[i].position,4) )
		{
			auto it=vector_boat.begin();
			vector_boat.erase(it+i);
		}
	}

	//enemies
	for(int i=0;i<vector_eb.size();i++)
	{
		if(colision(vector_bal[balno].position,vector_eb[i].position,4) || colision(vector_mbal[mbalno].position,vector_eb[i].position,4) )
		{
			dead[i]=true;
			auto it=vector_eb.begin();
			vector_eb.erase(it+i);
		}
	}

	//plane and enemies
	for(int i=enemyno*100;i<enemyno*100+100;i++)
	{
		if(colision(vector_enemybal[i].position,plane1.position,3))
		{
			health--;
			auto it=vector_enemybal.begin();
			vector_enemybal.erase(i+it);
		}
	}
}

void checkpointcheck()
{
	if(dead[enemyno])
		enemyno++;
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models

	plane1       = Plane(0,0,20);
	arr          = Arrow(0,0,40,COLOR_ARR);
	pani         = Water(0,0,-1,COLOR_WATER);
	ind1         = Indicator(sleft,100,5,COLOR_GREEN,1);//speed
	ind2         = Indicator(sleft,-3,5,COLOR_RED,1);//health
	ind3         = Indicator(sleft,100,0,COLOR_GOLDEN,1);//fuel
	ind4         = Indicator(sleft,100,0,COLOR_GREEN,1);//height

	int rx=-300;
	int ry=30;
	int rz=-300;
	while(rx<300)
	{
		Ring ring;
		ring=Ring(rx,ry,rz,COLOR_BLACK);
		vector_ring.push_back(ring);
		rx+=rand()%20+20;
		rz+=rand()%20+20;
		ry+=rand()%5;
	}


	//islands,volcanos,enemybases,boats
	int yi=10;
	for(int j=0;j<10;j++)
	{
		int xi=15;
		for(int i=0;i<10;i++)
		{

			Island isl;

			isl=Island(xi,yi,0,COLOR_GREEN);
			vector_i.push_back(isl);

			if(rand()%10==1)
			{
				Volcano vol;
				vol=Volcano(xi,yi,0);
				vector_v.push_back(vol);
			}

			else if(rand()%10==2)
				ebcor.push_back(make_pair(xi,yi));

			else if(rand()%4==3)
			{
				Powerup pu;
				pu=Powerup(xi,yi,0,rand()%2);
				vector_pu.push_back(pu);
			}


			isl=Island(-xi,yi,0,COLOR_GREEN);
			vector_i.push_back(isl);

			if(rand()%10==1)
			{
				Volcano vol;
				vol=Volcano(-xi,yi,0);
				vector_v.push_back(vol);
			}
			else if(rand()%10==2)
				ebcor.push_back(make_pair(-xi,yi));

			else if(rand()%4==3)
			{
				Powerup pu;
				pu=Powerup(-xi,yi,0,rand()%2);
				vector_pu.push_back(pu);
			}

			xi+=rand()%20+20;
		}
		xi=15;
		for(int i=0;i<10;i++)
		{
			Island isl;
			isl=Island(xi,-yi,0,COLOR_GREEN);
			vector_i.push_back(isl);

			if(rand()%10==1)
			{
				Volcano vol;
				vol=Volcano(xi,-yi,0);
				vector_v.push_back(vol);
			}
			else if(rand()%10==2)
				ebcor.push_back(make_pair(xi,-yi));

			else if(rand()%4==3)
			{
				Powerup pu;
				pu=Powerup(xi,-yi,0,rand()%2);
				vector_pu.push_back(pu);
			}

			isl=Island(-xi,-yi,0,COLOR_GREEN);
			vector_i.push_back(isl);

			if(rand()%10==1)
			{
				Volcano vol;
				vol=Volcano(-xi,-yi,0);
				vector_v.push_back(vol);
			}
			else if(rand()%10==2)
				ebcor.push_back(make_pair(-xi,-yi));

			else if(rand()%4==3)
			{
				Powerup pu;
				pu=Powerup(-xi,-yi,0,rand()%2);
				vector_pu.push_back(pu);
			}

			xi+=rand()%20+20;
		}
		yi+=rand()%20+20;
	}

	for(int i=0;i<ebcor.size();i++)
	{
		Enemybase eb;
		eb=Enemybase(ebcor[i].first,ebcor[i].second,0,COLOR_BUILDING);
		vector_eb.push_back(eb);
		dead.push_back(false);
	}

	for(int i=0;i<ebcor.size();i++)
	{
		Boat boat;
		boat=Boat(ebcor[i].first+12,ebcor[i].second+12,0,COLOR_BUILDING);
		vector_boat.push_back(boat);
	}

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	//color of the scene
	glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
	srand(time(0));
	int width  = 600;
	int height = 600;


	window = initGLFW(width, height);

	initGL (window, width, height);

	//50 baloons
	for(int i=0;i<maxbal;i++)
	{
		Baloon bal;
		bal=Baloon(0,0,0);
		vector_bal.push_back(bal);
		boon.push_back(false);
		spawn.push_back(false);
	}
	//50 mbaloons
	for(int i=0;i<mmaxbal;i++)
	{
		Mbaloon mbal;
		mbal=Mbaloon(0,0,0);
		vector_mbal.push_back(mbal);
		mboon.push_back(false);
		mspawn.push_back(false);
	}

	//enemyball
	for(int i=0;i<1000;i++)
	{
		Mbaloon mbal;
		mbal=Mbaloon(0,0,0);
		vector_enemybal.push_back(mbal);
		enemyspawn.push_back(true);
	}


	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// Process timers
		fuel-=.00001;
		//cout << fuel << "\n";
		//cout << health << "\n";
		//cout << camview << "\n";
		cout << glm::length(plane1.position-arr.position) << "\n";  

		//cout << vector_eb[enemyno].position.x << " " << vector_eb[enemyno].position.y << " " << vector_eb[enemyno].position.z << "\n";
		//cout << plane1.position.x << " " << plane1.position.y << " " << plane1.position.z << "\n";

		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands

			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();
			collide();
			checkpointcheck();
			tick_input(window);
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool colision(glm::vec3 v1,glm::vec3 v2,float distance){
	distance=distance*distance;
	float temp=(v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z);
	if(temp>distance)
		return(false);
	else
		return(true);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
		(abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
	stop    = screen_center_y + 4 / screen_zoom;
	sbottom = screen_center_y - 4 / screen_zoom;
	sleft   = screen_center_x - 4 / screen_zoom;
	sright  = screen_center_x + 4 / screen_zoom;
	Matrices.projection = glm::perspective(glm::radians(45.0f),4.0f/3.0f,0.1f,100.0f);
	//change it    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
