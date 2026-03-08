#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int secret = (rand() % 100) + 1;
    
    int attempts = 0;
    int guess;
    
    printf("Guess a number between 1 and 100. You get 7 tries.\n\n");
    
    while (attempts < 7) {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        while (getchar() != '\n');
        
        if (guess < 1 || guess > 100) {
            printf("Please guess between 1 and 100.\n\n");
            continue;
        }
        
        attempts++;
        
        if (guess == secret) {
            printf("You got it! It took %d guesses.\n", attempts);
            return 0;
        }
        
        if (guess < secret) {
            printf("Too low. ");
        } else {
            printf("Too high. ");
        }
        printf("Guesses left: %d\n\n", 7 - attempts);
    }
    
    printf("Out of guesses. The number was %d.\n", secret);
    return 0;
}