#include "GrE_Loader.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <fstream>
#include <algorithm>

void Graphic :: Loader :: loadTexture(const std :: string &file) { //Load a .bmp file
	if (att_textures.find(file) != att_textures.end()) //We already loaded this file
		return;

	std :: string tmp1("../" + file);
	std :: string tmp2("Game/" + file);
	SDL_Surface* img=SDL_LoadBMP(file.c_str());	//load the bmp image
	if (!img)
		if (!(img = SDL_LoadBMP(tmp1.c_str()))) //Used to working from Makefile directory, maybe the user is right after that
			if (!(img = SDL_LoadBMP(tmp2.c_str()))) //Maybe the user is right outside Game directory
				std :: cout << "Img loading failed: " << IMG_GetError() << std :: endl;
	GLuint num;
	glGenTextures(1,&num);	//we generate a unique id
	glBindTexture(GL_TEXTURE_2D,num);	//Whenever we call this texture, these modifications will be called
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Deal with texture being too small
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //same with texture being too large
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);	//we make the actual texture
	//			2D, 	precision, colors, w, h, border, colorFormat, how to store (5R, 6G, 5B), pixels array
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore

	att_textures[file] = num; //We register we have loaded this file, write the texture number
}

std :: ifstream Graphic :: Loader :: tryHardOpenFile(const std :: string &filename) {
	std :: string tmp1("../" + filename);
	std :: string tmp2("Game/" + filename);
	std :: ifstream file(filename);
	if (!file) { //I work from one folder above the binary
		file.open(tmp1); //Checking if app launched from binary folder
		if (!file.is_open()) {
			file.open(tmp2); //Checking if app launched from the folder above
			if (!file.is_open()) {
				std :: cout << "Error reading file: " << filename << ". Tried " << tmp1 << " and " << tmp2 << std :: endl;
				throw "Missed file " + filename + ". Please provide it"; //No idea how to deal with missing files
			}
		}
	}	
	return file;
}

void Graphic :: Loader :: readVertex(const std :: string &vertexLine) {
	std :: stringstream myLine(vertexLine);
	float vx(0.f), vy(0.f), vz(0.f);
	myLine.ignore(2);//'v '
	myLine >> vx >> vy >> vz;
	att_vertexes.emplace_back(Vector3f(vx, vy, vz));
}

void Graphic :: Loader :: readNormal(const std :: string &vertexLine) {
	std :: stringstream myLine(vertexLine);
	float vx(0.f), vy(0.f), vz(0.f);
	myLine.ignore(3); //'vn '
	myLine >> vx >> vy >> vz;
	att_normals.emplace_back(Vector3f(vx, vy, vz));	
}

void Graphic :: Loader :: readMaterialLib(const std :: string &prevFileName, const std :: string &vertexLine) {
	std :: string path(prevFileName.substr(0, prevFileName.find_last_of('/') + 1));
	std :: stringstream myLine(vertexLine);
	myLine.ignore(7); //'mtllib '
	std :: string tmp;
	myLine >> tmp;
	std :: ifstream myFile(tryHardOpenFile(path + tmp));
	if (!myFile.is_open()) {
		std :: cout << "Error loading. Missing file" << path + tmp << std :: endl;
		return;
	}
	while (!myFile.eof())
		readMaterial(path, myFile);
}

void Graphic :: Loader :: readKs(const std :: string &vertexLine, float &Kx1, float &Kx2, float &Kx3) {
	std :: stringstream myLine(vertexLine);
	myLine.ignore(3); //'Kx '. We assume the right Ks were given (Ka || Kd || Ks)
	myLine >> Kx1 >> Kx2 >> Kx3;
}

void Graphic :: Loader :: readFloat(const std :: string &vertexLine, float &myVar, unsigned int numberOfCharToIgnore) {
	std :: stringstream myLine(vertexLine);
	myLine.ignore(numberOfCharToIgnore); //'Ns ' or 'd '. We assume the right figures and vars are given
	myLine >> myVar;
}

void Graphic :: Loader :: readInt(const std :: string &vertexLine, int &myVar) {
	std :: stringstream myLine(vertexLine);
	myLine.ignore(6); //'illum '. We assume the right figures and vars are given
	myLine >> myVar;
}

