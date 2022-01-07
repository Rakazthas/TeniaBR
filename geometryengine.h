#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(int type);

    void drawWormGeometry(QOpenGLShaderProgram *program);
    void drawLauncherGeometry(QOpenGLShaderProgram *program);

private:
    void initWormGeometry();
    void initLauncherGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

};

#endif // GEOMETRYENGINE_H
