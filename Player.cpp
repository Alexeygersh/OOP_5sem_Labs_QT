#include "Player.h"
//#include "utils.h"

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
    if (std::to_string(getGender()) == "M"){q = "М";} else {q = "Ж";}
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