void Graphic :: Loader :: readMaterial(const std :: string &path, std :: ifstream &myFile) {
	std :: string myString("#"), matName(""), matFile(path);
	float Ka1(0.f), Ka2(0.f), Ka3(0.f), Kd1(0.f), Kd2(0.f), Kd3(0.f), 
		Ks1(0.f), Ks2(0.f), Ks3(0.f), Ke1(0.f), Ke2(0.f), Ke3(0.f), Ns(0.f), d(0.f);
	int illum(0); //Initiated all the variables I will need to use. No more no less.
	while (!myFile.eof()) {
		if (myString[0] == '#') ;			//Nothing to do. Go next
		else if (myString[0] == 'n')		//'newmtl '
			matName = myString.substr(7);	//We deleted 'newmtl ' and read the material name
		else if (myString[0] == 'N')		//'Ns '
			readFloat(myString, Ns, 3); 		//We delete 3 char before finding the Ns
		else if (myString[0] == 'K') { 		//4 kind of Ks: Ka, Kd, Ks, Ke (Seems to be optional)
			if (myString[1] == 'a')
				readKs(myString, Ka1, Ka2, Ka3);
			else if (myString[1] == 'd')
				readKs(myString, Kd1, Kd2, Kd3);
			else if (myString[1] == 's')
				readKs(myString, Ks1, Ks2, Ks3);
			else if (myString[1] == 'e')
				readKs(myString, Ke1, Ke2, Ke3);
		}
		else if (myString[0] == 'd')		//'d '
			readFloat(myString, d, 2);
		else if (myString[0] == 'i') 		//'illum '
			readInt(myString, illum);
		else if (myString[0] == 'm') { 		//'map_Kd '
			matFile += myString.substr(7);	//Will be 'res/name.bmp'
			loadTexture(matFile); 			//loadTexture knows if it took care of it or not
			break;
		}
		std :: getline(myFile, myString);		//Go to next line
	}
	GLuint newList(glGenLists(1));
	glNewList(newList, GL_COMPILE);
	float ambient[] = {Ka1, Ka2, Ka3};
	float diffuse[] = {Kd1, Kd2, Kd3};
	float specular[] = {Ks1, Ks2, Ks3};
	float emission[] = {Ke1, Ke2, Ke3};
	glMaterialf(GL_FRONT, GL_SHININESS, Ns);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	if (att_textures.find(matFile) != att_textures.end()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, att_textures.find(matFile)->second);
	}
	else 
		glDisable(GL_TEXTURE_2D);
	glEndList();
	att_materials[matName] = newList;
}

void Graphic :: Loader :: readTex(const std :: string &vertexLine) {
	std :: stringstream myLine(vertexLine);
	myLine.ignore(3); //'vt '
	float *pos(new float[2]);
	myLine >> pos[0] >> pos[1];
	pos[1] = 1 - pos[1]; //1 - x because .obj and OpenGL deal with y differently

	att_texVertex.push_back(pos);
}

void Graphic :: Loader :: readFigure(const std :: string &vertexLine) {
	unsigned int minus1(-1);
	if (att_currentMaterial == minus1) //collision
		return;
	std :: stringstream myLine(vertexLine);
	myLine.ignore(2); //'f '

	int posNum(0), texPosNum(0), normNum(0); //v, vt, vn
	char fake;
	
	GLuint myList = glGenLists(1); 	//Generating a unique id for the list
	glNewList(myList, GL_COMPILE); 	//Creating the list. calling it will call all the following
	glEnable(GL_TEXTURE_2D);				//Make sure it's initialized: We will bind a texture to a 2D shape
	if (att_currentMaterial)
		glCallList(att_currentMaterial - 1);//This shape has a material binded to it
	glBegin(GL_POLYGON);
	while (!myLine.eof()) {
		myLine >> posNum >> fake >> texPosNum >> fake >> normNum; //Get the three nums, separated by /, no reason to store
		glTexCoord2f(att_texVertex[texPosNum - 1][0], att_texVertex[texPosNum - 1][1]);
		glVertex3f(att_vertexes[posNum - 1].att_x, att_vertexes[posNum - 1].att_y, att_vertexes[posNum - 1].att_z);
		glNormal3f(att_normals[normNum - 1].att_x, att_normals[normNum - 1].att_y, att_normals[normNum - 1].att_z);
	}
	glEnd();
	glEndList();
	att_drawings.push_back(myList);
}

// void Graphic :: Loader :: readFigureNoTex(std :: stringstream &myLine) {
// 	//If I'm called, then the 'f ' has been deleted already
// 	int posNum(0), normNum(0); //v, vn
// 	char fake;
// 	GLuint myList = glGenLists(1); 	//Generating a unique id for the list
// 	glNewList(myList, GL_COMPILE); 	//Creating the list. calling it will call all the following
// 	glDisable(GL_TEXTURE_2D); //No need for textures
// 	glBegin(GL_POLYGON);
// 	while (!myLine.eof()) {
// 		myLine >> posNum >> fake >> fake >> normNum; //Get the two nums. Separated by //, no reason to store
// 		glVertex3f(att_vertexes[posNum - 1].att_x, att_vertexes[posNum - 1].att_y, att_vertexes[posNum - 1].att_z);
// 		glNormal3f(att_normals[normNum - 1].att_x, att_normals[normNum - 1].att_y, att_normals[normNum - 1].att_z);
// 	}
// 	glEnd();
// 	glEnable(GL_TEXTURE_2D);
// 	glEndList();
// 	att_drawings.push_back(myList);
// }

