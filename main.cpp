
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// Constants
const int TOTAL_SELECTED_COLORS = 3;
const int TOTAL_RGB_VALUES = 3;

const double MIN_BRIGHTNESS_DIFFERENCE = 25.0;
const double MIN_RGB_DIFFERENCE = 50.0;

// Store RGB values for each selected color
struct Color
{
    int rgb[TOTAL_RGB_VALUES];
};

// Function prototypes
void getRGBColor(Color &color, int colorNumber);

double calculateBrightness(const Color &color);

double calculateRGBDifference(const Color &firstColor,
                              const Color &secondColor);

bool needsColorImprovement(const Color &firstColor,
                           const Color &secondColor);

void analyzeColors(int choice,
                   string &mode,
                   string &problem,
                   string &whyItMatters,
                   string &suggestion);

void writeFeedback(ostream &output,
                   const string &mode,
                   const string &problem,
                   const string &whyItMatters,
                   const string &suggestion);

void writeComparison(ostream &output,
                     const Color &firstColor,
                     const Color &secondColor,
                     int firstNumber,
                     int secondNumber);

void compareColors(const Color &firstColor,
                   const Color &secondColor,
                   int firstNumber,
                   int secondNumber,
                   ofstream &outFile);

void writeOverallAccessibility(ostream &output,
                               const vector<Color> &colors);


