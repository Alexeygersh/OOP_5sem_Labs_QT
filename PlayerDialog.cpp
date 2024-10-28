#include "PlayerDialog.h"
#include "ui_PlayerDialog.h"
#include <iostream>

PlayerDialog::PlayerDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);
}

PlayerDialog::~PlayerDialog() {
    delete ui;
}


void PlayerDialog::closeEvent(QCloseEvent *event) {
    // Создаем объект игрока из введенных данных
    auto player = createPlayerFromInputs();

    // Отправляем сигнал с данными игрока
    emit playerAdded(player);

    // Завершаем обработку события закрытия окна
    QDialog::closeEvent(event);
}

std::shared_ptr<Player> PlayerDialog::createPlayerFromInputs() {
    auto player = std::make_shared<Player>();

    // Заполняем объект player данными из полей ввода
    player->setName(ui->nameEdit->text().toStdString());
    player->setAge(ui->ageSpinBox->value());
    player->setRating(ui->ratingSpinBox->value());
    player->setGender(ui->genderComboBox->currentText() == "Мужской" ? 'M' : 'F');
    QString a=ui->genderComboBox->currentText();
    std::cout << a.toStdString();
    player->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    player->setIsActive(ui->checkBox->isChecked());

    return player;
}


