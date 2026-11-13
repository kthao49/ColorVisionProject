
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

const int MIN_RGB_VALUE = 0;
const int MAX_RGB_VALUE = 255;

const int REGULAR_VISION = 1;
const int PROTANOPIA_VISION = 2;
const int TRITANOPIA_VISION = 3;

const int SUCCESS_STATUS = 0;
const int ERROR_STATUS = 1;

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
    cout << "========== COLOR DIFFERENCE & BRIGHTNESS ANALYSIS =========="
         << endl;

    cout << "\nThis program compares three colors "
         << "using their RGB values." << endl;

    cout << "Enter RGB values between " << MIN_RGB_VALUE
         << " and " << MAX_RGB_VALUE << "." << endl;

    // Get RGB values for all three colors
    for (int i = 0; i < TOTAL_SELECTED_COLORS; i++)
    {
        getRGBColor(selectedColors[i], i + 1);
    }

    // Ask the user to select a vision mode
    cout << "\nSelect a vision mode:" << endl;
    cout << REGULAR_VISION << ". Regular Vision" << endl;
    cout << PROTANOPIA_VISION << ". Protanopia" << endl;
    cout << TRITANOPIA_VISION << ". Tritanopia" << endl;

    cout << "\nEnter your choice: ";

    // Validate the vision mode selection
    while (!(cin >> visionChoice) ||
           visionChoice < REGULAR_VISION ||
           visionChoice > TRITANOPIA_VISION)
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
        return ERROR_STATUS;
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

    return SUCCESS_STATUS;
}


