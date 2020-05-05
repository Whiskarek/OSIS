#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <Enums.h>
#include <config.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void updateColor(QPainter &);
    void drawBuffer(const QPoint &);

private slots:
    void newColor(Color);
    void newPrimitive(Primitive);
    void drawUpdate(bool);

private:
    Ui::MainWindow *ui;
    Config *config;
    QPixmap *buffer;

    Color color = Color::RED;
    Primitive primitive = Primitive::STAR;
    bool draw = false;
};
#endif // MAINWINDOW_H
