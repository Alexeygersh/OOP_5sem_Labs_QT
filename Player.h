#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <fstream>
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <QString>
#include <QPainter>

class Player {

private:
    std::string name;
    int age;
    int rating;
    char gender;
    std::string registrationDate;
    bool isActive;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& name;
        ar& age;
        ar& rating;
        ar& gender;
        ar& registrationDate;
        ar& isActive;
    }

public:
    Player() : name("Неизвестно"), age(0), rating(0), gender('M'), registrationDate("01-09-2024"), isActive(true) {}
    virtual ~Player() = default;

    // virtual void readFromConsole();
    // virtual void displayToConsole() const;

    void setName(const std::string& newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setRating(int newRating) { rating = newRating; }
    void setGender(char newGender) { gender = newGender; }
    void setRegistrationDate(const std::string& newDate) { registrationDate = newDate; }
    void setIsActive(bool newIsActive) { isActive = newIsActive; }

    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    int getRating() const { return rating; }
    char getGender() const { return gender; }
    std::string getRegistrationDate() const { return registrationDate; }
    bool getisActive() const { return isActive; }

    virtual void readFromFile(std::ifstream& inputFile);
    virtual void writeToFile(std::ofstream& outputFile) const;

    void draw(QPainter& painter, int startX, int startY, int columnWidth, int rowHeight) const;
    QSize calculateSize(int columnWidth, int rowHeight) const;

};



#endif // PLAYER_H
