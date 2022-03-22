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

  this->sortByColumn(0, Qt::AscendingOrder);

  connect(this, &FileTree::doubleClicked, this, &FileTree::open_file);
}

void FileTree::open_file(const QModelIndex &index) {
  QFile file(model_->filePath(index));
  QFileInfo info(model_->filePath(index));
  if (info.suffix() == "lua") {
    if (file.open(QFile::ReadOnly | QFile::Text)) {
      QTextStream in(&file);
      QString script = in.readAll();
      file.close();
      emit load_script_signal(script);
    }
  } else if (info.suffix() == "npy") {
    emit load_pattern_signal(model_->filePath(index));
  }
}

void FileTree::open_folder() {
  QFileDialog dialog(this);
  QString path = dialog.getExistingDirectory(this, tr("Open Folder"), "");
  model_->setRootPath(path);
  model_->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
  this->setRootIndex(model_->index(path));
}