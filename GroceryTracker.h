#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <cstddef>
#include <map>
#include <ostream>
#include <string>

// Stores purchase counts and provides reporting operations.
class GroceryTracker {
public:
    explicit GroceryTracker(const std::string& inputFile);

    std::size_t GetFrequency(const std::string& item) const;
    void PrintFrequencies(std::ostream& output) const;
    void PrintHistogram(std::ostream& output) const;
    void WriteBackup(const std::string& outputFile) const;

private:
    // Each item name is paired with its purchase count.
    std::map<std::string, std::size_t> itemFrequencies;
};

#endif