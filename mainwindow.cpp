#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::handleLoadButtonClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLoadButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выберите файл",
        "",
        "*.png *.jpg *.bmp"
        );

    if (!fileName.isEmpty()) {
        // Загружаем изображение
        QPixmap image(fileName);

        if (image.isNull()) {
            ui->lineEdit->setText("Ошибка загрузки файла");
            return;
        }

        // Обновляем интерфейс
        ui->lineEdit->setText("Загружено: " + fileName);
        ui->imageLabel->setPixmap(image.scaled(
            ui->imageLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}
