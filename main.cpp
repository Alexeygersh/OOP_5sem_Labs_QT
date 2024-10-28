#include "mainwindow.h"
#include "PlayerContainer.h"
#include <boost/serialization/export.hpp>
// #include "utils.h"
// #include <cstdlib>

#include <QIcon>
#include <QApplication>
#include <QTextCodec>
#include <QMenuBar>
#include <QMenu>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    //std::system("chcp 1251");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Gersh Alexey");
    QIcon icon("C:/Users/first/OneDrive/Изображения/g.jpg");
    w.setWindowIcon(icon);

    a.setStyleSheet("QMenu::item:selected {border: 2px solid; color: rgb(170, 0, 0); spacing: 3px; padding: 2px 10px; border-radius: 5px; } QMenu::item { background-color: transparent; } QMenuBar::item:selected {   background-color:  rgb(170, 170, 127);}"
                    "QMenuBar::item { spacing: 3px; padding: 2px 10px; background-color: rgb(170, 170, 127); color: rgb(0,0,0); border-radius: 5px;}");

    //lineEdit -> setStyleSheet("border: 1px solid red");

    w.show();


    PlayerContainer container;
    int choice;

    // do {
    //     std::cout << "Система шахматного турнира\n";
    //     std::cout << "1. Добавить игрока\n";
    //     std::cout << "2. Добавить Онлайн игрока\n";
    //     std::cout << "3. Вывести всех игроков\n";
    //     std::cout << "4. Загрузить игроков из файла\n";
    //     std::cout << "5. Сохранить игроков в файл\n";
    //     std::cout << "6. Очистить всех игроков\n";
    //     std::cout << "0. Выход\n";
    //     std::cout << "Введите ваш выбор: ";
    //     choice = InputNum<int>(0, 6);

    //     switch (choice) {
    //     case 1: {
    //         container.addPlayer();
    //         break;
    //     }
    //     case 2: {
    //         container.addOnlinePlayer();
    //         break;
    //     }
    //     case 3: {
    //         container.displayPlayers();
    //         break;
    //     }

    //     case 4: {
    //         std::string filename;
    //         std::cout << "Введите название файла: ";
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::getline(std::cin, filename);
    //         container.readFromFile(filename);
    //         break;
    //     }
    //     case 5: {
    //         std::string filename;
    //         std::cout << "Введите название файла: ";
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::getline(std::cin, filename);
    //         container.writeToFile(filename);
    //         break;
    //     }
    //     case 6:
    //         container.clearPlayers();
    //         break;
    //     case 0:
    //         exit(0);
    //         break;
    //     default:
    //         std::cout << "Неверный выбор! Повторите ввод.\n";
    //     }
    // } while (choice != 0);



    return a.exec();
}


BOOST_CLASS_EXPORT(OnlinePlayer)
BOOST_CLASS_EXPORT(Player)
