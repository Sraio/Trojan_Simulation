#include <iostream>

#include "application.h"
#include "lab_environment.h"
#include "simulator.h"

using namespace std;

int main()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "       TROJAN BEHAVIOR SIMULATOR\n";
    cout << "============================================\n";

    // Initialize the controlled laboratory environment
    if (!LabEnvironment::initialize())
    {
        cerr << "\n[ERROR] Could not initialize lab environment.\n";

        return 1;
    }

    cout << "\n[+] Controlled lab environment initialized.\n";

    // Execute harmless Trojan-like behavior
    Simulator::executeSimulation();

    // Start the legitimate-looking application
    Application::run();

    cout << "\nProgram terminated safely.\n";

    return 0;
}