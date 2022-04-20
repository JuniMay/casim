#ifndef CASIM_GUI_FILE_TREE_HPP_
#define CASIM_GUI_FILE_TREE_HPP_

#include "gui/common.hpp"

class FileTree : public QTreeView {
    Q_OBJECT
   public:
    explicit FileTree(QWidget* parent = nullptr);
   signals:
    void loadScriptSignal(const QString& script);
    void loadPatternSignal(const QString& path);
   public slots:
    void openFile(const QModelIndex& index);
    void openFolder();

   private:
    QPointer<QFileSystemModel> model_;
};

#endif  // CASIM_GUI_FILE_TREE_HPP_
