/*
 * Implementation of sphere
 * Author: Weichen Xu
 * Date: 11/10/2015
*/
#include "sphere.h"
WCX_sphere::WCX_sphere(){
	this->radius = 1.0;
	this->rollingSpeed = 0.02;
	this->accumuRollingM = mat4();
}
void WCX_sphere::loadSphereFromFile(){
	int Index = 0, triangleNum = 0;
	std::string sphereFileName;
	std::ifstream inputFile(sphereFileName);
    std::string line;
	while(!inputFile.is_open()){
		std::cout<<"Please input the file name for the sphere info: "<<std::endl;
		std::cin>>sphereFileName;
		sphereFileName = "./"+sphereFileName;
		inputFile.open(sphereFileName, std::ifstream::in);
		if(!inputFile.is_open()){
			std::cout<<"Can not open the file, do this again!"<<std::endl;
			continue;
		}
	}
	std::getline(inputFile, line);
	char *chr = new char[line.size()+1];
	strcpy_s(chr, line.length()+1, line.c_str());
	triangleNum = atoi(chr);
	this->vertex_size = triangleNum*3;
	delete chr;
	for(int i=0; i<triangleNum; i++){
		// get each vertex info
		// since all vertex, skip a readline which n = 3
		std::getline(inputFile, line);
		for(int j=0; j<3; j++){
			std::getline(inputFile, line);
			char *chr = NULL, *tok = NULL;
			chr = new char[line.length()+1];
			strcpy_s(chr,line.length()+1, line.c_str());
			
			for(int k = 0; k<3; k++){
				if(!k){
					sphere_points[Index].x = atof(chr);
					tok = std::strtok(chr, " ");
				}
				if(k == 1){sphere_points[Index].y = atof(tok);}
				if(k == 2){
					sphere_points[Index].z = atof(tok);
					sphere_points[Index].w = 1.0;
				}
				tok = std::strtok(NULL, " ");
			}
			Index ++;
			delete chr;
		}
	}
}
void WCX_sphere::setColor(color4 uniformColor){
	for(int i=0; i<this->vertex_size; i++){
			this->sphere_colors[i] = uniformColor;
	}
}
int WCX_sphere::rollingFromAToB(point4 A, point4 B, mat4 lastRotateM){
	accumuRollingM = lastRotateM;
	this->rollingDirection = B-A;
	this->rollingAxis = cross(vec4(0.0,1.0,0.0,0.0),rollingDirection);
	this->rollingStart = A;
	return int(length(A-B)/radius/rollingSpeed);
}
mat4 WCX_sphere::rollingFramePosition(int frame){
	vec4 currentCenter = this->rollingStart + frame*this->rollingSpeed*this->radius*normalize(this->rollingDirection);
	return Translate(currentCenter.x,currentCenter.y,currentCenter.z);
}
mat4 WCX_sphere::rollingFrameRotate(int frame){
	mat4 currentRotateM = Rotate(this->rollingSpeed*frame*180/PI, rollingAxis.x, rollingAxis.y, rollingAxis.z);
	return currentRotateM*accumuRollingM;
}
void WCX_sphere::setShadowColor(color4 sColor){
	for(int i=0; i<this->vertex_size; i++){
			this->shadow_colors[i] = sColor;
	}
}
void WCX_sphere::setMaterial(){
	this->lp.material_ambient = color4(0.2, 0.2, 0.2, 1.0);
	this->lp.material_diffuse = color4(1.0, 0.84, 0.0, 1.0);
	this->lp.material_specular = color4(1.0, 0.84, 0.0, 1.0);
	this->lp.material_shininess = 125.0;
}
void WCX_sphere::setFlatNormals(){
	for(int i=0; i<this->vertex_size/3; i++){
		point4 a = this->sphere_points[i*3+1] - this->sphere_points[i*3];
		point4 b = this->sphere_points[i*3+2] - this->sphere_points[i*3+1];
		point3 a3(a.x, a.y, a.z), b3(b.x, b.y, b.z);
		point3 vNormal = cross(a3,b3);
		vNormal = normalize(vNormal);
		for(int j=0; j<3; j++)	this->sphere_normals[i*3+j] = vNormal;
	}
}
/*
 1: texture mapping for ground
 2: vertical in obj frame
 3: slanted in obj frame
 4: vertical in eye frame
 5: slanted in eye frame
 in 2D, +4
 default: no texture
*/
int WCX_sphere::getTextureAppFlag(){
	if(!this->textureFlag || !this->fill_flag)	return 0;
	return this->textureCoordFrame+this->textureCoordDir+4*this->texture2D;
}