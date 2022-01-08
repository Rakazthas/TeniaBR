#include "worm.h"

#include<QDebug>

Worm::Worm()
{
    category = 0;
}


int Worm::getHp(){return hp;}

void Worm::setHp(int newHP){
    hp = newHP;
}

void Worm::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    //Transform newTransform = transform.combineTransforms(globalTransform);
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);

    program->setUniformValue("texture", category);

    GeometryEngine *geometries = new GeometryEngine(category); //ajouter constructeurs specifiques worms/objet/map
    geometries->drawWormGeometry(program);

    for(unsigned int i = 0; i < children.size(); i++){
        qWarning() << typeid (children[i]).name();
        children[i]->render(newTransform, program, projection);
    }
}
