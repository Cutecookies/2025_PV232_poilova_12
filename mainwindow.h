#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QList>
#include <qlistwidget.h>
#include "smartstr.h"

namespace Ui {
class MainWindow;
}

struct ImageRecord {
    QString path;
    smartPtr<QFile> file_handler;

    explicit ImageRecord(QString path, smartPtr<QFile>&& file)
        : path(std::move(path)), file_handler(std::move(file)) {}
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadSavedPaths();
    void savePaths();

private slots:
    void handleLoadButtonClick();
    void handleSaveButtonClick();
     void handleItemClick(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;
    std::vector<ImageRecord> images;
    QString configFile = "saved_paths.txt";
};

#endif
