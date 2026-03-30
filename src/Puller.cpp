#include "Puller.h"
#include <cstdlib>

void Puller::PullLatestLog() {
    std::string TeamIP       = Util::GetTeamIP();
    std::string LogPath      = Config::GetLogPath();
    std::string DownloadPath = Config::GetDownloadPath();

    // Ensure trailing slash
    if (!DownloadPath.empty() && DownloadPath.back() != '/')
        DownloadPath += "/";

    std::string Command;

#if defined(_WIN32)

    // Detect if running inside Git Bash / MSYS / Cygwin
    const char* shell = std::getenv("MSYSTEM");
    bool isGitBash = (shell != nullptr);

    if (isGitBash) {
        // Git Bash behaves like Linux
        Command =
            "scp \"lvuser@" + TeamIP +
            ":$(ssh lvuser@" + TeamIP +
            " 'ls -t " + LogPath + "/*.wpilog 2>/dev/null | head -n 1')\" " +
            DownloadPath;
    } else {
        // PowerShell syntax
        Command =
            "powershell -Command \"scp ('lvuser@" + TeamIP +
            ":' + (ssh lvuser@" + TeamIP +
            " \\\"ls -t " + LogPath +
            "/*.wpilog 2>/dev/null | head -n 1\\\")) '" +
            DownloadPath + "'\"";
    }

#else
    // Linux + macOS
    Command =
        "scp \"lvuser@" + TeamIP +
        ":$(ssh lvuser@" + TeamIP +
        " 'ls -t " + LogPath + "/*.wpilog 2>/dev/null | head -n 1')\" " +
        DownloadPath;
#endif

    std::system(Command.c_str());
}
