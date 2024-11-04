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

    void addPlayer(const std::shared_ptr<Player>& player);
    void removePlayer(int index);

    void addOnlinePlayer();
    //void displayPlayers() const;
    void readFromFile(const std::string& filename);
    void writeToFile(const std::string& filename) const;
    void clearPlayers();

    const std::vector<std::shared_ptr<Player>>& getPlayers() const { return players; }

    std::vector<std::shared_ptr<Player>>::const_iterator begin() const { return players.cbegin(); }
    std::vector<std::shared_ptr<Player>>::const_iterator end() const { return players.cend(); }

    std::shared_ptr<Player> getPlayer(int index) const {
        if (index >= 0 && index < players.size()) {
            return players[index];
        }
        return nullptr;
    }



};


#endif // PLAYERCONTAINER_H
