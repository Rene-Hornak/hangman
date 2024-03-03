#include <stdio.h>
#include <string.h>

#define SIZE_NAME 16
#define SIZE_CHARACTERS 21
#define MAX_OPTIONS 10

// Function Prototypes
void sort(char sortedArray[][SIZE_CHARACTERS], int wordNumber);
int separateString(char sortedArray[][SIZE_CHARACTERS], char mainStr[], char hint[], char sep[]);
void printHangmanShape(int stage);
void playHangman(char sortedArray[][SIZE_CHARACTERS], int option, int lenOfOption, char hint[]);

int main() {
    char mainStr[SIZE_NAME * SIZE_CHARACTERS];
    char sortedArray[MAX_OPTIONS][SIZE_CHARACTERS];
    char hint[SIZE_CHARACTERS] = {};

    printf("Enter your words: (for example: name:John Carrot,Kennedy,Juraj )\n");
    scanf("%[^\n]", mainStr);

    int wordNumber = separateString(sortedArray, mainStr, hint, ",");

    sort(sortedArray, wordNumber);

    printf("Choose an option (by number):\n");
    for (int i = 0; i < wordNumber; i++) {
        printf("%d: %s\n", (i + 1), sortedArray[i]);
    }

    int option;
    scanf("%d", &option);
    option--;

    int lenOfOption = strlen(sortedArray[option]);

    playHangman(sortedArray, option, lenOfOption, hint);

    return 0;
}

void sort(char sortedArray[][SIZE_CHARACTERS], int wordNumber) {
    char temp[SIZE_CHARACTERS];

    for (int i = 0; i < wordNumber - 1; i++) {
        for (int j = i + 1; j < wordNumber; j++) {
            if (strcmp(sortedArray[i], sortedArray[j]) > 0) {
                strcpy(temp, sortedArray[i]);
                strcpy(sortedArray[i], sortedArray[j]);
                strcpy(sortedArray[j], temp);
            }
        }
    }
}

int separateString(char sortedArray[][SIZE_CHARACTERS], char mainStr[], char hint[], char sep[]) {
    const char start = ':';

    // Extracting hint
    int i;
    for (i = 0; mainStr[i] != start; i++) {
        hint[i] = mainStr[i];
    }

    // Tokenizing and storing words in sortedArray
    char *token;
    token = strchr(mainStr, start);

    token += sizeof(char);
    token = strtok(token, sep);

    int wordNumber = 0;

    while (token != NULL) {
        strcpy(sortedArray[wordNumber], token);
        token = strtok(NULL, sep);
        wordNumber++;
    }

    return wordNumber;
}

void printHangmanShape(int stage) {
	const int ZERO = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6;

	if(stage == ONE){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
			printf("|         |\n");
		}

		printf("|_________|\n");
	}
	else if(stage == TWO){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
			if(t == TWO){
				printf("| **      |\n");
			} else {
				printf("|         |\n");
			}
		}
		printf("|_________|\n");
			
	}
	else if(stage == THREE){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
			if(t == TWO){
				printf("| **   ** |\n");
			}
			else{
				printf("|         |\n");
			}
		}
		printf("|_________|\n");
	}
	else if(stage == FOUR){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
			if(t == ZERO){
				printf("| --      |\n");
			}
			else if(t == TWO){
				printf("| **   ** |\n");
			}
			else{
				printf("|         |\n");
			}
		}
		printf("|_________|\n");
	}
	else if(stage == FIVE){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
		       if(t == ZERO){
		       		printf("| --   -- |\n");
		       }	
		       else if(t == TWO){
			       	printf("| **   ** |\n");
		       }
		       else{
		       		printf("|         |\n");
		       }
		}
		printf("|_________|\n");

	}
	else if(stage == SIX){
		printf("___________\n");
		for(int t = 0; t < FIVE; t++){
			if(t == ZERO){
				printf("| --   -- |\n");
			}
			else if(t == TWO){
				printf("| XX   XX |\n");
			}
			else if(t == FOUR){
				printf("|  -----  |\n");
			}
			else{
				printf("|         |\n");
			}
		}
		printf("|_________|\n");
	}
}

void playHangman(char sortedArray[][SIZE_CHARACTERS], int option, int lenOfOption, char hint[]) {
    const int ONE = 1, SIX = 6;

    int stage = 1;
    int hintFlag = 1;
    int outFlag = 1;
    int correctFlag = 1;

    char answers[SIZE_CHARACTERS];
    int letIndex = 0;
    char choice = 0;
    char enter;

    const char UNDERLINE = '-', SPACE = ' ', ASTERISK = '*';

    char line[lenOfOption];

    // Initializing the line with underscores for each non-space character in the word
    for (int i = 0; i < lenOfOption; i++) {
        line[i] = (sortedArray[option][i] != SPACE) ? UNDERLINE : SPACE;
    }

    while (ONE) {
        printHangmanShape(stage);

        // If the word is guessed, print a message and break out of the loop
        if (strcmp(line, sortedArray[option]) == 0) {
            printf("The word is %s, good job!\n", sortedArray[option]);
            break;
        }

        // Print the current state of the guessed word
        for (int i = 0; i < lenOfOption; i++) {
            printf("%c", line[i]);
        }

        // Display a hint if hintFlag is true
        if (hintFlag == ONE) {
            printf("\nDo you want a clue? Press '*'");
        }

        // Display the letters that have been guessed
        printf("\nThe letters that you already tried: ");

        for (int k = 0; k < letIndex; k++) {
            printf("%c", answers[k]);
            if (k < letIndex - 1) {
                printf(" ");
            }
        }

        // Get user input for the next letter
        printf("\nPlease choose a letter:\n");

        scanf("%*[^\n]");
        scanf("%*[^\n]%*c");
        scanf("%c %c", &enter, &choice);

        // Check for special case: requesting a hint
        if (choice == ASTERISK && hintFlag == ONE) {
            printf("The clue is: %s.\n", hint);
            hintFlag = 0;
        } else if (choice != ASTERISK) {
            // Check if the letter has already been guessed
            for (int i = 0; i < letIndex; i++) {
                if (choice == answers[i]) {
                    outFlag = 0;
                }
            }

            // Process the chosen letter
            if (outFlag == ONE) {
                answers[letIndex] = choice;
                letIndex++;

                // Update the guessed word
                for (int i = 0; i < lenOfOption; i++) {
                    if (sortedArray[option][i] == choice) {
                        line[i] = choice;
                        correctFlag = 0;
                    }
                }

                // Update the stage if the chosen letter is incorrect
                if (correctFlag == ONE) {
                    stage++;

                    // If the stage reaches six, print a message and break out of the loop
                    if (stage == SIX) {
                        printHangmanShape(stage);
                        printf("The word is %s, GAME OVER!\n", sortedArray[option]);
                        break;
                    }
                }
            } else {
                printf("\nYou have already tried that letter.\n");
            }
        }

        // Reset flags for the next iteration
        outFlag = 1;
        correctFlag = 1;
    }
}
