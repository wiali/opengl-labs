/*
 * class for light
 * Author: Weichen Xu
 * Date : 12/07/2015
 * Store ambient, diffuse, specular light attributes
*/
#ifndef  _WCX_light
#define  _WCX_light
#include "Angel-yjc.h"
#include "light_products.h"
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
class WCX_light{
public:
	// source 1
	color4 global_ambient;
	color4 light_ambient;
    color4 light_diffuse;
    color4 light_specular;
    float const_att;
    float linear_att;
    float quad_att;
    point4 light_position; 
	point4 light_direction;
	// source 2
	//color4 global_ambient;
	color4 light_ambient2;
    color4 light_diffuse2;
    color4 light_specular2;
	float light_range2;
	float light_exp2;
	float const_att2;
    float linear_att2;
    float quad_att2;
    point4 light_position2; 
	point4 light_direction2;
	// function generate 
	// product light * material
	int smooth;
	int point;
	void getProduct(WCX_light_products &lp);
	void getProduct2(WCX_light_products &lp);
};
#endif