#include <stdio.h>

// Function to display an 18x18 matrix with points
void show_matrice() {
    int i, j;
    
    printf("\n18x18 Matrix with points:\n");
    printf("   ");
    // Print column numbers
    for (i = 0; i < 19; i++) {
        printf("%2d", i);
    }
    printf("\n");
    
    // Print matrix with points (all rows with spaces)
    // If row and col are both odd (impaire), put spaces, otherwise put point
    for (i = 0; i < 19; i++) {
        printf("%2d ", i); // Print row number
        for (j = 0; j < 19; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                // Both row and column are odd - put spaces
                printf("  ");
            } else {
                // Otherwise put point with space
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("Hello, World!\n");
    printf("Welcome to your C project!\n");
    
    // Call the function to show the matrix
    show_matrice();
    
    return 0;
}

