// Week 04 Programming Assignment
// Name: Farris Qureshi
// Description: A wristwatch collection tracker that builds on previous weeks.
//              This version adds a switch-based menu system, compound if/else
//              selection statements, and three loop types: for, while, do-while.
//              The program lets the user log multiple watches in one session
//              and view a running collection summary.

#include <iostream>
#include <string>
#include <iomanip>   // For setw, setprecision, left, right, fixed
#include <fstream>   // For writing the report to a file
#include <limits>    // For numeric_limits (used to clear bad input)

using namespace std;

int main() {

    // --- Collection totals (accumulated across all watches logged this session) ---
    int    watchCount         = 0;     // How many watches the user has logged
    double totalPurchaseValue = 0.0;   // Sum of all purchase prices entered
    double totalEstimatedValue = 0.0;  // Sum of all estimated current values

    // --- Variables for a single watch entry ---
    string brand;
    string model;
    string movementType;
    int    yearPurchased;
    double purchasePrice;
    double annualAppreciationRate;
    int    conditionRating;

    // --- Menu choice and loop control ---
    int  menuChoice;       // Stores what the user picks from the menu
    char addAnother;       // Used in do-while to ask if user wants to keep going

    //  WELCOME BANNER
    cout << "============================================================" << endl;
    cout << "        Welcome to Farris's Wristwatch Collection Log       " << endl;
    cout << "       Track your watches, estimate value, stay informed.   " << endl;
    cout << "============================================================" << endl;
    cout << endl;

    //  DO-WHILE LOOP — Keeps the main menu running until
    //  the user chooses to quit. The menu always shows at
    //  least once before checking the exit condition.
    do {

        // --- Display the main menu ---
        cout << "------------------------------------------------------------" << endl;
        cout << "  MAIN MENU" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "  1. Add a watch to your collection" << endl;
        cout << "  2. View weekly collection report" << endl;
        cout << "  3. Get a recommendation based on your collection" << endl;
        cout << "  4. Quit" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "  Enter your choice (1-4): ";
        cin >> menuChoice;

        // Clear the newline left behind by cin >>
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Validate the menu choice — must be 1, 2, 3, or 4
        if (cin.fail() || menuChoice < 1 || menuChoice > 4) {
            cout << "  [!] Invalid choice. Please enter 1, 2, 3, or 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;   // Skip back to the top of the do-while
        }

        cout << endl;

        //  SWITCH STATEMENT — Routes the user to the correct
        //  section of the program based on their menu choice.
        switch (menuChoice) {

            //  CASE 1: Add a watch entry
            case 1:

                cout << "============================================================" << endl;
                cout << "  ADD A WATCH" << endl;
                cout << "============================================================" << endl;
                cout << endl;

                // Read brand name (can include spaces like "Grand Seiko")
                cout << "  Watch Brand (e.g., Grand Seiko, Rolex, Omega): ";
                getline(cin, brand);

                // Read model name
                cout << "  Model Name  (e.g., Submariner, Snowflake, Speedmaster): ";
                getline(cin, model);

                // Read movement type
                cout << "  Movement Type (e.g., Automatic, Quartz, Manual): ";
                getline(cin, movementType);

                //  WHILE LOOP — Keeps asking for the year until the
                //  user enters a valid value. This is input validation
                //  through repetition rather than a one-shot check.
                cout << "  Year Purchased (1900 - 2026): ";
                cin >> yearPurchased;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Keep looping as long as the input is bad
                while (cin.fail() || yearPurchased < 1900 || yearPurchased > 2026) {
                    cout << "  [!] Please enter a valid year between 1900 and 2026: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> yearPurchased;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // Read and validate purchase price
                cout << "  Purchase Price (USD, e.g., 450.00): $";
                cin >> purchasePrice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (cin.fail() || purchasePrice <= 0) {
                    cout << "  [!] Invalid price. Defaulting to $100.00." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    purchasePrice = 100.00;
                }

                // Read and validate annual appreciation rate
                cout << "  Estimated Annual Appreciation Rate (%, e.g., 3.5): ";
                cin >> annualAppreciationRate;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (cin.fail() || annualAppreciationRate < 0 || annualAppreciationRate > 100) {
                    cout << "  [!] Invalid rate. Defaulting to 3.0%." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    annualAppreciationRate = 3.0;
                }

                // Read and validate condition rating 1-5
                cout << "  Condition Rating (1=Poor, 2=Fair, 3=Good, 4=Very Good, 5=Mint): ";
                cin >> conditionRating;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (cin.fail() || conditionRating < 1 || conditionRating > 5) {
                    cout << "  [!] Invalid rating. Defaulting to 3 (Good)." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    conditionRating = 3;
                }

                {
                    // --- Calculate derived values for this watch ---
                    int currentYear = 2026;
                    int yearsHeld   = currentYear - yearPurchased;

                    // yearsHeld cannot be negative
                    if (yearsHeld < 0) {
                        yearsHeld = 0;
                    }

                    // Base estimated value using linear appreciation:
                    // estimatedValue = price + (price * rate/100 * years)
                    double estimatedValue = purchasePrice
                                         + (purchasePrice * (annualAppreciationRate / 100.0) * yearsHeld);
                    double totalGain = estimatedValue - purchasePrice;

                    // Condition multiplier maps rating 1-5 to a percentage of value
                    double conditionMultiplier = 0.60
                                               + (conditionRating == 2) * 0.15
                                               + (conditionRating == 3) * 0.30
                                               + (conditionRating == 4) * 0.40
                                               + (conditionRating == 5) * 0.50;

                    double conditionAdjustedValue = estimatedValue * conditionMultiplier;

                    // Map numeric rating to a readable label
                    string conditionLabel = "Unknown";
                    conditionLabel = (conditionRating == 1) ? "Poor"      : conditionLabel;
                    conditionLabel = (conditionRating == 2) ? "Fair"      : conditionLabel;
                    conditionLabel = (conditionRating == 3) ? "Good"      : conditionLabel;
                    conditionLabel = (conditionRating == 4) ? "Very Good" : conditionLabel;
                    conditionLabel = (conditionRating == 5) ? "Mint"      : conditionLabel;

                    // --- Update running collection totals ---
                    watchCount++;
                    totalPurchaseValue  += purchasePrice;
                    totalEstimatedValue += estimatedValue;

                    // --- Display formatted entry summary ---
                    cout << endl;
                    cout << "============================================================" << endl;
                    cout << "              WRISTWATCH COLLECTION ENTRY REPORT            " << endl;
                    cout << "============================================================" << endl;

                    cout << left << setw(28) << "  Brand"          << ": " << brand        << endl;
                    cout << left << setw(28) << "  Model"          << ": " << model        << endl;
                    cout << left << setw(28) << "  Movement Type"  << ": " << movementType << endl;
                    cout << left << setw(28) << "  Year Purchased" << ": " << yearPurchased << endl;
                    cout << left << setw(28) << "  Years in Collection"
                                             << ": " << yearsHeld << " year(s)" << endl;
                    cout << left << setw(28) << "  Condition"
                                             << ": " << conditionRating << " / 5  (" << conditionLabel << ")" << endl;

                    cout << "------------------------------------------------------------" << endl;

                    cout << fixed << setprecision(2);
                    cout << left  << setw(28) << "  Purchase Price"
                         << ": $" << right << setw(10) << purchasePrice << endl;
                    cout << left  << setw(28) << "  Annual Appreciation Rate"
                         << ":  " << right << setw(10) << annualAppreciationRate << "%" << endl;
                    cout << left  << setw(28) << "  Base Estimated Value"
                         << ": $" << right << setw(10) << estimatedValue << endl;
                    cout << left  << setw(28) << "  Total Gain"
                         << ": $" << right << setw(10) << totalGain << endl;

                    cout << "------------------------------------------------------------" << endl;

                    cout << left  << setw(28) << "  Condition-Adjusted Value"
                         << ": $" << right << setw(10) << conditionAdjustedValue << endl;

                    cout << "============================================================" << endl;
                    cout << endl;

                    //  IF/ELSE BLOCK 1 — Compound boolean condition
                    //  Checks both condition AND years held to determine
                    //  if this watch is a strong resale candidate.
                    if (conditionRating >= 4 && yearsHeld >= 3) {
                        cout << "  >> Great news! This watch is in excellent condition AND" << endl;
                        cout << "     has been held for " << yearsHeld << " years — a strong resale candidate." << endl;
                    } else if (conditionRating <= 2 && totalGain > 0) {
                        cout << "  >> This watch has gained value, but its condition may" << endl;
                        cout << "     lower the resale price. Consider servicing it." << endl;
                    } else {
                        cout << "  >> Watch logged successfully to your collection." << endl;
                    }

                    cout << endl;

                    // Save this watch entry to report.txt
                    ofstream reportFile("report.txt", ios::app);  // Append mode so all watches are saved

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
                        cout << "  Report appended to report.txt successfully." << endl;
                    } else {
                        cout << "  [!] Could not open report.txt for writing." << endl;
                    }
                }

                cout << endl;
                break;

            //  CASE 2: View weekly collection report
            case 2:

                cout << "============================================================" << endl;
                cout << "              WEEKLY COLLECTION SUMMARY REPORT              " << endl;
                cout << "============================================================" << endl;
                cout << endl;

                // If no watches have been logged yet, say so
                if (watchCount == 0) {
                    cout << "  No watches have been logged this session yet." << endl;
                    cout << "  Use option 1 to add a watch first." << endl;
                } else {

                    double averageValue = totalEstimatedValue / watchCount;
                    double overallGain  = totalEstimatedValue - totalPurchaseValue;

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

                    cout << endl;

                    //  FOR LOOP — Runs a fixed number of times (watchCount)
                    //  to print a visual star rating bar for the session.
                    //  This gives the user a quick visual of how many
                    //  watches they've tracked this session.
                    cout << "  Session Progress: ";
                    for (int i = 0; i < watchCount; i++) {
                        cout << "[Watch " << (i + 1) << "] ";
                    }
                    cout << endl;

                    cout << endl;

                    //  IF/ELSE BLOCK 2 — Compound boolean condition
                    //  Assesses overall collection performance based on
                    //  both the number of watches AND the gain amount.
                    if (watchCount >= 3 && overallGain >= 500.0) {
                        cout << "  >> Impressive collection! You've logged " << watchCount
                             << " watches" << endl;
                        cout << "     with a total estimated gain of $"
                             << fixed << setprecision(2) << overallGain << "." << endl;
                        cout << "     Your collection is growing in both size and value!" << endl;
                    } else if (watchCount >= 1 && overallGain > 0) {
                        cout << "  >> Good progress! Your collection has gained $"
                             << fixed << setprecision(2) << overallGain
                             << " in estimated value." << endl;
                    } else {
                        cout << "  >> Keep adding watches to build your collection!" << endl;
                    }
                }

                cout << endl;
                cout << "============================================================" << endl;
                cout << endl;
                break;

            //  CASE 3: Get a recommendation
            case 3:

                cout << "============================================================" << endl;
                cout << "              COLLECTION RECOMMENDATION ENGINE              " << endl;
                cout << "============================================================" << endl;
                cout << endl;

                if (watchCount == 0) {
                    cout << "  Log at least one watch first (option 1) to get" << endl;
                    cout << "  a recommendation tailored to your collection." << endl;
                } else {
                    double averageValue = totalEstimatedValue / watchCount;

                    cout << fixed << setprecision(2);
                    cout << "  Your average watch value is: $" << averageValue << endl;
                    cout << endl;

                    // Tiered recommendation based on average value
                    if (averageValue >= 5000.0 && watchCount >= 2) {
                        cout << "  >> HIGH-END COLLECTOR: Your collection averages over $5,000" << endl;
                        cout << "     per watch. Consider diversifying with a dress watch" << endl;
                        cout << "     (e.g., A. Lange & Soehne or Patek Philippe)." << endl;
                    } else if (averageValue >= 1000.0 && averageValue < 5000.0) {
                        cout << "  >> MID-RANGE COLLECTOR: Solid range! You might enjoy adding" << endl;
                        cout << "     a Grand Seiko or Tudor to round out your collection." << endl;
                    } else {
                        cout << "  >> ENTRY-LEVEL COLLECTOR: Great start! Explore Seiko or" << endl;
                        cout << "     Orient for reliable, affordable automatic movements." << endl;
                    }
                }

                cout << endl;
                cout << "============================================================" << endl;
                cout << endl;
                break;

            //  CASE 4: Quit — the do-while condition will check this
            case 4:
                cout << "  Thanks for using Farris's Wristwatch Collection Log!" << endl;
                cout << "  Keep watching the market!" << endl;
                cout << endl;
                break;

        } // end switch

    //  DO-WHILE CONDITION — The menu keeps looping as long
    //  as the user's choice is NOT 4 (Quit).
    } while (menuChoice != 4);

    // Pause before the console window closes (useful during debugging)
    cout << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();

    return 0;
}