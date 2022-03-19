#include "gui/viewer.hpp"

Viewer::Viewer(QWidget *parent)
    : QOpenGLWidget(parent),
      vbo_(QOpenGLBuffer::VertexBuffer),
      yaw_(0.0),
      pitch_(0.0),
      sensitivity_(0.002),
      move_speed_(0.1),
      camera_pos_(-5.0f, 0.0f, 0.0f),
      camera_target_(0.0f, 0.0f, 0.0f),
      camera_direction_(cos(yaw_) * cos(pitch_), sin(pitch_),
                        sin(yaw_) * cos(pitch_)),
      camera_right_(
          QVector3D::crossProduct({0.0f, 1.0f, 0.0f}, camera_direction_)),
      camera_up_(QVector3D::crossProduct(camera_direction_, camera_right_)) {
  this->setFocusPolicy(Qt::StrongFocus);
  vertices_ = {-0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
               0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

               -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

               -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
               -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

               0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
               0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

               -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
               0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

               -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
               0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};
  cell_color_vectors_ = {
      {0.5f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.0f, 1.0f},
      {0.0f, 0.0f, 0.5f, 1.0f}, {0.5f, 0.3f, 0.0f, 1.0f},
      {0.5f, 0.3f, 0.6f, 1.0f},
  };
  cell_positions_ = {
      {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 2.0f, 1.0f},
      {1.0f, 4.0f, 1.0f}, {1.0f, 1.0f, 5.0f},
  };
}

void Viewer::initializeGL() {
  this->initializeOpenGLFunctions();

  if (!shader_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               ":/opengl/viewer.vert")) {
    qDebug() << "ERROR:" << shader_program_.log();
  }
  if (!shader_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               ":/opengl/viewer.frag")) {
    qDebug() << "ERROR:" << shader_program_.log();
  }
  if (!shader_program_.link()) {
    qDebug() << "ERROR:" << shader_program_.log();
  }
  QOpenGLVertexArrayObject::Binder{&vao_};
  vbo_.create();
  vbo_.bind();

  vbo_.allocate(vertices_.data(), sizeof(double) * vertices_.size());

  shader_program_.setAttributeBuffer("pos_", GL_DOUBLE, 0, 3,
                                     sizeof(GLdouble) * 3);
  shader_program_.enableAttributeArray("pos_");

  this->glEnable(GL_DEPTH_TEST);
}
void Viewer::paintGL() {
  this->glClearColor(1, 1, 1, 1);
  this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_program_.bind();

  QMatrix4x4 view;
  view.lookAt(camera_pos_, camera_pos_ + camera_direction_, camera_up_);
  shader_program_.setUniformValue("view", view);

  QMatrix4x4 projection;
  projection.perspective(45.0, width() / (double)height(), 0.1, 100.0);
  shader_program_.setUniformValue("projection", projection);
  QOpenGLVertexArrayObject::Binder{&vao_};
  for (qsizetype i = 0; i < cell_positions_.size(); ++i) {
    QMatrix4x4 model;
    model.translate(cell_positions_[i]);
    shader_program_.setUniformValue("model", model);
    shader_program_.setUniformValue("color", cell_color_vectors_[i]);
    this->glDrawArrays(GL_TRIANGLES, 0, 36);
  }
}
void Viewer::resizeGL(int w, int h) { this->glViewport(0, 0, w, h); }

void Viewer::mousePressEvent(QMouseEvent *event) { last_pos_ = event->pos(); }
void Viewer::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons()) {
    double dx = event->pos().x() - last_pos_.x();
    double dy = event->pos().y() - last_pos_.y();
    //    qDebug() << dx << dy;
    yaw_ -= dx * sensitivity_;
    pitch_ += dy * sensitivity_;
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
    //    qDebug() << yaw_ << pitch_;
    last_pos_ = event->pos();
    update();
  }
}
void Viewer::wheelEvent(QWheelEvent *event) {
  double n = event->angleDelta().y();
  camera_pos_ += camera_direction_ * n * sensitivity_;
  update();
}

void Viewer::keyPressEvent(QKeyEvent *event) {
  //  qDebug() << event->key();
  if (event->key() == Qt::Key_K) {
    camera_pos_.setY(camera_pos_.y() + move_speed_);
  } else if (event->key() == Qt::Key_J) {
    camera_pos_.setY(camera_pos_.y() - move_speed_);
  } else if (event->key() == Qt::Key_W) {
    camera_pos_ += camera_direction_ * move_speed_;
  } else if (event->key() == Qt::Key_S) {
    camera_pos_ -= camera_direction_ * move_speed_;
  } else if (event->key() == Qt::Key_A) {
    camera_pos_ -=
        QVector3D::crossProduct(camera_direction_, camera_up_) * move_speed_;
  } else if (event->key() == Qt::Key_D) {
    camera_pos_ +=
        QVector3D::crossProduct(camera_direction_, camera_up_) * move_speed_;
  } else if (event->key() == Qt::Key_Left) {
    yaw_ -= 5 * sensitivity_;
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  } else if (event->key() == Qt::Key_Right) {
    yaw_ += 5 * sensitivity_;
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  } else if (event->key() == Qt::Key_Up) {
    pitch_ += 5 * sensitivity_;
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));

  } else if (event->key() == Qt::Key_Down) {
    pitch_ -= 5 * sensitivity_;
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  }
  update();
}

void Viewer::reset_camera() {
  yaw_ = 0.0;
  pitch_ = 0.0;
  sensitivity_ = 0.002;
  move_speed_ = 0.1;
  camera_pos_ = {-5.0f, 0.0f, 0.0f};
  camera_target_ = {0.0f, 0.0f, 0.0f};
  camera_direction_ = {cos(yaw_) * cos(pitch_), sin(pitch_),
                       sin(yaw_) * cos(pitch_)};
  camera_right_ =
      QVector3D::crossProduct({0.0f, 1.0f, 0.0f}, camera_direction_);
  camera_up_ = QVector3D::crossProduct(camera_direction_, camera_right_);
  update();
}
