#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "PlayerDialog.h"
#include "OnlinePlayerDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем виджет для отрисовки таблицы игроков
    playerTableWidget = new PlayerTableWidget(playerContainer, this);

    // Устанавливаем виджет для scrollArea
    ui->scrollArea->setWidget(playerTableWidget);

    connect(ui->actionPlayer, &QAction::triggered, this, &MainWindow::onAddPlayer);
    connect(ui->actionOnlinePlayer, &QAction::triggered, this, &MainWindow::onAddOnlinePlayer);

    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadFromFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveToFile);

    //connect(ui->displayPlayersButton, &QPushButton::clicked, this, &MainWindow::onDisplayPlayers);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearPlayers);
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
    // Добавляем игрока в контейнер
    playerContainer.addPlayer(player);

    // Обновляем таблицу или интерфейс для отображения игроков
    playerTableWidget->update();  // Обновление таблицы игроков
}

//

void MainWindow::onAddOnlinePlayer() {
    OnlinePlayerDialog *dialog = new OnlinePlayerDialog(this);

    // Подключаем сигнал к слоту для добавления игрока в контейнер
    connect(dialog, &OnlinePlayerDialog::onlinePlayerAdded, this, &MainWindow::onOnlinePlayerAdded);

    dialog->open(); // Открываем диалоговое окно
}

void MainWindow::onOnlinePlayerAdded(const std::shared_ptr<OnlinePlayer>& onlinePlayer) {
    playerContainer.addPlayer(onlinePlayer); // Добавляем игрока в контейнер
    playerTableWidget->update();
}


// void MainWindow::onDisplayPlayers() {
//     playerTableWidget->update();
// }



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

