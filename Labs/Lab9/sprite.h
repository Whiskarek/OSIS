#ifndef SPRITE_H
#define SPRITE_H

#include <QLabel>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QVector2D>

#include <memory>

enum class SpriteState {
    IDLE,
    RUN
};

class Sprite : public QLabel
{
    Q_OBJECT
public:
    Sprite(QWidget *parent = nullptr, const QRect &position = {100, 100, 100, 100});

    void setPixmap(const QPixmap &);

    void move(const QPoint &position);

private:
    void LoadStates();
    void UpdatePosition();
    void updateSprite();

public slots:
    void move_by_timer();

private:
    QVector<QPixmap> run_states;
    QPixmap idle;
    std::unique_ptr<QTimer> timer;
    SpriteState state = SpriteState::IDLE;
    const int timer_tick = 16;

    QVector2D current_pos;
    QVector2D end_pos;
    QVector2D direction;

    int height;
    int width;

    int sprite_index = 0;
};

#endif // SPRITE_H
