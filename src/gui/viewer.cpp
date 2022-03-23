#include "gui/viewer.hpp"

Viewer::Viewer(QWidget* parent)
    : QOpenGLWidget(parent),
      vbo_(QOpenGLBuffer::VertexBuffer),
      yaw_(0.0),
      pitch_(0.0),
      sensitivity_(0.002),
      move_speed_(0.1),
      cell_size_(10),
      view_mode_(ViewMode::Refresh),
      acc_axis_(0),
      acc_cnt_(0),
      camera_pos_(0.0f, 0.0f, 0.0f),
      camera_target_(0.0f, 0.0f, 0.0f),
      camera_direction_(cos(yaw_) * cos(pitch_),
                        sin(pitch_),
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
      {0.5f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 0.5f},
      {0.5f, 0.3f, 0.0f}, {0.5f, 0.3f, 0.6f},
  };
  cell_positions_ = {
      {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 2.0f, 1.0f},
      {1.0f, 4.0f, 1.0f}, {1.0f, 1.0f, 5.0f},
  };
}

void Viewer::set_automaton(QSharedPointer<casim::core::Automaton> automaton) {
  automaton_ = automaton;
}

void Viewer::initializeGL() {
  emit yaw_changed(yaw_);
  emit pitch_changed(pitch_);
  emit sensitivity_changed(sensitivity_);
  emit move_speed_changed(move_speed_);
  emit cell_size_changed(cell_size_);

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
  this->glClearColor(background_color_.redF(), background_color_.greenF(),
                     background_color_.blueF(), 1);
  this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_program_.bind();

  QMatrix4x4 view;
  view.lookAt(camera_pos_, camera_pos_ + camera_direction_, camera_up_);
  shader_program_.setUniformValue("view", view);

  QMatrix4x4 projection;
  // TODO: perspective/orthographic switch
  // TODO: near/far plane auto adjust
  // projection.perspective(45.0, width() / (double)height(), 0.1, 100.0);
  projection.ortho(-(float)width() / 2 / cell_size_,
                   (float)width() / 2 / cell_size_,
                   (float)height() / 2 / cell_size_,
                   -(float)height() / 2 / cell_size_, -100, 100.0f);
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
void Viewer::resizeGL(int w, int h) {
  this->glViewport(0, 0, w, h);
}

void Viewer::mousePressEvent(QMouseEvent* event) {
  last_pos_ = event->pos();
}
void Viewer::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons()) {
    double dx = event->pos().x() - last_pos_.x();
    double dy = event->pos().y() - last_pos_.y();
    yaw_ += dx * sensitivity_;
    pitch_ += dy * sensitivity_;

    emit yaw_changed(yaw_);
    emit pitch_changed(pitch_);

    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
    last_pos_ = event->pos();
    update();
  }
}
void Viewer::wheelEvent(QWheelEvent* event) {
  float n = event->angleDelta().y();

  float x = event->position().x() - width() / 2;
  float y = height() - event->position().y() - height() / 2;

  x /= cell_size_;
  y /= cell_size_;

  float sgn = n > 0 ? 80 : -80;
  cell_size_ *= 1 + n * sensitivity_;

  emit cell_size_changed(cell_size_);

  camera_pos_ += sgn * QVector3D::crossProduct(camera_direction_, camera_up_) *
                 x * sensitivity_;
  camera_pos_.setY(camera_pos_.y() - sgn * y * sensitivity_);
  update();
}

void Viewer::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_K) {
    camera_pos_.setY(camera_pos_.y() - move_speed_);
  } else if (event->key() == Qt::Key_J) {
    camera_pos_.setY(camera_pos_.y() + move_speed_);
  } else if (event->key() == Qt::Key_W) {
    emit cell_size_changed(cell_size_);
    cell_size_ *= 1 + move_speed_;
  } else if (event->key() == Qt::Key_S) {
    emit cell_size_changed(cell_size_);
    cell_size_ *= 1 - move_speed_;
  } else if (event->key() == Qt::Key_A) {
    camera_pos_ -=
        QVector3D::crossProduct(camera_direction_, camera_up_) * move_speed_;
  } else if (event->key() == Qt::Key_D) {
    camera_pos_ +=
        QVector3D::crossProduct(camera_direction_, camera_up_) * move_speed_;
  } else if (event->key() == Qt::Key_Left) {
    yaw_ -= 5 * sensitivity_;
    emit yaw_changed(yaw_);
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  } else if (event->key() == Qt::Key_Right) {
    yaw_ += 5 * sensitivity_;
    emit yaw_changed(yaw_);
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  } else if (event->key() == Qt::Key_Up) {
    pitch_ -= 5 * sensitivity_;
    emit pitch_changed(pitch_);
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));

  } else if (event->key() == Qt::Key_Down) {
    pitch_ += 5 * sensitivity_;
    emit pitch_changed(pitch_);
    camera_direction_.setX(cos(yaw_) * cos(pitch_));
    camera_direction_.setY(sin(pitch_));
    camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  }
  update();
}

