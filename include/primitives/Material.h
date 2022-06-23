//
// Created by shoham on 6/18/22.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


class Material {
public:
    double specular =0, diffusive= 0, transparent = 0, reflective = 0;
    int shininess =0;

    Material();
    Material setSpecular(double s);
    Material setDiffusive(double d);
    Material setTransparent(double t);
    Material setReflective(double r);
    Material setShininess(int shine);

};


#endif //RAYTRACER_MATERIAL_H
