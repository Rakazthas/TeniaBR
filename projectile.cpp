#include "projectile.h"

Projectile::Projectile()
{
    category = 4;

    weight = 0.1;
    elasticity = 0;

    transform = Transform();



    height = 0.15f;
    width = 0.2f;

    updateBoundingBox();

    damage = 3;
    dmgRadius = 1.5f;
}

Projectile::Projectile(Transform transform){
    category = 4;

    weight = 0.1;
    elasticity = 0;

    this->transform = transform;



    height = 0.2;
    width =0.3 ;
    updateBoundingBox();

    damage = 3;
    dmgRadius = 1.5f;
}

int Projectile::getDamage(){return damage;}
float Projectile::getDmgRadius(){return dmgRadius;}

void Projectile::setDamage(int newDmg){
    damage = newDmg;
}
void Projectile::setDmgRadius(float newRadius){
    dmgRadius = newRadius;
}

void Projectile::setType(int type){
    if(type<4){
        category = 4;
        height = 0.2;
        width = 0.3;
    }
    else if(type>6){
        category = 6;
        height = 0.3;
        width = 0.3;
    }
    else{
        category = type;
        height = 0.05;
        width = 0.1;
    }

    updateBoundingBox();
}

void Projectile::handleCollision(GameObject *collider){
    if(category == 4 || category == 5)
        boom = true;
    else
        GameObject::handleCollision(collider);
}

bool Projectile::needDestroy(){
    return boom;
}

void Projectile::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    //Transform newTransform = transform.combineTransforms(globalTransform);
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);

    program->setUniformValue("texture", category);

    GeometryEngine *geometries = new GeometryEngine(category);
    geometries->drawGeometry(program);

    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
