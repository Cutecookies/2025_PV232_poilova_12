#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::handleLoadButtonClick);
    connect(ui->pushButton_2, &QPushButton::clicked,
            this, &MainWindow::handleSaveButtonClick);
}

MainWindow::~MainWindow() {
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

    QPixmap image(file_name);

    if (image.isNull()) {
        ui->lineEdit->setText("Отсутствует файл для сохранения");
        return;
    }

    QList<QListWidgetItem*> foundItems = ui->listWidget->findItems(file_name, Qt::MatchContains);
    if (foundItems.isEmpty()) {
        ui->listWidget->addItem(file_name);
        ui->lineEdit->setText("Ссылка на файл сохранена");
    }
    else {
        ui->lineEdit->setText("Ссылка на файл уже была сохранена ранее");
    }

}
