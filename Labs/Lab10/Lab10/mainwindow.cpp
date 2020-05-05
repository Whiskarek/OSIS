#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QPainter>
#include <QMouseEvent>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    config = new Config();
    config->show();

    connect(config, SIGNAL(sendColor(Color)), this, SLOT(newColor(Color)));
    connect(config, SIGNAL(sendPrimitive(Primitive)), this, SLOT(newPrimitive(Primitive)));
    connect(config, SIGNAL(sendDraw(bool)), this, SLOT(drawUpdate(bool)));

    buffer = new QPixmap(width(), height());
    buffer->fill(Qt::transparent);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newColor(Color new_color) {
    color = new_color;
}

void MainWindow::newPrimitive(Primitive new_primitive) {
    primitive = new_primitive;
}

void MainWindow::drawUpdate(bool state) {
    draw = state;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter main(this);
    main.drawPixmap({0 ,0, width(), height()}, *buffer);
}


void MainWindow::mousePressEvent(QMouseEvent *event) {
    drawBuffer(event->pos());
    update();
}

void MainWindow::updateColor(QPainter &painter) {
    switch (color) {
        case Color::RED:
            painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
            break;
        case Color::GREEN:
            painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap));
            break;
        case Color::BLUE:
            painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
            break;
    }
}

void MainWindow::drawBuffer(const QPoint &position) {
    if (!draw)
        return;
    QPainter painter(buffer);
    updateColor(painter);
    switch (primitive) {
        case Primitive::CIRCLE: {
            painter.drawEllipse(position, 50, 50);
            break;
        }
        case Primitive::SQUARE: {
            painter.drawRect(position.x() - 50, position.y() - 50, 100, 100);
            break;
        }
        case Primitive::STAR: {
            QPainterPath star;
            star.moveTo(position.x(), position.y() - 60);
            star.lineTo(position.x() + 20, position.y() - 20);
            star.lineTo(position.x() + 50, position.y() - 20);
            star.lineTo(position.x() + 20, position.y());
            star.lineTo(position.x() + 40, position.y() + 40);
            star.lineTo(position.x(), position.y() + 20);
            star.lineTo(position.x() - 40, position.y() + 40);
            star.lineTo(position.x() - 20, position.y());
            star.lineTo(position.x() - 50, position.y() - 20);
            star.lineTo(position.x() - 20, position.y() - 20);
            star.lineTo(position.x(), position.y() - 60);
            painter.drawPath(star);
            break;
        }
        case Primitive::RHOMB: {
            QPainterPath rhomb;
            rhomb.moveTo(position.x(), position.y() - 45);
            rhomb.lineTo(position.x() + 20, position.y());
            rhomb.lineTo(position.x(), position.y() + 45);
            rhomb.lineTo(position.x() - 20, position.y());
            rhomb.lineTo(position.x(), position.y() - 45);
            painter.drawPath(rhomb);
            break;
        }
    }
}
