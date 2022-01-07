#include "gameobject.h"

GameObject::GameObject()
{
    parent = nullptr;
    children = std::vector<GameObject*>();
    transform = Transform();


}

GameObject* GameObject::getParent(){return parent;}
std::vector<GameObject*> GameObject::getChildren(){return children;}
Transform GameObject::getTransform(){return transform;}
std::vector<QVector3D> GameObject::getVertices(){return vertices;}
std::vector<std::vector<int>> GameObject::getFaces(){return faces;}
float GameObject::getWeight(){return weight;}
float GameObject::getElasticity(){return elasticity;}
bool GameObject::testLink(){return isLink;}
QVector2D GameObject::getPos(){return position;}


void GameObject::setParent(GameObject *newParent){
    parent = newParent;
}
void GameObject::setChildren(std::vector<GameObject *> newChildren){
    children = newChildren;
}
void GameObject::addChild(GameObject *child){
    children.push_back(child);
}
void GameObject::removeChild(GameObject *child){
    child->setParent(NULL);
    std::vector<GameObject*>::iterator pos = std::find(children.begin(), children.end(), child);
    if(pos != children.end())
        children.erase(pos);
}

void GameObject::setTransform(Transform newTransform){
    transform = newTransform;
}

void GameObject::setVertices(std::vector<QVector3D> newVertices){
    vertices = newVertices;
}
void GameObject::setFaces(std::vector<std::vector<int>> newFaces){
    faces = newFaces;
}
void GameObject::setWeight(float newWeight){
    weight = newWeight;
}
void GameObject::setElasticity(float newElasticity){
    elasticity = newElasticity;
}
void GameObject::setLink(bool link){
    isLink = link;
}
void GameObject::setPos(QVector2D newPos){
    position = newPos;
}


void GameObject::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    //Transform newTransform = transform.combineTransforms(globalTransform);
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);


    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
