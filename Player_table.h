#ifndef PLAYER_TABLE_H
#define PLAYER_TABLE_H

#pragma once

#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include "PlayerContainer.h"

class PlayerTableWidget : public QWidget {
    Q_OBJECT

public:
    explicit PlayerTableWidget(PlayerContainer& container, QWidget *parent = nullptr);

    // Переопределение метода для отрисовки
    void paintEvent(QPaintEvent *event) override;

    // Устанавливаем контейнер игроков
    void setPlayerContainer(PlayerContainer& container);

private:
    PlayerContainer& playerContainer;  // Ссылка на контейнер с игроками
};



#endif // PLAYER_TABLE_H
