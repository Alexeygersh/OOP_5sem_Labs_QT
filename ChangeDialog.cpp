#include "ChangeDialog.h"
#include "AddDialog.h"
#include "ui_ChangeDialog.h"
#include "Player.h"
#include "OnlinePlayer.h"

#include <QDebug>
#include <QMessageBox>

ChangeDialog::ChangeDialog(QWidget* parent, PlayerContainer* container)
    : QDialog(parent), playerContainer(container), ui(new Ui::ChangeDialog) {

    ui->setupUi(this);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);

    connect(ui->addButton, &QPushButton::clicked, this, &ChangeDialog::onAddPlayers);
    connect(ui->editButton, &QPushButton::clicked, this, &ChangeDialog::onEditPlayer);
    connect(ui->deleteButton, &QPushButton::clicked, this, &ChangeDialog::onDeletePlayer);

    populateList();  // Заполнение списка при открытии диалога

}

ChangeDialog::~ChangeDialog() {
    delete ui;
}

void ChangeDialog::onAddPlayers() {

    AddDialog dialog(this, false);
    // Подключение сигнала playerAdded к слоту onPlayerAdded
    connect(&dialog, &AddDialog::playerAdded, this, &ChangeDialog::onPlayerAdded);
    dialog.exec();
}

void ChangeDialog::onPlayerAdded(const std::shared_ptr<Player>& player) {
    playerContainer->addPlayer(player); // Добавляем игрока в контейнер
    populateList();
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1); // Выбираем добавленный элемент
}

void ChangeDialog::populateList() {

    if (!ui->listWidget) {
        qDebug() << "Error: listWidget is null in populateList";
        return;
    }

    ui->listWidget->clear();

    std::for_each(playerContainer->getPlayers().begin(), playerContainer->getPlayers().end(),
                  [this](const std::shared_ptr<Player>& player) {
                      ui->listWidget->addItem(QString::fromStdString(player->getName()));
                  });
}


void ChangeDialog::onDeletePlayer() {
    int currentIndex = ui->listWidget->currentRow();
    if (currentIndex < 0) {
        QMessageBox::warning(this, "Удаление", "Выберите игрока для удаления.");
        return;
    }

    playerContainer->removePlayer(currentIndex);
    populateList(); // Обновляем список
    int newIndex = std::min(currentIndex, ui->listWidget->count() - 1);
    //int newIndex = (currentIndex >= ui->listWidget->count()) ? ui->listWidget->count() - 1 : currentIndex;
    if (newIndex >= 0) ui->listWidget->setCurrentRow(newIndex);
}

void ChangeDialog::onEditPlayer() {
    int currentIndex = ui->listWidget->currentRow();
    if (currentIndex < 0 || currentIndex >= playerContainer->getPlayers().size()) {
        QMessageBox::warning(this, "Редактирование", "Выберите игрока для редактирования.");
        return;
    }
    // Получаем выбранного игрока
    std::shared_ptr<Player> selectedPlayer = playerContainer->getPlayers().at(currentIndex);//[currentIndex];
    if (!selectedPlayer) {
        QMessageBox::warning(this, "Редактирование", "Выберите игрока для редактирования.");
        return;
    }
    // Создаем AddDialog
    AddDialog dialog(this, true);
    dialog.loadPlayerData(selectedPlayer); // Заполняем данные выбранного игрока в форме


    // Открываем диалог в режиме редактирования
    if (dialog.exec() == QDialog::Accepted) {
        // Обновляем игрока, если пользователь подтвердил изменения
        auto updatedPlayer = (isOnlinePlayer(selectedPlayer)) ? dialog.createOnlinePlayerFromInputs() : dialog.createPlayerFromInputs();

        if (updatedPlayer) {
            playerContainer->updatePlayer(currentIndex, updatedPlayer);
            populateList();
            ui->listWidget->setCurrentRow(currentIndex);
        }

        populateList();  // Обновляем список после изменения данных игрока
    }
}


void ChangeDialog::resizeEvent(QResizeEvent *event) {

    int scrollAreaWidth = this->width() - 40;
    int scrollAreaHeight = this->height() - 40;
    ui->scrollArea->resize(scrollAreaWidth, scrollAreaHeight);
    ui->scrollArea->move(20, 20);

    int contentWidth = 650;
    ui->scrollAreaWidgetContents->setFixedWidth(contentWidth);
    ui->scrollAreaWidgetContents->setFixedHeight(contentWidth);

    QDialog::resizeEvent(event);
}
