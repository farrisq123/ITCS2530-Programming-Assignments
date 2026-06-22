// Week 05 Programming Assignment
// Name: Farris Qureshi
// Description: A wristwatch collection tracker. This version refactors the
//              program into user-defined functions for the banner, menu,
//              input collection, validation, calculations, report saving,
//              and console color. Magic numbers replaced with const variables.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include <windows.h>   // For SetConsoleTextAttribute (console color)

using namespace std;

// --- Constants (replaces magic numbers used throughout the program) ---
const int    MIN_YEAR       = 1900;
const int    MAX_YEAR       = 2026;
const double MIN_PRICE      = 0.01;
const double MAX_RATE       = 100.0;
const int    MIN_CONDITION  = 1;
const int    MAX_CONDITION  = 5;
const double DEFAULT_PRICE  = 100.00;
const double DEFAULT_RATE   = 3.0;
const int    DEFAULT_COND   = 3;

// --- Console color codes (Windows) ---
const int COLOR_DEFAULT = 7;   // White on black
const int COLOR_HEADER  = 11;  // Bright cyan  -- banners and section headers
const int COLOR_PROMPT  = 14;  // Yellow       -- user prompts
const int COLOR_SUCCESS = 10;  // Bright green -- positive feedback
const int COLOR_WARNING = 12;  // Bright red   -- warnings and errors
const int COLOR_DATA    = 15;  // Bright white -- table data

//  FUNCTION: setColor
//  Purpose : Changes the console text color.
//  Param   : colorCode - Windows console color attribute (0-15)
void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

//  FUNCTION: displayBanner
//  Purpose : Prints the welcome banner at program startup.
void displayBanner() {
    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    cout << "        Welcome to Farris's Wristwatch Collection Log       " << endl;
    cout << "       Track your watches, estimate value, stay informed.   " << endl;
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
}

//  FUNCTION: displayMenu
//  Purpose : Prints the main menu options to the console.
void displayMenu() {
    setColor(COLOR_HEADER);
    cout << "------------------------------------------------------------" << endl;
    cout << "  MAIN MENU" << endl;
    cout << "------------------------------------------------------------" << endl;
    setColor(COLOR_DEFAULT);
    cout << "  1. Add a watch to your collection" << endl;
    cout << "  2. View weekly collection report" << endl;
    cout << "  3. Get a recommendation based on your collection" << endl;
    cout << "  4. Quit" << endl;
    setColor(COLOR_HEADER);
    cout << "------------------------------------------------------------" << endl;
    setColor(COLOR_PROMPT);
    cout << "  Enter your choice (1-4): ";
    setColor(COLOR_DEFAULT);
}

//  FUNCTION: validateMenuChoice
//  Purpose : Returns true if the menu choice is 1-4, false otherwise.
//  Param   : choice - the integer entered by the user
bool validateMenuChoice(int choice) {
    return (choice >= 1 && choice <= 4);
}

