#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "PlayerContainer.h"
#include "Player_table.h"
#include "OnlinePlayer.h"
#include <memory>

namespace Ui {
class ChangeDialog;
}


class ChangeDialog : public QDialog {
    Q_OBJECT

public:
    //explicit ChangeDialog(QWidget *parent = nullptr);

    ChangeDialog(QWidget *parent, PlayerContainer* container);
    void populateList();

    ~ChangeDialog();

    bool isOnlinePlayer(const std::shared_ptr<Player>& player) const {
        return std::dynamic_pointer_cast<OnlinePlayer>(player) != nullptr;
    }

private slots:

    void onAddPlayers();

    void onDeletePlayer();
    void onEditPlayer();

    void onPlayerAdded(const std::shared_ptr<Player>& player); // Слот для добавления игрока

private:
    PlayerContainer* playerContainer;
    Ui::ChangeDialog *ui;
    //PlayerTableWidget* playerTableWidget;

protected:
    void resizeEvent(QResizeEvent *event) override;
};


#endif // CHANGEDIALOG_H
