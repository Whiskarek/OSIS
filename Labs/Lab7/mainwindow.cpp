#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->button_add, SIGNAL(clicked()), this, SLOT(Add()));
    connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(Clear()));
    connect(ui->button_to_right, SIGNAL(clicked()), this, SLOT(ToRight()));
    connect(ui->button_delete, SIGNAL(clicked()), this, SLOT(Delete()));
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::Contains(QListWidget *list, QString text) {
    return !list->findItems(text, Qt::MatchFlag::MatchExactly).empty();
}

void MainWindow::Add() {
    auto edit = ui->edit;
    auto text = edit->text();
    if (text.count(' ') == text.length())
        return;
    if (!Contains(ui->list_left, text)) {
        ui->list_left->addItem(text);
        edit->setText("");
    }
}

void MainWindow::Clear() {
    ui->list_left->clear();
    ui->list_right->clear();
}

void MainWindow::ToRight() {
    QString selected = ui->list_left->selectedItems().first()->text();
    if (!Contains(ui->list_right, selected)) {
        ui->list_right->addItem(selected);
    }
}

void MainWindow::Delete() {
    delete ui->list_left->takeItem(ui->list_left->currentRow());
    delete ui->list_right->takeItem(ui->list_right->currentRow());
}
