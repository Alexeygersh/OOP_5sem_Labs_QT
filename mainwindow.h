#pragma once

#include "PlayerContainer.h"
#include "Player_table.h"
#include "ChangeDialog.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddPlayer();
    void onAddOnlinePlayer();
    void onChangePlayers();
    void onLoadFromFile();
    void onSaveToFile();
    void onClearPlayers();

    void onPlayerAdded(const std::shared_ptr<Player>& player); // Слот для добавления игрока
    void onOnlinePlayerAdded(const std::shared_ptr<OnlinePlayer>& onlineplayer);

private:
    Ui::MainWindow *ui;
    PlayerContainer playerContainer;
    PlayerTableWidget* playerTableWidget;
    //ChangeDialog* changeDialog;

protected:
    void resizeEvent(QResizeEvent *event) override;

};
