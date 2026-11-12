#include "logger.h"
#include "lab_environment.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

namespace fs = filesystem;


namespace
{
    string getCurrentTime()
    {
        auto now =
            chrono::system_clock::now();

        time_t currentTime =
            chrono::system_clock::to_time_t(now);

        tm localTime{};

#ifdef _WIN32
        localtime_s(
            &localTime,
            &currentTime
        );
#else
        localtime_r(
            &currentTime,
            &localTime
        );
#endif

        stringstream ss;

        ss << put_time(
            &localTime,
            "%Y-%m-%d %H:%M:%S"
        );

        return ss.str();
    }


    fs::path getLogFile()
    {
        return LabEnvironment::getLabDirectory()
               / "activity_log.txt";
    }
}


namespace Logger
{
    bool logEvent(const string& action)
    {
        fs::path logFile =
            getLogFile();

        // Safety check:
        // Log file must remain inside lab/
        if (!LabEnvironment::isInsideLab(logFile))
        {
            cerr << "[ERROR] Invalid log location.\n";

            return false;
        }

        ofstream file(
            logFile,
            ios::app
        );

        if (!file)
        {
            cerr
                << "[ERROR] Could not open activity log.\n";

            return false;
        }

        file << "Trojan Behavior Simulator Event\n";
        file << "Time: "
             << getCurrentTime()
             << '\n';

        file << "Action: "
             << action
             << '\n';

        file << "Scope: lab directory only\n";

        file << "Status: Harmless simulation\n";

        

        file.close();

        return true;
    }


    void displayLog()
    {
        fs::path logFile =
            getLogFile();

        if (!LabEnvironment::isInsideLab(logFile))
        {
            cerr << "[ERROR] Invalid log location.\n";

            return;
        }

        if (!fs::exists(logFile))
        {
            cout
                << "\nNo simulation events recorded yet.\n";

            return;
        }

        ifstream file(logFile);

        if (!file)
        {
            cerr
                << "[ERROR] Could not open activity log.\n";

            return;
        }

        cout << "\n";
        cout << "              ACTIVITY LOG\n";

        string line;

        while (getline(file, line))
        {
            cout << line << '\n';
        }

        cout << "\n";

        file.close();
    }
}