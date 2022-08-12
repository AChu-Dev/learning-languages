#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
using namespace std;

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
      cout << "Please input a Dividend as a Float:  ";
      cin >> dividend_Float;
      check_Input();
      cout << "Please input a Divisor as a Float: ";
      cin >> divisor_Float;
      check_Input();
    }

    void check_Input()
    {
      if(cin.fail()) 
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "This input was not accepted due to incompatible data" << endl;
        clean_Console();
        input_Data();
      }
    }
    
    void logic()
    {
      string dividend_String(to_string(dividend_Float));
      for(int i = 1; dividend_String[i] == '.' ; i++)
      {
          varying_Reciprocal_Float = varying_Reciprocal_Float * 0.1;
          indices_10_Int = indices_10_Int * 10;
      }
      float fixed_Reciprocal_Float = varying_Reciprocal_Float * 0.1;
      
      while(divisor_Float * varying_Reciprocal_Float < 1 - fixed_Reciprocal_Float)
      {
        varying_Reciprocal_Float = varying_Reciprocal_Float + fixed_Reciprocal_Float;
      }
      
      cout << "Reciprocal:  " << varying_Reciprocal_Float << endl;
      cout << "Fixed Iterative Modifier:  " << indices_10_Int << endl;

      varying_Reciprocal_Float = varying_Reciprocal_Float * indices_10_Int * 100;
      string varying_Reciprocal_String = to_string(fixed_Reciprocal_Float);

      string program_Output_String = "";
             
      if(dividend_Float == divisor_Float)
      {
       final_Answer_Float = 1; 
      }
      else
      {
        if(varying_Reciprocal_String[1] == varying_Reciprocal_String[2] && varying_Reciprocal_String[1] == varying_Reciprocal_String[3])
        {
          cout << 1 << endl;
          program_Output_String = "0.";
          for(int i = 1; i < 8; i++)
          {
            program_Output_String = program_Output_String + varying_Reciprocal_String[1];
          }
        }
        else if(varying_Reciprocal_String[1] == varying_Reciprocal_String[2])
        {
          cout << 2 << endl;
          program_Output_String = "0.1";
          for(int i = 1; i < 8; i++)
          {
            program_Output_String = program_Output_String + varying_Reciprocal_String[1];
          }
        }
        else 
        {
          cout << 3 << endl;
          cout << varying_Reciprocal_Float << endl;
          program_Output_String = varying_Reciprocal_String;
        }
        cout << stof(program_Output_String) << endl;
        final_Answer_Float = stof(program_Output_String) * dividend_Float;
      }
    }
    void output()
    {
      cout << dividend_Float << " / " << divisor_Float << " = " << setprecision(3) << final_Answer_Float << endl;
    }

};

int main() 
{
  Divisor divisor;
  divisor.input_Data();
  divisor.logic();
  divisor.output();

  return 0;
}
