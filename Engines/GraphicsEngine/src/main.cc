#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GrE_Camera.hh"
#include "GrE_Item.hh"
#include "GrE_Player.hh"
#include "GrE_Weapon.hh"
#include "GrE_Gun.hh"
#include "GrE_PowerUp.hh"
#include "GrE_Particule.hh"
#include "GrE_Loader.hh"
#include "GrE_Level.hh"
#include "Vector3f.hh"

#include <iostream>
#include <vector>


#include <chrono>
#include <ctime>   

void drawMap(float att_size) {
	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	bool b2=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);	//turn off lighting, when making the map
//	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glColor3f(0,1,1);
		glVertex3f(att_size/2,att_size/2,att_size/2);	//and a vertex
		glColor3f(1,0,1);
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glColor3f(1,1,0);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
		glColor3f(1,0,0);
		glVertex3f(att_size/2,-att_size/2,att_size/2);
	glEnd();
	glColor3f(0,1,1);
	glBegin(GL_QUADS);	
		//left face
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_QUADS);	
		//front face
		glVertex3f(att_size/2,att_size/2,-att_size/2);
		glColor3f(1,0,0);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glColor3f(1,0,1);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glColor3f(1,1,0);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
		glColor3f(0,1,1);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);	
		//right face
		glVertex3f(att_size/2,att_size/2,-att_size/2);
		glVertex3f(att_size/2,att_size/2,att_size/2);
		glVertex3f(att_size/2,-att_size/2,att_size/2);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
	glEnd();
	glColor3f(1,0,1);
	glBegin(GL_QUADS);			//top face
		glVertex3f(att_size/2,att_size/2,att_size/2);
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glVertex3f(att_size/2,att_size/2,-att_size/2);
	glEnd();
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
		//bottom face
		glVertex3f(att_size/2,-att_size/2,att_size/2);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
	if(b2)
		glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
	//	std::cout << "called" << std::endl;
}
/*
GLuint loadTexture(const char *file) {
	SDL_Surface* img=SDL_LoadBMP(file);	//load the bmp image
	if (!img)
		std :: cout << "Img loading failed: " << IMG_GetError() << std :: endl;
	GLuint num;
	glGenTextures(1,&num);	//we generate a unique id
	glBindTexture(GL_TEXTURE_2D,num);	//Whenever we call this texture, these modifications will be called
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Deal with texture being too small
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same with texture being too large
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id

}
*/
int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std :: cerr << "Failed initialising SDL: " << SDL_GetError() << std :: endl;
		throw "Failed initialising \n";
	}
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	int myFPS = displayMode.refresh_rate;

	SDL_Window *window;
	if (!(window = SDL_CreateWindow("tryGame", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL))) {
		std :: cerr << "Failed creating window: " << SDL_GetError() << std :: endl;
		throw "Failed creating window \n";
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
//	SDL_GL_SetSwapInterval(1); //Buffer swap synchronized with monitor's vertical refresh
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.777778f, 0.1f, 400.0f); //Angle, width/height, how close you can see, how far
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
/*
	glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_EXP); //By default it's EXP. Possibilities: GL_LINEAR, GL_EXP, GL_EXP2
		glFogf(GL_FOG_DENSITY, 0.1f); //To make the fog go slower
//EXP is SO BAD, doesn't let you chose the distances
*/
/*
	glEnable(GL_NORMALIZE);
	glFogi(GL_FOG_MODE, GL_LINEAR); //By default it's EXP. Possibilities: GL_LINEAR, GL_EXP, GL_EXP2
	glFogf(GL_FOG_START, 30.f); //Beginning position of the fog
	glFogf(GL_FOG_END, 100.f); //End distance
	{
		GLfloat tmp[4] {0.4f, 0.4f, 0.4f, 1.f}; //Create a color
		//Last float: Not so sure
		glFogfv(GL_FOG_COLOR, tmp); //Fog color
		//Need to clear color with same color as fog
	}
//Decent fog, but I don't like it so much
*/
/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

	glEnable(GL_LIGHTING);	//Requires to have normals on every shape, may be too much a bother
	glEnable(GL_LIGHT0); 	//Some lighting
	float light_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
							//Modify Light0, positionning it there, lighting everywhere?
	float light_diff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
							//White color
	float light_amb[] = {0.6f, 0.6f, 0.6f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
							//Ambient light
	glEnable(GL_COLOR_MATERIAL);
			//Need to change the GL_LIGHT0 param every single time ?



	std :: vector <GLuint> myBackGround;
	myBackGround.emplace_back(glGenLists(1));
	{
		glNewList(myBackGround[0], GL_COMPILE);
		glColor3f(0,1,0);
	    glBegin(GL_QUADS); //Back face
	    glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f + 5.f);
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f + 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f + 5.f);
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f + 5.f);
		glEnd();

		glBegin(GL_QUADS); //Right face
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f + 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f + 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f - 5.f);
		glEnd();

		glBegin(GL_QUADS); //Front face
		glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f - 5.f);
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f - 5.f);
		glEnd();

		glBegin(GL_QUADS); //Left face
		glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f + 5.f);
		glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f - 5.f);
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f - 5.f);
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f + 5.f);
		glEnd();

		glBegin(GL_QUADS); //Bottom face
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f + 5.f, 20.f + 5.f);
		glVertex3f(20.f - 5.f, 5.f + 5.f, 20.f + 5.f);
		glEnd();

		glBegin(GL_QUADS); //Top face
		glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f - 5.f);
		glVertex3f(20.f + 5.f, 5.f - 5.f, 20.f + 5.f);
		glVertex3f(20.f - 5.f, 5.f - 5.f, 20.f + 5.f);
		glEnd();
		glEndList();
	}

	myBackGround.emplace_back(glGenLists(1));

	{
		glNewList(myBackGround[1], GL_COMPILE);
		glEnable(GL_TEXTURE_2D);	//and turn on texturing
		glColor3f(1,1,1);
		glBegin(GL_QUADS);	//and draw a face
			//back face
			glColor3f(0,1,1);
			glVertex3f(200.f/2,200.f/2,200.f/2);	//and a vertex
			glColor3f(1,0,1);
			glVertex3f(-200.f/2,200.f/2,200.f/2);
			glColor3f(1,1,0);
			glVertex3f(-200.f/2,-200.f/2,200.f/2);
			glColor3f(1,0,0);
			glVertex3f(200.f/2,-200.f/2,200.f/2);
		glEnd();
		glColor3f(0,1,1);
		glBegin(GL_QUADS);	
			//left face
			glVertex3f(-200.f/2,200.f/2,200.f/2);
			glVertex3f(-200.f/2,200.f/2,-200.f/2);
			glVertex3f(-200.f/2,-200.f/2,-200.f/2);
			glVertex3f(-200.f/2,-200.f/2,200.f/2);
		glEnd();
		glColor3f(0,0,1);
		glBegin(GL_QUADS);	
			//front face
			glVertex3f(200.f/2,200.f/2,-200.f/2);
			glColor3f(1,0,0);
			glVertex3f(-200.f/2,200.f/2,-200.f/2);
			glColor3f(1,0,1);
			glVertex3f(-200.f/2,-200.f/2,-200.f/2);
			glColor3f(1,1,0);
			glVertex3f(200.f/2,-200.f/2,-200.f/2);
			glColor3f(0,1,1);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_QUADS);	
			//right face
			glVertex3f(200.f/2,200.f/2,-200.f/2);
			glVertex3f(200.f/2,200.f/2,200.f/2);
			glVertex3f(200.f/2,-200.f/2,200.f/2);
			glVertex3f(200.f/2,-200.f/2,-200.f/2);
		glEnd();
		glColor3f(1,0,1);
		glBegin(GL_QUADS);			//top face
			glVertex3f(200.f/2,200.f/2,200.f/2);
			glVertex3f(-200.f/2,200.f/2,200.f/2);
			glVertex3f(-200.f/2,200.f/2,-200.f/2);
			glVertex3f(200.f/2,200.f/2,-200.f/2);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
			//bottom face
			glVertex3f(200.f/2,-200.f/2,200.f/2);
			glVertex3f(-200.f/2,-200.f/2,200.f/2);
			glVertex3f(-200.f/2,-200.f/2,-200.f/2);
			glVertex3f(200.f/2,-200.f/2,-200.f/2);
		glEnd();
		glEndList();
	}


	Graphic :: Player player;
	Graphic :: Loader myLoader;

	GLuint myGun(myLoader.loadFile("res/pistolet.obj"));


	std :: vector <GLuint> frames(myLoader.loadAnimation("res/pistol/pistolet")); //We read the folder for all objs starting with "pistolet_abcdef", return the animation

	Graphic :: PowerUp somePowerUp(myGun, frames, {-2.f, 0.f, -2.f}, {10.f, 0.f, 10.f}, 0); 
	//								outerLook 	  animation		position		rotation	currentFrame(vec.size() because it is not posessed)



	GLuint someDrawing(myLoader.loadFile("res/try.obj"));
