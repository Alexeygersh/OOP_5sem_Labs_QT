#include "PlayerContainer.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

void PlayerContainer::readFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        boost::archive::text_iarchive ia(inputFile);
        ia >> *this;
        inputFile.close();
    }
}


void PlayerContainer::writeToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        boost::archive::text_oarchive oa(outputFile);
        oa << *this;
        outputFile.close();
    }
}

void PlayerContainer::clearPlayers() {
    players.clear();
}
