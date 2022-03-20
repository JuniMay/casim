#ifndef CASIM_GUI_VIEWER_HPP_
#define CASIM_GUI_VIEWER_HPP_

#include "gui/common.hpp"

class Viewer : public QOpenGLWidget, public QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  explicit Viewer(QWidget *parent = nullptr);

  void set_automaton(QSharedPointer<casim::core::Automaton> automaton);

 protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;

 signals:
  // changes very frequently
  void yaw_changed(const float &yaw);
  void pitch_changed(const float &pitch);
  // these two below are mainly used in initialization part
  void sensitivity_changed(const float &sensitivity);
  void move_speed_changed(const float &move_speed);
  void cell_size_changed(const float &cell_size);

 public slots:
  void reset_camera();
  void display_automaton();

  // slots for xxx_set from config_editor
  void set_yaw(const float &yaw);
  void set_pitch(const float &pitch);
  void set_sensitivity(const float &sensitivity);
  void set_move_speed(const float &move_speed);
  void set_cell_size(const float &cell_size);

 private:
  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_;
  QOpenGLShaderProgram shader_program_;

  QVector<double> vertices_;
  QVector<QVector3D> cell_positions_;
  QVector<QVector3D> cell_color_vectors_;

  float yaw_;
  float pitch_;
  float sensitivity_;
  float move_speed_;
  float cell_size_;

  QVector3D camera_pos_;
  QVector3D camera_target_;
  QVector3D camera_direction_;
  QVector3D camera_right_;
  QVector3D camera_up_;

  QPoint last_pos_;

  QSharedPointer<casim::core::Automaton> automaton_;


  QColor background_color_ { QColor::fromRgb(0xff, 0xff, 0xff ) };
};

#endif
