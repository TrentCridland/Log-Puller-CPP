#include "App.h"

App::App() {
    std::cout << "Starting log puller...\n";

    if(Config::ConfigFileExists()) {
        std::cout << "Found config file at assets/config.json\n";
    } else {
        std::cout << "Couldn't find the config file at assets/config.json\n";
        Config::CreateConfigFile();
        
        // Set new values
        std::cout << "Set the values for this config file:\n";
        Config::SetTeamNumberWithInput();
        Config::SetLogPathWithInput();
        Config::SetDownloadPathWithInput();
    }
}

App::~App() {
    
}

void App::RunApp() {
    while (true) {
        std::string input = Util::GetValidStringUserInput(
            "Input your next action:\n" \
            "1. \"pull\" - pulls the latest log from the robot\n" \
            "2. \"set\" - sets a config value\n" \
            "3. \"exit\" - exits the program\n" \
            "Input your action : "
        );

        if (input == "pull" || input == "1") {
            RunPull();
        } else if (input == "set" || input == "2") {
            RunSet();
        } else if (input == "exit" || input == "3") {
            std::cout << "Exiting...\n";
            break;
        }
    }
}

void App::RunPull() {

}

void App::RunSet() {
    while (true) {
        std::string input = Util::GetValidStringUserInput(
            "Input your next action:\n" \
            "1. \"team number\" - sets the team number\n" \
            "2. \"log path\" - sets the log path\n" \
            "3. \"download path\" - sets the \n" \
            "4. \"back\" - goes back \n" \
            "Input your action : "
        );

        if (input == "team number" || input == "1") {
            Config::SetTeamNumberWithInput();
        } else if (input == "log path" || input == "2") {
            Config::SetLogPathWithInput();
        } else if (input == "download path" || input == "3") {
            Config::SetDownloadPathWithInput();
        } else if (input == "back" || input == "4") {
            std::cout << "Going back...\n";
            break;
        }
    }
}
