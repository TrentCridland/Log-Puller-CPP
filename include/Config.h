#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "nlohmann/json.hpp"

#define CONFIG_PATH "assets/config.json"

class Config { 
    public:
        static std::string GetTeamNumber();
        static std::string GetLogPath();
        static std::string GetDownloadPath();
    public:
        static void SetTeamNumber(std::string value);
        static void SetLogPath(std::string value);
        static void SetDownloadPath(std::string value);
};

#endif