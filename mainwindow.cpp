#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets/qpushbutton.h"
#include <QQuickWidget>
#include <QPushButton>
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

        QObject::connect(button, &QPushButton::clicked, this, &MainWindow::on_openQml);

        ui->horizontalLayout->addWidget(button);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openQml()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(button) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QQuickWidget *container = new QQuickWidget;

        container->setLayout(layout);

        QPushButton *backButton = new QPushButton("Back", this);
        layout->addWidget(backButton);

        QQuickWidget *qmlWidget = new QQuickWidget;
        layout->addWidget(qmlWidget);

        QString path = button->property("path").toString();
        qmlWidget->setSource(QUrl::fromLocalFile(path));

        setCentralWidget(container);
    }
}

