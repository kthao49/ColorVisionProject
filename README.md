# Replace with your unique project name
Color difference & Brightness analysis
## Description
My program is about examines three colors by looking at their RGB values. It's calculates how bright each other color is and how diffrent the colors
is and how diffrent the colors are from one another to see if they can be easily distinguished. The user enters RGB values to 0-225 colors.
Afterwards they enters three colors to 0-225. It will ask them to choose three vision settings such as,
Regular Vision,Protanopia, and Tritanopia. My program will compares each colors combination by checking its brightness difference of 25 and a minimum RGB differecne of 50 to identify color
combinations that may need improvment. After analyzing the colors, the program provides results showing which combinations pass or fail the requierments.
It also explains potenial problems, why it matters, and ways to improvment the colors. At the end, the program will save the results which called ColorVisionFeedback.txt. 
**version 1.0**
## New in v2.0
Adding new feedback about the problem, why it matter, and improvment 
calculates the brightness colors 
RGB colors difference 
give feedback about the brightness 
ASSESSMENT feedback
## how to run
g++ --std=c++11 *.cpp -o cvp
./cvp

## Developer
Kaylee Thao


## Example
## example input
========== COLOR DIFFERENCE & BRIGHTNESS ANALYSIS ==========

This program compares three colors using their RGB values.
Enter RGB values between 0 and 255.

Enter RGB values for Color 1:

Red (0-255): 
> 20 
Green (0-255): 
> 30
Blue (0-255): 
> 100

Enter RGB values for Color 2:
Red (0-255): 
> 30
Green (0-255): 
> 255
Blue (0-255): 
> 68

Enter RGB values for Color 3:
Red (0-255): 
> 78
Green (0-255): 
> 255
Blue (0-255): 
> 41



## example output
Select a vision mode:
1. Regular Vision
2. Protanopia
3. Tritanopia

Enter your choice: 1

COLOR VISION FEEDBACK

Vision Mode: Regular Vision

Problem:
Even individuals with typical color vision may have difficulty distinguishing between colors that have similar appearances or brightness levels. When two colors have very similar RGB values, they may look almost identical when displayed next to each other. When we are using the colors red, green, and blue.

Why It Matters:
Color contrast is important because it helps people recognize and understand visual information. When colors have similar brightness levels or RGB values, important details in charts, graphs, images, and digital interfaces may become harder to see. For example, text placed over a background with a similar brightness level may be difficult to read. Using colors with enough contrast improves readability, visibility, and the overall clarity of a design.

Suggested Improvement:
Choose colors with noticeable differences in brightness and RGB values to create stronger visual contrast. Consider combining lighter colors with darker colors instead of selecting shades that look almost identical. Check both the RGB distance and brightness difference between selected colors to identify combinations that may need improvement.


========== COLOR COMPARISON RESULTS ==========

====================================
Comparing Color 1 and Color 2
====================================

Color 1 RGB: (20, 30, 100)
Color 2 RGB: (30, 255, 68)

RGB Difference: 227.48
Brightness Difference: 131.42

--- Brightness Analysis ---
Calculated Brightness Difference: 131.42
Minimum Brightness Threshold: 25.00
Result: VALID
Color 2 is brighter than Color 1.
The two colors have a noticeable difference in how light or dark they appear.
For example, a brightness difference of 65 is greater than the minimum requirement of 25.
Black and light gray are examples of colors with a large difference in brightness.

--- RGB Difference Analysis ---
Calculated RGB Distance: 227.48
Minimum RGB: 50.00
Result: VALID
The selected colors have greater numerical separation in their RGB values.
For example, red and blue have a large RGB distance because their red and blue components are very different.
A high RGB distance of 150 passes the minimum requirement of 50.

====================================
Comparing Color 1 and Color 3
====================================

Color 1 RGB: (20, 30, 100)
Color 3 RGB: (78, 255, 41)

RGB Difference: 239.73
Brightness Difference: 142.69

--- Brightness Analysis ---
Calculated Brightness Difference: 142.69
Minimum Brightness Threshold: 25.00
Result: VALID
Color 3 is brighter than Color 1.
The two colors have a noticeable difference in how light or dark they appear.
For example, a brightness difference of 65 is greater than the minimum requirement of 25.
Black and light gray are examples of colors with a large difference in brightness.

--- RGB Difference Analysis ---
Calculated RGB Distance: 239.73
Minimum RGB: 50.00
Result: VALID
The selected colors have greater numerical separation in their RGB values.
For example, red and blue have a large RGB distance because their red and blue components are very different.
A high RGB distance of 150 passes the minimum requirement of 50.

====================================
Comparing Color 2 and Color 3
====================================

Color 2 RGB: (30, 255, 68)
Color 3 RGB: (78, 255, 41)

RGB Difference: 55.07
Brightness Difference: 11.27

--- Brightness Analysis ---
Calculated Brightness Difference: 11.27
Minimum Brightness Threshold: 25.00
Result: INVALID
The colors have similar brightness levels.
This may make the colors harder to distinguish together.
Example of a low value: A brightness difference of 10 is below the minimum requirement of 25.
Example: Black and dark gray have similar brightness levels.
Recommendation: Choose colors with a greater brightness difference.

--- RGB Difference Analysis ---
Calculated RGB Distance: 55.07
Minimum RGB: 50.00
Result: VALID
The selected colors have greater numerical separation in their RGB values.
For example, red and blue have a large RGB distance because their red and blue components are very different.
A high RGB distance of 150 passes the minimum requirement of 50.

===== OVERALL ACCESSIBILITY ASSESSMENT =====

Result: Some selected colors may be difficult to distinguish.

Main Concern:
At least one color pair does not meet the minimum brightness or RGB thresholds.

Suggested Improvements:
1. Use lighter and darker shades to create stronger brightness contrast.
2. Choose colors with more noticeable differences in their RGB values.
3. Add labels, patterns, or symbols so information does not depend on color alone.

Important Note:
These measurements do not fully simulate different types of color vision or guarantee that everyone can distinguish the colors.

Feedback saved to ColorVisionFeedback.txt



