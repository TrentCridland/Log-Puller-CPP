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
}