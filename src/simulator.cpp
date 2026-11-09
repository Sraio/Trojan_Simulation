#include "simulator.h"

#include "lab_environment.h"
#include "logger.h"

#include <fstream>
#include <iostream>

using namespace std;

namespace fs = filesystem;


namespace Simulator
{
    void executeSimulation()
    {
        cout << "\n";
        cout << "[Simulator] Starting predefined action...\n";

        fs::path simulationFile =
            LabEnvironment::getLabDirectory()
            / "simulation_result.txt";


        // Safety check:
        // The simulator can only write inside lab/
        if (!LabEnvironment::isInsideLab(simulationFile))
        {
            cerr
                << "[Simulator] Safety check failed.\n";

            return;
        }


        ofstream file(simulationFile);

        if (!file)
        {
            cerr
                << "[Simulator] Could not create "
                << "simulation_result.txt.\n";

            return;
        }


        file << "This file was created by the educational\n";
        file << "Trojan Behavior Simulator.\n\n";

        file << "Simulated behavior:\n";

        file << "A predefined action was executed after\n";
        file << "the application started.\n\n";

        file << "This is NOT a real malicious action.\n";

        file << "Only the controlled lab directory was used.\n";

        file.close();


        if (Logger::logEvent(
                "Created simulation_result.txt"
            ))
        {
            cout
                << "[Simulator] Predefined action completed.\n";

            cout
                << "[Simulator] Result saved inside lab/.\n";
        }
    }
}