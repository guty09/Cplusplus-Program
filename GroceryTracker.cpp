#include "GroceryTracker.h"
#include <fstream>
#include <stdexcept>

// Read the purchase records and count each item.
GroceryTracker::GroceryTracker(const std::string& inputFile) {
    std::ifstream input(inputFile);

    if (!input) {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    std::string item;

    while (input >> item) {
        ++itemFrequencies[item];
    }

    if (input.bad()) {
        throw std::runtime_error("Error reading input file: " + inputFile);
    }
}

// Return zero when the requested item is not found.
std::size_t GroceryTracker::GetFrequency(const std::string& item) const {
    const auto entry = itemFrequencies.find(item);

    return entry == itemFrequencies.end() ? 0 : entry->second;
}

// Print every item and its count in alphabetical order.
void GroceryTracker::PrintFrequencies(std::ostream& output) const {
    for (const auto& entry : itemFrequencies) {
        output << entry.first << ' ' << entry.second << '\n';
    }
}

// Print one asterisk for each purchase.
void GroceryTracker::PrintHistogram(std::ostream& output) const {
    for (const auto& entry : itemFrequencies) {
        output << entry.first << ' '
            << std::string(entry.second, '*') << '\n';
    }
}

// Create the backup file and check for writing errors.
void GroceryTracker::WriteBackup(const std::string& outputFile) const {
    std::ofstream output(outputFile);

    if (!output) {
        throw std::runtime_error("Cannot create backup file: " + outputFile);
    }

    PrintFrequencies(output);
    output.close();

    if (!output) {
        throw std::runtime_error("Error writing backup file: " + outputFile);
    }
}