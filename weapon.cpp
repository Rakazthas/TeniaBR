#include "weapon.h"

Weapon::Weapon()
{

    category = 1;

    weight = 0;
    elasticity = 0;

    transform = Transform();



    height = 0.25f;
    width = 0.35f;

    updateBoundingBox();


}

Weapon::Weapon(Transform transform){
    category = 1;

    weight = 0;
    elasticity = 0;

    this->transform = transform;



    height = 0.25f;
    width = 0.35f;

    updateBoundingBox();
}

/*
 * category = 1 : bazooka
 * category = 2 : shotgun
 * category = 3 : grenade
 * */
void Weapon::setType(int type){
    if(type<1)
        category = 1;
    else if(type>3)
        category = 3;
    else
        category = type;

    //update width/heigth + box (no collision so not urgent)
}

void Weapon::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    //Transform newTransform = transform.combineTransforms(globalTransform);
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);

    program->setUniformValue("texture", category);

    GeometryEngine *geometries = new GeometryEngine(category); //ajouter constructeurs specifiques worms/objet/map
    geometries->drawGeometry(program);


    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
