#ifndef PLAYERCONTAINER_H
#define PLAYERCONTAINER_H

#pragma once
#include "Player.h"
#include "OnlinePlayer.h"
#include <vector>
#include <memory>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

class PlayerContainer {
private:
    std::vector<std::shared_ptr<Player>> players;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& players;
    }

public:
    PlayerContainer() = default;
    ~PlayerContainer() = default;

    //void addPlayer();
    void addPlayer(const std::shared_ptr<Player>& player) {
        players.push_back(player);
    }
    void addOnlinePlayer();
    //void displayPlayers() const;
    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;
    void clearPlayers();

    const std::vector<std::shared_ptr<Player>>& getPlayers() const { return players; }
};


#endif // PLAYERCONTAINER_H
