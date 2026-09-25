#include <iostream>
#include <string>
using namespace std;

int main() 
{
    string colors [3];
    char choice = 'c';

    while (choice == 'c') 
    {

        // Created a lists and ask the user three colors 
        cout << "Choose three colors to compare" << endl;
        cout << "Avilable colors: red, green, blue, yellow" << endl;

        //Compare each color with the other colors
        for (int first = 0; first < 3; first++) 
        {
            cout << "Enter color" << first + 1 << ": ";
            cin >> colors[first];
        }

        // Make a contrast to see  if easy or diffrecult 
        if (colors[0] == "red" &&
            colors[1] == "green" &&
            colors[2] == "blue") {

            cout << "These colors may have limited contrast and could be diffcult to differentiate." << endl;
        }
           
        else if (colors[0] == "blue" &&
                colors[1] == "green" &&
                colors[2] == "red") {

                cout << "These colors have moderate and may be be somewhat diffcult to differentiate." << endl;
        }
        else if (colors[0] == "blue" &&
                colors[1] == "green" &&
                colors[2] == "yellow") {

                cout << "These colors have some contrast but a couple of them can be hard to differentiate." << endl;
        }
        else if (colors[0] == "yellow" &&
                colors[1] == "blue" &&
                colors[2] == "red") {

                cout << "Thses colors provide noticeable contrast and are relatively easy to see." << endl;
        }
        else if (colors[0] == "yellow" &&
                colors[1] == "red" &&
                colors[2] == "blue") {

                cout << "These colors provide strong visual contrast and are easy to tell apart." << endl;
        }  
        
        else {
            cout << "This color combination has not been evaluated yet." << endl;
        }
            cout << endl;
            cout << "Enter c to test another set or q to quit):";
            cin >> choice;

            cout << endl;
    }
   cout << "Program ended." << endl;
            
            
  return 0;
}
        












  

