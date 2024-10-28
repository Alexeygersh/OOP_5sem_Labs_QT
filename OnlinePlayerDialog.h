#ifndef ONLINEPLAYERDIALOG_H
#define ONLINEPLAYERDIALOG_H

#include <QDialog>
#include "OnlinePlayer.h"
#include <memory>

namespace Ui {
class OnlinePlayerDialog;
}

class OnlinePlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit OnlinePlayerDialog(QWidget *parent = nullptr);
    ~OnlinePlayerDialog();

    //std::shared_ptr<OnlinePlayer> getOnlinePlayerData() const; // Метод для получения данных из диалога
signals:
    void onlinePlayerAdded(const std::shared_ptr<OnlinePlayer>& onlinePlayer); // Сигнал для добавления игрока

protected:
    void closeEvent(QCloseEvent *event) override; // Переопределяем обработку закрытия окна

private:
    Ui::OnlinePlayerDialog *ui;
};

#endif // ONLINEPLAYERDIALOG_H

