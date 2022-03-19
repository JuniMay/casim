#include "file_tree.hpp"

FileTree::FileTree(QWidget *parent) : QTreeView{parent} {
  model_ = new QFileSystemModel(this);
  model_->setRootPath(".");
  model_->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
  this->setModel(model_);
  this->setRootIndex(model_->index("./"));
  for (int i = 1; i < model_->columnCount(); ++i) {
    this->hideColumn(i);
  }
  this->setAnimated(false);
  this->setIndentation(20);
  this->setSortingEnabled(true);
}
