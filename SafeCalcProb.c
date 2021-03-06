/*
Safe integer calculator - warns if an overflow or
underflow error occurs.

Menu
Negation
Safe unsigned ops
Safe signed ops
Arithmetic without + - * / % ++ or --

Code the functions below and uncomment the code in main()
when completed.

Code the functions in order as they appear. Subsequent
functions depend on previous functions. You cannot use
any math operators (+ - * / % ++ or --) except simple
assignment (=). However, you may use relational and
logical operators.

The _add() function should only use bitwise operators. All
other functions can call functions necessary to complete the
required operation. I added some hints above functions.
*/

#include <stdio.h>
#include <stdlib.h>

// Prototypes

int _add(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int neg(int a);
int mul(int a, int b);
int divide(int a, int b);
int mod(int a, int b);
int power(int a, int b);
int convert(char *input);
void menu();


// Main

int main(int argc, char *argv[]) {

    int res = 0; // Cumulative result - running total

    int n = 0; // For number conversion from input string

    char input[50]; // Input string

    input[0] = '\0'; // Put null in operator char so loop works

    // Write code here to test your functions

    // Uncomment code below when done

    // Loop until quit is selected

    while(input[0] != 'q' && input[0] != 'Q') {

        // Show menu choices

        menu();

        // Print prompt with running total

        printf("\nres = %d > ", res);

        // Get input string

        gets(input);

        // Clear screen

        system("cls");

        // Switch on operator char input[0]

        switch (input[0]) {

            case '+':

                res = add(res, convert(input));
                break;

            case '-':

                res = sub(res, convert(input));
                break;

            case '*':

                res = mul(res, convert(input));
                break;

            case '/':

                res = divide(res, convert(input));
                break;

            case '%':

                res = mod(res, convert(input));
                break;

            case '~':

                res = neg(res);
                break;

            case '^':

                res = power(res, convert(input));
                break;

            case 'c':
            case 'C':

                res = 0;
                break;

            case 'q':
            case 'Q':

                printf("Good-bye!\n");
                break;

            default:

                printf("Enter a valid operator and operand\n");

        }

    }

    return 0;

}

// Show menu choices

void menu() {

    printf("\nSafe Integer Calculator\n");
    printf("+ x to add\n");
    printf("- x to subtract\n");
    printf("* x to multiply\n");
    printf("/ x to divide\n");
    printf("%% x to modulus\n");
    printf("~ x to negate\n");
    printf("^ x to raise by power x\n");
    printf("c x to clear result\n");
    printf("q x to quit\n");
    return;

}


// This function should only use bitwise operators and relational operators


// Add operation using only bitwise operators

int _add(int a, int b) {
  
    // Find carry 1 bits - a AND b assign to carry

    // Find non carry 1 bits - a XOR b assign to a

    // Multiply carry by 2 by shift and assign to b

    while(b != 0) {

        int carry = a & b;
        a = a ^ b;
        b = carry << 1;

    }

    return a;

}

// Safe add() should call _add() and check for both overflow and underflow errors.


// Safe add operation

int add(int a, int b) {

    // Call to _add() a and b and assign to result

    // Check for overflow - look at page 90 in book

    // Check for underflow - look at page 90 in book

    int res = 0;

    res = _add(a, b);

    if(a > 0 && b > 0 && res < 0) {

        printf("Results in an overflow!");

        exit(1);

    }
    if(a < 0 && b < 0 && res > 0) {

        printf("Results in an undeflow!");

        exit(2);

    }

    return res;

}


// Negate a by using a bitwise operator and safe add(). Look on page 95 in book. Replace the zero with an expression that solves this.


// Define negation with ~ and safe add

int neg(int a) {

    // Return negation of a and add 1

    a = add(~a, 1);

    return a; // Replace 0 with code

}


// Remember that subtraction is the same as addition if you negate one of the operands. Replace the zero with an expression that solves this.


// Define safe subtract by safe add - negate b

int sub(int a, int b) {

    int res = add(a, neg(b));

    return res;

}


// Safe mul() uses an iterative call to safe add() to calculate a product. Remember that 5 x 4 = 5 + 5 + 5 + 5 = 20


// Define safe multiply by calling safe add b times

int mul(int a, int b) {

    // Declare and initialize cumulative result

    // Declare sign of product - initially assume positive

    // For efficiency - smaller number should be multiplier

    // Absolute value of a and flip sign

    // Absolute value of b and flip sign

    // Accumulate result

    // Set sign to output


    int res = 0;

    int prod = 0;

    int sign = 1;

    if(a < 0 && b < 0) {

        a = abs(a);

        b = abs(b);

        sign = 1;

    } else if (a < 0 || b < 0) {

        b = abs(b);

        a = abs(a);

        sign = -1;

    } else {

        sign = 1;

    }

    if(a >= b) {

        for(int i = 0; i < b; i = add(i, 1)) {

            prod = add(prod,a);

        }

    } else if(b > a) {

        for(int p = 0; p < a; p = add(p, 1)) {

            prod = add(prod, b);

        }

    }

    if(sign == -1) {

            prod = neg(prod);

    }

    return prod;

}


// Safe div() repeatedly subtracts b from a, counting the number of subtractions until a < b, which it returns.


// Define safe divide by calling safe subtract b times

int divide(int a, int b) {

    // Declare int to count how many times can b be subtracted from a

    // Declare sign

    // Absolute value of a and flip sign

    // Absolute value of b and flip sign

    // loop to calculate how many times can b be subtracted from a

    // Set sign to output

    int cnt = 0;

    int sign = 1;

    if(a < 0 && b < 0) {

        a = abs(a);

        b = abs(b);

        sign = 1;

    }

    if (a < 0) {

        a = abs(a);

        sign = -1;

    }

    if(b < 0) {

        b = abs(b);

        sign = -1;

    }

    if(a == b) {

        return sign;

    }

    while (a >= b) {

        a = sub(a,b);   

        cnt = add(cnt,1);

    }  

    if(sign == -1) {

        cnt = neg(cnt);

    }

    return cnt;

}



// Safe mod() repeatedly subtracts b from a until a < b, returning a.


// Define safe modulus by calling safe subtract

int mod(int a, int b) {

    // Absolute value of a

    // Absolute value of b

    // Find remainder by repeated subtraction a - b

    int sign = 1;

    if(a < 0) {

        a = abs(a);

    }

    if( b < 0) {

        b = abs(b);

    }

    if(a == b) {

        return 0;

    }

    while(a > b) {

        a = sub(a, b);

    }

    return a;

}

/*

Safe pow() calculates as the math pow function but
only uses the safe operations.
res = n^exp
Loop until exp is zero
res = res * n
exp = exp - 1
Remember the special case for n^0

*/

// Define safe pow by calling safe multiply exp times

int power(int n, int exp) {

    // Declare int for result of n^exp

    // Loop and multiply to calculate n^exp
    
    int res = 1;

    while(exp > 0) {

        res = mul(res, n);

        exp = sub(exp, 1);

    }

    if(exp < 0) {

        return 0;

    }

    return res;

}

/*

This function extracts the integer value from the input string.
If input = "+ -123", res = -123.
If input = "* 987654", res = 987654.
The best way to solve complicated problems is to work them out
on paper first.

*/

// Extract the integer from the input string and convert to int

int convert(char *input) {

    // Declare int for result extracted from input

    // Declare int for sign of result

    // Declare two iterators

    // Declare a buffer for numeric chars

    // Set error to zero - no error found yet

    // Check for space in element 1

    // Check for negative integer at element 2

    // Loop to copy all numeric chars to buffer

    // i is iterator for input string and should start at first numeric char

    // j is iterator for buffer where numeric chars are copied

    // This must test for chars between 0 and 9

    // i gets position of last numeric char in buffer

    // j is now used for pow function - start at zero

    // Construct integer from buffer using pow j increases and i decreases

    // Set sign for output

    int res = 0;

    int sign = 1;

    int i = 2;

    int j = 0;
    
    char buffer[50];

    if(input[1] != ' ') {

        printf("Invalid!\n");

        exit(3);

    }

    if(input[2] == '-') {

        sign = neg(sign);

        i = 3;

    }

    while (input[i] != '\0' ) {

        if(input[i] >= '0' && input[i] <= '9') {

            buffer[j] = input[i];

            j = add(j, 1);

            i = add(i, 1);

        }

    }

    buffer[j] = '\0';

    i = sub(j, 1);

    j = 0;

    while(i >= 0) {

        res = add(res, mul(sub(buffer[i], '0'), power(10, j)));

        i = sub(i, 1);

        j = add(j, 1);

    }

    if(sign < 0) {

        res = neg(res);

    }

    return res;

}