void Viewer::reset_camera() {
  yaw_ = 0.0;
  pitch_ = 0.0;
  camera_pos_ = {0.0f, 0.0f, 0.0f};
  camera_target_ = {0.0f, 0.0f, 0.0f};
  camera_direction_ = {(float)cos(yaw_) * (float)cos(pitch_),
                       (float)sin(pitch_),
                       (float)sin(yaw_) * (float)cos(pitch_)};
  camera_right_ =
      QVector3D::crossProduct({0.0f, 1.0f, 0.0f}, camera_direction_);
  camera_up_ = QVector3D::crossProduct(camera_direction_, camera_right_);

  emit yaw_changed(yaw_);
  emit pitch_changed(pitch_);

  update();
}

void Viewer::reset_view() {
  if (view_mode_ == ViewMode::Accumulate) {
    size_t dim = automaton_->get_dim();
    if (dim == 3) {
      view_mode_ = ViewMode::Refresh;
      return;
    }
    acc_axis_ = dim;
    acc_cnt_ = 0;
  }

  acc_cnt_ = 0;
  cell_positions_.clear();
  cell_color_vectors_.clear();
}

void Viewer::display_automaton() {
  if (view_mode_ == ViewMode::Refresh) {
    cell_positions_.clear();
    cell_color_vectors_.clear();
  } else {
    acc_cnt_++;
  }

  QColor color_vector;

  auto generation = automaton_->get_curr_generation();
  auto shape = automaton_->get_shape();
  auto state_color_list = automaton_->get_state_color_list();

  if (automaton_->get_dim() == 1) {
    generation.reshape({1, 1, shape[0]});
  } else if (automaton_->get_dim() == 2) {
    generation.reshape({1, shape[0], shape[1]});
  }

  auto shape3d = generation.shape();

  // camera_pos_.setX((float)shape3d[2] / 2);
  // camera_pos_.setY((float)shape3d[1] / 2);

  for (size_t i = 0; i < shape3d[0]; ++i) {
    for (size_t j = 0; j < shape3d[1]; ++j) {
      for (size_t k = 0; k < shape3d[2]; ++k) {
        uint32_t state = generation[{i, j, k}];
        if (state == 0)
          continue;
        if (view_mode_ == ViewMode::Refresh) {
          cell_positions_.push_back({(float)i, (float)j, (float)k});
        } else {
          if (acc_axis_ == 1) {
            cell_positions_.push_back(
                {(float)i, (float)j + acc_cnt_, (float)k});
          } else if (acc_axis_ == 2) {
            cell_positions_.push_back(
                {(float)i + acc_cnt_, (float)j, (float)k});
          }
        }
        color_vector.setNamedColor(state_color_list[state].c_str());
        cell_color_vectors_.push_back(QVector3D(
            color_vector.redF(), color_vector.greenF(), color_vector.blueF()));
      }
    }
  }
  update();
}

void Viewer::set_yaw(const float& yaw) {
  yaw_ = yaw;
  camera_direction_.setX(cos(yaw_) * cos(pitch_));
  camera_direction_.setY(sin(pitch_));
  camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  update();
}

void Viewer::set_pitch(const float& pitch) {
  pitch_ = pitch;
  camera_direction_.setX(cos(yaw_) * cos(pitch_));
  camera_direction_.setY(sin(pitch_));
  camera_direction_.setZ(sin(yaw_) * cos(pitch_));
  update();
}

void Viewer::set_sensitivity(const float& sensitivity) {
  sensitivity_ = sensitivity;
}

void Viewer::set_move_speed(const float& move_speed) {
  move_speed_ = move_speed;
}

void Viewer::set_cell_size(const float& cell_size) {
  cell_size_ = cell_size;
  update();
}

void Viewer::set_view_mode(const ViewMode& view_mode) {
  view_mode_ = view_mode;
  if (view_mode_ == ViewMode::Accumulate) {
    size_t dim = automaton_->get_dim();
    if (dim == 3) {
      view_mode_ = ViewMode::Refresh;
      return;
    }
    acc_axis_ = dim;
    acc_cnt_ = 0;
  }
}
