#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sprite = std::make_unique<Sprite>(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    sprite->move(event->localPos().toPoint());
    QMainWindow::mousePressEvent(event);
}
