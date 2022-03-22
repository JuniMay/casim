#ifndef CASIM_GUI_PATTERN_CONFIG_HPP_
#define CASIM_GUI_PATTERN_CONFIG_HPP_

#include "gui/common.hpp"

// TODO: signals and slots

class PatternConfig : public QWidget {
  Q_OBJECT
 public:
  PatternConfig(QWidget* parent = nullptr);

 signals:
  void add_signal(const size_t& x, const size_t& y, const size_t& z,
                  const uint32_t& state);
  void load_signal();
  void save_signal();
  void reset_signal();

 public slots:
  void add_button_clicked_handler();

 private:
  QPointer<QLabel> x_label_;
  QPointer<QLineEdit> x_line_edit_;

  QPointer<QLabel> y_label_;
  QPointer<QLineEdit> y_line_edit_;

  QPointer<QLabel> z_label_;
  QPointer<QLineEdit> z_line_edit_;

  QPointer<QLabel> state_label_;
  QPointer<QLineEdit> state_line_edit_;

  QPointer<QPushButton> add_button_;
  QPointer<QPushButton> load_button_;
  QPointer<QPushButton> save_button_;
  QPointer<QPushButton> reset_button_;
  QPointer<QGridLayout> layout_;
};

#endif