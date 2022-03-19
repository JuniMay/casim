#ifndef CASIM_GUI_FILE_TREE_HPP_
#define CASIM_GUI_FILE_TREE_HPP_

#include "gui/common.hpp"

class FileTree : public QTreeView {
  Q_OBJECT
 public:
  explicit FileTree(QWidget *parent = nullptr);
 public slots:
 private:
  QPointer<QFileSystemModel> model_;
};

#endif  // CASIM_GUI_FILE_TREE_HPP_