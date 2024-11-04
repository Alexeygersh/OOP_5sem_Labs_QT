#include "mainwindow.h"
#include "PlayerContainer.h"
#include <boost/serialization/export.hpp>

#include <QIcon>
#include <QApplication>
#include <QTextCodec>
#include <QMenuBar>
#include <QMenu>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
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

    return a.exec();
}


BOOST_CLASS_EXPORT(OnlinePlayer)
BOOST_CLASS_EXPORT(Player)
