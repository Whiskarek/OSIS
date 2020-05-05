#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void moveText(QLabel *);

private slots:
    void thread1Start();
    void thread2Start();
    void thread3Start();
    void onClickStart();
    void onClickStop();

private:
    Ui::MainWindow *ui;
    QTimer *thread1;
    QTimer *thread2;
    QTimer *thread3;
};
#endif // MAINWINDOW_H
