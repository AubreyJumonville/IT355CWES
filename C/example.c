// CWE-495: Private Data structure returned from Public Method 
// CWE-676: Use of potentially dangerous function 
// CWE-123: Write-what-where Condition 
// CWE-134: Use of Externally-Controlled Format String 
// CWE-462: Duplicate Key in Associative List (Alist) 
// CWE-466: Return of Pointer Value Outside of Expected Range 

#include <stdio.h>
#include <string.h> // Include the string.h header for strlen()

void functionWith1Argment(char a){
    printf("You have selected task %c", a);
}

int main() {
    char input[10]; // Declare a character array with a size limit of 10 characters to prevent buffer overflow
    // CWE-457: Use of Uninitialized Variables 
    printf("Enter a character to determine which task to perform: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        /*
        In this section of code, the sizeof operator is being used on an array (input) 
        rather than a pointer type, so it is being used correctly. fgets() requires 
        the size of the buffer it is reading into as its second argument, and sizeof(input) 
        provides the size of the input array in bytes, which is the correct size to pass to fgets().

        CWE-467 applies when sizeof() is used on a pointer type, as the size returned by sizeof() 
        in that case is the size of the pointer, not the size of the pointed-to object. This can 
        lead to buffer overflows or other memory-related errors. However, in the above code, sizeof()
        is being used on an array, not a pointer type, so this CWE does not apply.
        */
        printf("Error reading input\n");
        return 1;
    }
    input[strcspn(input, "\n")] = '\0'; //Use strcspn() to find the length of the 
    //input string and ensure that it is less than the size of the input buffer.
    //This will prevent switch() from accessing elements of the input array that are beyond the end of the string.()
    //CWE-125 (Out-of-bounds read) and CWE-787 (Out-of-bounds write) 
    /*
    This helps prevent CWE-126 (Buffer Over-read) and CWE-131 (Incorrect Calculation of 
    Buffer Size) by placing a terminator and by dynamically checking size with size of.
    This helps prevent CWE-170 (Improper Null Termination) by ensuring that the 
    input is properly null-terminated.
    NULL termination also helps with 
    */
    if (strlen(input) != 1) { // Check if the input is more than one character long
    /*
     If it's more than one character long, an error message is displayed and the program returns with an error code of 1. 
     This helps prevent CWE-127 (Buffer Under-read) by ensuring that only one character is read from the input.
    */
        printf("Invalid input\n");
        return 1;
    }

    char task = input[0];
    /*
    This avoids direct manipulation of the input buffer and prevents CWE-468 by ensuring that 
    pointer arithmetic is not used to reduce the size of the input buffer.

    Note that strncpy() could also be used instead of char task = input[0]; to copy the 
    first character of input to task with a buffer size limit of 1, but since we only need 
    to copy one character, using char task = input[0]; is simpler and less error-prone.

    by specifying input[0] CWE-197: Numeric Truncation Error can be avoided.
    */

    functionWith1Argument(task);
    /*
        input is reduced to task to insure CWE-685: "Function call with incorrect number of arguments"
        is avoided for the above function. CWE-688: "Function Call With Incorrect Variable or Reference
        as Argument" is also avoided through the input validation.
    */

    switch (task) { // Check the first character of the input array
        case 'a':
            printf("Performing Task A\n");
                //divide 2 numbers
                int a = 3;
                int b = 7;
                printf("%d / %d = %f", a, b, (double)a/b );
                /*
                    CWE-480: Use of Incorrect Operator
                    CWE-704: Incorrect Type Conversion or Cast 
                    Be careful to ensure that the actual conversion/cast
                    you are trying to do is possible given the relationship 
                    conditions. This will generally cause a syntax error in the development
                    environment but when working outside of development you should always be 
                    cautious. A cast may sometimes be possible without a syntax error but on 
                    object creation an exception will occur.  
                */
                
            break;// CWE-484: Omitted Break Statement in Switch 
        case 'b':
            printf("Performing Task B\n");
            // Code to perform Task B goes here
            break;// CWE-484: Omitted Break Statement in Switch 
        case 'c':
            printf("Performing Task C\n");
            // Code to perform Task C goes here
            break;// CWE-484: Omitted Break Statement in Switch 
        default:
            printf("Invalid input\n");
            return 1;
    }

    free(input);//
    /*
    by placing free after all uses the below CWEs can be prevented
    */
    // CWE-401: Missing Release of Memory after Effective Lifetime 
    // CWE-415: Double Free 
    // CWE-416: Use After Free 

    return 0;
}