// Agustin Espinoza Ruvalcaba
// CS - 210
// Professor Bill Chan


#include "GroceryTracker.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

// Accept only a single integer from 1 through 4.
int ReadMenuChoice(const std::string& line) {
    std::istringstream input(line);
    int choice = 0;
    std::string extra;

    if (!(input >> choice) || (input >> extra)
        || choice < 1 || choice > 4) {
        return 0;
    }

    return choice;
}

int main() {
    try {
        GroceryTracker tracker("CS210_Project_Three_Input_File.txt");

        // Create the backup automatically before displaying the menu.
        tracker.WriteBackup("frequency.dat");

        std::string line;

        while (true) {
            std::cout << "\nCorner Grocer\n"
                << "1. Find item frequency\n"
                << "2. List all frequencies\n"
                << "3. Display histogram\n"
                << "4. Exit\n"
                << "Choose an option: ";

            // Exit cleanly if the input stream closes.
            if (!std::getline(std::cin, line)) {
                break;
            }

            const int choice = ReadMenuChoice(line);

            if (choice == 4) {
                break;
            }

            switch (choice) {
            case 1: {
                std::cout
                    << "Enter item (case-sensitive, e.g., Cranberries): ";

                if (!std::getline(std::cin, line)) {
                    std::cout << "\nGoodbye.\n";
                    return 0;
                }

                std::istringstream input(line);
                std::string item;
                std::string extra;

                // Require exactly one item name.
                if (!(input >> item) || (input >> extra)) {
                    std::cout << "Enter exactly one item name.\n";
                }
                else {
                    std::cout << item << " frequency: "
                        << tracker.GetFrequency(item) << '\n';
                }

                break;
            }

            case 2:
                tracker.PrintFrequencies(std::cout);
                break;

            case 3:
                tracker.PrintHistogram(std::cout);
                break;

            default:
                std::cout << "Invalid choice. Enter 1, 2, 3, or 4.\n";
                break;
            }
        }

        std::cout << "Goodbye.\n";
        return 0;
    }
    catch (const std::exception& error) {
        // Report file errors instead of terminating without an explanation.
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}