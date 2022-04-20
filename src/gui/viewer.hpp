#ifndef CASIM_GUI_VIEWER_HPP_
#define CASIM_GUI_VIEWER_HPP_

#include "gui/common.hpp"

enum class ViewMode {
    Refresh = 0,
    Accumulate = 1,
};

class Viewer : public QOpenGLWidget, public QOpenGLExtraFunctions {
    Q_OBJECT
   public:
    explicit Viewer(QWidget* parent = nullptr);

    void setAutomaton(QSharedPointer<casim::core::Automaton> automaton);

   protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;

   signals:
    // changes very frequently
    void yawChanged(const float& yaw);
    void pitchChanged(const float& pitch);
    // these two below are mainly used in initialization part
    void sensitivityChanged(const float& sensitivity);
    void moveSpeedChanged(const float& move_speed);
    void cellSizeChanged(const float& cell_size);

   public slots:
    void resetCamera();
    void resetView();
    void displayAutomaton();

    // slots for xxx_set from config_editor
    void setYaw(const float& yaw);
    void setPitch(const float& pitch);
    void setSensitivity(const float& sensitivity);
    void setMoveSpeed(const float& move_speed);
    void setCellSize(const float& cell_size);

    void setViewMode(const ViewMode& view_mode);

   private:
    QOpenGLVertexArrayObject vao_;
    QOpenGLVertexArrayObject light_vao_;
    QOpenGLBuffer vbo_;
    QOpenGLShaderProgram shader_program_;
    QOpenGLShaderProgram light_shader_program_;

    QVector<float> vertices_;
    QVector<QVector3D> cell_positions_;
    QVector<QVector3D> cell_color_vectors_;

    float yaw_;
    float pitch_;
    float sensitivity_;
    float move_speed_;
    float cell_size_;

    ViewMode view_mode_;
    size_t acc_axis_;
    size_t acc_cnt_;

    QVector3D camera_pos_;
    QVector3D camera_target_;
    QVector3D camera_direction_;
    QVector3D camera_right_;
    QVector3D camera_up_;

    QPoint last_pos_;

    QSharedPointer<casim::core::Automaton> automaton_;

    QColor background_color_{QColor::fromRgb(0x1f, 0x1f, 0x1f)};
};

#endif
