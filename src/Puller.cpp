#include "Puller.h"
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <array>
#include <iostream>

static std::string ExecCommand(const std::string& cmd) {
    std::array<char, 256> buffer;
    std::string result;

#if defined(_WIN32)
    FILE* pipe = _popen(cmd.c_str(), "r");
#else
    FILE* pipe = popen(cmd.c_str(), "r");
#endif

    if (!pipe) return "";

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

#if defined(_WIN32)
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    return result;
}

void Puller::PullLatestLog() {
    std::string TeamIP       = Util::GetTeamIP();
    std::string LogPath      = Config::GetLogPath();
    std::string DownloadPath = Config::GetDownloadPath();

    // Ensure trailing slash
    if (!DownloadPath.empty() && DownloadPath.back() != '/' && DownloadPath.back() != '\\')
        DownloadPath += "/";

#if defined(_WIN32)
    const char* shell = std::getenv("MSYSTEM");
    bool isGitBash = (shell != nullptr);
#endif

    std::string sshOptions =
        "-o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null ";

    std::string sshCmd =
        "ssh " + sshOptions + "lvuser@" + TeamIP +
        " \"ls -t " + LogPath + "/*.wpilog 2>/dev/null | head -n 1\"";

    std::cout << "Running SSH command...\n";
    std::string latestFile = ExecCommand(sshCmd);

    if (latestFile.empty()) {
        std::cerr << "Error: No log file found or SSH failed.\n";
        return;
    }

    std::cout << "Latest log file: " << latestFile << "\n";

    std::string scpCmd;

#if defined(_WIN32)
    if (isGitBash) {
        // Git Bash behaves like Linux
        scpCmd =
            "scp " + sshOptions +
            "\"lvuser@" + TeamIP + ":" + latestFile + "\" \"" +
            DownloadPath + "\"";
    } else {
        // PowerShell
        scpCmd =
            "powershell -Command \"scp " + sshOptions +
            "'lvuser@" + TeamIP + ":" + latestFile + "' '" +
            DownloadPath + "'\"";
    }
#else
    // Linux / macOS
    scpCmd =
        "scp " + sshOptions +
        "\"lvuser@" + TeamIP + ":" + latestFile + "\" \"" +
        DownloadPath + "\"";
#endif

    std::cout << "Running SCP command...\n";
    int result = std::system(scpCmd.c_str());

    if (result != 0) {
        std::cerr << "Error: SCP failed with code " << result << "\n";
        return;
    }

    std::cout << "Download successful.\n";
}