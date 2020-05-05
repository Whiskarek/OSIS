#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(onClickStart()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(onClickStop()));

    thread1 = new QTimer(this);
    thread2 = new QTimer(this);
    thread3 = new QTimer(this);

    thread1->setInterval(8);
    thread2->setInterval(16);
    thread3->setInterval(24);

    connect(thread1, SIGNAL(timeout()), this, SLOT(thread1Start()));
    connect(thread2, SIGNAL(timeout()), this, SLOT(thread2Start()));
    connect(thread3, SIGNAL(timeout()), this, SLOT(thread3Start()));

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::thread1Start() {
    moveText(ui->thr1);
}


void MainWindow::thread2Start() {
    moveText(ui->thr2);
}


void MainWindow::thread3Start() {
    moveText(ui->thr3);
}

void MainWindow::onClickStart() {
    thread1->start();
    thread2->start();
    thread3->start();
}

void MainWindow::onClickStop() {
    thread1->stop();
    thread2->stop();
    thread3->stop();
}

void MainWindow::moveText(QLabel *l1) {
    auto move = [](auto label) {
        auto geometry = label->geometry();
        if (geometry.x() < -geometry.width()) {
            geometry.setX(geometry.x() + 1000);
            geometry.setWidth(geometry.width() + 1000);
        } else {
            geometry.setX(geometry.x() - 1);
            geometry.setWidth(geometry.width() - 1);
        }
        label->setGeometry(geometry);
        label->updateGeometry();
    };

    move(l1);
}
