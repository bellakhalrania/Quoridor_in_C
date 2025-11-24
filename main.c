#include <stdio.h>
#include <conio.h>  // For Windows keyboard input
#include <stdlib.h> // For system("cls")
#include <string.h> // For strcat, sprintf

// Structure to store character position (emplacement)
typedef struct {
    char character;
    int row;
    int col;
} CharPosition;

// Global array to store character positions
CharPosition saved_positions[100];
int position_count = 0;

// Global variables for character positions (A and B)
int pos_A_row = 17, pos_A_col = 9;  // Initial position for A
int pos_B_row = 1, pos_B_col = 9;   // Initial position for B

// Global variables for character bars (each character has 10 bars)
int bar_A = 10;
int bar_B = 10;

// Function to save the emplacement (position) for a character
void save_char_position(char character, int row, int col) {
    if (position_count < 100) {
        saved_positions[position_count].character = character;
        saved_positions[position_count].row = row;
        saved_positions[position_count].col = col;
        position_count++;
        printf("Saved: Character '%c' at position (%d, %d)\n", character, row, col);
    } else {
        printf("Error: Maximum number of positions reached!\n");
    }
}

// Function to display all saved character positions
void show_saved_positions() {
    int i;
    printf("\n=== Saved Character Positions ===\n");
    if (position_count == 0) {
        printf("No positions saved yet.\n");
    } else {
        for (i = 0; i < position_count; i++) {
            printf("Character '%c' at position (row=%d, col=%d)\n", 
                   saved_positions[i].character, 
                   saved_positions[i].row, 
                   saved_positions[i].col);
        }
    }
    printf("================================\n\n");
}

// Function to save character position to a text file (each character has its own file)
void save_char_position_to_file(char character, int row, int col) {
    char filename[50];
    FILE *file;
    
    // Create filename: "char_A.txt", "char_B.txt", etc.
    sprintf(filename, "char_%c.txt", character);
    
    // Open file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot create file %s\n", filename);
        return;
    }
    
    // Write character position to file
    fprintf(file, "Character: %c\n", character);
    fprintf(file, "Row: %d\n", row);
    fprintf(file, "Col: %d\n", col);
    
    fclose(file);
    printf("Position saved to file: %s (Character '%c' at row=%d, col=%d)\n", 
           filename, character, row, col);
}

// Function to read character position from a text file
int read_char_position_from_file(char character, int *row, int *col) {
    char filename[50];
    FILE *file;
    char line[100];
    char temp_char;
    
    // Create filename: "char_A.txt", "char_B.txt", etc.
    sprintf(filename, "char_%c.txt", character);
    
    // Open file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s (file does not exist)\n", filename);
        return 0; // Return 0 if file doesn't exist
    }
    
    // Read the file content
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "Character: %c", &temp_char) == 1) {
            // Character line read
        } else if (sscanf(line, "Row: %d", row) == 1) {
            // Row read
        } else if (sscanf(line, "Col: %d", col) == 1) {
            // Column read
        }
    }
    
    fclose(file);
    printf("Position read from file: %s (Character '%c' at row=%d, col=%d)\n", 
           filename, character, *row, *col);
    return 1; // Return 1 if successful
}

// Function to get arrow key input (returns: 1=up, 2=down, 3=left, 4=right, 0=invalid)
int get_arrow_key() {
    int ch = getch();
    if (ch == 224 || ch == 0) {  // Arrow key prefix
        ch = getch();
        switch(ch) {
            case 72: return 1; // Up
            case 80: return 2; // Down
            case 75: return 3; // Left
            case 77: return 4; // Right
            default: return 0;
        }
    }
    return 0;
}

// Function to validate position (check if position is within bounds and valid)
int is_valid_position(int row, int col, char character) {
    // Check bounds (0-18 for 19x19 matrix)
    if (row < 0 || row > 18 || col < 0 || col > 18) {
        return 0; // Out of bounds
    }
    
    // Check if both row and column are odd (impaire)
    if (row % 2 != 1 || col % 2 != 1) {
        return 0; // Position must have both row and column as odd numbers
    }
    
    // Check if position is not occupied by the other character
    if (character == 'A') {
        if (row == pos_B_row && col == pos_B_col) {
            return 0; // Position occupied by B
        }
    } else if (character == 'B') {
        if (row == pos_A_row && col == pos_A_col) {
            return 0; // Position occupied by A
        }
    }
    
    return 1; // Valid position
}