// Get RGB values from the user
void getRGBColor(Color &color, int colorNumber)
{
    cout << "\nEnter RGB values for Color "
         << colorNumber << ":" << endl;

    string colorNames[TOTAL_RGB_VALUES] =
    {
        "Red", "Green", "Blue"
    };

    for (int i = 0; i < TOTAL_RGB_VALUES; i++)
    {
        cout << colorNames[i] << " (0-255): ";

        while (!(cin >> color.rgb[i]) ||
               color.rgb[i] < 0 ||
               color.rgb[i] > 255)
        {
            cout << "Invalid input. Enter a value "
                 << "between 0 and 255: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


// Calculate brightness using RGB values
double calculateBrightness(const Color &color)
{
    return (0.299 * color.rgb[0]) +
           (0.587 * color.rgb[1]) +
           (0.114 * color.rgb[2]);
}


// Calculate the numerical distance between two RGB colors
double calculateRGBDifference(const Color &firstColor,
                              const Color &secondColor)
{
    double redDifference =
        firstColor.rgb[0] - secondColor.rgb[0];

    double greenDifference =
        firstColor.rgb[1] - secondColor.rgb[1];

    double blueDifference =
        firstColor.rgb[2] - secondColor.rgb[2];

    return sqrt(
        (redDifference * redDifference) +
        (greenDifference * greenDifference) +
        (blueDifference * blueDifference)
    );
}


// Check whether a color pair needs improvement
bool needsColorImprovement(const Color &firstColor,
                           const Color &secondColor)
{
    double brightnessDifference =
        fabs(calculateBrightness(firstColor) -
             calculateBrightness(secondColor));

    double rgbDifference =
        calculateRGBDifference(firstColor, secondColor);

    return (brightnessDifference < MIN_BRIGHTNESS_DIFFERENCE ||
            rgbDifference < MIN_RGB_DIFFERENCE);
}


// Analyze the selected vision mode
void analyzeColors(int choice,
                   string &mode,
                   string &problem,
                   string &whyItMatters,
                   string &suggestion)
{
    if (choice == 1)
    {
        mode = "Regular Vision";

        problem =
            "The selected colors may look too similar when "
            "displayed next to each other. Differences in "
            "brightness can make certain colors harder "
            "to identify.";

        whyItMatters =
            "When colors have similar brightness or appearance, "
            "important details in images, charts, and graphs "
            "may become difficult to recognize. Good color "
            "contrast helps make information easier to read.";

        suggestion =
            "Try selecting colors with noticeable differences "
            "in brightness and RGB values. Use lighter and "
            "darker shades to separate important information. "
            "Consider adding labels or borders to make each "
            "color easier to identify.";
    }
    else if (choice == 2)
    {
        mode = "Protanopia";

        problem =
            "Red and green color combinations may be difficult "
            "to distinguish for individuals with protanopia. "
            "Some brown and red shades may also appear similar.";

        whyItMatters =
            "Color differences are important when presenting "
            "visual information. Without enough contrast, "
            "people with protanopia may struggle to identify "
            "certain details.";

        suggestion =
            "Consider using colors with different brightness "
            "levels and avoiding red and green as the only "
            "way to communicate important information. "
            "Add labels, patterns, or symbols.";
    }
    else
    {
        mode = "Tritanopia";

        problem =
            "Blue and yellow color combinations may be difficult "
            "to distinguish for individuals with tritanopia. "
            "Some shades may appear more similar than expected.";

        whyItMatters =
            "Tritanopia affects the perception of blue and "
            "yellow color differences. This may affect how "
            "easily people understand visual information.";

        suggestion =
            "Use colors with different brightness levels "
            "and stronger visual separation. Avoid depending "
            "only on blue and yellow to communicate important "
            "information. Add text descriptions and visual "
            "indicators.";
    }
}


// Display and save general feedback
void writeFeedback(ostream &output,
                   const string &mode,
                   const string &problem,
                   const string &whyItMatters,
                   const string &suggestion)
{
    output << "\n========== COLOR VISION FEEDBACK =========="
           << endl;

    output << "\nVision Mode: " << mode << endl;

    output << "\nProblem:\n"
           << problem << endl;

    output << "\nWhy It Matters:\n"
           << whyItMatters << endl;

    output << "\nSuggested Improvement:\n"
           << suggestion << endl;
}


// Display the comparison results
void writeComparison(ostream &output,
                     const Color &firstColor,
                     const Color &secondColor,
                     int firstNumber,
                     int secondNumber)
{
    double rgbDifference =
        calculateRGBDifference(firstColor, secondColor);

    double firstBrightness =
        calculateBrightness(firstColor);

    double secondBrightness =
        calculateBrightness(secondColor);

    double brightnessDifference =
        fabs(firstBrightness - secondBrightness);

    output << "\n====================================" << endl;

    output << "Comparing Color " << firstNumber
           << " and Color " << secondNumber << endl;

    output << "====================================" << endl;

    output << fixed << setprecision(2);

    // Display RGB values
    output << "\nColor " << firstNumber << " RGB: ("
           << firstColor.rgb[0] << ", "
           << firstColor.rgb[1] << ", "
           << firstColor.rgb[2] << ")" << endl;

    output << "Color " << secondNumber << " RGB: ("
           << secondColor.rgb[0] << ", "
           << secondColor.rgb[1] << ", "
           << secondColor.rgb[2] << ")" << endl;

    // Display calculated differences
    output << "\nRGB Difference: "
           << rgbDifference << endl;

    output << "Brightness Difference: "
           << brightnessDifference << endl;

    // Analyze brightness differences
    output << "\n--- Brightness Analysis ---" << endl;

    if (brightnessDifference < MIN_BRIGHTNESS_DIFFERENCE)
    {
        output << "The colors have similar brightness levels."
               << endl;

        output << "This may make the colors harder to "
               << "distinguish when displayed together."
               << endl;

        output << "Recommendation: Choose colors with a "
               << "greater brightness difference."
               << endl;
    }
    else if (firstBrightness > secondBrightness)
    {
        output << "Color " << firstNumber
               << " is brighter than Color " << secondNumber
               << "." << endl;

        output << "The brightness difference meets your "
               << "selected threshold." << endl;
    }
    else
    {
        output << "Color " << secondNumber
               << " is brighter than Color " << firstNumber
               << "." << endl;

        output << "The brightness difference meets your "
               << "selected threshold." << endl;
    }

    // Analyze RGB distance
    output << "\n--- RGB Difference Analysis ---" << endl;

    if (rgbDifference < MIN_RGB_DIFFERENCE)
    {
        output << "The RGB distance is below the minimum "
               << "threshold of " << MIN_RGB_DIFFERENCE
               << "." << endl;

        output << "The colors have limited numerical "
               << "separation in their RGB values."
               << endl;

        output << "Recommendation: Select colors with "
               << "more variation in their red, green, "
               << "and blue values." << endl;
    }
    else
    {
        output << "The RGB distance meets or exceeds "
               << "the minimum threshold." << endl;

        output << "The colors have greater numerical "
               << "separation in their RGB values."
               << endl;
    }
}


// Display comparisons on the screen and save them to the file
void compareColors(const Color &firstColor,
                   const Color &secondColor,
                   int firstNumber,
                   int secondNumber,
                   ofstream &outFile)
{
    // Display comparison on the screen
    writeComparison(cout, firstColor, secondColor,
                    firstNumber, secondNumber);

    // Save comparison to the output file
    writeComparison(outFile, firstColor, secondColor,
                    firstNumber, secondNumber);
}


// Overall accessibility assessment
void writeOverallAccessibility(ostream &output,
                               const vector<Color> &colors)
{
    bool needsImprovement = false;

    // Check all three pairs of colors
    for (int i = 0; i < TOTAL_SELECTED_COLORS; i++)
    {
        for (int j = i + 1; j < TOTAL_SELECTED_COLORS; j++)
        {
            if (needsColorImprovement(colors[i], colors[j]))
            {
                needsImprovement = true;
            }
        }
    }

    output << "\n===== OVERALL ACCESSIBILITY ASSESSMENT ====="
           << endl;

    if (needsImprovement)
    {
        output << "\nResult: Some selected colors may be "
               << "difficult to distinguish." << endl;

        output << "\nMain Concern:" << endl;

        output << "At least one color pair does not meet "
               << "the selected brightness or RGB thresholds."
               << endl;

        output << "\nSuggested Improvements:" << endl;

        output << "1. Use lighter and darker shades to create "
               << "stronger brightness contrast." << endl;

        output << "2. Choose colors with more noticeable "
               << "differences in their RGB values." << endl;

        output << "3. Add labels, patterns, or symbols so "
               << "information does not depend on color alone."
               << endl;
    }
    else
    {
        output << "\nResult: All three color combinations "
               << "passed the selected numerical checks."
               << endl;

        output << "\nAccessibility Notes:" << endl;

        output << "The selected colors meet your program's "
               << "brightness and RGB thresholds." << endl;

        output << "Continue using text labels, patterns, "
               << "and symbols to support color identification."
               << endl;
    }

    output << "\nImportant Note:" << endl;

    output << "These measurements do not fully simulate "
           << "different types of color vision or guarantee "
           << "that everyone can distinguish the colors."
           << endl;
}


// Main function
int main()
{
    // Create a vector to store the three selected colors
    vector<Color> selectedColors(TOTAL_SELECTED_COLORS);

    int visionChoice;

    string mode;
    string problem;
    string whyItMatters;
    string suggestion;

    // Display program title and instructions
    cout << "========== COLOR VISION CHECKER =========="
         << endl;

    cout << "\nThis program compares three colors "
         << "using their RGB values." << endl;

    cout << "Enter RGB values between 0 and 255."
         << endl;

    // Get RGB values for all three colors
    for (int i = 0; i < TOTAL_SELECTED_COLORS; i++)
    {
        getRGBColor(selectedColors[i], i + 1);
    }

    // Ask the user to select a vision mode
    cout << "\nSelect a vision mode:" << endl;
    cout << "1. Regular Vision" << endl;
    cout << "2. Protanopia" << endl;
    cout << "3. Tritanopia" << endl;

    cout << "\nEnter your choice: ";

    // Validate the vision mode selection
    while (!(cin >> visionChoice) ||
           visionChoice < 1 ||
           visionChoice > 3)
    {
        cout << "Invalid choice. Enter 1, 2, or 3: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Open output file
    ofstream outFile("ColorVisionFeedback.txt");

    if (!outFile)
    {
        cout << "Error opening feedback file." << endl;
        return 1;
    }

    // Analyze the selected vision mode
    analyzeColors(visionChoice, mode, problem,
                  whyItMatters, suggestion);

    // Display general feedback on the screen
    writeFeedback(cout, mode, problem,
                  whyItMatters, suggestion);

    // Save general feedback to the output file
    writeFeedback(outFile, mode, problem,
                  whyItMatters, suggestion);

    // Compare all three pairs of colors
    cout << "\n\n========== COLOR COMPARISON RESULTS =========="
         << endl;

    outFile << "\n\n========== COLOR COMPARISON RESULTS =========="
            << endl;

    for (int i = 0; i < TOTAL_SELECTED_COLORS; i++)
    {
        for (int j = i + 1; j < TOTAL_SELECTED_COLORS; j++)
        {
            compareColors(selectedColors[i],
                          selectedColors[j],
                          i + 1, j + 1, outFile);
        }
    }

    // Display overall assessment on the screen
    writeOverallAccessibility(cout, selectedColors);

    // Save overall assessment to the output file
    writeOverallAccessibility(outFile, selectedColors);

    // Close the output file
    outFile.close();

    cout << "\nFeedback saved to ColorVisionFeedback.txt"
         << endl;

    return 0;
}