// Week 01 Programming Assignment
// Name: Farris Qureshi
// Description: A wristwatch collection entry program that gathers details
//              about a watch and calculates its estimated resale value.

#include <iostream>
#include <string>

using namespace std;

int main() {

    // --- Declare variables to store watch information ---
    string brand;
    string model;
    string movementType;
    int yearPurchased;
    double purchasePrice;
    double annualAppreciationRate;

    // --- Welcome banner ---
    cout << "=============================================" << endl;
    cout << "      Farris's Wristwatch Collection Log     " << endl;
    cout << "=============================================" << endl;
    cout << endl;
    cout << "Let's log a watch from your collection!" << endl;
    cout << endl;

    // --- Prompt the user for watch details ---
    cout << "Watch Brand (e.g., Seiko, Rolex, Omega): ";
    cin >> brand;

    cout << "Model Name (e.g., Submariner, Speedmaster): ";
    cin >> model;

    cout << "Movement Type (e.g., Automatic, Quartz, Manual): ";
    cin >> movementType;

    cout << "Year Purchased (e.g., 2021): ";
    cin >> yearPurchased;

    cout << "Purchase Price (USD, e.g., 450.00): $";
    cin >> purchasePrice;

    // Ask for the estimated annual appreciation rate for market tracking
    cout << "Estimated Annual Appreciation Rate (%, e.g., 3.5 for 3.5%): ";
    cin >> annualAppreciationRate;

    // --- Calculate estimated current market value ---
    // Formula: estimatedValue = purchasePrice * (1 + rate)^years
    // Since we can't use loops, we use a simplified single-year calculation
    // and multiply by years held manually using basic math
    int currentYear = 2025;
    int yearsHeld = currentYear - yearPurchased;

    // Calculate appreciation multiplier: approximate (1 + r)^n
    // We'll compute this step-by-step without a loop using a known formula
    // For simplicity at this stage: estimatedValue = purchasePrice + (purchasePrice * rate/100 * years)
    double estimatedValue = purchasePrice + (purchasePrice * (annualAppreciationRate / 100.0) * yearsHeld);
    double totalGain = estimatedValue - purchasePrice;

    // --- Display the formatted collection entry summary ---
    cout << endl;
    cout << "=============================================" << endl;
    cout << "           COLLECTION ENTRY SUMMARY          " << endl;
    cout << "=============================================" << endl;
    cout << endl;
    cout << "You've logged your " << brand << " " << model << " — a fine choice!" << endl;
    cout << "Movement Type : " << movementType << endl;
    cout << "Year Purchased: " << yearPurchased << endl;
    cout << "Years in Collection: " << yearsHeld << " year(s)" << endl;
    cout << endl;
    cout << "--- Market Value Estimate ---" << endl;
    cout << "Original Purchase Price : $" << purchasePrice << endl;
    cout << "Annual Appreciation Rate: " << annualAppreciationRate << "%" << endl;
    cout << "Estimated Current Value : $" << estimatedValue << endl;
    cout << "Estimated Total Gain    : $" << totalGain << endl;
    cout << endl;

    // Fun personalized closing message
    cout << "Your " << brand << " " << model << " has been with you for " << yearsHeld
         << " year(s) and is now worth an estimated $" << estimatedValue << "." << endl;
    cout << "Keep watching the market, Farris — that " << movementType
         << " movement only gets better with time!" << endl;
    cout << endl;
    cout << "=============================================" << endl;

    return 0;
}