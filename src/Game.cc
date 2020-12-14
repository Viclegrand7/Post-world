#ifndef RV_ZD_GAME_H
#define RV_ZD_GAME_H
#include "Game.hh"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	SDL_Texture *background = window.loadTexture("../res/img/Background.png");
	entities.push_back(Entity(Vector3f(0,0,0), background));
*/
/*
	{
		Entity platform0(Vector3f(100, 0, 0), imaginaryTexture);
		entities.push_back(platform0);
	} //Adding those create a scope, ensuring platform0 gets deleted afterwards. Same than entities.pushback(Entity(Vector3f(100, 0, 0), imaginaryTexture))?
*/
/*
		att_render.clear();
		for (Entity &someone : entities)
			att_render.render(someone);
//		att_render.render(platform0);
		att_render.display();

*/

unsigned int skybox[6];

unsigned int loadTexture(const char* filename, SDL_PixelFormat *format)	//load the filename named texture
{

	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* img=SDL_LoadBMP(filename);	//load the bmp image
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id


/*
	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* tmp(IMG_Load(filename));	//load the png image
	SDL_Surface* img(SDL_ConvertSurface(tmp, format, 0));	//Optimize the png
	SDL_FreeSurface(tmp);
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,	0,GL_RGB,	img->w,img->h,0,	GL_RGB,GL_UNSIGNED_SHORT_5_6_5,	img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id
*/
}


void killSkyBox() {
	glDeleteTextures(6, &skybox[0]);
}


void Game :: initskybox(std :: vector <Entity> &entities, SDL_PixelFormat *format)
{

	skybox[0]=loadTexture("../res/img/back.bmp", format);
	skybox[1]=loadTexture("../res/img/left.bmp", format);
	skybox[2]=loadTexture("../res/img/front.bmp", format);
	skybox[3]=loadTexture("../res/img/right.bmp", format);
	skybox[4]=loadTexture("../res/img/top.bmp", format);
	skybox[5]=loadTexture("../res/img/bottom.bmp", format);


/*
	int size = 50;

	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,skybox[0]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(size/2,size/2,size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();

*/

/*
	entities.clear();
	{
		SDL_Texture *background = att_render.loadTexture("../res/img/Background.png");
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
	}
*/
}

void drawSkybox(float size)
{
	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	bool b2=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,skybox[0]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(size/2,size/2,size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[1]);
	glBegin(GL_QUADS);	
		//left face
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[2]);
	glBegin(GL_QUADS);	
		//front face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[3]);	
	glBegin(GL_QUADS);	
		//right face
		glTexCoord2f(0,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[4]);		
	glBegin(GL_QUADS);			//top face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[5]);		
	glBegin(GL_QUADS);	
		//bottom face
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
	if(b2)
		glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
	//	std::cout << "called" << std::endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










#define MAX_OBJ_NUMBER 5

Game :: Game(SDL_DisplayMode DM) : att_render("Best_Game v0.0", DM.w, DM.h) {
	att_fps = DM.refresh_rate;


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1.777778f, 1.0f, 500.0f); //Angle, width/height, how close you can see, how far
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	initskybox(att_entities, att_render.getFormat());

	std :: vector <CollisionPlane> tmp_cp;
	std :: vector <Vector3f> tmp_sp;
	tmp_sp.push_back(Vector3f(3.0f, 4.0f, 5.0f)); //Ennemies spawns
	unsigned int map = att_obj.load("../res/obj/map.obj", &tmp_cp);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	att_levels.push_back(new Level("name", map, tmp_cp, tmp_sp));

	Vector3f tmp_pos(10.0f, 1000.0f, 10.0f);
	att_player = new Player("User", CollisionSphere(tmp_pos, 3.0f));
}

Game :: ~Game() {
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i)
		delete att_levels[i];
	killSkyBox();
	att_render.cleanUp();
	SDL_Quit();
}

void Game :: run() {

//	SDL_Texture *imaginaryTexture = window.loadTexture("../res/img/someImage.png");

/*
	SDL_Texture *background = window.loadTexture("../res/img/Background.png");
	entities.push_back(Entity(Vector3f(0,0,0), background));
*/
/*
	{
		Entity platform0(Vector3f(100, 0, 0), imaginaryTexture);
		entities.push_back(platform0);
	} //Adding those create a scope, ensuring platform0 gets deleted afterwards. Same than entities.pushback(Entity(Vector3f(100, 0, 0), imaginaryTexture))?
*/


	bool isRunning = true;
	Uint32 currentTimeTick(0); //FPS regulation

	SDL_Event event;

	while (isRunning) {
		currentTimeTick = SDL_GetTicks();
	
		while (SDL_PollEvent(&event))
			switch (event.type) {
				case SDL_QUIT :
					isRunning = false;
				break;
				case SDL_MOUSEBUTTONDOWN :
					att_player->att_cam.mouseIn(true);
//					if (inOptions) {
//						//Do stuff
//					}
//					else
						SDL_ShowCursor(SDL_ENABLE);
//						SDL_ShowCursor(SDL_DISABLE);
				break;
// 				case SDL_MOUSEMOTION:
// //					if (inOptions) {
// //						//Do stuff
// //					}
// 					att_cam.control(att_render);
// 				break;
			}

		update();
		display();



/*
		att_render.clear();
		for (Entity &someone : entities)
			att_render.render(someone);
//		att_render.render(platform0);
		att_render.display();
*/

		SDL_GL_SwapWindow(att_render.getWindow());

		if (1000./att_fps > SDL_GetTicks() - currentTimeTick)
			SDL_Delay(1000./att_fps - (SDL_GetTicks() - currentTimeTick)); //FPS regulation based on how fast monitor can go

	}

}

void Game :: update() {
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i) 
		att_levels[i]->update();
	att_player->update(att_levels[0]->getColl());
}


void Game :: display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	att_render.isFull() ? att_player->att_cam.control(att_render, true) : att_player->att_cam.control(att_render, false);
	drawSkybox(50.0f);
	att_player->att_cam.updateCamera();
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i) //Probably should just display and update the level we're in
		att_levels[i]->display();
	att_player->display();
}