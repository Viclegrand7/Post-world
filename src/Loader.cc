#ifndef RV_ZD_LOADER_H
#define RV_ZD_LOADER_H
#include "Loader.hh"
#endif



Face :: Face(int facen, unsigned int f1, unsigned int f2, unsigned int f3, int t1, int t2, int t3, int m) 
: att_facenum(facen), att_four(false), att_faces{f1, f2, f3, 0}, att_texcoord{t1, t2, t3, 0}, att_mat(m) {}

Face :: Face(int facen, unsigned int f1, unsigned int f2, unsigned int f3, unsigned int f4, int t1, int t2, int t3, int t4, int m)
: att_facenum(facen), att_four(true), att_faces{f1, f2, f3, f4}, att_texcoord{t1, t2, t3, t4}, att_mat(m) {}



Material :: Material(const char* na, float al, float n, float ni2, float *d, float *a, float *s, int i, int t) 
: att_name(na), att_alpha(al), att_ns(n), att_ni(ni2), att_dif{d[0], d[1], d[2]}, att_amb{a[0], a[1], a[2]}, att_spec{s[0], s[1], s[2]}, att_illum(i), att_texture(t) {}



Texcoord :: Texcoord(float a,float b) : att_u(a), att_v(b) {}



int Objloader :: load(const std :: string &filename, std :: vector <CollisionPlane> *collisionPlane) {
	att_isMaterial = false; 	att_isNormals = false;
	att_isTexture = false;		att_isVertexNormal = false;
	std :: ifstream in(filename.c_str());
	if (!in.is_open()) {
		att_out << "File " << filename << " could not be loaded" << std :: endl;
		return -1;
	}
	std :: string path(filename.substr(0, (filename.find_last_of('/') + 1 != std :: string :: npos) ? (filename.find_last_of('/') + 1 ) : 0));
	char buf[256];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Honestly too bored to do it now. Should find a way to parse files, read them, load walls, images, character designs,...
//The guy I found did THIS:
//He used Blender.org to generate some objetcs in a 3D map, then exported as a file
//Also he duplicated everything in Blender, differentiating collisionMaterials from Sprites. Maybe just saying everything is both would be better

//sscanf instead of >> 

//CAREFUL : He used int to compare with .size(), gotta redo EVERY SINGLE FOR, no matter what
//Also, wrong names : att_ missing

	int curmat=0;
	bool coll=false;
	while(!in.eof())
	{
		in.getline(buf,256);
		att_coord.push_back(new std::string(buf));
	}
	for(unsigned int i=0;i<att_coord.size();i++)
	{
		if((*att_coord[i])[0]=='#')
			continue;
		else if((*att_coord[i])[0]=='v' && (*att_coord[i])[1]==' ')
		{
			float tmpx,tmpy,tmpz;
			sscanf(att_coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
			att_vertex.push_back(new Vector3f(tmpx,tmpy,tmpz));
			att_out << "v " << tmpx << " " << tmpy << " " << tmpz << std::endl;
		}else if((*att_coord[i])[0]=='v' && (*att_coord[i])[1]=='n')
		{
			float tmpx,tmpy,tmpz;
			sscanf(att_coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			att_normals.push_back(new Vector3f(tmpx,tmpy,tmpz));	
			att_out << "vn " << tmpx << " " << tmpy << " " << tmpz << std::endl;
		}else if((*att_coord[i])[0]=='f')
		{
			int a,b,c,d,e;			
			if(coll && collisionPlane!=NULL)
			{
				sscanf(att_coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				collisionPlane->push_back(CollisionPlane(Vector3f(att_normals[b-1]->att_x,att_normals[b-1]->att_y,att_normals[b-1]->att_z),Vector3f(att_vertex[a-1]->att_x,att_vertex[a-1]->att_y,att_vertex[a-1]->att_z),Vector3f(att_vertex[c-1]->att_x,att_vertex[c-1]->att_y,att_vertex[c-1]->att_z),Vector3f(att_vertex[d-1]->att_x,att_vertex[d-1]->att_y,att_vertex[d-1]->att_z),Vector3f(att_vertex[e-1]->att_x,att_vertex[e-1]->att_y,att_vertex[e-1]->att_z)));
			}else
			{
				if(count(att_coord[i]->begin(),att_coord[i]->end(),' ')==4)
				{
					if(att_coord[i]->find("//")!=std::string::npos)
					{
						sscanf(att_coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
						att_faces.push_back(new Face(b,a,c,d,e,0,0,0,0,curmat));
					}else if(att_coord[i]->find("/")!=std::string::npos)
					{
						int t[4];
						sscanf(att_coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b,&e,&t[3],&b);
						att_out << t[0] << " " <<t[1] << " " <<t[2] << " " <<t[3] << " " << a << " " << b << " " << c << " " << d << " " << e << std::endl;
						att_faces.push_back(new Face(b,a,c,d,e,t[0],t[1],t[2],t[3],curmat));
					}else{
						sscanf(att_coord[i]->c_str(),"f %d %d %d %d",&a,&b,&c,&d);
						att_faces.push_back(new Face(-1,a,b,c,d,0,0,0,0,curmat));					
					}
				}else{
						if(att_coord[i]->find("//")!=std::string::npos)
						{
							sscanf(att_coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
							att_faces.push_back(new Face(b,a,c,d,0,0,0,curmat));
						}else if(att_coord[i]->find("/")!=std::string::npos)
						{
							int t[3];
							sscanf(att_coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b);
							att_faces.push_back(new Face(b,a,c,d,t[0],t[1],t[2],curmat));
						}else{
							sscanf(att_coord[i]->c_str(),"f %d %d %d",&a,&b,&c);
							att_faces.push_back(new Face(-1,a,b,c,0,0,0,curmat));					
						}
				}
			}
	}else if((*att_coord[i])[0]=='u' && (*att_coord[i])[1]=='s' && (*att_coord[i])[2]=='e')
	{
		char tmp[200];
		sscanf(att_coord[i]->c_str(),"usemtl %s",tmp);
		if(strcmp(tmp,"collision")==0)
		{
			coll=true;
		}else{
			coll=false;
			for(unsigned int i=0;i<att_materials.size();i++)
			{
				if(strcmp(att_materials[i]->att_name.c_str(),tmp)==0)
				{
					curmat=i;
					att_out << "curmat=" << i  << std::endl;
					break;
				}
			}
		}
	}else if((*att_coord[i])[0]=='m' && (*att_coord[i])[1]=='t' && (*att_coord[i])[2]=='l' && (*att_coord[i])[3]=='l')
	{
		char filen[200];
		sscanf(att_coord[i]->c_str(),"mtllib %s",filen);
		std::string filen2=path+filen;
		std::ifstream mtlin(filen2.c_str());
		if(!mtlin.is_open())
		{
			att_out << "connot open the material file " << filen2 << std::endl;
			clean();
			return -1;
		}
		att_isMaterial=true;
		std::vector<std::string> tmp;
		char c[200];
		while(!mtlin.eof())
		{
			mtlin.getline(c,200);
			tmp.push_back(c);
		}
		char name[200];
		char filename[200];
		float amb[3],dif[3],spec[3],alpha,ns,ni;
		int illum;
		unsigned int att_texture;
		bool ismat=false;
		strcpy(filename,"\0");
//		std::cout << tmp.size() << std::endl;
		for(unsigned int i=0;i<tmp.size();i++)
		{
			if(tmp[i][0]=='#')
				continue;
			if(tmp[i][0]=='n' && tmp[i][1]=='e' && tmp[i][2]=='w')
			{
				if(ismat)
				{
					if(strcmp(filename,"\0")!=0 && strcmp(filename,"collision")!=0)
					{
						att_materials.push_back(new Material(name,alpha,ns,ni,dif,amb,spec,illum,att_texture));
						strcpy(filename,"\0");
					}else{
							att_materials.push_back(new Material(name,alpha,ns,ni,dif,amb,spec,illum,-1));				
					}
				}
				ismat=false;
				sscanf(tmp[i].c_str(),"newmtl %s",name);
				att_out << "newmtl " << name << std::endl;
			}else if(tmp[i][0]=='N' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ns %f",&ns);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"Ka %f %f %f",&amb[0],&amb[1],&amb[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='d')
			{
				sscanf(tmp[i].c_str(),"Kd %f %f %f",&dif[0],&dif[1],&dif[2]);
				ismat=true;
			}else if(tmp[i][0]=='K' && tmp[i][1]=='s')
			{
				sscanf(tmp[i].c_str(),"Ks %f %f %f",&spec[0],&spec[1],&spec[2]);
				ismat=true;
			}else if(tmp[i][0]=='N' && tmp[i][1]=='i')
			{
				sscanf(tmp[i].c_str(),"Ni %f",&ni);
				ismat=true;
			}else if(tmp[i][0]=='d' && tmp[i][1]==' ')
			{
				sscanf(tmp[i].c_str(),"d %f",&alpha);
				ismat=true;
			}else if(tmp[i][0]=='i' && tmp[i][1]=='l')
			{
				sscanf(tmp[i].c_str(),"illum %d",&illum);
				ismat=true;
			}else if(tmp[i][0]=='m' && tmp[i][1]=='a')
			{
				sscanf(tmp[i].c_str(),"map_Kd %s",filename);
				bool l=0;
				att_out << "Opening image: " << filename << std::endl;
				std::string filename2=path+filename;
				for(unsigned int i=0;i<att_loadedTextures.size();i++)
					if(att_loadedTextures[i]==filename2)
					{
						att_out << "loading "  << filename2 << std::endl;
						att_texture=att_loadedTexturesNum[i];
						l=1;
						break;
					}
				if(l==0)
					att_texture=loadTexture(filename2.c_str());
				ismat=true;
			}
		}
				if(ismat)
				{
					if(strcmp(filename,"\0")!=0)
					{
						att_materials.push_back(new Material(name,alpha,ns,ni,dif,amb,spec,illum,att_texture));
					}else{
							att_materials.push_back(new Material(name,alpha,ns,ni,dif,amb,spec,illum,-1));				
					}
				}
	}else if((*att_coord[i])[0]=='v' && (*att_coord[i])[1]=='t')
	{
		float u,v;
		sscanf(att_coord[i]->c_str(),"vt %f %f",&u,&v);
		att_textureCoordinate.push_back(new Texcoord(u,1-v));
		att_isTexture=true;
	}
}
	if(att_materials.size()==0)
		att_isMaterial=false;
	else
		att_isMaterial=true;
	att_out << "numvertex :" << att_vertex.size() << " " << att_normals.size() << " " << att_faces.size() << " " << att_materials.size() << std::endl; 
	//draw
	if(att_isVertexNormal)
		smoothNormals();
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
	int last=-1;
	for(unsigned int i=0;i<att_faces.size();i++)
	{
		if(last!=att_faces[i]->att_mat && att_isMaterial)
		{
			float diffuse[]={att_materials[att_faces[i]->att_mat]->att_dif[0],att_materials[att_faces[i]->att_mat]->att_dif[1],att_materials[att_faces[i]->att_mat]->att_dif[2],1.0};
			float ambient[]={att_materials[att_faces[i]->att_mat]->att_amb[0],att_materials[att_faces[i]->att_mat]->att_amb[1],att_materials[att_faces[i]->att_mat]->att_amb[2],1.0};
			float specular[]={att_materials[att_faces[i]->att_mat]->att_spec[0],att_materials[att_faces[i]->att_mat]->att_spec[1],att_materials[att_faces[i]->att_mat]->att_spec[2],1.0};
			glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
			glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
			glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			glMaterialf(GL_FRONT,GL_SHININESS,att_materials[att_faces[i]->att_mat]->att_ns);
			glColor3f(diffuse[0],diffuse[1],diffuse[2]);
			last=att_faces[i]->att_mat;
			att_out << "1....." << std::endl;
			if(att_materials[att_faces[i]->att_mat]->att_texture==-1)
				glDisable(GL_TEXTURE_2D);
			else{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,att_materials[att_faces[i]->att_mat]->att_texture);
			}
		}
		if(att_faces[i]->att_texcoord[0]==0)
			att_isTexture=false;
		else
			att_isTexture=true;
		att_out << "2....." << std::endl;
		att_isNormals=false;
		if(att_faces[i]->att_four)
		{
			glBegin(GL_QUADS);
				att_out << "att_faces[i]->texcoord[0]-1 " << att_faces[i]->att_facenum-1 << std::endl;
				if(att_isNormals)
					glNormal3f(att_normals[att_faces[i]->att_facenum-1]->att_x,att_normals[att_faces[i]->att_facenum-1]->att_y,att_normals[att_faces[i]->att_facenum-1]->att_z);
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[0]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[0]-1]->att_v);

				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_z);

				
				att_out << "att_faces[i]->att_faces[0]-1: " << att_faces[i]->att_faces[0]-1 << " " << att_faces[i]->att_faces[1]-1 << " " << att_faces[i]->att_faces[2]-1 << " " << att_faces[i]->att_faces[3]-1 << " "  << std::endl;
				glVertex3f(att_vertex[att_faces[i]->att_faces[0]-1]->att_x,att_vertex[att_faces[i]->att_faces[0]-1]->att_y,att_vertex[att_faces[i]->att_faces[0]-1]->att_z);
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[1]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[1]-1]->att_v);


				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_z);
				
				glVertex3f(att_vertex[att_faces[i]->att_faces[1]-1]->att_x,att_vertex[att_faces[i]->att_faces[1]-1]->att_y,att_vertex[att_faces[i]->att_faces[1]-1]->att_z);
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[2]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[2]-1]->att_v);

				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_z);

				glVertex3f(att_vertex[att_faces[i]->att_faces[2]-1]->att_x,att_vertex[att_faces[i]->att_faces[2]-1]->att_y,att_vertex[att_faces[i]->att_faces[2]-1]->att_z);
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[3]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[3]-1]->att_v);

				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[3]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[3]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[3]-1]->att_z);
			
				glVertex3f(att_vertex[att_faces[i]->att_faces[3]-1]->att_x,att_vertex[att_faces[i]->att_faces[3]-1]->att_y,att_vertex[att_faces[i]->att_faces[3]-1]->att_z);
			glEnd();
		}else{
			glBegin(GL_TRIANGLES);
				if(att_isNormals)
					glNormal3f(att_normals[att_faces[i]->att_facenum-1]->att_x,att_normals[att_faces[i]->att_facenum-1]->att_y,att_normals[att_faces[i]->att_facenum-1]->att_z);

				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[0]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[0]-1]->att_v);

				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[0]-1]->att_z);


				glVertex3f(att_vertex[att_faces[i]->att_faces[0]-1]->att_x,att_vertex[att_faces[i]->att_faces[0]-1]->att_y,att_vertex[att_faces[i]->att_faces[0]-1]->att_z);
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[1]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[1]-1]->att_v);
				
				
				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[1]-1]->att_z);
				
				glVertex3f(att_vertex[att_faces[i]->att_faces[1]-1]->att_x,att_vertex[att_faces[i]->att_faces[1]-1]->att_y,att_vertex[att_faces[i]->att_faces[1]-1]->att_z);
				
				
				if(att_isTexture && att_materials[att_faces[i]->att_mat]->att_texture!=-1)
					glTexCoord2f(att_textureCoordinate[att_faces[i]->att_texcoord[2]-1]->att_u,att_textureCoordinate[att_faces[i]->att_texcoord[2]-1]->att_v);


				if(att_isVertexNormal)
					glNormal3f(att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_x,att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_y,att_vertexNormals[att_faces[i]->att_faces[2]-1]->att_z);
		
				glVertex3f(att_vertex[att_faces[i]->att_faces[2]-1]->att_x,att_vertex[att_faces[i]->att_faces[2]-1]->att_y,att_vertex[att_faces[i]->att_faces[2]-1]->att_z);
			glEnd();
		}
	}
	glEndList();
	att_out << "3....." << std::endl;
	clean();
	att_lists.push_back(num);
	return num;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void Objloader :: clean() {
	for (unsigned int i = 0 ; i < att_coord.size() ; ++i)
		delete att_coord[i];
	for (unsigned int i = 0 ; i < att_faces.size() ; ++i)
		delete att_faces[i];
	for (unsigned int i = 0 ; i < att_normals.size() ; ++i)
		delete att_normals[i];
	for (unsigned int i = 0 ; i < att_vertex.size() ; ++i)
		delete att_vertex[i];
	for (unsigned int i = 0 ; i < att_materials.size() ; ++i)
		delete att_materials[i];
	for (unsigned int i = 0 ; i < att_textureCoordinate.size() ; ++i)
		delete att_textureCoordinate[i];
	for (unsigned int i = 0 ; i < att_vertexNormals.size() ; ++i)
		delete att_vertexNormals[i];
	att_coord.clear();
	att_faces.clear();
	att_normals.clear();
	att_vertex.clear();
	att_materials.clear();
	att_textureCoordinate.clear();
	att_vertexNormals.clear();
}

