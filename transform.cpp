#include "transform.h"

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>


Transform::Transform()
{
    _translation = QVector3D();
    _rotation = QQuaternion();
    _scale = QVector3D(1,1,1);

}

Transform::Transform(QVector3D translation, QQuaternion rotation, QVector3D scale){
    _translation = translation;
    _rotation = rotation;
    _scale = scale;
}

Transform::Transform(QVector3D translation, float rotAngle, QVector3D rotAxis, QVector3D scale){
    _translation = translation;
    _rotation = QQuaternion::fromAxisAndAngle(rotAxis, rotAngle);
    _scale = scale;
}


QVector3D Transform::getTranslation(){return _translation;}
QQuaternion Transform::getRotation(){return _rotation;}
QVector3D Transform::getScale(){return _scale;}

void Transform::setTranslation(QVector3D translation){
    _translation = translation;
}
void Transform::setRotation(QQuaternion rotation){
    _rotation = rotation;
}
void Transform::setRotationAngAxis(float angle, QVector3D axis){
    _rotation = QQuaternion::fromAxisAndAngle(axis, angle);
}
void Transform::setScale(QVector3D scale){
    _scale = scale;
}

QMatrix4x4 Transform::getTransform(){
    QMatrix4x4 transform;
    transform.setToIdentity();
    transform.translate(_translation);
    transform.rotate(_rotation);

    transform.scale(_scale);

    return transform;
}

Transform Transform::combineTransforms(Transform otherTransform){
    Transform newTransform;

    newTransform.setTranslation(otherTransform.getTranslation()*_translation);
    newTransform.setRotation(otherTransform.getRotation()*_rotation);
    newTransform.setScale(otherTransform.getScale()*_scale);

    return newTransform;
}
