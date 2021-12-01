#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QQuaternion>




class Transform
{
public:
    Transform();
    Transform(QVector3D translation, QQuaternion rotation, QVector3D scale);
    Transform(QVector3D translation, float rotAngle, QVector3D rotAxis, QVector3D scale);

    QVector3D getTranslation();
    QQuaternion getRotation();
    QVector3D getScale();
    void setTranslation(QVector3D translation);
    void setRotation(QQuaternion rotation);
    void setRotationAngAxis(float angle, QVector3D axis);
    void setScale(QVector3D scale);

    QMatrix4x4 getTransform();

    Transform combineTransforms(Transform otherTransform);

protected:
    QVector3D _translation;
    QQuaternion _rotation;
    QVector3D _scale;
};

#endif // TRANSFORM_H
