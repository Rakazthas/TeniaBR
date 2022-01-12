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
    textureGrenade(0),
    textureShotgun(0),
    textureRocket(0),
    textureBullet(0),
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

    currProj = nullptr;


    QWidget::setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete textureWorm;
    delete textureLauncher;
    delete textureGrenade;
    delete textureShotgun;
    delete textureRocket;
    delete textureBullet;
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

        case Qt::Key_1:
            currWeapon->setType(1);
        break;

        case Qt::Key_2:
            currWeapon->setType(2);
        break;

        case Qt::Key_3:
            currWeapon->setType(3);
        break;

        default:
        break;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *){
}

void MainWidget::mouseMoveEvent(QMouseEvent *event){
    mousePos = QVector2D(event->localPos());
}

void MainWidget::mousePressEvent(QMouseEvent *e){
    if(currProj == nullptr){
        QVector2D initPos = currWorm->getPos();
        QVector2D initDir = QVector2D(e->localPos())-initPos;

        Transform initTransform = Transform();
        initTransform.setTranslation(QVector3D(initPos.x() + 1.2*(initDir.x()/abs(initDir.x())),
                                               initPos.y() + 1.2*(initDir.y()/abs(initDir.y())),
                                               0));
        if(initDir.x()<0)
            initTransform.setScale(QVector3D(-1,1,1));

        Projectile *proj = new Projectile(initTransform);
        if(currWeapon->getType()==1){
            proj->setType(4);
        }
        if(currWeapon->getType()==2){
            proj->setType(5);
        }
        if(currWeapon->getType()==3){
            proj->setType(6);
        }
        currProj = proj;
        currProj->setMovement(initDir/10);

        objects.push_back(proj);

    }
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
                objects[i]->handleCollision(objects[j]);
                objects[j]->handleCollision(objects[i]);
            }
         }
    }

    /*for(unsigned int i = objects.size() - 1; i >= 0; i--){
        if(objects[i]->needDestroy()){
            //destruction
            if(typeid (objects[i]) == typeid (Projectile)){
                //handle boom
            }
            //call destroychildren
            if(objects[i] == currWorm)
                currWorm = nullptr;
            if(objects[i] == currProj)
                currProj = nullptr;

            delete objects[i];
            objects.erase(objects.begin()+i);
        }
    }*/

    QVector2D direction = mousePos-currWorm->getPos();
    QVector2D ref = QVector2D(1,0);

    float angle = acos(QVector2D::dotProduct(direction, ref)/(direction.length()*ref.length()));
    angle *= 180.0/M_PI;

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

    textureGrenade = new QOpenGLTexture(QImage(":/grenade.png"));
    textureGrenade->setMinificationFilter(QOpenGLTexture::Nearest);
    textureGrenade->setMagnificationFilter(QOpenGLTexture::Linear);
    textureGrenade->setWrapMode(QOpenGLTexture::ClampToEdge);

    textureShotgun = new QOpenGLTexture(QImage(":/shotgun.png"));
    textureShotgun->setMinificationFilter(QOpenGLTexture::Nearest);
    textureShotgun->setMagnificationFilter(QOpenGLTexture::Linear);
    textureShotgun->setWrapMode(QOpenGLTexture::ClampToEdge);

    textureRocket = new QOpenGLTexture(QImage(":/rocket.png"));
    textureRocket->setMinificationFilter(QOpenGLTexture::Nearest);
    textureRocket->setMagnificationFilter(QOpenGLTexture::Linear);
    textureRocket->setWrapMode(QOpenGLTexture::ClampToEdge);

    textureBullet = new QOpenGLTexture(QImage(":/small_bullet.png"));
    textureBullet->setMinificationFilter(QOpenGLTexture::Nearest);
    textureBullet->setMagnificationFilter(QOpenGLTexture::Linear);
    textureBullet->setWrapMode(QOpenGLTexture::ClampToEdge);

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
    textureGrenade->bind(2);
    textureShotgun->bind(3);
    textureRocket->bind(4);
    textureGrenade->bind(5);
    textureBullet->bind(6);
    textureFloor->bind(7);


//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -25.0);
    //matrix.rotate(90,1,0,0);
    //matrix.rotate(rotation);
    //matrix.scale(QVector3D(scale,scale,scale));


    geometries = new GeometryEngine(7);
    program.setUniformValue("mvp_matrix", projection * matrix);
    program.setUniformValue("texture", 7);
    geometries->drawGeometry(&program);



    // Set modelview-projection matrix
    //program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]



    for(unsigned int i = 0; i < objects.size(); i++){
        objects[i]->render(matrix, &program, projection);
    }

}
