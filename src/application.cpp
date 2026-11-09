#include "application.h"

#include "lab_environment.h"
#include "logger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <limits>

using namespace std;

namespace fs = filesystem;


namespace
{
    void showMenu()
    {
        cout << "\n";
        cout << "--------------- MENU ----------------\n";

        cout << "1. Create a Note\n";
        cout << "2. View Lab Files\n";
        cout << "3. View Activity Log\n";
        cout << "4. About Application\n";
        cout << "5. Exit\n";

        cout << "-------------------------------------\n";

        cout << "Choose an option: ";
    }


    void createNote()
    {
        string note;

        cout << "\nEnter your note:\n";
        cout << "> ";

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        getline(cin, note);


        fs::path noteFile =
            LabEnvironment::getLabDirectory()
            / "user_note.txt";


        // Safety check
        if (!LabEnvironment::isInsideLab(noteFile))
        {
            cerr
                << "[ERROR] Invalid note location.\n";

            return;
        }


        ofstream file(noteFile);

        if (!file)
        {
            cerr
                << "[ERROR] Could not save note.\n";

            return;
        }


        file << note << '\n';

        file.close();


        cout
            << "\n[+] Note saved successfully.\n";


        Logger::logEvent(
            "User created a note"
        );
    }


    void showLabFiles()
    {
        fs::path labDirectory =
            LabEnvironment::getLabDirectory();


        cout << "\n";
        cout << "============================================\n";
        cout << "                 LAB FILES\n";
        cout << "============================================\n";


        try
        {
            for (const auto& entry :
                 fs::directory_iterator(labDirectory))
            {
                cout
                    << "- "
                    << entry.path()
                           .filename()
                           .string();


                if (fs::is_directory(entry))
                {
                    cout << " [Directory]";
                }
                else
                {
                    cout << " [File]";
                }

                cout << '\n';
            }
        }
        catch (const fs::filesystem_error& e)
        {
            cerr
                << "[ERROR] "
                << e.what()
                << '\n';
        }


        cout
            << "============================================\n";
    }


    void showAbout()
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "              ABOUT PROJECT\n";
        cout << "============================================\n";


        cout
            << "Project : Trojan Behavior Simulator\n";

        cout
            << "Language: C++\n";

        cout
            << "Purpose : Cyber Security Education\n\n";


        cout
            << "This program demonstrates the basic concept\n";

        cout
            << "of Trojan-like behavior in a controlled lab.\n\n";


        cout
            << "The simulator does not access personal files,\n";

        cout
            << "passwords, network resources, or system settings.\n";


        cout
            << "============================================\n";
    }
}


namespace Application
{
    void run()
    {
        int choice = 0;


        do
        {
            showMenu();


            if (!(cin >> choice))
            {
                cin.clear();

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );


                cout
                    << "\n[!] Please enter a number.\n";

                continue;
            }


            switch (choice)
            {
                case 1:
                    createNote();
                    break;


                case 2:
                    showLabFiles();
                    break;


                case 3:
                    Logger::displayLog();
                    break;


                case 4:
                    showAbout();
                    break;


                case 5:
                    cout
                        << "\nExiting application...\n";

                    break;


                default:
                    cout
                        << "\n[!] Invalid option.\n";
            }

        }
        while (choice != 5);
    }
}