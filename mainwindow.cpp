#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QQuickWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl::fromLocalFile("/Users/destec2/Documents/QmlViewer/QmlViewer/imports/blueRectangle.qml"));
    view->show();
}

