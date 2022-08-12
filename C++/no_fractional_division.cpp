#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>

/*
Fork of the Divsion Python Problem which aims to create and reverse engineer
the Divsion operator, using other operators. This fork is using C++ as a way
to test my own knowledege of the language.

Rules:
- Allowing usages of the std::libaries to make it equivalent to Python 3.10's
included functionality

- This is a rewriting excerise so I am allowed to copy the already working
algorithm from Python, but does mean flaws are shared.

- Internet is allowed to query things like changes in syntax and best
practices
*/

class Divisor {
//Initalising Public Variables, could alter these to be private and then require public getters and setters for security
public:
  float dividend_Float;
  float divisor_Float;
  float varying_Reciprocal_Float {0.01};
  float indices_10_Int {10};
  float final_Answer_Float;

  //Basic void that just analyses which os using macros and then just cleans the console output
  void clean_Console() {
#if defined _WIN32
    system("cls");
#elif defined(__linux__) || defined(__gnu_linux__) || defined(__LINUX__) ||    \
    defined(__APPLE__)
    system("clear");
#endif
  }

  //Basic input/output function using the <iostream> library
  void input_Data() {
    clean_Console();
    std::cout << "Please input a Dividend as a Float:  ";
    std::cin >> dividend_Float;
    check_Input(dividend_Float);
    std::cout << "Please input a Divisor as a Float: ";
    std::cin >> divisor_Float;
    check_Input(divisor_Float);
  }

  //Basic function to check inputs, if cin failed or is 0 it throws an error as that would cause division to fail
  void check_Input(float input_Float) {
    if (std::cin.fail() || input_Float == 0) {
      //cleans the std::cin buffer to stop that from being reallocated later on     
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "This input was not accepted due to incompatible data"
                << std::endl;
      std::cout << "Would you like to restart the application (Y/N)? : ";
      
      //input output asking if program should restart
      char x;
      std::cin >> x;
      if ((char)std::tolower(x) == 'y') {
        clean_Console();
        input_Data();
      } else {
        exit(EXIT_FAILURE);
      }
    }
  }

  //Main logic function containing the main actual algorithm 
  //TODO --split into multiple smaller functions with test blocks
  void logic() {
    //For every place value that is larger than the decimal point increment the varying_Reciprocal_Float and indices_10_Int by 10 and 0.1
    //This is effectively doing Scientific Notation, and helps to reduce the iteration time as it is easier to increment to 9.32 instead of 932.
    std::string dividend_String(std::to_string(dividend_Float));
    //for loop where it stops when the current char is '.'
    for (int i = 0; dividend_String[i] != '.'; i++) {
      std::cout << dividend_String[i] << std::endl;
      varying_Reciprocal_Float = varying_Reciprocal_Float * 0.1;
      indices_10_Int = indices_10_Int * 10;
    }
    
    //Create the fixed iterator this then is 0.1 of the varying_Reciprocal_Float which is 0.01 by default
    //The reason its incremented again is due to the fact that if the Dividend is a unit then the loop above is skipped
    float fixed_Reciprocal_Float = varying_Reciprocal_Float * 0.1;

    //This then increments the varying_Reciprocal_Float by adding the fixed value until it is greater than 1 - the fixed_Reciprocal_Float
    while (divisor_Float * varying_Reciprocal_Float <
           1 - fixed_Reciprocal_Float) {
      varying_Reciprocal_Float =
          varying_Reciprocal_Float + fixed_Reciprocal_Float;
    }

    //std::cout these values for user interaction
    std::cout << "Reciprocal:  " << varying_Reciprocal_Float << std::endl;
    std::cout << "Fixed Iterative Modifier:  " << fixed_Reciprocal_Float
              << std::endl;
    
    //The reciprocal is always between 0 < x <= 1 getting that value by multiplying it by the values by the indices_10_Int * 100 
    //varying_Reciprocal_Float = varying_Reciprocal_Float * indices_10_Int;
    std::string varying_Reciprocal_String =
        std::to_string(fixed_Reciprocal_Float);


    std::string program_Output_String = "";
    //Skip recursive logic if the original values are equivalent
    if (dividend_Float == divisor_Float) {
      final_Answer_Float = 1;
    } else {
      //if 3 values in the iterative reciprocal are equivalent then  just make the output one 0.x recursive 
      if (varying_Reciprocal_String[1] == varying_Reciprocal_String[2] &&
          varying_Reciprocal_String[1] == varying_Reciprocal_String[3]) {
        std::cout << "Recursive Detected, In the form 0.x" << std::endl;
        program_Output_String = "0.";
        //Just generate a string of this to make it more accurate just increase that range on the for loop
        for (int i = 1; i < 8; i++) {
          program_Output_String =
              program_Output_String + varying_Reciprocal_String[1];
        }
      } else if (varying_Reciprocal_String[1] == varying_Reciprocal_String[2]) {
        //If its a recursive reciprocal in its 1st and 2nd position onwards
        std::cout << "Recursive Detected, In the form 0.1x" << std::endl;
        program_Output_String = "0.1";
        //This would be in the form of 0.1x
        for (int i = 1; i < 8; i++) {
          program_Output_String =
              program_Output_String + varying_Reciprocal_String[1];
        }
      } else {
        //This just takes the varying_Reciprocal_Float and converts it to the output value as its not recursive
        std::cout << "Not Recursive, jumping to multiplication" << std::endl;
        program_Output_String = std::to_string(varying_Reciprocal_Float);
      } 
      //Multiply the reciprocal of the divisor by the original dividend_Float
      final_Answer_Float = stof(program_Output_String) * dividend_Float;
    }
  }
  //Output function to std::cout the equation nicely
  void output() {
    std::cout << dividend_Float << " / " << divisor_Float << " = "
              << std::setprecision(3) << final_Answer_Float << std::endl;
  }
};

int main() {
  //Just run while true with an integrated loop break after each run 
  bool x {true};
  while (x) {
    Divisor divisor;
    divisor.input_Data();
    divisor.logic();
    divisor.output();
    
    std::cout << "Would you like to do another division (Y/N)? :  ";
    char toss;
    std::cin >> toss;
    if ((char)std::tolower(toss) == 'n') {
      x = false;
    }
  }
  return 0;
}
