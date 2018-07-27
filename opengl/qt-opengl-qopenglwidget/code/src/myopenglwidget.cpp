#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

/**
 * @brief 初期化処理を記述する。
 */
void MyOpenGLWidget::initializeGL()
{
    // OpenGL の API を呼ぶ前に呼ぶ。
    initializeOpenGLFunctions();
}

/**
 * @brief リサイズされた際の処理を記述する。
 */
void MyOpenGLWidget::resizeGL(int width, int height)
{
}

/**
 * @brief 描画する際の処理を記述する。
 */
void MyOpenGLWidget::paintGL()
{
    glBegin(GL_TRIANGLES);
    glColor3d(1, 0, 0);
    glVertex3d(0, 0.8, 0);
    glVertex3d(-0.8, 0, 0);
    glVertex3d(0.8, 0, 0);
    glEnd();
}
