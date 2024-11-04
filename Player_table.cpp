#include "Player_table.h"
#include <QScrollArea>

PlayerTableWidget::PlayerTableWidget(PlayerContainer& container, QWidget *parent)
    : QWidget(parent), playerContainer(container) {}

void PlayerTableWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    int startX = 10, startY = 20;
    int rowHeight = 50;
    int columnWidth = 100;

    QStringList headers = {"Имя", "Возраст", "Рейтинг", "Пол", "Дата", "Активность", "Никнейм", "Почта", "Телефон"};

    // Рисуем заголовки таблицы
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawText(startX + i * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, headers[i]);
        painter.drawRect(startX + i * columnWidth, startY, columnWidth, rowHeight);
    }

    // Переход к следующей строке для данных игроков
    startY += rowHeight;

    // Перебор всех игроков с использованием for_each и lambda
    std::for_each(playerContainer.getPlayers().begin(), playerContainer.getPlayers().end(),
                  [&](std::shared_ptr<Player> player) {
                      if (std::shared_ptr<OnlinePlayer> onlinePlayer = std::dynamic_pointer_cast<OnlinePlayer>(player)) {
                          onlinePlayer->draw(painter, startX, startY, columnWidth, rowHeight);  // Отрисовка online player
                      } else {
                          player->draw(painter, startX, startY, columnWidth, rowHeight);  // Отрисовка обычного игрока
                      }
                      startY += rowHeight;  // Переход к следующей строке
                  });

    // Обновляем размеры виджета на основе количества строк и столбцов
    int widgetWidth = startX + headers.size() * columnWidth + 10;
    int widgetHeight = startY;

    setMinimumSize(widgetWidth, widgetHeight);  // Устанавливаем минимальные размеры
    resize(widgetWidth, widgetHeight);  // Устанавливаем текущие размеры

}

void PlayerTableWidget::setPlayerContainer(PlayerContainer& container) {
    playerContainer = container;
    update();  // Обновляем виджет для отрисовки
}