//  FUNCTION: collectWatchInput
//  Purpose : Prompts the user for all watch details and stores
//            them in the referenced variables. Uses a while loop
//            for year validation and if/else for other fields.
//  Params  : brand, model, movementType, yearPurchased,
//            purchasePrice, annualAppreciationRate, conditionRating
//            -- all passed by reference so changes persist
void collectWatchInput(string &brand, string &model, string &movementType,
                       int &yearPurchased, double &purchasePrice,
                       double &annualAppreciationRate, int &conditionRating) {

    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    cout << "  ADD A WATCH" << endl;
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    // -- String input: brand (spaces allowed via getline) --
    setColor(COLOR_PROMPT);
    cout << "  Watch Brand (e.g., Grand Seiko, Rolex, Omega): ";
    setColor(COLOR_DEFAULT);
    getline(cin, brand);

    // -- String input: model --
    setColor(COLOR_PROMPT);
    cout << "  Model Name  (e.g., Submariner, Snowflake, Speedmaster): ";
    setColor(COLOR_DEFAULT);
    getline(cin, model);

    // -- String input: movement type --
    setColor(COLOR_PROMPT);
    cout << "  Movement Type (e.g., Automatic, Quartz, Manual): ";
    setColor(COLOR_DEFAULT);
    getline(cin, movementType);

    // -- Int input: year purchased -- validated with a while loop --
    setColor(COLOR_PROMPT);
    cout << "  Year Purchased (" << MIN_YEAR << " - " << MAX_YEAR << "): ";
    setColor(COLOR_DEFAULT);
    cin >> yearPurchased;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // WHILE LOOP: keeps asking until a valid year is entered
    while (cin.fail() || yearPurchased < MIN_YEAR || yearPurchased > MAX_YEAR) {
        setColor(COLOR_WARNING);
        cout << "  [!] Please enter a valid year between "
             << MIN_YEAR << " and " << MAX_YEAR << ": ";
        setColor(COLOR_DEFAULT);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> yearPurchased;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // -- Double input: purchase price --
    setColor(COLOR_PROMPT);
    cout << "  Purchase Price (USD, e.g., 450.00): $";
    setColor(COLOR_DEFAULT);
    cin >> purchasePrice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || purchasePrice <= 0) {
        setColor(COLOR_WARNING);
        cout << "  [!] Invalid price. Defaulting to $"
             << fixed << setprecision(2) << DEFAULT_PRICE << "." << endl;
        setColor(COLOR_DEFAULT);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        purchasePrice = DEFAULT_PRICE;
    }

    // -- Double input: appreciation rate --
    setColor(COLOR_PROMPT);
    cout << "  Estimated Annual Appreciation Rate (%, e.g., 3.5): ";
    setColor(COLOR_DEFAULT);
    cin >> annualAppreciationRate;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || annualAppreciationRate < 0 || annualAppreciationRate > MAX_RATE) {
        setColor(COLOR_WARNING);
        cout << "  [!] Invalid rate. Defaulting to "
             << DEFAULT_RATE << "%." << endl;
        setColor(COLOR_DEFAULT);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        annualAppreciationRate = DEFAULT_RATE;
    }

    // -- Int input: condition rating --
    setColor(COLOR_PROMPT);
    cout << "  Condition Rating (1=Poor, 2=Fair, 3=Good, 4=Very Good, 5=Mint): ";
    setColor(COLOR_DEFAULT);
    cin >> conditionRating;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || conditionRating < MIN_CONDITION || conditionRating > MAX_CONDITION) {
        setColor(COLOR_WARNING);
        cout << "  [!] Invalid rating. Defaulting to "
             << DEFAULT_COND << " (Good)." << endl;
        setColor(COLOR_DEFAULT);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        conditionRating = DEFAULT_COND;
    }
}

//  FUNCTION: calculateValues
//  Purpose : Computes derived values for a single watch entry.
//            All results are passed back through reference params.
//  Params  : yearPurchased, purchasePrice, annualAppreciationRate,
//            conditionRating -- inputs
//            yearsHeld, estimatedValue, totalGain,
//            conditionAdjustedValue, conditionLabel -- outputs
void calculateValues(int yearPurchased, double purchasePrice,
                     double annualAppreciationRate, int conditionRating,
                     int &yearsHeld, double &estimatedValue,
                     double &totalGain, double &conditionAdjustedValue,
                     string &conditionLabel) {

    yearsHeld = MAX_YEAR - yearPurchased;
    if (yearsHeld < 0) {
        yearsHeld = 0;
    }

    // Linear appreciation: price + (price * rate/100 * years)
    estimatedValue = purchasePrice
                   + (purchasePrice * (annualAppreciationRate / 100.0) * yearsHeld);
    totalGain = estimatedValue - purchasePrice;

    // Condition multiplier: rating 1-5 maps to 60%-110% of estimated value
    double conditionMultiplier = 0.60
                               + (conditionRating == 2) * 0.15
                               + (conditionRating == 3) * 0.30
                               + (conditionRating == 4) * 0.40
                               + (conditionRating == 5) * 0.50;

    conditionAdjustedValue = estimatedValue * conditionMultiplier;

    // Map numeric rating to readable label
    conditionLabel = "Unknown";
    conditionLabel = (conditionRating == 1) ? "Poor"      : conditionLabel;
    conditionLabel = (conditionRating == 2) ? "Fair"      : conditionLabel;
    conditionLabel = (conditionRating == 3) ? "Good"      : conditionLabel;
    conditionLabel = (conditionRating == 4) ? "Very Good" : conditionLabel;
    conditionLabel = (conditionRating == 5) ? "Mint"      : conditionLabel;
}

