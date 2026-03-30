#ifndef UTIL_H
#define UTIL_H

#include "Config.h"

#include <string>

namespace Util {
    std::string GetValidStringUserInput(const std::string& Message);
    std::string GetTeamIP();
}

#endif
