#include "AddDialog.h"
#include "ui_AddDialog.h"
#include "Player.h"
#include "OnlinePlayer.h"

#include <QButtonGroup>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QDebug>

AddDialog::AddDialog(QWidget *parent, bool isEditing)
    : QDialog(parent), ui(new Ui::AddDialog), isEditing(isEditing)  {

    ui->setupUi(this);

    // Настройка видимости поля выбора Online для режима редактирования
    ui->onlineWidget->setVisible(!isEditing);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);


    QButtonGroup *genderGroup = new QButtonGroup(this);
    genderGroup->addButton(ui->maleRadioButton);
    genderGroup->addButton(ui->femaleRadioButton);
    ui->maleRadioButton->setChecked(true);

    QRegularExpression regExp("[0-9]{1,10}"); // Максимум 10 цифр для номера
    ui->telEdit->setValidator(new QRegularExpressionValidator(regExp, this));
    ui->ageLineEdit->setValidator(new QIntValidator(0, 120, this));
    ui->ratingLineEdit->setValidator(new QIntValidator(0, 3000, this));

    connect(ui->pushButton, &QPushButton::clicked, this, &AddDialog::onAddEditPlayer);
    connect(ui->isOnlineCheckBox, &QCheckBox::stateChanged, this, &AddDialog::onIsOnlineCheckBoxStateChanged);


    if (isEditing) {
        ui->onlineWidget->hide();
    }

    if (!isEditing) {
        onIsOnlineCheckBoxStateChanged(ui->isOnlineCheckBox->isChecked() ? Qt::Checked : Qt::Unchecked);
    }
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::loadPlayerData(const std::shared_ptr<Player>& player) {
    // Заполнение общих полей
    ui->nameEdit->setText(QString::fromStdString(player->getName()));
    ui->ageLineEdit->setText(QString::number(player->getAge()));
    ui->ratingLineEdit->setText(QString::number(player->getRating()));

    if (player->getGender() == 'M') {
        ui->maleRadioButton->setChecked(true);
    } else if (player->getGender() == 'F') {
        ui->femaleRadioButton->setChecked(true);
    }

    ui->registrationDateEdit->setText(QString::fromStdString(player->getRegistrationDate()));
    ui->checkBox->setChecked(player->getisActive());


    // Проверка, является ли игрок типом OnlinePlayer
    if (auto onlinePlayer = std::dynamic_pointer_cast<OnlinePlayer>(player)) {
        // Если игрок - OnlinePlayer, заполняем дополнительные поля и показываем их
        ui->isOnlineCheckBox->setChecked(true);
        ui->additionalFieldsWidget->show();

        ui->virtualNameEdit->setText(QString::fromStdString(onlinePlayer->getVirtual_name()));
        ui->emailEdit->setText(QString::fromStdString(onlinePlayer->getEmail()));
        ui->telEdit->setText(QString::number(onlinePlayer->getTel()));
    } else {
        // Если игрок - обычный Player, скрываем дополнительные поля
        ui->isOnlineCheckBox->setChecked(false);
        ui->additionalFieldsWidget->hide();
    }
}

void AddDialog::onAddEditPlayer() {

    int age = ui->ageLineEdit->text().toInt();
    int rating = ui->ratingLineEdit->text().toInt();

    if (ui->ageLineEdit->text().isEmpty() || ui->nameEdit->text().isEmpty() ||
        ui->ratingLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все необходимые поля.");
        return;
    }

    if (age < 0 || age > 120 || rating < 0 || rating > 3000) {
        QMessageBox::warning(this, "Ошибка", "Возраст и рейтинг должны быть в допустимых пределах.");
        return;
    }

    if(ui->isOnlineCheckBox->isChecked()){
        if (ui->telEdit->text().isEmpty()){
            QMessageBox::warning(this, "Ошибка", "Заполните все необходимые поля.");
            return;
        }
    }


    // std::shared_ptr<Player> player;
    // if (ui->isOnlineCheckBox->isChecked()) {
    //     player = createOnlinePlayerFromInputs(); // Создаем OnlinePlayer
    // } else {
    //     player = createPlayerFromInputs(); // Создаем обычного Player
    // }

    // emit playerAdded(player); // Отправляем один сигнал для всех игроков
    // this->accept(); // Закрываем диалоговое окно


    auto player = ui->isOnlineCheckBox->isChecked() ? createOnlinePlayerFromInputs() : createPlayerFromInputs();
    emit playerAdded(player);
    accept();

}


std::shared_ptr<OnlinePlayer> AddDialog::createOnlinePlayerFromInputs() {
    auto onlinePlayer = std::make_shared<OnlinePlayer>();

    onlinePlayer->setName(ui->nameEdit->text().toStdString());
    onlinePlayer->setAge(ui->ageLineEdit->text().toInt());
    onlinePlayer->setRating(ui->ratingLineEdit->text().toInt());
    onlinePlayer->setGender(ui->maleRadioButton->isChecked() ? 'M' : 'F');
    onlinePlayer->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    onlinePlayer->setIsActive(ui->checkBox->isChecked());
    onlinePlayer->setVirtualName(ui->virtualNameEdit->text().toStdString());
    onlinePlayer->setEmail(ui->emailEdit->text().toStdString());
    onlinePlayer->setTel(ui->telEdit->text().toULongLong());

    return onlinePlayer;
}


std::shared_ptr<Player> AddDialog::createPlayerFromInputs() {
    auto player = std::make_shared<Player>();

    player->setName(ui->nameEdit->text().toStdString());
    player->setAge(ui->ageLineEdit->text().toInt());
    player->setRating(ui->ratingLineEdit->text().toInt());
    player->setGender(ui->maleRadioButton->isChecked() ? 'M' : 'F');
    player->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    player->setIsActive(ui->checkBox->isChecked());

    return player;
}


// void AddDialog::onIsOnlineCheckBoxStateChanged(int state) {
//     bool isOnline = (state == Qt::Checked);

//     if (isOnline) {
//         // Отображаем дополнительные поля, если выбран `OnlinePlayer`
//         ui->additionalFieldsWidget->show();

//     } else {
//         // Скрываем дополнительные поля для базового `Player`
//         ui->additionalFieldsWidget->hide();
//     }
// }

void AddDialog::onIsOnlineCheckBoxStateChanged(int state) {
    ui->additionalFieldsWidget->setVisible(state == Qt::Checked);
}


void AddDialog::resizeEvent(QResizeEvent *event) {
    int scrollAreaWidth = this->width() - 40;
    int scrollAreaHeight = this->height() - 40;
    ui->scrollArea->resize(scrollAreaWidth, scrollAreaHeight);
    ui->scrollArea->move(20, 20);

    int contentWidth = 661;
    ui->scrollAreaWidgetContents->setFixedWidth(contentWidth);
    ui->scrollAreaWidgetContents->setFixedHeight(contentWidth);

    QDialog::resizeEvent(event);
}
