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
    std::vector<std::string> stringList;

    for (const auto & entry : fs::directory_iterator(path)){
        stringList.push_back(entry.path());
        std::cout << entry.path() << std::endl;
    }

    for (const auto & entry : stringList){
        QPushButton *button = new QPushButton("entry", this);
        ui->horizontalLayout->addWidget(button);

        // Connect button click to slot for changing view
        connect(button, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl::fromLocalFile("/Users/destec2/Documents/QmlViewer/QmlViewer/imports/blueRectangle.qml"));
    setCentralWidget(view);
    //view->show();
}

