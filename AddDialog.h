#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include "PlayerContainer.h"
#include "OnlinePlayer.h"
#include "Player.h"

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include <memory>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr, bool isEditing = false);
    ~AddDialog();

    // void setPlayerData(const std::shared_ptr<Player>& player) {
    //     loadPlayerData(player);
    // }
    // std::shared_ptr<Player> getPlayerFromInputs() {
    //     return createPlayerFromInputs();
    // }
    void loadPlayerData(const std::shared_ptr<Player>& player);
    std::shared_ptr<OnlinePlayer> createOnlinePlayerFromInputs();
    std::shared_ptr<Player> createPlayerFromInputs();

    bool isOnlinePlayer(const std::shared_ptr<Player>& player) const {
        return std::dynamic_pointer_cast<OnlinePlayer>(player) != nullptr;
    }

private slots:
    void onIsOnlineCheckBoxStateChanged(int state);
    void onAddEditPlayer();

signals:
    void playerAdded(const std::shared_ptr<Player>& player); // Сигнал для добавления игрока

private:
    Ui::AddDialog *ui;
    bool isEditing;



protected:
    void resizeEvent(QResizeEvent *event) override;

};

#endif // ADDDIALOG_H
