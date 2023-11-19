#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets/qpushbutton.h"
#include <QQuickWidget>
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::string path = "/Users/destec2/Documents/QmlViewer/QmlViewer/imports/";

    for (const auto & file : fs::directory_iterator(path)){ 
        QString filename = QString::fromStdString(file.path().filename().string());
        QPushButton *button = new QPushButton(filename, this);

        QString path = QString::fromStdString(file.path().string());
        button->setProperty("path", QVariant(path));

        connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

        std::cout << file.path() << std::endl;
        ui->horizontalLayout->addWidget(button);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button) {
        QString path = button->property("path").toString();
        QQuickWidget *view = new QQuickWidget;
        view->setSource(QUrl::fromLocalFile(path));
        setCentralWidget(view);
    }
}

