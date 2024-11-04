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

void PlayerContainer::removePlayer(int index) {
    if (index >= 0 && index < players.size()) {
        players.erase(players.begin() + index);
    }
}

void PlayerContainer::addPlayer(const std::shared_ptr<Player>& player) {
    players.push_back(player);
}
