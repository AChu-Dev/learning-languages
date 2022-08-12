#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <stdlib.h>

class Divisor
{
  public:
    float dividend_Float;
    float divisor_Float;
    float varying_Reciprocal_Float = 0.01;
    float indices_10_Int = 10;
    float final_Answer_Float;
 
    void clean_Console()
    {
      #if defined _WIN32 
      system("cls");
      #elif defined(__linux__) || defined(__gnu_linux__) || defined(__LINUX__) || defined(__APPLE__)
      system("clear");
      #endif
    }
    
    void input_Data()
    {
      clean_Console();
      std::cout << "Please input a Dividend as a Float:  ";
      std::cin >> dividend_Float;
      check_Input(dividend_Float);
      std::cout << "Please input a Divisor as a Float: ";
      std::cin >> divisor_Float;
      check_Input(divisor_Float);
    }

    void check_Input(float input_Float)
    {
      if(std::cin.fail() || input_Float == 0) 
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "This input was not accepted due to incompatible data" << std::endl;
        std::cout << "Would you like to restart the application (Y/N)? : ";
        
        char x;
        std::cin >> x;
        if((char) std::tolower(x) == 'y'){
          clean_Console();
          input_Data();
        }
        else
        {
          exit(EXIT_FAILURE);
        }
      }
    }
    
    void logic()
    {
      std::string dividend_String(std::to_string(dividend_Float));
      for(int i = 0; dividend_String[i] != '.' ; i++)
      {
        varying_Reciprocal_Float = varying_Reciprocal_Float * 0.1;
        indices_10_Int = indices_10_Int * 10;
      }

      float fixed_Reciprocal_Float = varying_Reciprocal_Float * 0.1;
      
      while(divisor_Float * varying_Reciprocal_Float < 1 - fixed_Reciprocal_Float)
      {
        varying_Reciprocal_Float = varying_Reciprocal_Float + fixed_Reciprocal_Float;
      }
      
      std::cout << "Reciprocal:  " << varying_Reciprocal_Float << std::endl;
      std::cout << "Fixed Iterative Modifier:  " << fixed_Reciprocal_Float << std::endl;

      varying_Reciprocal_Float = varying_Reciprocal_Float * indices_10_Int * 100;
      std::string varying_Reciprocal_String = std::to_string(fixed_Reciprocal_Float);

      std::string program_Output_String = "";
             
      if(dividend_Float == divisor_Float)
      {
       final_Answer_Float = 1; 
      }
      else
      {
        if(varying_Reciprocal_String[1] == varying_Reciprocal_String[2] && varying_Reciprocal_String[1] == varying_Reciprocal_String[3])
        {
          std::cout << "Recursive Detected, In the form 0.x" << std::endl;
          program_Output_String = "0.";
          for(int i = 1; i < 8; i++)
          {
            program_Output_String = program_Output_String + varying_Reciprocal_String[1];
          }
        }
        else if(varying_Reciprocal_String[1] == varying_Reciprocal_String[2])
        {
          std::cout << "Recursive Detected, In the form 0.1x" << std::endl;
          program_Output_String = "0.1";
          for(int i = 1; i < 8; i++)
          {
            program_Output_String = program_Output_String + varying_Reciprocal_String[1];
          }
        }
        else 
        {
          std::cout << "Not Recursive, jumping to multiplication" << std::endl;
          program_Output_String = std::to_string(varying_Reciprocal_Float);
        }
        std::cout << program_Output_String << std::endl;
        final_Answer_Float = stof(program_Output_String) * dividend_Float;
      }
    }
    void output()
    {
      std::cout << dividend_Float << " / " << divisor_Float << " = " << std::setprecision(3) << final_Answer_Float << std::endl;
    }

};

int main() 
{
  bool x = true;
  while(x)
  {
  Divisor divisor;
  divisor.input_Data();
  divisor.logic();
  divisor.output();

  char x;
  std::cin >> x;
  if((char) std::tolower(x) == 'n')
  {
    x = false;
  }
  }
  return 0;
}
