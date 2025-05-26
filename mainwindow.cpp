#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::handleLoadButtonClick);
    connect(ui->pushButton_2, &QPushButton::clicked,
            this, &MainWindow::handleSaveButtonClick);
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &MainWindow::handleItemClick);

    loadSavedPaths();
}

MainWindow::~MainWindow() {
    savePaths();
    delete ui;
}

void MainWindow::handleLoadButtonClick() {
    QString file_name = QFileDialog::getOpenFileName(
        this, "Выберите файл", "", "*.png *.jpg *.bmp");

    if (!file_name.isEmpty()) {
        QPixmap image(file_name);

        if (image.isNull()) {
            ui->lineEdit->setText("Ошибка загрузки файла");
            return;
        }

        ui->lineEdit->setText("Загружено: " + file_name);
        ui->imageLabel->setPixmap(image.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}

void MainWindow::handleSaveButtonClick() {
    QString text = ui->lineEdit->text();
    QString file_name = text.mid(11, 1000);

    if(file_name.isEmpty()) {
        ui->lineEdit->setText("Файл не загружен");
        return;
    }

    smartPtr<QFile> file(new QFile(file_name));
    if(!file->exists()) {
        ui->lineEdit->setText("Файл не существует");
        return;
    }

    auto it = std::find_if(images.begin(), images.end(),
                           [&file_name](const ImageRecord& record) {
                               return record.path == file_name;
                           });

    if (it != images.end()) {
        ui->lineEdit->setText("Файл уже в списке");
        return;
    }

    images.emplace_back(file_name, std::move(file));
    ui->listWidget->addItem(file_name);
    ui->lineEdit->setText("Ссылка сохранена");
}

void MainWindow::handleItemClick(QListWidgetItem* item) {
    QString path = item->text();
    QPixmap image(path);

    if(image.isNull()) {
        ui->lineEdit->setText("Ошибка загрузки из списка");
        return;
    }

    ui->imageLabel->setPixmap(image.scaled(
        ui->imageLabel->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation));
    ui->lineEdit->setText("Отображено: " + path);
}

void MainWindow::loadSavedPaths() {
    QFile file(configFile);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString path = in.readLine();
            if(!path.isEmpty()) {
                smartPtr<QFile> f(new QFile(path));
                if(f->exists()) {
                    images.emplace_back(path, std::move(f));
                    ui->listWidget->addItem(path);
                }
            }
        }
        file.close();
    }
}

void MainWindow::savePaths() {
    QFile file(configFile);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for(const auto& record : images) {
            out << record.path << "\n";
        }
        file.close();
    }
}
