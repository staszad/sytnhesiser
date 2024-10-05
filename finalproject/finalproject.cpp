// finalproject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    std::cout << "Hello World!\a";
    Beep(400, 125);
    Beep(450, 125);
    Beep(500, 125);
    Beep(450, 125);
    Beep(400, 250);
    Beep(381, 250);

    Beep(400, 500);
    Beep(800, 500);
    Beep(600, 500);
    Beep(500, 500);
    Beep(525, 500);
    Beep(450, 500);
    Beep(600, 500);
    Beep(525, 250);
    Beep(450, 250);

    Beep(400, 500);
    Beep(800, 500);
    Beep(600, 500);
    Beep(500, 500);
    Beep(525, 500);
    Beep(450, 500);
    Beep(400, 1000);
    std::cout << "\a";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
