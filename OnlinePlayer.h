#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#pragma once
#include "Player.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <fstream>
#include <string>

class OnlinePlayer : public Player {
private:

    std::string virtual_name;
    std::string email;
    unsigned long long int tel;

    // предоставление доступа к приватным данным для boost
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& boost::serialization::base_object<Player>(*this);
        ar& virtual_name;
        ar& email;
        ar& tel;
    }

public:
    OnlinePlayer();
    virtual ~OnlinePlayer();

    // virtual void readFromConsole() override;
    // virtual void displayToConsole() const override;

    void readFromFile(std::ifstream& inputFile) override;
    void writeToFile(std::ofstream& outputFile) const override;

    void draw(QPainter& painter, int startX, int startY, int columnWidth, int rowHeight) const;
    QSize calculateSize(int columnWidth, int rowHeight) const;

    void setVirtualName(const std::string& newVirtualName) { virtual_name = newVirtualName; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setTel(unsigned long long int newTel) { tel = newTel; }

    const std::string& getVirtual_name() const { return virtual_name; }
    const std::string& getEmail() const { return email; }
    unsigned long long int getTel() const { return tel; }

};



#endif // ONLINEPLAYER_H