Objloader :: ~Objloader() {
	for (unsigned int i = 0 ; i < att_texture.size() ; ++i)
		glDeleteTextures(1, &att_texture[i]);
	for (unsigned int i = 0 ; i < att_lists.size() ; ++i)
		glDeleteLists(att_lists[i], 1);
}

unsigned int Objloader :: loadTexture(const char* filename) {
	unsigned int num;
	glGenTextures(1, &num);
	SDL_Surface* img(SDL_LoadBMP(filename));
	glBindTexture(GL_TEXTURE_2D, num);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	SDL_FreeSurface(img);
	att_texture.push_back(num);
	att_loadedTextures.push_back(filename);
	att_loadedTexturesNum.push_back(num);
	return num;
}

Objloader :: Objloader() : att_isMaterial(false), att_isNormals(false), att_isTexture(false), att_isVertexNormal(false), att_out("errorLog.txt") {} //Maybe I should have inheritance rather than tons of bools

void Objloader :: smoothNormals() {
	for (unsigned int i = 1 ; i < att_vertex.size() + 1 ; ++i) {
		float vecX(0.0f), vecY(0.0f), vecZ(0.0f);
		Vector3f temp(0.0f, 0.0f, 0.0f);
		int num(0);
		for(unsigned int j = 0 ; j < att_faces.size() ; ++j)	{
			if(att_faces[j]->att_faces[0] == i || att_faces[j]->att_faces[1] == i || att_faces[j]->att_faces[2] == i || att_faces[j]->att_faces[3] == i) {
				vecX += att_normals[att_faces[j]->att_facenum - 1]->att_x;
				vecY += att_normals[att_faces[j]->att_facenum - 1]->att_y;
				vecZ += att_normals[att_faces[j]->att_facenum - 1]->att_z;
				++num;
			}
		}
		if(num)	{
			vecX /= num;
			vecY /= num;
			vecZ /= num;
		}
		float d(sqrt(vecX * vecX + vecY * vecY + vecZ * vecZ));
		if(d) {
			vecX /= d;
			vecY /= d;
			vecZ /= d;
		}
		att_vertexNormals.push_back(new Vector3f(vecX, vecY, vecZ));
	}
}
