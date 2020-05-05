#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <memory>

#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void mousePressEvent(QMouseEvent *event) override;
private:
    Ui::MainWindow *ui;
    std::unique_ptr<Sprite> sprite;
};
#endif // MAINWINDOW_H