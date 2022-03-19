#ifndef CASIM_GUI_VIEWER_HPP_
#define CASIM_GUI_VIEWER_HPP_

#include "gui/common.hpp"

class Viewer : public QOpenGLWidget, public QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  explicit Viewer(QWidget *parent = nullptr);

 protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;

 public slots:
  void reset_camera();

 private:
  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_;
  QOpenGLShaderProgram shader_program_;

  QVector<double> vertices_;
  QVector<QVector3D> cell_positions_;
  QVector<QVector4D> cell_color_vectors_;

  float yaw_;
  float pitch_;
  float sensitivity_;
  float move_speed_;

  QVector3D camera_pos_;
  QVector3D camera_target_;
  QVector3D camera_direction_;
  QVector3D camera_right_;
  QVector3D camera_up_;

  QPoint last_pos_;

  QPointer<casim::core::Automaton> automaton_;
};

#endif
