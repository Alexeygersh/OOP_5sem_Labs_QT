#include "Player.h"
//#include "utils.h"


// void Player::readFromConsole() {

//     std::cout << "Введите имя: ";
//     std::cin.ignore();
//     std::getline(std::cin, name);

//     std::cout << "Введите возраст (0-120): ";
//     age = InputNum<int>(0, 120);

//     std::cout << "Введите рейтинг (0-3000): ";
//     rating = InputNum<int>(0, 3000);

//     std::cout << "Введите пол | '0' для Мужского пола или '1' для женского: ";
//     bool genderInput = InputNum<bool>(0, 1);
//     gender = (genderInput == 0) ? 'M' : 'F';

//     std::cin.ignore();

//     std::cout << "Введите дату регистрации (DD-MM-YYYY): ";
//     std::getline(std::cin, registrationDate);

//     std::cout << "Игрок активен в данный момент? (1 - да, 0 - нет): ";
//     isActive = InputNum<bool>(0, 1);

// }

// void Player::displayToConsole() const {
//     std::cout << " Имя: " << name
//               << ", Возраст: " << age
//               << ", Рейтинг: " << rating
//               << ", Пол: " << (gender == 0 ? 'M' : 'F')
//               << ", Дата регистрации: " << registrationDate
//               << ", Активен?: " << (isActive ? "Да" : "Нет")
//               << std::endl;
// }


void Player::readFromFile(std::ifstream& inputFile) {
    //inputFile >> id;
    //inputFile.ignore();
    std::getline(inputFile, name);
    inputFile >> age >> rating;

    char genderChar;
    inputFile >> genderChar;
    gender = (genderChar == '1') ? 'M' : 'F';
    inputFile.ignore();

    std::getline(inputFile, registrationDate);
    inputFile >> isActive;
    inputFile.ignore();
}

void Player::writeToFile(std::ofstream& outputFile) const {

    //boost::archive::text_oarchive oa(outputFile);

    outputFile << name << std::endl
               << age << std::endl
               << rating << std::endl
               << (char)gender << std::endl
               << registrationDate << std::endl
               << isActive << std::endl;
}



void Player::draw(QPainter& painter, int startX, int startY, int columnWidth, int rowHeight) const {
    // Отрисовка базовой информации о игроке
    painter.drawText(startX, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::fromStdString(getName()));
    painter.drawText(startX + columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::number(getAge()));
    painter.drawText(startX + 2 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::number(getRating()));
    QString q;
    if (std::to_string(getGender()) == "-52"){q = "М";} else {q = "Ж";}
    painter.drawText(startX + 3 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, q);
    painter.drawText(startX + 4 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::fromStdString(getRegistrationDate()));
    painter.drawText(startX + 5 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::number(getisActive()));

    // Рисуем границы для каждой ячейки игрока
    for (int i = 0; i < 6; ++i) {
        painter.drawRect(startX + i * columnWidth, startY, columnWidth, rowHeight);
    }
}

// Размер таблицы для одного игрока: ширина всех колонок и высота одной строки
QSize Player::calculateSize(int columnWidth, int rowHeight) const {
    // Для каждого игрока считаем высоту строки
    return QSize(columnWidth * 6, rowHeight);
}
