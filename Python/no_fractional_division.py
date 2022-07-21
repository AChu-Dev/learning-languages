# Problem: Create a calculator for dividing two numbers against eachother
# Rules!
# - Must not use the / operator
# - Must not use any external Pip/Conda Libaries like NumPy / Pandas
# - Allowed internal Python Libaries but these are not to be used for core logic
# - Should be accurate
# - Documented well so that it can be reviewed by other devs
# - Use Python OOP structures

#Imports
import os

class Divisor: 
    def __init__(self):
        # Defining core variables that need to be initalised; these are a base value for the multiplier of 10 and the Reciprocal.
        self.varying_Reciprocal_Float = 0.01
        self.indices_10_Int = 10

    def clean_console(self):
        # These are cleaning the console by printing a empty tty
        # If operating system:
        # Microsoft DOS = os.clear, 
        # UNIX = os.cls

        cmd = 'cls'
        if os.name not in ('cls', 'dos'):
            cmd = 'clear'
        os.system(cmd)

    def inputs(self):
        try:
            # Ask the user for the numbers to be calculated.
            # Dividend = Number to be Divided.
            # Divisor = Number that is Divided against.
            self.clean_console()
            self.dividend_Float = float(input('Please Input the Dividend as a Float:    '))
            self.divisor_Float = float(input('Please Input the Divisor as a Float:  '))
            
            if not self.dividend_Float or not self.divisor_Float:
                # Protection - You cannot divide a zero sum in either position but classed as a legal input to a Float Dtype
                print('You tried to break the application by using zero as a dividend or divisor!')
                self.refusal_Argument()
                
        except:
            # Protection - Any non legal input to the Float Dtype
            self.refusal_Argument()

    def refusal_Argument(self): 
        # Asks the user if they want to reboot the input function if they used a erroneous input
        print('This input was not accepted as a Float')
        user_Input_Str = input('Do you want to restart this application?')
        if user_Input_Str.lower() in ['y', 'yes', 'true']:
                self.inputs()
        else:
            quit()

    def logic(self):
        # Get the individual chars that make up the dividend
        self.dividend_Float_chars = list(str(self.dividend_Float))
        for x in range(1, len(self.dividend_Float_chars)):
            # If the char itself is the a decimal place it means that values are less than 0
            if self.dividend_Float_chars[x] == '.':
                break
            else:
                # For every place value is larger than '.' it will reduce the reciprocal to 1/10 per column.
                self.varying_Reciprocal_Float = self.varying_Reciprocal_Float * 0.1
                self.indices_10_Int = self.indices_10_Int * 10
        
        # Multiply the Reciprocal Float by 0.1x, as a Reciprocal will always fall in 0 < x < 1 
        self.fixed_Reciprocal_Float = self.varying_Reciprocal_Float * 0.1
        
        # Iteratively build the Reciprocal of the Divisor by calculating when the 
        # Divisor * varying_Reciprocal_Float is less than 1 - fixed_Reciprocal_Float
        while self.divisor_Float * self.varying_Reciprocal_Float < 1 - self.fixed_Reciprocal_Float:
            self.varying_Reciprocal_Float = self.varying_Reciprocal_Float + self.fixed_Reciprocal_Float

        #Print the Reciprocal and the Fixed Iterative Modifier
        print('Reciprocal:    ', self.varying_Reciprocal_Float)
        print('Fixed Iterative Modifier:  ', self.fixed_Reciprocal_Float)
        
        #Take the Reciprocal and multiply it by the the offset calculated in the first loop and 100, this makes it a number in the form of 0.x
        #Get the Chars for this new float
        self.varying_Reciprocal_float = float(self.varying_Reciprocal_Float * self.indices_10_Int * 100)
        self.varying_Reciprocal_Chars = list(str(self.fixed_Reciprocal_Float))
        
        #initalise a DType String for the outputting chars.
        self.program_Output_String = ""

        #Skip Logic is the divisor and the dividend are equivalent as that would 1 anyway
        if self.dividend_Float == self.divisor_Float:
            self.final_Answer_Float = 1
        
        else:
            try:
                #This is for recurring decimal placed resuts, which just copy the varying_Reciprocal_Float created but only keep the a fixed value like 0.33333333
                #This isolates if it is recursive and then just adds the 3 iteratively
                if self.varying_Reciprocal_Chars[1] == self.varying_Reciprocal_Chars[2] and self.varying_Reciprocal_Chars[1] == self.varying_Reciprocal_Chars[3]:
                    self.program_Output_String = '0.'
                    for x in range(1,8):
                        self.program_Output_String = self.program_Output_String + str(self.varying_Reciprocal_Chars[1])
                        x += 1 
                #Similarly to the upper number but this is for 0.1x recurring decimals in the Reciprocal
                elif self.varying_Reciprocal_Chars[1] == self.varying_Reciprocal_Chars[2]:
                    self.program_Output_String = '0.1'
                    for x in range(1,8):
                        self.program_Output_String = self.program_Output_String + str(self.varying_Reciprocal_Chars[1])
                        x += 1
                else:
                    #If its not a recursive decimal, just inherit the Varying_Reciprocal_Float
                    self.program_Output_String = str(self.varying_Reciprocal_Float)
                
                #Final Answer is the Dividend * Reciprocal
                self.final_Answer_Float = float(self.program_Output_String) * float(self.dividend_Float)

            except Exception as error:
                print('There was an error occuring during the recursive loop:   ', error)

    def output(self):
        #Output in a nice fashion
        #Print to 3 Decimal Places as a rounding measure
        print('{} / {} = {:.3f}'.format(self.dividend_Float, self.divisor_Float, self.final_Answer_Float))


def main():
    #iterative system to keep program running
    statement = True
    while statement:
        divisorBot = Divisor()
        divisorBot.inputs()
        divisorBot.logic()
        divisorBot.output()
        if input('Do you want to try another division?:     ') not in ['y', 'yes', 'true']:
            statement = False

if __name__ == '__main__':
    main()
