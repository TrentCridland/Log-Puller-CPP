#include "Config.h"
#include <fstream>

using json = nlohmann::json;

static json Load()
{
    std::ifstream in(CONFIG_PATH);
    if (!in.is_open())
        throw std::runtime_error("Failed to open config file: " CONFIG_PATH);

    json j;
    in >> j;
    return j;
}

static void Save(const json& j)
{
    std::ofstream out(CONFIG_PATH);
    if (!out.is_open())
        throw std::runtime_error("Failed to write config file: " CONFIG_PATH);

    out << j.dump(4);
}

std::string Config::GetTeamNumber()
{
    json j = Load();
    return j.value("team", "");
}

std::string Config::GetLogPath()
{
    json j = Load();
    return j.value("logs_path", "");
}

std::string Config::GetDownloadPath()
{
    json j = Load();
    return j.value("download_path", "");
}

void Config::SetTeamNumber(std::string value)
{
    json j = Load();
    j["team"] = value;
    Save(j);
}

void Config::SetLogPath(std::string value)
{
    json j = Load();
    j["logs_path"] = value;
    Save(j);
}

void Config::SetDownloadPath(std::string value)
{
    json j = Load();
    j["download_path"] = value;
    Save(j);
}