// Function to display instructions in a box made of "*"
void display_instructions_box() {
    int i;
    const char *instructions[] = {
        "INSTRUCTIONS",
        "",
        "MOVEMENT:",
        "  Arrow Keys",
        "  Move character",
        "",
        "ACTIONS:",
        "  P - Pick a bar",
        "  Q - Quit game",
        "",
        "RULES:",
        "  - Move to ODD",
        "    positions only",
        "  - Each char has",
        "    10 bars",
        "  - Turn by turn",
        "",
        "STATUS:",
        "  A: Bars available",
        "  B: Bars available"
    };
    int num_lines = 20;
    int box_width = 35;
    
    // Print top border
    for (i = 0; i < box_width; i++) {
        printf("*");
    }
    printf("\n");
    
    // Print instructions with side borders
    for (i = 0; i < num_lines; i++) {
        printf("*");
        if (i < sizeof(instructions)/sizeof(instructions[0])) {
            printf(" %-32s", instructions[i]);
        } else {
            printf(" %-32s", "");
        }
        printf("*\n");
    }
    
    // Print bottom border
    for (i = 0; i < box_width; i++) {
        printf("*");
    }
    printf("\n");
}

// Function to display matrix with current character positions
void display_matrix_with_positions(char current_char, int current_bar) {
    int i, j;
    
    system("cls"); // Clear screen (Windows)
    printf("\n18x18 Matrix - Use Arrow Keys to Move (Turn by Turn)\n");
    printf("Current: A at (%d, %d) [Bars: %d] | B at (%d, %d) [Bars: %d]\n", 
           pos_A_row, pos_A_col, bar_A, pos_B_row, pos_B_col, bar_B);
    
    // Print header
    printf("   ");
    for (i = 0; i < 19; i++) {
        printf("%2d", i);
    }
    printf("      ");
    for (i = 0; i < 32; i++) printf("*");
    printf("\n");
    
    // Print matrix rows with small instruction box
    for (i = 0; i < 19; i++) {
        // Print matrix row
        printf("%2d ", i);
        for (j = 0; j < 19; j++) {
            // Check if A is at this position
            if (i == pos_A_row && j == pos_A_col) {
                printf("A ");
            }
            // Check if B is at this position
            else if (i == pos_B_row && j == pos_B_col) {
                printf("B ");
            }
            else if (i % 2 == 1 && j % 2 == 1) {
                // Both row and column are odd - put spaces
                printf("  ");
            } else {
                // Otherwise put point with space
                printf(". ");
            }
        }
        
        // Print small instruction box (only for first 9 rows)
        printf("      ");
        if (i == 0) {
            printf("*");
            for (j = 0; j < 30; j++) printf(" ");
            printf("*");
        } else if (i == 1) {
            printf("* >>> %c's Turn - Bars: %2d <<<  *", current_char, current_bar);
        } else if (i == 2) {
            printf("*                                *");
        } else if (i == 3) {
            printf("* ACTIONS:                        *");
        } else if (i == 4) {
            printf("* Arrow Keys = Move               *");
        } else if (i == 5) {
            printf("* P - Pick a bar                  *");
        } else if (i == 6) {
            printf("* Q - Quit game                   *");
        } else if (i == 7) {
            printf("*                                *");
        } else if (i == 8) {
            printf("* A: %2d bars | B: %2d bars         *", bar_A, bar_B);
        } else {
            // Empty space for remaining rows
            printf("                                  ");
        }
        printf("\n");
    }
    
    // Print bottom border of instruction box (only for the small box)
    printf("   ");
    for (i = 0; i < 38; i++) printf(" ");
    for (i = 0; i < 32; i++) printf("*");
    printf("\n\n");
}

