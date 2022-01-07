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

    if(type == 0)
        initWormGeometry();
    else if(type==1)
        initLauncherGeometry();
}

void GeometryEngine::initWormGeometry(){

    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D(-1.0f, 1.0f,  -1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, 1.0f,  -1.0f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)}
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

void GeometryEngine::drawWormGeometry(QOpenGLShaderProgram *program){
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


void GeometryEngine::initLauncherGeometry(){
    unsigned int vertexNumber = 4;
    VertexData vertices[] = {
        {QVector3D(-1.0f, 1.0f,  -0.5f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, 1.0f,  -0.5f), QVector2D(1.0f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)}
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
