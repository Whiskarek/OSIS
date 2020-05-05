#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>

#include "Enums.h"

namespace Ui {
class Config;
}

class Config : public QWidget
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = nullptr);
    ~Config();

signals:
    void sendColor(Color);
    void sendPrimitive(Primitive);
    void sendDraw(bool);

private slots:
    void colorChanged();
    void primitiveChanged();
    void drawChanged();

private:
    Ui::Config *ui;
};

#endif // CONFIG_H