//  FUNCTION: displayWatchSummary
//  Purpose : Prints a formatted table for a single watch entry
//            and displays a recommendation using compound
//            if/else conditions (IF/ELSE BLOCK 1).
void displayWatchSummary(const string &brand, const string &model,
                         const string &movementType, int yearPurchased,
                         int yearsHeld, int conditionRating,
                         const string &conditionLabel, double purchasePrice,
                         double annualAppreciationRate, double estimatedValue,
                         double totalGain, double conditionAdjustedValue) {

    setColor(COLOR_HEADER);
    cout << endl;
    cout << "============================================================" << endl;
    cout << "              WRISTWATCH COLLECTION ENTRY REPORT            " << endl;
    cout << "============================================================" << endl;
    setColor(COLOR_DATA);

    cout << left << setw(28) << "  Brand"          << ": " << brand        << endl;
    cout << left << setw(28) << "  Model"          << ": " << model        << endl;
    cout << left << setw(28) << "  Movement Type"  << ": " << movementType << endl;
    cout << left << setw(28) << "  Year Purchased" << ": " << yearPurchased << endl;
    cout << left << setw(28) << "  Years in Collection"
                             << ": " << yearsHeld << " year(s)" << endl;
    cout << left << setw(28) << "  Condition"
                             << ": " << conditionRating
                             << " / 5  (" << conditionLabel << ")" << endl;

    setColor(COLOR_HEADER);
    cout << "------------------------------------------------------------" << endl;
    setColor(COLOR_DATA);

    cout << fixed << setprecision(2);
    cout << left  << setw(28) << "  Purchase Price"
         << ": $" << right << setw(10) << purchasePrice << endl;
    cout << left  << setw(28) << "  Annual Appreciation Rate"
         << ":  " << right << setw(10) << annualAppreciationRate << "%" << endl;
    cout << left  << setw(28) << "  Base Estimated Value"
         << ": $" << right << setw(10) << estimatedValue << endl;
    cout << left  << setw(28) << "  Total Gain"
         << ": $" << right << setw(10) << totalGain << endl;

    setColor(COLOR_HEADER);
    cout << "------------------------------------------------------------" << endl;
    setColor(COLOR_DATA);

    cout << left  << setw(28) << "  Condition-Adjusted Value"
         << ": $" << right << setw(10) << conditionAdjustedValue << endl;

    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    // IF/ELSE BLOCK 1 -- Compound boolean condition
    // Checks both condition rating AND years held to assess resale potential.
    if (conditionRating >= 4 && yearsHeld >= 3) {
        setColor(COLOR_SUCCESS);
        cout << "  >> Great news! This watch is in excellent condition AND" << endl;
        cout << "     has been held for " << yearsHeld
             << " years -- a strong resale candidate." << endl;
    } else if (conditionRating <= 2 && totalGain > 0) {
        setColor(COLOR_WARNING);
        cout << "  >> This watch has gained value, but its condition may" << endl;
        cout << "     lower the resale price. Consider servicing it." << endl;
    } else {
        setColor(COLOR_DEFAULT);
        cout << "  >> Watch logged successfully to your collection." << endl;
    }

    setColor(COLOR_DEFAULT);
    cout << endl;
}

//  FUNCTION: saveReport
//  Purpose : Appends a single watch entry's data to report.txt.
void saveReport(const string &brand, const string &model,
                const string &movementType, int yearPurchased,
                int yearsHeld, int conditionRating,
                const string &conditionLabel, double purchasePrice,
                double annualAppreciationRate, double estimatedValue,
                double totalGain, double conditionAdjustedValue) {

    ofstream reportFile("report.txt", ios::app);

    if (reportFile.is_open()) {
        reportFile << "============================================================" << endl;
        reportFile << "              WRISTWATCH COLLECTION ENTRY REPORT            " << endl;
        reportFile << "============================================================" << endl;
        reportFile << left << setw(28) << "  Brand"          << ": " << brand        << endl;
        reportFile << left << setw(28) << "  Model"          << ": " << model        << endl;
        reportFile << left << setw(28) << "  Movement Type"  << ": " << movementType << endl;
        reportFile << left << setw(28) << "  Year Purchased" << ": " << yearPurchased << endl;
        reportFile << left << setw(28) << "  Years in Collection"
                                       << ": " << yearsHeld << " year(s)" << endl;
        reportFile << left << setw(28) << "  Condition"
                                       << ": " << conditionRating
                                       << " / 5  (" << conditionLabel << ")" << endl;
        reportFile << "------------------------------------------------------------" << endl;
        reportFile << fixed << setprecision(2);
        reportFile << left  << setw(28) << "  Purchase Price"
                   << ": $" << right << setw(10) << purchasePrice << endl;
        reportFile << left  << setw(28) << "  Annual Appreciation Rate"
                   << ":  " << right << setw(10) << annualAppreciationRate << "%" << endl;
        reportFile << left  << setw(28) << "  Base Estimated Value"
                   << ": $" << right << setw(10) << estimatedValue << endl;
        reportFile << left  << setw(28) << "  Total Gain"
                   << ": $" << right << setw(10) << totalGain << endl;
        reportFile << "------------------------------------------------------------" << endl;
        reportFile << left  << setw(28) << "  Condition-Adjusted Value"
                   << ": $" << right << setw(10) << conditionAdjustedValue << endl;
        reportFile << "============================================================" << endl;
        reportFile << endl;
        reportFile.close();

        setColor(COLOR_SUCCESS);
        cout << "  Report appended to report.txt successfully." << endl;
        setColor(COLOR_DEFAULT);
    } else {
        setColor(COLOR_WARNING);
        cout << "  [!] Could not open report.txt for writing." << endl;
        setColor(COLOR_DEFAULT);
    }
}

