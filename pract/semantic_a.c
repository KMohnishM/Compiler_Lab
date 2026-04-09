#include <stdio.h>
#include <ctype.h>

char input[100];
int ip = 0;

// This function processes the string recursively
void S() {
    if (isalnum(input[ip])) {
        char c = input[ip]; // Store current char
        ip++;               // Move to next char
        S();                // Recursive call
        printf("%c", c);    // Print after return (reverses the string)
    }
}

int main() {
    printf("Enter a string: ");
    if (scanf("%s", input) == 1) {
        S(); 
        
        if (input[ip] == '\0') {
            printf("\nAccepted\n");
        } else {
            printf("\nError: Unexpected character\n");
        }
    }
    return 0;
}