#include <stdio.h>
#include <math.h>

void print_menu() {
    printf("\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Power\n6. Quit\nChoose: ");
}

int main() {
    char again = 'y';
    while (again == 'y' || again == 'Y') {
        print_menu();
        int choice;
        scanf("%d", &choice);
        
        if (choice == 6) {
            printf("Bye!\n");
            break;
        }
        
        double a, b;
        printf("First number: ");
        scanf("%lf", &a);
        printf("Second number: ");
        scanf("%lf", &b);
        
        if (choice == 1) printf("Result: %.2f\n", a + b);
        else if (choice == 2) printf("Result: %.2f\n", a - b);
        else if (choice == 3) printf("Result: %.2f\n", a * b);
        else if (choice == 4) {
            if (b == 0) printf("Can't divide by zero!\n");
            else printf("Result: %.2f\n", a / b);
        }
        else if (choice == 5) printf("Result: %.2f\n", pow(a, b));
        else printf("Invalid choice\n");
        
        printf("Again? (y/n): ");
        scanf(" %c", &again);
    }
    return 0;
}