// Function to move characters turn by turn using arrow keys
void move_characters_turn_by_turn() {
    int arrow_key;
    int current_turn = 0; // 0 = A's turn, 1 = B's turn
    char current_char;
    int *current_row, *current_col;
    int new_row, new_col;
    
    system("cls"); // Clear screen
    printf("========================================\n");
    printf("   GAME STARTED!\n");
    printf("========================================\n");
    printf(">>> Character A starts first! <<<\n");
    printf("========================================\n");
    printf("Each character starts with 10 bars.\n");
    printf("Each turn: Arrow Keys = Move | P = Pick a bar\n");
    printf("Characters can only move to ODD positions (impaire).\n");
    printf("Press 'Q' to quit.\n");
    printf("========================================\n\n");
    printf("Press any key to continue...\n");
    getch();
    
    while (1) {
        int *current_bar;
        int action_taken = 0;
        
        // Determine whose turn it is
        if (current_turn == 0) {
            current_char = 'A';
            current_row = &pos_A_row;
            current_col = &pos_A_col;
            current_bar = &bar_A;
        } else {
            current_char = 'B';
            current_row = &pos_B_row;
            current_col = &pos_B_col;
            current_bar = &bar_B;
        }
        
        display_matrix_with_positions(current_char, *current_bar);
        printf("Choose an action: ");
        
        // Get input
        arrow_key = get_arrow_key();
        
        // Check if user wants to quit or pick a bar
        if (arrow_key == 0) {
            int ch = getch();
            if (ch == 'q' || ch == 'Q') {
                printf("\nGame ended. Saving positions...\n");
                save_char_position_to_file('A', pos_A_row, pos_A_col);
                save_char_position_to_file('B', pos_B_row, pos_B_col);
                break;
            } else if (ch == 'p' || ch == 'P') {
                // Pick a bar
                if (*current_bar > 0) {
                    (*current_bar)--;
                    printf("\n*** %c picked a bar! Remaining bars: %d ***\n", current_char, *current_bar);
                    printf("Press any key to continue...\n");
                    getch();
                    action_taken = 1;
                    // Switch turn after picking a bar
                    current_turn = (current_turn + 1) % 2;
                } else {
                    printf("\n*** No bars left! You must move. ***\n");
                    printf("Press any key to continue...\n");
                    getch();
                    continue;
                }
            } else {
                continue;
            }
        }
        
        // If action was picking a bar, skip movement
        if (action_taken) {
            continue;
        }
        
        // Calculate new position based on arrow key
        // Move by 2 to stay on odd positions (impaire)
        new_row = *current_row;
        new_col = *current_col;
        
        switch(arrow_key) {
            case 1: new_row -= 2; break; // Up (move by 2 to stay on odd)
            case 2: new_row += 2; break; // Down (move by 2 to stay on odd)
            case 3: new_col -= 2; break; // Left (move by 2 to stay on odd)
            case 4: new_col += 2; break; // Right (move by 2 to stay on odd)
        }
        
        // Validate new position
        if (is_valid_position(new_row, new_col, current_char)) {
            // Move is valid - update position
            *current_row = new_row;
            *current_col = new_col;
            
            // Save position to file
            save_char_position_to_file(current_char, *current_row, *current_col);
            
            // Switch turn after moving
            current_turn = (current_turn + 1) % 2;
        } else {
            // Invalid position
            printf("\n*** Invalid position! Characters can only move to odd positions (impaire). Try again. ***\n");
            printf("Press any key to continue...\n");
            getch();
        }
    }
}

// Function to display matrix with two characters: A in last row, B in second row
// Parameters: row and col (emplacement) - the position where characters will be placed
void show_matrice_with_chars(int row, int col, char char1, char char2) {
    int i, j;
    
    // Save the positions for each character before displaying
    save_char_position(char1, 17, col);  // A in last row
    save_char_position(char2, 1, col);   // B in second row
    
    // Save positions to text files (each character has its own file)
    save_char_position_to_file(char1, 17, col);
    save_char_position_to_file(char2, 1, col);
    
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
            // Place B in the second row (i=1) at column col
            else if (i == 1 && j == col) {
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
    
    // Initialize character positions
    pos_A_row = 17;
    pos_A_col = 9;
    pos_B_row = 1;
    pos_B_col = 9;
    
    // Start the turn-by-turn movement game
    move_characters_turn_by_turn();
    
    printf("\nThank you for playing!\n");
    
    return 0;
}

