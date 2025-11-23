#include <stdio.h>

// Function to display matrix with two characters: A in last row, B in second row
// Parameters: row and col (emplacement) - the position where characters will be placed
void show_matrice_with_chars(int row, int col, char char1, char char2) {
    int i, j;
    
    printf("\n18x18 Matrix with characters at position (%d, %d):\n", row, col);
    printf("   ");
    // Print column numbers
    for (i = 0; i < 19; i++) {
        printf("%2d", i);
    }
    printf("\n");
    
    // Print matrix with points
    for (i = 0; i < 19; i++) {
        printf("%2d ", i); // Print row number
        for (j = 0; j < 19; j++) {
            // Place A in the last row (i=17) at column col
            if (i == 17 && j == col) {
                printf("%c ", char1);
            }
            // Place B in the second row (i=1) at column col + 2
            else if (i == 1 && j == col ) {
                printf("%c ", char2);
            }
            else if (i % 2 == 1 && j % 2 == 1) {
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
    
    // Example: Show matrix with two characters in the middle of first and last row
    // Parameters: row=9, col=9 (middle position), characters 'A' and 'B'
    show_matrice_with_chars(9, 9, 'A', 'B');
    
    return 0;
}

