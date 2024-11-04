#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ChangeDialog.h"
#include "PlayerDialog.h"
#include "OnlinePlayerDialog.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // виджет для отрисовки таблицы игроков
    playerTableWidget = new PlayerTableWidget(playerContainer, this);

    // виджет для scrollArea
    ui->scrollArea->setWidget(playerTableWidget);
    ui->scrollArea->setWidgetResizable(true);

    connect(ui->actionPlayer, &QAction::triggered, this, &MainWindow::onAddPlayer);
    connect(ui->actionOnlinePlayer, &QAction::triggered, this, &MainWindow::onAddOnlinePlayer);

    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadFromFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveToFile);

    connect(ui->actionChange, &QAction::triggered, this, &MainWindow::onChangePlayers);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::onClearPlayers);

    //changeDialog = new ChangeDialog(this, &playerContainer);
    //connect(ui->actionChange, &QAction::triggered, this, &MainWindow::onChangePlayers);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onAddPlayer() {
    PlayerDialog dialog(this);
    // Подключение сигнала playerAdded к слоту onPlayerAdded
    connect(&dialog, &PlayerDialog::playerAdded, this, &MainWindow::onPlayerAdded);
    dialog.exec();
}

void MainWindow::onPlayerAdded(const std::shared_ptr<Player>& player) {
    playerContainer.addPlayer(player); // Добавляем игрока в контейнер
    playerTableWidget->update();  // Обновление таблицы
}



void MainWindow::onAddOnlinePlayer() {
    OnlinePlayerDialog *dialog = new OnlinePlayerDialog(this);

    // Подключаем сигнал к слоту для добавления игрока в контейнер
    connect(dialog, &OnlinePlayerDialog::onlinePlayerAdded, this, &MainWindow::onOnlinePlayerAdded);

    dialog->open(); // Открываем диалоговое окно
}

void MainWindow::onOnlinePlayerAdded(const std::shared_ptr<OnlinePlayer>& onlinePlayer) {
    playerContainer.addPlayer(onlinePlayer);
    playerTableWidget->update();
}


void MainWindow::onChangePlayers() {

    // EditPlayerDialog dialog(&playerContainer, this);
    // dialog.exec();
    // playerTableWidget->update();

    //changeDialog->populateList();
    //changeDialog->exec();
}



void MainWindow::onLoadFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для загрузки", "", "Файлы данных ()");//*.txt
    if (!filename.isEmpty()) {
        playerContainer.readFromFile(filename.toStdString());
        playerTableWidget->update();
    }
}

void MainWindow::onSaveToFile() {
    QString filename = QFileDialog::getSaveFileName(this, "Выберите файл для сохранения", "", "Файлы данных ()");
    if (!filename.isEmpty()) {
        playerContainer.writeToFile(filename.toStdString());
    }
}

void MainWindow::onClearPlayers() {
    playerContainer.clearPlayers();
    playerTableWidget->update();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    // размер QScrollArea
    int scrollAreaWidth = this->width() - 40;
    int scrollAreaHeight = this->height() - 100;
    ui->scrollArea->resize(scrollAreaWidth, scrollAreaHeight);
    ui->scrollArea->move(20, 20);

    // QLineEdit
    int lineEditWidth = scrollAreaWidth;
    int lineEditHeight = 21;
    int lineEditY = ui->scrollArea->geometry().bottom();

    ui->lineEdit->resize(lineEditWidth, lineEditHeight);
    ui->lineEdit->move(20, lineEditY);

    QMainWindow::resizeEvent(event);
}

