#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <filesystem>
#include <iostream>

#include "nlohmann/json.hpp"
#include "Util.h"

#define CONFIG_PATH "assets/config.json"
#define CONFIG_ASSETS_PATH "assets"

class Config { 
    public:
        static std::string GetTeamNumber();
        static std::string GetLogPath();
        static std::string GetDownloadPath();
    public:
        static void SetTeamNumber(const std::string& value);
        static void SetLogPath(const std::string& value);
        static void SetDownloadPath(const std::string& value);
    public:
        static void SetTeamNumberWithInput();
        static void SetLogPathWithInput();
        static void SetDownloadPathWithInput();
    public:
        static bool ConfigFileExists();
    public: 
        static void CreateConfigFile();
};

#endif