//	GLuint myWeapon(myLoader.loadFile("res/pistolet_000001.obj"));
	Graphic :: Gun *pistol(new Graphic :: Gun(myLoader.loadFile("res/pistol/pistolet_000001.obj"), 0, {-0.01f, -0.4f, -1.3f}, {1.f, -1.f, 0.35f}, {0.75f, -0.7f, -1.5f}, {0.8f, 2.0f, 1.0f}, frames, 1, 11, 26));
//												outerLook, 								currentFrame, 		aimPos 				aimRot 				position 				rotation 		frames norm, att, secondary
	std :: vector <Graphic :: Particule> particules;
	particules.emplace_back(Graphic :: Particule(myGun, {0.f, 0.f, 0.f}, 10));
	particules.emplace_back(Graphic :: Particule(someDrawing, {0.f, 0.f, 0.f}, 10));
//													visual 		pos 		duration 
	Graphic :: Level myLevel(myBackGround, particules);
//					setup(list GLuint)	 particules
	
	bool isRunning(true);
	bool isSprinting(false);
	Uint32 currentTimeTick(0); //FPS regulation
	bool tryExplode(false);

	SDL_Event event;
	int width, height;

	while (isRunning) {
auto start(std :: chrono :: system_clock :: now());

		currentTimeTick = SDL_GetTicks();

		while (SDL_PollEvent(&event))
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
				break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						pistol->attack();
					if (event.button.button == SDL_BUTTON_RIGHT)
						player.secondary(pistol);
					player.att_camera.isMouseIn() = true;
					SDL_ShowCursor(SDL_DISABLE);
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_LSHIFT:
							isSprinting = true;
						break;
						case SDL_SCANCODE_SPACE:
							player.jump();
						break;
						case SDL_SCANCODE_ESCAPE:
							isRunning = false;
						break;
						case SDL_SCANCODE_O:
							myLevel.spawnParticules(1, player.att_camera.getLocation() + 10 * player.att_camera.getSight(), 10);
						break;
						case SDL_SCANCODE_L:
							myLevel.spawnParticules(0, player.att_camera.getLocation() + 10 * player.att_camera.getSight(), 5);
						break;
						case SDL_SCANCODE_R:
							pistol->reload();
						break;
						// case SDL_SCANCODE_I:
						// 	++pistol_g.getLocation().att_z;
						// break;
						// case SDL_SCANCODE_K:
						// 	--pistol_g.getLocation().att_z;
						// break;
						// case SDL_SCANCODE_L:
						// 	++pistol_g.getLocation().att_x;
						// break;
						// case SDL_SCANCODE_J:
						// 	--pistol_g.getLocation().att_x;
						// break;
						case SDL_SCANCODE_LALT:
							player.att_camera.isMouseIn() = false;
							SDL_ShowCursor(SDL_ENABLE);
						default:
						break;
					}
				break;
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
						isSprinting = false;
				break;
			}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		SDL_GetWindowSize(window, &width, &height);
		player.update(width, height, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN, isSprinting, 0.f);
		player.att_camera.updateCamera();
		if (somePowerUp.update(tryExplode))
			tryExplode = false;
		pistol->update(false);
		myLevel.update();

//		glCallList(myGun);

		glCallList(someDrawing);
		myLevel.draw();
		somePowerUp.draw();
//		glClear(GL_DEPTH_BUFFER_BIT); //Activate this if want my weapons to be seen through walls
		player.draw(pistol);

auto end(std :: chrono :: system_clock :: now());
std::chrono::duration<double> elapsed_seconds = end-start;

		if (1000.0f/myFPS > SDL_GetTicks() - currentTimeTick) {
			std :: cout << 1.f/(elapsed_seconds.count()) << " fps" << std :: endl;
			SDL_Delay(1000./myFPS - (SDL_GetTicks() - currentTimeTick));
		}
		SDL_GL_SwapWindow(window);
	}

	delete pistol;
	SDL_DestroyWindow(window);
	SDL_Quit();
	SDL_GL_DeleteContext(glContext);
}
// Anti-crénelage, Anti-aliasing, filtrage anisotropique, flou selon distance au centre, occlusion ambiante, zoom en visant