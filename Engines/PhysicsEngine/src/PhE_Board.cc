#include "PhE_Board.hh"
#include <sstream>
#include <fstream>
#include <algorithm>

#include <iostream>

// std :: vector<Vector3f> Physic :: Board :: playerShoot(const Vector3f &dir) {
// 	float firstWallDistance(0);
// 	Vector3f particulePoint{0.f, 0.f, 0.f};
// 	Vector3f origin(att_player->givePos());
// 	for (unsigned int i = 0 ; i < att_levels[att_curLevel].size() ; ++i)
// 		Physic :: Collision :: rayBox(origin, dir, *att_levels[att_curLevel][i], &firstWallDistance, &particulePoint);
// 	std :: vector <Vector3f> particulesToSpawn{particulePoint};
// 	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i)
// 		if (att_ennemies[i]->doesGetHit(origin, dir, &firstWallDistance, &particulePoint)) {
// 			std :: cout << i << " got hit" << std :: endl;
// 			particulesToSpawn.push_back(particulePoint);
// 		}
// 	return particulesToSpawn;
// }
//Should not exist. Will be done in the Game, no engines. Gives the collisionPoints, the ennemies hit, what particules to draw. Intervenes with litterally all 3 engines

void Physic :: Board :: changeLevel(unsigned int level) {
	att_curLevel = level;
}

Physic :: Board :: Board(const char *fileName)
: att_currentMaterial(0), att_currentSecond{false, false, false, false, false, false}, att_tmpQuads(), att_curLevel(0) {
//Here is what one of these files will look like: 
//	EnnemyFile		moveLength	attackLength	dieLength
//	MeleeNumber		WeaponFile	normLength	attackLength	secondaryLength	WeaponFile	...	secondaryLength
//	GunNumber		WeaponFile	normLength	attackLength	reloadLength	aimX aimY aimZ aimRotX aimRotY aimRotZ	WeaponFile	...	aimRotz
//	PowerUpNumber	PowerUpFile	PowerUpFile	...	PowerUpFile
//	ParticuleNumber	ParticuleFile	ParticuleDuration	ParticuleFile	...	ParticuleDuration	Level1
//	ParticuleNumber	ParticuleFile	ParticuleDuration	ParticuleFile	...	ParticuleDuration	Level2
//...
	std :: ifstream myFile(tryHardOpenFile(fileName));
	std :: string nextFileToRead("");
	unsigned int length1(0), garbage(0);
	myFile >> nextFileToRead;
	loadAnimation(nextFileToRead);
	unsigned int numberOfLevel(0);
	for (unsigned int i = 0 ; i < 3 ; ++i)
		std :: getline(myFile, nextFileToRead);
	myFile >> length1;
	for (unsigned int i = 0 ; i < length1 ; ++i) {
		myFile >> nextFileToRead;
		loadPowerUp(nextFileToRead);
	}
	while (!myFile.eof()) {
		myFile >> length1;
		for (unsigned int i = 0 ; i < length1 ; ++i)
			myFile >> nextFileToRead >> garbage;
		myFile >> nextFileToRead;
		myFile >> nextFileToRead;
		loadLevel(nextFileToRead, numberOfLevel++);
	}
	myFile.close();
}	

void Physic :: Board :: loadLevel(const std :: string &filename, unsigned int number) {
	std :: ifstream file(tryHardOpenFile(filename + ".obj"));
	std :: string buffer;
	while (!file.eof()) {
		std :: getline(file, buffer); //Read a line, place it in "buffer"
		if (buffer[0] == '#') //Comment, we do nothing. Go next
			continue; //Now we know we have something interesting to read. But what?
		if (buffer[0] == 'v') {
			if (buffer[1] == ' ') 		//vertex
				readVertex(buffer);
			else if (buffer[1] == 'n') 	//Normal vertex
				readNormal(buffer);
		}
		else if (buffer[0] == 'f' && att_currentMaterial)		//shapes
			loadFigure(buffer, number);
		else if (buffer[0] == 'u') {	//'usemtl '
			if (buffer.substr(7, 15) == "collision")
				att_currentMaterial = 1;
			else 
				att_currentMaterial = 0; //We use an offset to make sure we have a way to recognize materials to ignore
		}
	}
	att_vertexes.clear();
	att_normals.clear(); //Need to make sure they don't interfere with next file
	att_currentMaterial = 0;
}