//  FUNCTION: displayWeeklyReport
//  Purpose : Shows a summary of all watches logged this session.
//            Uses a for loop to print a session progress bar,
//            and a compound if/else to assess overall performance
//            (IF/ELSE BLOCK 2).
void displayWeeklyReport(int watchCount, double totalPurchaseValue,
                         double totalEstimatedValue) {

    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    cout << "              WEEKLY COLLECTION SUMMARY REPORT              " << endl;
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    if (watchCount == 0) {
        setColor(COLOR_WARNING);
        cout << "  No watches have been logged this session yet." << endl;
        cout << "  Use option 1 to add a watch first." << endl;
        setColor(COLOR_DEFAULT);
    } else {
        double averageValue = totalEstimatedValue / watchCount;
        double overallGain  = totalEstimatedValue - totalPurchaseValue;

        setColor(COLOR_DATA);
        cout << fixed << setprecision(2);
        cout << left << setw(30) << "  Watches Logged This Session" << ": " << watchCount  << endl;
        cout << left << setw(30) << "  Total Amount Invested"
             << ": $" << right << setw(10) << totalPurchaseValue << endl;
        cout << left << setw(30) << "  Total Estimated Value"
             << ": $" << right << setw(10) << totalEstimatedValue << endl;
        cout << left << setw(30) << "  Overall Collection Gain"
             << ": $" << right << setw(10) << overallGain << endl;
        cout << left << setw(30) << "  Average Watch Value"
             << ": $" << right << setw(10) << averageValue << endl;
        setColor(COLOR_DEFAULT);
        cout << endl;

        // FOR LOOP: runs exactly watchCount times to print a session progress bar
        setColor(COLOR_PROMPT);
        cout << "  Session Progress: ";
        for (int i = 0; i < watchCount; i++) {
            cout << "[Watch " << (i + 1) << "] ";
        }
        setColor(COLOR_DEFAULT);
        cout << endl << endl;

        // IF/ELSE BLOCK 2 -- Compound boolean condition
        // Evaluates both watch count AND overall gain to give feedback.
        if (watchCount >= 3 && overallGain >= 500.0) {
            setColor(COLOR_SUCCESS);
            cout << "  >> Impressive collection! You've logged " << watchCount
                 << " watches" << endl;
            cout << "     with a total estimated gain of $"
                 << fixed << setprecision(2) << overallGain << "." << endl;
            cout << "     Your collection is growing in both size and value!" << endl;
        } else if (watchCount >= 1 && overallGain > 0) {
            setColor(COLOR_SUCCESS);
            cout << "  >> Good progress! Your collection has gained $"
                 << fixed << setprecision(2) << overallGain
                 << " in estimated value." << endl;
        } else {
            setColor(COLOR_DEFAULT);
            cout << "  >> Keep adding watches to build your collection!" << endl;
        }
        setColor(COLOR_DEFAULT);
    }

    cout << endl;
    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
}

