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
    void onChangePlayers();
    void onLoadFromFile();
    void onSaveToFile();
    void onClearPlayers();

private:
    Ui::MainWindow *ui;
    PlayerContainer playerContainer;
    PlayerTableWidget* playerTableWidget;
    ChangeDialog* changeDialog;

protected:
    void resizeEvent(QResizeEvent *event) override;

};