void Physic :: Board :: loadFigure(const std :: string &vertexLine, unsigned int number) {
	std :: stringstream myLine(vertexLine);
	myLine.ignore(2); //'f '

	int posNum1(0), normNum(0); //v//vn
	int posNum2(0);
	int posNum3(0);
	int posNum4(0);
	char fake;
	
	while (!myLine.eof()) {
		myLine 	>> posNum1 >> fake >> fake >> normNum 
				>> posNum2 >> fake >> fake >> normNum
				>> posNum3 >> fake >> fake >> normNum
				>> posNum4 >> fake >> fake >> normNum;
		if (att_levels.size() != number)
			att_levels[att_levels.size() - 1].emplace_back(new Physic :: CollisionQuad(att_vertexes[posNum1 - 1], att_vertexes[posNum2 - 1], att_vertexes[posNum3 - 1], att_vertexes[posNum4 - 1], att_normals[normNum - 1]));
		else {
			std :: vector <Physic :: CollisionQuad *> tmpVector;
			tmpVector.emplace_back(new Physic :: CollisionQuad(att_vertexes[posNum1 - 1], att_vertexes[posNum2 - 1], att_vertexes[posNum3 - 1], att_vertexes[posNum4 - 1], att_normals[normNum - 1]));
			att_levels.push_back(tmpVector);
		}
	}
}

std :: ifstream Physic :: Board :: tryHardOpenFile(const std :: string &filename) {
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

void Physic :: Board :: readVertex(const std :: string &vertexLine) {
	std :: stringstream myLine(vertexLine);
	float vx(0.f), vy(0.f), vz(0.f);
	myLine.ignore(2);//'v '
	myLine >> vx >> vy >> vz;
	att_vertexes.emplace_back(Vector3f(vx, vy, vz));
}

void Physic :: Board :: readNormal(const std :: string &vertexLine) {
	std :: stringstream myLine(vertexLine);
	float vx(0.f), vy(0.f), vz(0.f);
	myLine.ignore(3); //'vn '
	myLine >> vx >> vy >> vz;
	att_normals.emplace_back(Vector3f(vx, vy, vz));	
}

void Physic :: Board :: readFigure(const std :: string &vertexLine, Physic :: Ennemy &myEnnemy) {
	if (!att_currentMaterial)
		return; //We do not care
	if (att_currentMaterial == 1) {
		myEnnemy.equals(loadSphere(vertexLine), true);
		return;
	}
	else if (att_currentMaterial == 7) {
		myEnnemy.equals(loadSphere(vertexLine), false);
		return;
	}
									return; //Because I miss an element, I will just not write any :)))))
	std :: stringstream myLine(vertexLine);
	myLine.ignore(2); //'f '

	int posNum1(0), texPosNum(0), normNum(0); //v, vt, vn
	int posNum2(0);
	int posNum3(0);
	int posNum4(0);
	char fake;
	
	myLine >> posNum1 >> fake >> texPosNum >> fake >> normNum; //Get the three nums, separated by /, no reason to store
	myLine >> posNum2 >> fake >> texPosNum >> fake >> normNum; //Get the three nums, separated by /, no reason to store
	myLine >> posNum3 >> fake >> texPosNum >> fake >> normNum; //Get the three nums, separated by /, no reason to store
	myLine >> posNum4 >> fake >> texPosNum >> fake >> normNum; //Get the three nums, separated by /, no reason to store
	if (att_currentSecond[att_currentMaterial]) {
		myEnnemy.equals(Physic :: CollisionBox(att_tmpQuads[att_currentMaterial], att_vertexes[posNum1 - 1], att_vertexes[posNum2 - 1], att_vertexes[posNum3 - 1], att_vertexes[posNum4 - 1], att_normals[normNum - 1]), att_currentMaterial);
		att_tmpQuads[att_currentMaterial] = Physic :: CollisionQuad();
		att_currentSecond[att_currentMaterial] = false;
	}
	else {
		att_currentSecond[att_currentMaterial] = true;
		att_tmpQuads[att_currentMaterial] = Physic :: CollisionQuad(att_vertexes[posNum1 - 1], att_vertexes[posNum2 - 1], att_vertexes[posNum3 - 1], att_vertexes[posNum4 - 1], att_normals[normNum - 1]);
	}
}

// void Physic :: Board :: readFigureNoTex(std :: stringstream &myLine) {
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
Physic :: Ennemy Physic :: Board :: loadFile(const std :: string &filename) {	//Load a .obj file
	Physic :: Ennemy myEnnemy;
	std :: ifstream file(tryHardOpenFile(filename));
	std :: string buffer;
	while (!file.eof()) {
		std :: getline(file, buffer); //Read a line, place it in "buffer"
		if (buffer[0] == '#') //Comment, we do nothing. Go next
			continue; //Now we know we have something interesting to read. But what?
		if (buffer[0] == 'v') {
			if (buffer[1] == ' ') 		//vertex
				readVertex(buffer);
			else if (buffer[1] == 'n') 	//Normal vertex
				readNormal(buffer);
		}
		else if (buffer[0] == 'f')		//shapes
			readFigure(buffer, myEnnemy);
		else if (buffer[0] == 'u') {	//'usemtl '
			if (buffer[7] == 'C') { //Collision
				if (buffer[16] == 'H') //Head
					att_currentMaterial = 1;
				else if (buffer[16] == 'T') //Torso
					att_currentMaterial = 2;
				else if (buffer[16] == 'L' && buffer[20] == 'L') //LeftLeg
					att_currentMaterial = 3;
				else if (buffer[16] == 'R' && buffer[21] == 'L') //RightLeg
					att_currentMaterial = 4;
				else if (buffer[16] == 'L' && buffer[20] == 'A') //LeftArm
					att_currentMaterial = 5;
				else if (buffer[16] == 'R' && buffer[21] == 'A') //RightArm
					att_currentMaterial = 6;
				else if (buffer[16] == 'B') //BigBox
					att_currentMaterial = 7;
				else att_currentMaterial = 0; //We don't care
			}
			else 
				att_currentMaterial = 0;
		}
	}
	att_vertexes.clear();
	att_normals.clear(); //Need to make sure they don't interfere with next file
	att_currentMaterial = 0;
	return myEnnemy;
}

void Physic :: Board :: loadAnimation(const std :: string &name) { //Loads a whole animation for a given rootFileName (pistolet -> pistolet_abcdef.obj)
	std :: string tmpName;
	std :: ifstream myFile;
	Physic :: Ennemy tmpEnnemy;
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
		if (!myFile.is_open()) {//We have done all the bmp files we had
			att_ennemies.emplace_back(new Physic :: Ennemy(tmpEnnemy));
			return;
		}
		myFile.close(); 
		i == 1 ? (tmpEnnemy = loadFile(tmpName)) : (tmpEnnemy += loadFile(tmpName));
	}
}