//  FUNCTION: displayRecommendation
//  Purpose : Gives a watch buying recommendation based on the
//            user's average collection value.
void displayRecommendation(int watchCount, double totalEstimatedValue) {

    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    cout << "              COLLECTION RECOMMENDATION ENGINE              " << endl;
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    if (watchCount == 0) {
        setColor(COLOR_WARNING);
        cout << "  Log at least one watch first (option 1) to get" << endl;
        cout << "  a recommendation tailored to your collection." << endl;
        setColor(COLOR_DEFAULT);
    } else {
        double averageValue = totalEstimatedValue / watchCount;

        setColor(COLOR_DATA);
        cout << fixed << setprecision(2);
        cout << "  Your average watch value is: $" << averageValue << endl;
        setColor(COLOR_DEFAULT);
        cout << endl;

        if (averageValue >= 5000.0 && watchCount >= 2) {
            setColor(COLOR_SUCCESS);
            cout << "  >> HIGH-END COLLECTOR: Your collection averages over $5,000" << endl;
            cout << "     per watch. Consider diversifying with a dress watch" << endl;
            cout << "     (e.g., A. Lange & Soehne or Patek Philippe)." << endl;
        } else if (averageValue >= 1000.0 && averageValue < 5000.0) {
            setColor(COLOR_SUCCESS);
            cout << "  >> MID-RANGE COLLECTOR: Solid range! You might enjoy adding" << endl;
            cout << "     a Grand Seiko or Tudor to round out your collection." << endl;
        } else {
            setColor(COLOR_DEFAULT);
            cout << "  >> ENTRY-LEVEL COLLECTOR: Great start! Explore Seiko or" << endl;
            cout << "     Orient for reliable, affordable automatic movements." << endl;
        }
        setColor(COLOR_DEFAULT);
    }

    cout << endl;
    setColor(COLOR_HEADER);
    cout << "============================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
}

//  FUNCTION: main
//  Purpose : Entry point. Manages the do-while menu loop and
//            calls the appropriate function for each menu option.
int main() {

    // --- Collection totals (accumulated across the session) ---
    int    watchCount          = 0;
    double totalPurchaseValue  = 0.0;
    double totalEstimatedValue = 0.0;

    // --- Variables for a single watch entry ---
    string brand, model, movementType, conditionLabel;
    int    yearPurchased, conditionRating, yearsHeld;
    double purchasePrice, annualAppreciationRate;
    double estimatedValue, totalGain, conditionAdjustedValue;

    int menuChoice = 0;

    // Display the welcome banner
    displayBanner();

    // DO-WHILE LOOP: shows the menu at least once, repeats until user quits
    do {
        displayMenu();
        cin >> menuChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Validate menu choice; if bad, warn and loop again
        if (cin.fail() || !validateMenuChoice(menuChoice)) {
            setColor(COLOR_WARNING);
            cout << "  [!] Invalid choice. Please enter 1, 2, 3, or 4." << endl;
            setColor(COLOR_DEFAULT);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            continue;
        }

        cout << endl;

        // SWITCH: routes the user to the correct program section
        switch (menuChoice) {

            case 1:
                // Collect input, calculate values, display and save the report
                collectWatchInput(brand, model, movementType,
                                  yearPurchased, purchasePrice,
                                  annualAppreciationRate, conditionRating);

                calculateValues(yearPurchased, purchasePrice,
                                annualAppreciationRate, conditionRating,
                                yearsHeld, estimatedValue, totalGain,
                                conditionAdjustedValue, conditionLabel);

                displayWatchSummary(brand, model, movementType,
                                    yearPurchased, yearsHeld,
                                    conditionRating, conditionLabel,
                                    purchasePrice, annualAppreciationRate,
                                    estimatedValue, totalGain,
                                    conditionAdjustedValue);

                saveReport(brand, model, movementType,
                           yearPurchased, yearsHeld,
                           conditionRating, conditionLabel,
                           purchasePrice, annualAppreciationRate,
                           estimatedValue, totalGain,
                           conditionAdjustedValue);

                // Update running totals
                watchCount++;
                totalPurchaseValue  += purchasePrice;
                totalEstimatedValue += estimatedValue;

                cout << endl;
                break;

            case 2:
                displayWeeklyReport(watchCount, totalPurchaseValue,
                                    totalEstimatedValue);
                break;

            case 3:
                displayRecommendation(watchCount, totalEstimatedValue);
                break;

            case 4:
                setColor(COLOR_SUCCESS);
                cout << "  Thanks for using Farris's Wristwatch Collection Log!" << endl;
                cout << "  Keep watching the market!" << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
                break;
        }

    } while (menuChoice != 4);  // DO-WHILE condition: keep looping until quit

    // Pause before the console window closes
    cout << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}