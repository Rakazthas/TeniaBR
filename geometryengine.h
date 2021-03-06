#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(int type);

    void drawGeometry(QOpenGLShaderProgram *program);

private:
    void initWormGeometry();
    void initLauncherGeometry();
    void initGrenadeGeometry();
    void initShotgunGeometry();
    void initRocketGeometry();
    void initBulletGeometry();
    void initFloorGeometry();
    void initSkyGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

};

#endif // GEOMETRYENGINE_H
