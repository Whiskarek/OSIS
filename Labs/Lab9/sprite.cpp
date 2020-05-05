#include "sprite.h"
#include <cmath>

Sprite::Sprite(QWidget *parent, const QRect &position)
    : QLabel(parent){
    current_pos.setX(position.x());
    current_pos.setY(position.y());
    width = position.width();
    height = position.height();
    UpdatePosition();
    LoadStates();
    timer = std::make_unique<QTimer>();
    timer->setInterval(timer_tick);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(move_by_timer()));
}

void Sprite::setPixmap(const QPixmap &pixmap) {
    auto geom = geometry();
    auto img = pixmap.scaled(geom.width(), geom.height(), Qt::KeepAspectRatio);
    QLabel::setPixmap(img);
}

#include <QDebug>

void Sprite::move(const QPoint &position) {
    if (timer->isActive())
        timer->stop();
    end_pos = QVector2D(position);
    if (current_pos == end_pos)
        return;
    auto tmp = end_pos;
    tmp -= current_pos;
    tmp *= 50;
    direction = current_pos;
    direction += tmp;
    direction.normalize();
    state = SpriteState::RUN;
    timer->start();
}


void Sprite::LoadStates(){
    const size_t run_states_amount = 10;
    const QString run_prefix = ":/run/Run_%1";
    for (size_t i = 1; i <= run_states_amount; ++i) {
        run_states.push_back(run_prefix.arg(i));
    }
    idle = QPixmap(":/idle/Idle");
    setPixmap(idle);
}

void Sprite::UpdatePosition() {
    setGeometry({
        static_cast<int>(current_pos.x() - width / 4),
        static_cast<int>(current_pos.y() - height / 2),
        width,
        height
    });
    updateGeometry();
}

void Sprite::updateSprite() {
    if (state == SpriteState::IDLE) {
        setPixmap(idle);
    } else {
        setPixmap(run_states[sprite_index]);
    }
}

void Sprite::move_by_timer() {
    auto speed = direction;
    speed *= 4;
    current_pos += speed;
    if (powf(current_pos.x() - end_pos.x(), 2) < 20)
        direction.setX(0);
    if (powf(current_pos.y() - end_pos.y(), 2) < 20)
        direction.setY(0);
    if (direction == QVector2D()) {
        timer->stop();
        state = SpriteState::IDLE;
        sprite_index = 0;
    }
    UpdatePosition();
    updateSprite();
    if (state == SpriteState::RUN) {
        sprite_index++;
        if (sprite_index >= run_states.size())
            sprite_index = 0;
    }
}
