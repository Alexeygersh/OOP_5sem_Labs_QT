#include "PlayerDialog.h"
#include "ui_PlayerDialog.h"
#include <QButtonGroup>
#include <QIntValidator>
#include <QMessageBox>

PlayerDialog::PlayerDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);

    QButtonGroup *genderGroup = new QButtonGroup(this);
    genderGroup->addButton(ui->maleRadioButton);
    genderGroup->addButton(ui->femaleRadioButton);
    ui->maleRadioButton->setChecked(true);

    auto ageValidator = new QIntValidator(0, 120, this);
    ui->ageLineEdit->setValidator(ageValidator);
    auto ratingValidator = new QIntValidator(0, 3000, this);
    ui->ratingLineEdit->setValidator(ratingValidator);

    connect(ui->pushButton, &QPushButton::clicked, this, &PlayerDialog::onAddPlayerButtonClicked);
}
// PlayerDialog::PlayerDialog(QWidget *parent, std::shared_ptr<Player> player)
//     : QDialog(parent), player(player) {
//     setupUi(this);
//     if (player) {
//         ui->nameLineEdit->setText(player->getName());
//         ui->ratingSpinBox->setValue(player->getRating());
//     }
// }



PlayerDialog::~PlayerDialog() {
    delete ui;
}

void PlayerDialog::onAddPlayerButtonClicked() {
    int age = ui->ageLineEdit->text().toInt();
    int rating = ui->ratingLineEdit->text().toInt();
    if (ui->ageLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните возраст.");
        return;
    }
    else if (ui->nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните имя.");
        return;
    }
    else if (ui->ratingLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните рейтинг.");
        return;
    }


    if (age < 0 || age > 120) {
        QMessageBox::warning(this, "Ошибка", "Возраст должен быть в пределах от 0 до 120.");
        return;
    }

    if (rating < 0 || rating > 3000) {
        QMessageBox::warning(this, "Ошибка", "Рейтинг должен быть в пределах от 0 до 3000.");
        return;
    }
    auto player = createPlayerFromInputs(); // Создаем объект игрока из введенных данных
    emit playerAdded(player); // Отправляем сигнал с данными игрока
    this->accept(); // Закрываем диалоговое окно после добавления игрока
}

std::shared_ptr<Player> PlayerDialog::createPlayerFromInputs() {
    auto player = std::make_shared<Player>();

    // Заполняем объект player данными из полей ввода
    player->setName(ui->nameEdit->text().toStdString());
    player->setAge(ui->ageLineEdit->text().toInt());
    player->setRating(ui->ratingLineEdit->text().toInt());

    // Определяем пол на основе состояния радиокнопок
    if (ui->maleRadioButton->isChecked()) {
        player->setGender('M');
    } else if (ui->femaleRadioButton->isChecked()) {
        player->setGender('F');
    }

    player->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    player->setIsActive(ui->checkBox->isChecked());

    return player;
}

void PlayerDialog::resizeEvent(QResizeEvent *event)
{
    int scrollAreaWidth = this->width() - 40;
    int scrollAreaHeight = this->height() - 40;
    ui->scrollArea->resize(scrollAreaWidth, scrollAreaHeight);
    ui->scrollArea->move(20, 20);

    int contentWidth = 531;
    int contentHeight = 491;
    ui->scrollAreaWidgetContents->setFixedWidth(contentWidth);
    ui->scrollAreaWidgetContents->setFixedHeight(contentHeight);

    QDialog::resizeEvent(event);
}
