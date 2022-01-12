#include "mainwidget.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include <math.h>



MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    textureWorm(0),
    textureLauncher(0),
    textureFloor(0),
    angularSpeed(0)
{
    objects = std::vector<GameObject*>();

    Transform worm1Transform = Transform();
    worm1Transform.setTranslation(QVector3D(2.0,0.0,0.0));
    worm1Transform.setScale(QVector3D(-1.0,1.0,1.0));

    Transform worm2Transform = Transform();
    worm2Transform.setTranslation(QVector3D(-3.0, 1.0,0.0));
    worm2Transform.setScale(QVector3D(-1.0,1.0,1.0));

    Transform worm3Transform = Transform();
    worm3Transform.setTranslation(QVector3D(2.0,1.5,0.0));

    Worm *worm1 = new Worm(worm1Transform);
    Worm *worm2 = new Worm(worm2Transform);
    Worm *worm3 = new Worm(worm3Transform);

    objects.push_back(worm1);
    objects.push_back(worm2);
    objects.push_back(worm3);

    currWorm = objects[0];

    Transform weaponTransform = Transform();
    Weapon *wormWeapon = new Weapon(weaponTransform);

    currWorm->addChild(wormWeapon);
    currWeapon = wormWeapon;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete textureWorm;
    delete textureLauncher;
    delete textureFloor;
    doneCurrent();
}


void MainWidget::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Right:
            currWorm->setMovement(QVector2D(10, currWorm->getMovement().y()));
        break;

        case Qt::Key_Left:
            currWorm->setMovement(QVector2D(-10, currWorm->getMovement().y()));
        break;

        case Qt::Key_Space:
            currWorm->setMovement(QVector2D(currWorm->getMovement().x(),60));
        break;

        default:
        break;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *){
}


//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    //applique mouvement + verif si hors sol
    for(unsigned int i = 0; i < objects.size(); i++){
        objects[i]->applyMovement(deltaT);

        QVector2D pos = objects[i]->getPos();
        QVector2D downBox, upBox;
        objects[i]->getBoundingBox(&upBox, &downBox);

        if(downBox.y()<0){
            objects[i]->setPos(QVector2D(pos.x(), pos.y()+(-downBox.y())));
        }
    }

    //verifie et gere collisions
    for(unsigned int i = 0; i < objects.size(); i++){
        QVector2D downBoxI, upBoxI;
        objects[i]->getBoundingBox(&upBoxI, &downBoxI);

        for(unsigned int j = i+1; j < objects.size(); j++){
            QVector2D downBoxJ, upBoxJ;
            objects[j]->getBoundingBox(&upBoxJ, &downBoxJ);

            if(     downBoxI.x()-upBoxJ.x()<=0 &&
                    downBoxI.y()-upBoxJ.y()<=0&&
                    downBoxJ.x()-upBoxI.x()<=0&&
                    downBoxJ.y()-upBoxI.y()<=0){
                //collision
                //qWarning() << "Collision entre " << i << "et" << j;
                objects[i]->handleCollision(objects[j]);
                objects[j]->handleCollision(objects[i]);
            }else{
                //qWarning() << "Pas de collision entre " << i << "et" << j;
            }
        }
    }

    QVector2D p = QVector2D(QCursor::pos());

    //float angle = acos(p.x()/(sqrt(pow(p.x(),2)+pow(p.y(),2))));
    float angle = atan2(p.y(), p.x());

    Transform newTrans = currWeapon->getTransform();
    newTrans.setRotationAngAxis(angle, QVector3D(0,0,1));
    currWeapon->setTransform(newTrans);

    update();
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

    textureFloor = new QOpenGLTexture(QImage(":/floor.png"));
    textureFloor->setMinificationFilter(QOpenGLTexture::Nearest);
    textureFloor->setMagnificationFilter(QOpenGLTexture::Linear);
    textureFloor->setWrapMode(QOpenGLTexture::ClampToEdge);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 2.0, zFar = 60.0, fov = 45.0;

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
    textureFloor->bind(7);


//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    //matrix.rotate(90,1,0,0);
    //matrix.rotate(rotation);
    matrix.scale(QVector3D(scale,scale,scale));


    geometries = new GeometryEngine(7);
    program.setUniformValue("texture", 7);
    geometries->drawGeometry(&program);



    // Set modelview-projection matrix
    //program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]



    for(unsigned int i = 0; i < objects.size(); i++){
        objects[i]->render(matrix, &program, projection);
    }

}