//Cheatsheet: 	# : comment
//				mtllib : file to read to know textures
//	X			v : position, vertex
//	X			vt : texture. has an u and a v
//	X			vn : normal vector
//				usemtl : Using a texture
//				g : number of group, to relate following Fs together (until another g)
//				s : groupNumber. All following Fs until another s are part of the same 'smoothing group'
//	X			f : shapes
GLuint Graphic :: Loader :: loadFile(const std :: string &filename) {	//Load a .obj file
	unsigned int curDrawing(att_drawings.size());
	std :: ifstream file(tryHardOpenFile(filename));
	std :: string buffer;
	while (!file.eof()) {
		std :: getline(file, buffer); //Read a line, place it in "buffer"
		if (buffer[0] == '#') //Comment, we do nothing. Go next
			continue; //Now we know we have something interesting to read. But what?
		if (buffer[0] == 'v') {
			if (buffer[1] == ' ') 		//vertex
				readVertex(buffer);
			else if (buffer[1] == 't') 	//Texture vertex
				readTex(buffer);
			else if (buffer[1] == 'n') 	//Normal vertex
				readNormal(buffer);
		}
		else if (buffer[0] == 'f')		//shapes
			readFigure(buffer);
		else if (buffer[0] == 'm')		//mtllib
			readMaterialLib(filename, buffer);
		else if (buffer[0] == 'u') {	//'usemtl '
			if (buffer.substr(7, 15) == "collision" || buffer.substr(7, 12) == "(null)") {
				unsigned int minus1(-1);
				att_currentMaterial = minus1;
			}
			else if (att_materials.find(buffer.substr(7)) != att_materials.end() && buffer.substr(7, 15) != "collision")
				att_currentMaterial = att_materials.find(buffer.substr(7))->second + 1;
			else 
				att_currentMaterial = 0; //We use an offset to make sure we have a way to recognize materials with no textures
		}
	}
	if (att_drawings.size() != curDrawing + 1) { //We added only one drawing
		GLuint myList(glGenLists(1));
		glNewList(myList, GL_COMPILE);
		glColor3f(1.f, 1.f, 1.f); //Just in case I messed up and set a different color, so it doesn't propagate
		for (unsigned int i = curDrawing ; i < att_drawings.size() ; ++i)
			glCallList(att_drawings[i]);
		glColor3f(1.f, 1.f, 1.f); //Just in case I messed up and set a different color, so it doesn't propagate
		glEndList();
		att_drawings.push_back(myList);
	}
	att_vertexes.clear();
	att_texVertex.clear();
	att_normals.clear(); //Need to make sure they don't interfere with next file
	att_currentMaterial = 0;
	return att_drawings[att_drawings.size() - 1];
}

std :: vector <GLuint> Graphic :: Loader :: loadAnimation(const std :: string &name) { //Loads a whole animation for a given rootFileName (pistolet -> pistolet_abcdef.obj)
	std :: vector <GLuint> myList;
	std :: string tmpName;
	std :: ifstream myFile;
	for (int i = 1 ; i < 1000000 ; ++i) {//We get every single possibility
#ifdef NSFW
		tmpName = "." + name;
#else
		tmpName = name; //Refreshes the name
#endif
		if (i < 10)
			tmpName += "_00000" + std :: to_string(i) + ".obj";
		else if (i < 100)
			tmpName += "_0000" + std :: to_string(i) + ".obj";
		else if (i < 1000)
			tmpName += "_000" + std :: to_string(i) + ".obj";
		else if (i < 10000)
			tmpName += "_00" + std :: to_string(i) + ".obj";
		else if (i < 100000)
			tmpName += "_0" + std :: to_string(i) + ".obj";
		else
			tmpName += "_" + std :: to_string(i) + ".obj";
		myFile.open(tmpName);
		if (!myFile.is_open()) //We have done all the bmp files we had
			return myList;
		myFile.close();
		myList.emplace_back(loadFile(tmpName));
	}
	return myList;
}

Graphic :: Loader :: ~Loader() {
	for (std :: map <std :: string, GLuint> :: iterator it = att_textures.begin() ; it != att_textures.end() ; ++it)
		glDeleteTextures(1, &it->second);
	for (unsigned int i = 0 ; i < att_drawings.size() ; ++i)
		glDeleteLists(att_drawings[i], 1);
	for (std :: map <std :: string, GLuint> :: iterator it = att_materials.begin() ; it != att_materials.end() ; ++it)
		glDeleteLists(it->second, 1);
	for (unsigned int i = 0 ; i < att_texVertex.size() ; ++i)
		delete[] att_texVertex[i];
}