#include "Util.h"

#include <iostream>
#include <limits>

namespace Util {
    std::string GetValidStringUserInput(const std::string& Message) {
        std::string value;
        while (true) {
            std::cout << Message;
            std::getline(std::cin >> std::ws, value);
            if (!value.empty()) {
                return value;
            }
            std::cout << "Config cannot be empty. Please try again.\n";
        }
    }

    std::string GetTeamIP() {
        std::string TeamNumber = Config::GetTeamNumber();

        for (char c : TeamNumber) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument("Team number must be numeric.");
            }
        }

        int teamNum = std::stoi(TeamNumber);
        if (teamNum <= 0 || teamNum > 25599) {
            throw std::out_of_range("Team number must be between 1 and 25599.");
        }

        int TE = teamNum / 100;
        int AM = teamNum % 100;

        return "10." + std::to_string(TE) + "." + std::to_string(AM) + ".2";
    }
}