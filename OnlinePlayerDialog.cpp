#include "OnlinePlayerDialog.h"
#include "ui_OnlinePlayerDialog.h"
#include <QButtonGroup>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QMessageBox>

OnlinePlayerDialog::OnlinePlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlinePlayerDialog){

    ui->setupUi(this);

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);

    QButtonGroup *genderGroup = new QButtonGroup(this);
    genderGroup->addButton(ui->maleRadioButton);
    genderGroup->addButton(ui->femaleRadioButton);
    ui->maleRadioButton->setChecked(true);

    QRegularExpression regExp("[0-9]{1,10}"); // Максимум 10 цифр для номера
    auto phoneValidator = new QRegularExpressionValidator(regExp, this);
    ui->telEdit->setValidator(phoneValidator);

    ui->ageLineEdit->setValidator(new QIntValidator(0, 120, this));
    ui->ratingLineEdit->setValidator(new QIntValidator(0, 3000, this));

    connect(ui->pushButton, &QPushButton::clicked, this, &OnlinePlayerDialog::onAddPlayerButtonClicked);
}

OnlinePlayerDialog::~OnlinePlayerDialog() {
    delete ui;
}

void OnlinePlayerDialog::onAddPlayerButtonClicked() {
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
    else if (ui->telEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните телефон.");
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
    emit onlinePlayerAdded(player); // Отправляем сигнал с данными игрока
    this->accept(); // Закрываем диалоговое окно после добавления игрока
}

std::shared_ptr<OnlinePlayer> OnlinePlayerDialog::createPlayerFromInputs() {
    auto onlinePlayer = std::make_shared<OnlinePlayer>();

    // Устанавливаем все данные из полей UI в onlinePlayer
    onlinePlayer->setName(ui->nameEdit->text().toStdString());
    onlinePlayer->setAge(ui->ageLineEdit->text().toInt());
    onlinePlayer->setRating(ui->ratingLineEdit->text().toInt());

    if (ui->maleRadioButton->isChecked()) {
        onlinePlayer->setGender('M');
    } else if (ui->femaleRadioButton->isChecked()) {
        onlinePlayer->setGender('F');
    }

    onlinePlayer->setRegistrationDate(ui->registrationDateEdit->text().toStdString());
    onlinePlayer->setIsActive(ui->checkBox->isChecked());
    onlinePlayer->setVirtualName(ui->virtualNameEdit->text().toStdString());
    onlinePlayer->setEmail(ui->emailEdit->text().toStdString());
    onlinePlayer->setTel(ui->telEdit->text().toULongLong());

    return onlinePlayer;
}

void OnlinePlayerDialog::resizeEvent(QResizeEvent *event) {
    int scrollAreaWidth = this->width() - 40;
    int scrollAreaHeight = this->height() - 40;
    ui->scrollArea->resize(scrollAreaWidth, scrollAreaHeight);
    ui->scrollArea->move(20, 20);

    int contentWidth = 661;
    ui->scrollAreaWidgetContents->setFixedWidth(contentWidth);
    ui->scrollAreaWidgetContents->setFixedHeight(contentWidth);

    QDialog::resizeEvent(event);
}
