#include "OnlinePlayer.h"
//#include "utils.h"


OnlinePlayer::OnlinePlayer() : virtual_name("unknown"), email("unknown@gmail.com"), tel(9909990100) {}

OnlinePlayer::~OnlinePlayer() {}


// void OnlinePlayer::readFromConsole() {
//     Player::readFromConsole();

//     std::cout << "Введите ник: ";
//     std::cin.ignore();
//     std::getline(std::cin, virtual_name);

//     std::cout << "Введите адрес почты: ";
//     std::cin.ignore();
//     std::getline(std::cin, email);

//     std::cout << "Введите номер телефона в виде 9991010010: (+7)";
//     tel = InputNum<unsigned long long int>(1000000000, 9999999999);
// }

// void OnlinePlayer::displayToConsole() const {
//     Player::displayToConsole(); // Сначала выводим данные базового класса
//     std::cout << "Ник пользователя: " << virtual_name << ", Адрес почты: " << email << ", Номер телефона: +7" << tel << std::endl;
// }

void OnlinePlayer::readFromFile(std::ifstream& inputFile) {

    inputFile.ignore();
    std::getline(inputFile, virtual_name);

    inputFile.ignore();
    std::getline(inputFile, email);

    inputFile >> tel;
}

void OnlinePlayer::writeToFile(std::ofstream& outputFile) const {

    outputFile << virtual_name << std::endl
               << email << std::endl
               << tel << std::endl;
}


void OnlinePlayer::draw(QPainter& painter, int startX, int startY, int columnWidth, int rowHeight) const {
    // Вызываем метод родителя для базовых данных
    Player::draw(painter, startX, startY, columnWidth, rowHeight);

    // Дополнительные данные для OnlinePlayer
    painter.drawText(startX + 6 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::fromStdString(getVirtual_name()));
    painter.drawText(startX + 7 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::fromStdString(getEmail()));
    painter.drawText(startX + 8 * columnWidth, startY, columnWidth, rowHeight, Qt::AlignCenter, QString::number(getTel()));

    // Рисуем границы для дополнительных ячеек OnlinePlayer
    for (int i = 6; i < 9; ++i) {
        painter.drawRect(startX + i * columnWidth, startY, columnWidth, rowHeight);
    }
}

QSize OnlinePlayer::calculateSize(int columnWidth, int rowHeight) const {
    // Размер таблицы для OnlinePlayer: ширина всех колонок (9 колонок для OnlinePlayer)
    return QSize(columnWidth * 9, rowHeight);
}


