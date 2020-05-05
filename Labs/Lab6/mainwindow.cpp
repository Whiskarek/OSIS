#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = ui->label;

    label->hide();

    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(onClickStart()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(onClickStop()));

    timer = std::make_unique<QTimer>(new QTimer());
    timer->setInterval(3);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(moveText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionStart_triggered()
{
    if (labelExist != true){
        label->show();
        labelExist = true;
    }
    timer->start();
}

void MainWindow::on_actionStop_triggered()
{
    timer->stop();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::moveText() {
    auto move = [](auto label) {
        auto geometry = label->geometry();
        if (geometry.x() < -geometry.width()) {
            geometry.setX(geometry.x() + 900);
        } else {
            geometry.setX(geometry.x() - 1);
            geometry.setWidth(geometry.width() - 1);
        }
        label->setGeometry(geometry);
        label->updateGeometry();
    };

    move(label);
}