// Get RGB values from the user
void getRGBColor(Color &color, int colorNumber)
{
    string colorNames[TOTAL_RGB_VALUES] =
    {
        "Red", "Green", "Blue"
    };

    cout << "\nEnter RGB values for Color "
         << colorNumber << ":" << endl;

    for (int i = 0; i < TOTAL_RGB_VALUES; i++)
    {
        cout << colorNames[i] << " ("
             << MIN_RGB_VALUE << "-"
             << MAX_RGB_VALUE << "): ";

        while (!(cin >> color.rgb[i]) ||
               color.rgb[i] < MIN_RGB_VALUE ||
               color.rgb[i] > MAX_RGB_VALUE)
        {
            cout << "Invalid input. Enter a value "
                 << "between " << MIN_RGB_VALUE
                 << " and " << MAX_RGB_VALUE << ": ";

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
    if (choice == REGULAR_VISION)
    {
      mode = "Regular Vision";

problem =
    "Even individuals with typical color vision may "
    "have difficulty distinguishing between colors "
    "that have similar appearances or brightness "
    "levels. When two colors have very similar RGB "
    "values, they may look almost identical when "
    "displayed next to each other. When we are using"
    " the colors red, green, and blue.";

whyItMatters =
    "Color contrast is important because it helps "
    "people recognize and understand visual information. "
    "When colors have similar brightness levels or "
    "RGB values, important details in charts, graphs, "
    "images, and digital interfaces may become harder "
    "to see. For example, text placed over a background "
    "with a similar brightness level may be difficult "
    "to read. Using colors with enough contrast improves "
    "readability, visibility, and the overall clarity "
    "of a design.";

suggestion =
    "Choose colors with noticeable differences in "
    "brightness and RGB values to create stronger "
    "visual contrast. Consider combining lighter "
    "colors with darker colors instead of selecting "
    "shades that look almost identical. Check both "
    "the RGB distance and brightness difference "
    "between selected colors to identify combinations "
    "that may need improvement.";
}
    else if (choice == PROTANOPIA_VISION)
    {
        mode = "Protanopia";

problem =
    "Individuals with protanopia may have difficulty "
    "distinguishing between red and green colors because "
    "their perception of red light is affected. Certain "
    "red, green, and brown shades may appear similar or "
    "be difficult to tell apart. For example, dark red "
    "and dark green colors may be harder to distinguish "
    "when they are placed next to each other.";

whyItMatters =
    "Protanopia can affect how easily individuals "
    "understand visual information that depends on red "
    "and green color differences. When these colors are "
    "used without enough contrast, important details "
    "may be overlooked or misunderstood. For example, "
    "a person may have difficulty identifying different "
    "categories in a graph or recognizing information "
    "that is communicated using red and green. This "
    "can make certain designs less accessible and "
    "more difficult to understand.";

suggestion =
    "Use colors with noticeably different brightness "
    "levels to create stronger visual separation. Avoid "
    "using red and green as the only way to communicate "
    "important information. Consider using dark blue, "
    "light orange, or other contrasting colors as "
    "alternatives when appropriate. Add text labels, "
    "patterns, borders, and symbols to help distinguish "
    "between different categories. These additional "
    "visual indicators allow people to understand the "
    "information without depending entirely on color.";
    }
    else
    {
        mode = "Tritanopia";

problem =
    "Individuals with tritanopia may have difficulty "
    "distinguishing between blue and yellow colors. "
    "Colors such as light blue, dark blue, yellow, and "
    "green may appear different from how they normally "
    "look to individuals with typical color vision. "
    "When these colors are placed next to each other, "
    "they may be harder to identify or tell apart. ";

whyItMatters =
    "Tritanopia affects the way individuals perceive "
    "blue and yellow color differences. When a design "
    "uses these colors without enough contrast, important "
    "information may become difficult to understand. "
    "For example, someone may have trouble identifying "
    "different sections of a graph or recognizing "
    "important information displayed using blue and "
    "yellow. This can reduce the readability and "
    "accessibility of the design.";

suggestion =
    "Choose colors that have noticeably different "
    "brightness levels and RGB values to create stronger "
    "visual separation. Avoid using blue and yellow as "
    "the only way to communicate important information. "
    "Consider using darker blue shades with lighter "
    "orange or other contrasting colors when appropriate. ";
    }
}


// Display and save general feedback
void writeFeedback(ostream &output,
                   const string &mode,
                   const string &problem,
                   const string &whyItMatters,
                   const string &suggestion)
{
    output << "\nCOLOR VISION FEEDBACK" << endl;

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

    output << "Calculated Brightness Difference: "
           << brightnessDifference << endl;

    output << "Minimum Brightness Threshold: "
           << MIN_BRIGHTNESS_DIFFERENCE << endl;

    if (brightnessDifference < MIN_BRIGHTNESS_DIFFERENCE)
    {
        output << "Result: INVALID" << endl;

        output << "The colors have similar brightness levels."
               << endl;

        output << "This may make the colors harder to "
               << "distinguish together." << endl;

        output << "Example of a low value: A brightness "
               << "difference of 10 is below the minimum "
               << "requirement of 25." << endl;

        output << "Example: Black and dark gray have "
               << "similar brightness levels." << endl;

        output << "Recommendation: Choose colors with a "
               << "greater brightness difference." << endl;
    }
    else
    {
        output << "Result: VALID" << endl;

        if (firstBrightness > secondBrightness)
        {
            output << "Color " << firstNumber
                   << " is brighter than Color "
                   << secondNumber << "." << endl;
        }
        else if (secondBrightness > firstBrightness)
        {
            output << "Color " << secondNumber
                   << " is brighter than Color "
                   << firstNumber << "." << endl;
        }

        output << "The two colors have a noticeable difference "
               << "in how light or dark they appear." << endl;

        output << "For example, a brightness difference of 65 "
               << "is greater than the minimum requirement of 25."
               << endl;

        output << "Black and light gray are examples of colors "
               << "with a large difference in brightness."
               << endl;
    }

    // Analyze RGB distance
    output << "\n--- RGB Difference Analysis ---" << endl;

    output << "Calculated RGB Distance: "
           << rgbDifference << endl;

    output << "Minimum RGB: "
           << MIN_RGB_DIFFERENCE << endl;

    if (rgbDifference < MIN_RGB_DIFFERENCE)
    {
        output << "Result: INVALID" << endl;

        output << "The selected colors have very little "
               << "numerical separation in their RGB values."
               << endl;

        output << "For example, two similar shades of red "
               << "may have RGB values that are close together."
               << endl;

        output << "A low RGB distance of 20 does not meet "
               << "the minimum requirement of 50." << endl;

        output << "Recommendation: Try selecting colors "
               << "with greater differences in their red, "
               << "green, or blue components." << endl;
    }
    else
    {
        output << "Result: VALID" << endl;

        output << "The selected colors have greater "
               << "numerical separation in their RGB values."
               << endl;

        output << "For example, red and blue have a large "
               << "RGB distance because their red and blue "
               << "components are very different." << endl;

        output << "A high RGB distance of 150 passes "
               << "the minimum requirement of 50." << endl;
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
               << "the minimum brightness or RGB thresholds."
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
               << "brightness and more colors of RGB." << endl;

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