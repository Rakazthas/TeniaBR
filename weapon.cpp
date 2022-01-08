#include "weapon.h"

Weapon::Weapon()
{
    weight = 0;
    elasticity = 0;
}

void Weapon::setType(int type){
    if(type<1)
        category = 1;
    else if(type>3)
        category = 3;
    else
        category = type;
}

void Weapon::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    //Transform newTransform = transform.combineTransforms(globalTransform);
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);

    program->setUniformValue("texture", category);

    GeometryEngine *geometries = new GeometryEngine(category); //ajouter constructeurs specifiques worms/objet/map
    geometries->drawWormGeometry(program);

    updateBoundingBox(newTransform);

    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
