#include "OnlinePlayerDialog.h"
#include "ui_OnlinePlayerDialog.h"

OnlinePlayerDialog::OnlinePlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlinePlayerDialog) {
    ui->setupUi(this);
}

OnlinePlayerDialog::~OnlinePlayerDialog() {
    delete ui;
}

void OnlinePlayerDialog::closeEvent(QCloseEvent *event) {
    auto onlinePlayer = std::make_shared<OnlinePlayer>();

    // Устанавливаем все данные из полей UI в onlinePlayer
    onlinePlayer->setName(ui->nameEdit->text().toStdString());
    onlinePlayer->setAge(ui->ageSpinBox->value());
    onlinePlayer->setRating(ui->ratingSpinBox->value());
    onlinePlayer->setGender(ui->genderComboBox->currentText().toStdString()[0]);
    onlinePlayer->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    onlinePlayer->setIsActive(ui->checkBox->isChecked());
    onlinePlayer->setVirtualName(ui->virtualNameEdit->text().toStdString());
    onlinePlayer->setEmail(ui->emailEdit->text().toStdString());
    onlinePlayer->setTel(ui->telEdit->text().toULongLong());

    // Отправляем сигнал с заполненным объектом OnlinePlayer
    emit onlinePlayerAdded(onlinePlayer);

    QDialog::closeEvent(event);
}
