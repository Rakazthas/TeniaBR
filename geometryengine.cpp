#include "geometryengine.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

GeometryEngine::GeometryEngine(int type): indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    switch (type) {
        case 0:
            initWormGeometry();
        break;

        case 1:
            initLauncherGeometry();
        break;

        case 2:
            initGrenadeGeometry();
        break;

        case 3:
            initShotgunGeometry();
        break;

        case 4:
            initRocketGeometry();
        break;

        case 5:
            initGrenadeGeometry();
        break;

        case 6:
            initBulletGeometry();
        break;

        case 7:
            initFloorGeometry();
        break;

        default:
        break;
    }
}

void GeometryEngine::initWormGeometry(){

    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D(-1.0f,  1.0f,  0.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f,  1.0f,  0.0f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D(-1.0f, -1.0f,  0.0f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D( 1.0f, -1.0f,  0.0f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initLauncherGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D( -0.5f,  0.35f,  0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(  0.5f,  0.35f,  0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D( -0.5f, -0.35f,  0.5f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D(  0.5f, -0.35f,  0.5f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initGrenadeGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D( -0.30f,  0.30f,  0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(  0.30f,  0.30f,  0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D( -0.30f, -0.30f,  0.5f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D(  0.30f, -0.30f,  0.5f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initShotgunGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D( -0.40f,  0.20f,  0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(  0.40f,  0.20f,  0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D( -0.40f, -0.20f,  0.5f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D(  0.40f, -0.20f,  0.5f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initRocketGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D( -0.3f,  0.2f,  0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(  0.3f,  0.2f,  0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D( -0.3f, -0.2f,  0.5f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D(  0.3f, -0.2f,  0.5f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initBulletGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D( -0.1f,  0.05f,  0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(  0.1f,  0.05f,  0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D( -0.1f, -0.05f,  0.5f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D(  0.1f, -0.05f,  0.5f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}

void GeometryEngine::initFloorGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D(-20.0f,  0.0f,  0.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 20.0f,  0.0f,  0.0f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D(-20.0f, -40.0f,  0.0f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D( 20.0f, -40.0f,  0.0f), QVector2D(1.0f, 1.0f)}
    };

    unsigned int indexCount = 5;
    GLushort indices[] = {
        0, 1, 2, 3, 3
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof (VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, indexCount * sizeof (GLushort));
}




void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program){
    arrayBuf.bind();
    indexBuf.bind();

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset += sizeof (QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof (VertexData));

    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_SHORT, 0);
}
