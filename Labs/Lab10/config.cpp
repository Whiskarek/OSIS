#include "config.h"
#include "ui_config.h"
#include <QDebug>

Config::Config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Config) {
    ui->setupUi(this);
    connect(ui->rb_red, SIGNAL(toggled(bool)), this, SLOT(colorChanged()));
    connect(ui->rb_green, SIGNAL(toggled(bool)), this, SLOT(colorChanged()));
    connect(ui->rb_blue, SIGNAL(toggled(bool)), this, SLOT(colorChanged()));

    connect(ui->rb_rhomb, SIGNAL(toggled(bool)), this, SLOT(primitiveChanged()));
    connect(ui->rb_square, SIGNAL(toggled(bool)), this, SLOT(primitiveChanged()));
    connect(ui->rb_circle, SIGNAL(toggled(bool)), this, SLOT(primitiveChanged()));
    connect(ui->rb_star, SIGNAL(toggled(bool)), this, SLOT(primitiveChanged()));

    connect(ui->cb_draw, SIGNAL(toggled(bool)), this, SLOT(drawChanged()));
}

Config::~Config() {
    delete ui;
}

void Config::colorChanged() {
    if (ui->rb_red->isChecked())
        emit sendColor(Color::RED);
    else if (ui->rb_green->isChecked())
        emit sendColor(Color::GREEN);
    else if (ui->rb_blue->isChecked())
        emit sendColor(Color::BLUE);
}

void Config::primitiveChanged() {
    if (ui->rb_rhomb->isChecked())
        emit sendPrimitive(Primitive::RHOMB);
    else if (ui->rb_square->isChecked())
        emit sendPrimitive(Primitive::SQUARE);
    else if (ui->rb_circle->isChecked())
        emit sendPrimitive(Primitive::CIRCLE);
    else if (ui->rb_star->isChecked())
        emit sendPrimitive(Primitive::STAR);
}

void Config::drawChanged() {
    emit sendDraw(ui->cb_draw->isChecked());
}
