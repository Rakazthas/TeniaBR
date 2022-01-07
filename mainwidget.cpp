#include "mainwidget.h"

#include <QMouseEvent>
#include <QKeyEvent>

#include <math.h>

#include "gameobject.h"
#include "worm.h"
#include "weapon.h"
#include "transform.h"


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    textureWorm(0),
    textureLauncher(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete textureWorm;
    delete textureLauncher;
    delete geometries;
    doneCurrent();
}


void MainWidget::keyPressEvent(QKeyEvent *e){

}

void MainWidget::keyReleaseEvent(QKeyEvent *){

}

//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed = 0.8;
    rotationAxis = QVector3D(0.0,0.0,1.0);
    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation


        if(scale < 0)
            scale = 0;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);
//! [2]

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load .png image
    textureWorm = new QOpenGLTexture(QImage(":/base_sprite.png"));

    // Set nearest filtering mode for texture minification
    textureWorm->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    textureWorm->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    textureWorm->setWrapMode(QOpenGLTexture::ClampToEdge);

    textureLauncher = new QOpenGLTexture(QImage(":/launcher.png"));
    textureLauncher->setMinificationFilter(QOpenGLTexture::Nearest);
    textureLauncher->setMagnificationFilter(QOpenGLTexture::Linear);
    textureLauncher->setWrapMode(QOpenGLTexture::ClampToEdge);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 2.0, zFar = 10.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    textureWorm->bind(0);
    textureLauncher->bind(1);


//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(135,1,0,0);
    matrix.rotate(rotation);
    matrix.scale(QVector3D(scale,scale,scale));


    // Set modelview-projection matrix
    //program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 1);


    std::vector<QVector3D> vertices;
    std::vector<std::vector<int>> faces;


    Worm testWorm;
    Transform testWormTransform;

    Weapon testLauncher;
    Transform testLauncherTransform;

    testLauncher.setType(1);
    testLauncherTransform.setRotationAngAxis(20, QVector3D(0,1,0));

    testWorm.setTransform(testWormTransform);
    testLauncher.setTransform(testLauncherTransform);

    testWorm.addChild(&testLauncher);

    testWorm.render(matrix, &program, projection);


}