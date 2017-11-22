#include "light.h"
void WCX_light::getProduct(WCX_light_products &lp){
	lp.ambient_product = (global_ambient+light_ambient)*lp.material_ambient;
	lp.diffuse_product = (light_diffuse)*lp.material_diffuse;
	lp.specular_product = (light_specular)*lp.material_specular;
}
void WCX_light::getProduct2(WCX_light_products &lp){
	lp.ambient_product2 = (light_ambient2)*lp.material_ambient;
	lp.diffuse_product2 = (light_diffuse2)*lp.material_diffuse;
	lp.specular_product2 = (light_specular2)*lp.material_specular;
}