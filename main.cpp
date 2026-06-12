// Week 02 Programming Assignment
// Name: Farris Qureshi
// Description: An upgraded wristwatch collection entry program that gathers
//              details about a watch, validates user input, calculates an
//              estimated resale value and a condition-adjusted market value,
//              and outputs a formatted report to both the console and report.txt.

#include <iostream>
#include <string>
#include <iomanip>   // For setw, setprecision, left, right, fixed
#include <fstream>   // For writing the report to a file
#include <limits>    // For numeric_limits (used to clear bad input)

using namespace std;

int main() {

    // --- Declare variables to store watch information ---
    string brand;
    string model;
    string movementType;
    int    yearPurchased;
    double purchasePrice;
    double annualAppreciationRate;
    int    conditionRating;   // NEW: user rates the watch condition 1-5

    //  WELCOME BANNER
    cout << "============================================================" << endl;
    cout << "        Welcome to Farris's Wristwatch Collection Log       " << endl;
    cout << "       Track your watches, estimate value, stay informed.   " << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << "Let's log a watch from your collection!" << endl;
    cout << endl;

    //  USER INPUT  (mixed types: string, string, string, int,
    //               double, double, int)

    // Read full brand name including spaces (e.g., "Grand Seiko")
    cout << "Watch Brand (e.g., Grand Seiko, Rolex, Omega): ";
    getline(cin, brand);

    // Read full model name including spaces (e.g., "Black Boy")
    cout << "Model Name  (e.g., Submariner, Snowflake, Speedmaster): ";
    getline(cin, model);

    // Read movement type
    cout << "Movement Type (e.g., Automatic, Quartz, Manual): ";
    getline(cin, movementType);

    // Read year purchased and validate it is a reasonable year
    cout << "Year Purchased (e.g., 2021): ";
    cin >> yearPurchased;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline left by cin >>

    // Validate: year must be between 1900 and 2026
    if (cin.fail() || yearPurchased < 1900 || yearPurchased > 2026) {
        cout << "  [!] Invalid year entered. Defaulting to 2020." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        yearPurchased = 2020;
    }

    // Read purchase price and validate it is a positive number
    cout << "Purchase Price (USD, e.g., 450.00): $";
    cin >> purchasePrice;

    // Validate: price must be greater than zero
    if (cin.fail() || purchasePrice <= 0) {
        cout << "  [!] Invalid price entered. Defaulting to $100.00." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        purchasePrice = 100.00;
    }

    // Read annual appreciation rate
    cout << "Estimated Annual Appreciation Rate (%, e.g., 3.5): ";
    cin >> annualAppreciationRate;

    // Validate: rate should be between 0 and 100
    if (cin.fail() || annualAppreciationRate < 0 || annualAppreciationRate > 100) {
        cout << "  [!] Invalid rate entered. Defaulting to 3.0%." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        annualAppreciationRate = 3.0;
    }

    // NEW INPUT: Condition rating 1-5 (1=Poor, 5=Mint)
    cout << "Condition Rating (1 = Poor, 2 = Fair, 3 = Good, 4 = Very Good, 5 = Mint): ";
    cin >> conditionRating;

    // Validate: rating must be 1 through 5
    if (cin.fail() || conditionRating < 1 || conditionRating > 5) {
        cout << "  [!] Invalid rating entered. Defaulting to 3 (Good)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        conditionRating = 3;
    }

    //  DERIVED CALCULATIONS

    int currentYear = 2026;
    int yearsHeld   = currentYear - yearPurchased;

    // Make sure yearsHeld is not negative (e.g., if user entered a future year)
    if (yearsHeld < 0) {
        yearsHeld = 0;
    }

    // Base estimated value using simple linear appreciation formula:
    //   estimatedValue = purchasePrice + (purchasePrice * rate/100 * years)
    double estimatedValue = purchasePrice + (purchasePrice * (annualAppreciationRate / 100.0) * yearsHeld);
    double totalGain      = estimatedValue - purchasePrice;

    // NEW DERIVED VALUE: condition-adjusted market value
    // Condition multiplier maps rating 1-5 to a percentage of estimated value:
    //   1 = 60%,  2 = 75%,  3 = 90%,  4 = 100%,  5 = 110%
    // We store the multiplier as a double, then apply it.
    double conditionMultiplier = 0.60
                               + (conditionRating == 2) * 0.15
                               + (conditionRating == 3) * 0.30
                               + (conditionRating == 4) * 0.40
                               + (conditionRating == 5) * 0.50;

    double conditionAdjustedValue = estimatedValue * conditionMultiplier;

    // Map numeric rating to a human-readable label
    string conditionLabel = "Unknown";
    conditionLabel = (conditionRating == 1) ? "Poor"      : conditionLabel;
    conditionLabel = (conditionRating == 2) ? "Fair"      : conditionLabel;
    conditionLabel = (conditionRating == 3) ? "Good"      : conditionLabel;
    conditionLabel = (conditionRating == 4) ? "Very Good" : conditionLabel;
    conditionLabel = (conditionRating == 5) ? "Mint"      : conditionLabel;

    //  FORMATTED CONSOLE OUTPUT  (using setw and alignment)

    cout << endl;
    cout << "============================================================" << endl;
    cout << "              WRISTWATCH COLLECTION ENTRY REPORT            " << endl;
    cout << "============================================================" << endl;

    // Watch details table
    cout << left << setw(28) << "Brand"          << ": " << brand        << endl;
    cout << left << setw(28) << "Model"          << ": " << model        << endl;
    cout << left << setw(28) << "Movement Type"  << ": " << movementType << endl;
    cout << left << setw(28) << "Year Purchased" << ": " << yearPurchased << endl;
    cout << left << setw(28) << "Years in Collection"
                             << ": " << yearsHeld << " year(s)" << endl;
    cout << left << setw(28) << "Condition"
                             << ": " << conditionRating << " / 5  (" << conditionLabel << ")" << endl;

    cout << "------------------------------------------------------------" << endl;

    // Financial summary table (right-aligned dollar amounts)
    cout << fixed << setprecision(2);
    cout << left  << setw(28) << "Purchase Price"
         << ": $" << right << setw(10) << purchasePrice << endl;

    cout << left  << setw(28) << "Annual Appreciation Rate"
         << ": "  << right << setw(10) << annualAppreciationRate << "%" << endl;

    cout << left  << setw(28) << "Base Estimated Value"
         << ": $" << right << setw(10) << estimatedValue << endl;

    cout << left  << setw(28) << "Total Gain"
         << ": $" << right << setw(10) << totalGain << endl;

    cout << "------------------------------------------------------------" << endl;

    cout << left  << setw(28) << "Condition-Adjusted Value"
         << ": $" << right << setw(10) << conditionAdjustedValue << endl;

    cout << "============================================================" << endl;
    cout << endl;

    // Personalized closing message
    cout << "Your " << brand << " " << model << " has appreciated over "
         << yearsHeld << " year(s)." << endl;
    cout << "At a condition of \"" << conditionLabel
         << "\", its adjusted market value is estimated at $"
         << fixed << setprecision(2) << conditionAdjustedValue << "." << endl;
    cout << "Keep watching the market, Farris — that "
         << movementType << " movement only gets better with time!" << endl;
    cout << endl;
    cout << "============================================================" << endl;
    cout << endl;

    //  SAVE REPORT TO FILE  (report.txt)

    // Open report.txt for writing; this creates or overwrites the file
    ofstream reportFile("report.txt");

    // Check that the file opened successfully before writing
    if (reportFile.is_open()) {

        reportFile << "============================================================" << endl;
        reportFile << "              WRISTWATCH COLLECTION ENTRY REPORT            " << endl;
        reportFile << "============================================================" << endl;

        reportFile << left << setw(28) << "Brand"          << ": " << brand         << endl;
        reportFile << left << setw(28) << "Model"          << ": " << model         << endl;
        reportFile << left << setw(28) << "Movement Type"  << ": " << movementType  << endl;
        reportFile << left << setw(28) << "Year Purchased" << ": " << yearPurchased << endl;
        reportFile << left << setw(28) << "Years in Collection"
                                       << ": " << yearsHeld << " year(s)" << endl;
        reportFile << left << setw(28) << "Condition"
                                       << ": " << conditionRating
                                       << " / 5  (" << conditionLabel << ")" << endl;

        reportFile << "------------------------------------------------------------" << endl;

        reportFile << fixed << setprecision(2);
        reportFile << left  << setw(28) << "Purchase Price"
                   << ": $" << right << setw(10) << purchasePrice << endl;

        reportFile << left  << setw(28) << "Annual Appreciation Rate"
                   << ": "  << right << setw(10) << annualAppreciationRate << "%" << endl;

        reportFile << left  << setw(28) << "Base Estimated Value"
                   << ": $" << right << setw(10) << estimatedValue << endl;

        reportFile << left  << setw(28) << "Total Gain"
                   << ": $" << right << setw(10) << totalGain << endl;

        reportFile << "------------------------------------------------------------" << endl;

        reportFile << left  << setw(28) << "Condition-Adjusted Value"
                   << ": $" << right << setw(10) << conditionAdjustedValue << endl;

        reportFile << "============================================================" << endl;
        reportFile << endl;
        reportFile << "Your " << brand << " " << model << " has appreciated over "
                   << yearsHeld << " year(s)." << endl;
        reportFile << "At a condition of \"" << conditionLabel
                   << "\", its adjusted market value is estimated at $"
                   << fixed << setprecision(2) << conditionAdjustedValue << "." << endl;
        reportFile << "Keep watching the market, Farris — that "
                   << movementType << " movement only gets better with time!" << endl;
        reportFile << endl;
        reportFile << "============================================================" << endl;

        reportFile.close();  // Always close the file when done writing

        cout << "Report saved to report.txt successfully." << endl;

    } else {
        // If the file could not be opened, let the user know
        cout << "[!] Could not open report.txt for writing." << endl;
    }

    cout << endl;

    // Pause so the console window doesn't close immediately during debugging
    cin.ignore();
    cin.get();

    return 0;
}