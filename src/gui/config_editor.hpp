#ifndef CASIM_GUI_RULE_EDITOR_HPP_
#define CASIM_GUI_RULE_EDITOR_HPP_

#include "gui/common.hpp"

class ConfigEditor : public QTabWidget {
  Q_OBJECT
 public:
  explicit ConfigEditor(QWidget* parent = nullptr);

 private:
  QPointer<QWidget> dummy1_, dummy2_;
};

#endif