Physic :: CollisionSphere Physic :: Board :: loadSphere(const std :: string &line) {
	CollisionSphere mySphere(0.f, 0.f, 0.f, 0.f);
	char garbage;
	std :: stringstream myLine(line);
	myLine.ignore(2); //'f '
	int posNum(0); myLine >> posNum;
	mySphere.att_center = att_vertexes[posNum - 1];
	myLine >> garbage >> posNum >> garbage >> posNum >> posNum; //The two next to each other are the closest
	myLine >> garbage >> posNum >> garbage >> posNum >> posNum;
	mySphere.att_radius = (mySphere.att_center - att_vertexes[posNum - 1]).length();
	return mySphere;
}

void Physic :: Board :: loadPowerUp(const std :: string &name) { //Loads a whole animation for a given rootFileName (pistolet -> pistolet_abcdef.obj)
	std :: ifstream myFile(tryHardOpenFile(name + "_000001.obj"));
	std :: string buffer;
	bool doSomething(false); //Just to know if I'm reading what interests me
	while (!myFile.eof()) {
		std :: getline(myFile, buffer); //Read a line, place it in "buffer"
		if (buffer[0] == '#') //Comment, we do nothing. Go next
			continue; //Now we know we have something interesting to read. But what?
		if (buffer[0] == 'v') {
			if (buffer[1] == ' ') 		//vertex
				readVertex(buffer);
			else if (buffer[1] == 'n') 	//Normal vertex
				readNormal(buffer);
		}
		else if (buffer[0] == 'f' && doSomething) {		//shapes
			att_items.emplace_back(new Physic :: Item(loadSphere(buffer)));
			return;
		}	
		else if (buffer[0] == 'u') {	//'usemtl '
			if (buffer[7] == 'C' && buffer[16] == 'S') //CollisionSphere
				doSomething = true;
			else 
				doSomething = false;
		}
	}
	att_vertexes.clear();
	att_normals.clear(); //Need to make sure they don't interfere with next file
	att_currentMaterial = 0;
}

Physic :: Board :: ~Board() {
	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i) {
		delete att_ennemies[i];
	}
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i)
		for (unsigned int j = 0 ; j < att_levels.size() ; ++j)
			delete att_levels[i][j];
}