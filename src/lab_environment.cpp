#include "lab_environment.h"

#include <fstream>
#include <iostream>

using namespace std;

namespace fs = filesystem;

namespace LabEnvironment
{
    fs::path getLabDirectory()
    {
        return fs::path("lab");
    }


    bool isInsideLab(const fs::path& path)
    {
        try
        {
            fs::path labPath =
                fs::absolute(getLabDirectory())
                .lexically_normal();

            fs::path targetPath =
                fs::absolute(path)
                .lexically_normal();

            auto labIt = labPath.begin();
            auto targetIt = targetPath.begin();

            for (;
                 labIt != labPath.end();
                 ++labIt, ++targetIt)
            {
                if (targetIt == targetPath.end()
                    || *labIt != *targetIt)
                {
                    return false;
                }
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }


    bool initialize()
    {
        try
        {
            fs::path labDirectory =
                getLabDirectory();

            // Create lab directory if it doesn't exist
            if (!fs::exists(labDirectory))
            {
                fs::create_directory(labDirectory);
            }

            // Make sure "lab" is actually a directory
            if (!fs::is_directory(labDirectory))
            {
                cerr << "[ERROR] 'lab' is not a directory.\n";

                return false;
            }

            // Create harmless test file
            fs::path testFile =
                labDirectory / "test_data.txt";

            if (!fs::exists(testFile))
            {
                ofstream file(testFile);

                if (!file)
                {
                    cerr
                        << "[ERROR] Could not create test_data.txt.\n";

                    return false;
                }

                file << "This is harmless test data.\n";
                file << "It belongs to the Trojan Behavior Simulator lab.\n";

                file.close();
            }

            return true;
        }
        catch (const fs::filesystem_error& e)
        {
            cerr
                << "[ERROR] Filesystem error: "
                << e.what()
                << '\n';

            return false;
        }
    }
}