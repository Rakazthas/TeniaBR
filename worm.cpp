#include "worm.h"


Worm::Worm()
{
    category = 0;

    weight = 1;

    transform = Transform();

    height = 0.5;
    width = 0.5;

    hp = 20;

    updateBoundingBox();
}

Worm::Worm(Transform transform)
{
    category = 0;

    weight = 1;

    this->transform = transform;

    height = 1;
    width = 1;

    hp = 20;

    updateBoundingBox();
}


int Worm::getHp(){return hp;}

void Worm::setHp(int newHP){
    hp = newHP;
}

bool Worm::needDestroy(){
    return hp<1;
}

/*
 * render ver
 * */
void Worm::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
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
