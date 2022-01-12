#include "gameobject.h"

GameObject::GameObject()
{
    parent = nullptr;
    children = std::vector<GameObject*>();
    transform = Transform();

    movement = QVector2D(0,0);

}

/*
 * Getters
*/
GameObject* GameObject::getParent(){return parent;}
std::vector<GameObject*> GameObject::getChildren(){return children;}
Transform GameObject::getTransform(){return transform;}
float GameObject::getWeight(){return weight;}
float GameObject::getElasticity(){return elasticity;}
bool GameObject::testLink(){return isLink;}
QVector2D GameObject::getPos(){return worldPosition;}
QVector2D GameObject::getMovement(){return movement;}
float GameObject::getHeight(){return height;}
float GameObject::getWidth(){return width;}

void GameObject::getBoundingBox(QVector2D *upRight, QVector2D *downLeft){
    *upRight = AABB[1];
    *downLeft = AABB[0];
}

/*
 * sets
 * */
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
    worldPosition = newPos;

    //todo gerer changement pos si objet enfant (donc pas world coodrinates)
    transform.setTranslation(QVector3D(worldPosition.x(), worldPosition.y(), 0));
}

void GameObject::setMovement(QVector2D move){
    movement = move;
}


/*
 * Update box selon coordonnees monde
 * */
void GameObject::updateBoundingBox(){
    QMatrix4x4 worldTransform = getWorldTransform();

    worldPosition = QVector2D(worldTransform(0,3), worldTransform(1,3));
    float scaleX = worldTransform.column(0).length();
    float scaleY = worldTransform.column(1).length();
    worldScale = QVector2D(scaleX, scaleY);
    worldRotationAxis = std::acos(worldTransform(0,0)); //a verif

    float tempx[4], tempy[4], x[4], y[4];
    tempx[0] = -width*scaleX; tempx[1] = width*scaleX; tempx[2] = -width*scaleX; tempx[3] = width*scaleX;
    tempy[0] = height*scaleY; tempy[1] = height*scaleY; tempy[2] = -height*scaleY; tempy[3] = -height*scaleY;

    for(unsigned int i = 0; i < 4; i++){
        x[i] = tempx[i]*std::cos(worldRotationAxis) - tempy[i]*std::sin(worldRotationAxis);
        y[i] = tempx[i]*std::sin(worldRotationAxis) + tempy[i]*std::cos(worldRotationAxis);

        x[i] += worldPosition.x();
        y[i] += worldPosition.y();
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();

    for(unsigned int i = 0; i < 4; i++){
        if(x[i] < minX)
            minX = x[i];
        if(x[i] > maxX)
            maxX = x[i];
        if(y[i] < minY)
            minY = y[i];
        if(y[i] > maxY)
            maxY = y[i];
    }

    AABB[0] = QVector2D(minX, minY);
    AABB[1] = QVector2D(maxX, maxY);
}


/*
 *
 * recupere les coordonees monde via l'objet parent
 * */
QMatrix4x4 GameObject::getWorldTransform(){
    if(parent == nullptr){
        return transform.getTransform();
    }else{
        return parent->getWorldTransform()*transform.getTransform();
    }
}


/*
 * gere le deplacement et la gravite
 * */
void GameObject::applyMovement(float time){
    float translateX, translateY = 0;

    translateX = movement.x()*time;
    if(AABB[0].y()>0.01 || movement.y() > 9.91*weight){
        translateY = (-9.81*weight + movement.y())*time;
    }
    QVector3D worldMove = QVector3D(translateX, translateY, 0);

    transform.setTranslation(transform.getTranslation()+worldMove);
    if(movement.x()<0){
        transform.setScale(QVector3D(-1,1,1));
    }
    if(movement.x()>0){
        transform.setScale(QVector3D(1,1,1));
    }

    movement = movement*0.95;
    if(movement.x() < 0.01)
        movement = QVector2D(0, movement.y());
    if(movement.y() < 0.01)
        movement = QVector2D(movement.x(), 0);

    updateBoundingBox();
}

/*gestion generale des collisions
 * */
void GameObject::handleCollision(GameObject *collider){
    QVector2D collPos = collider->getPos();
    QVector2D collUp, collDown;
    collider->getBoundingBox(&collUp, &collDown);
    float diffX = worldPosition.x()-collPos.x();
    float diffY = worldPosition.y()-collPos.y();
    if(diffY > (collider->getHeight()*1/2) && (diffX<(collider->getWidth()*1/2)||diffX>(collider->getWidth()*-1/2))){
        worldPosition = QVector2D(worldPosition.x(), worldPosition.y()+abs(AABB[0].y()-collUp.y()));
    }else if(diffY > -(height*1/2)){
        float weightRatio = collider->getWeight()/(weight+collider->getWeight());//le plus leger recule plus
        if(diffX<0)
            worldPosition = QVector2D(worldPosition.x()-weightRatio*abs(AABB[1].x()-collDown.x()), worldPosition.y());
        else
            worldPosition = QVector2D(worldPosition.x()+weightRatio*abs(AABB[0].x()-collUp.x()), worldPosition.y());
        if(diffX*movement.x()<0)
            movement = QVector2D(0, movement.y());
    }

    transform.setTranslation(QVector3D(worldPosition.x(), worldPosition.y(), 0));
    updateBoundingBox();
}

bool GameObject::needDestroy(){
    return false;
}
/*
 *
 * render d'un gameObject generique : appelle juste le render des enfants
 * */
void GameObject::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);


    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
