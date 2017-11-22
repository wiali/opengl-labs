#pragma once
#include "Angel-yjc.h"
typedef Angel::vec4  color4;
struct WCX_light_products{
	// for source 1
	color4 ambient_product;
    color4 diffuse_product;
    color4 specular_product;
	// for source 2
	color4 ambient_product2;
    color4 diffuse_product2;
    color4 specular_product2;
	// material
	color4 material_ambient;
    color4 material_diffuse;
    color4 material_specular;
    float  material_shininess;
};