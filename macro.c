#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100

int main() {
    char label[MAX_STRING_SIZE], opcode[MAX_STRING_SIZE], operand[MAX_STRING_SIZE], maclabel[MAX_STRING_SIZE];
    char label1[MAX_STRING_SIZE], opcode1[MAX_STRING_SIZE], operand1[MAX_STRING_SIZE];
    char l1[MAX_STRING_SIZE];
    int count;
    FILE *f1, *f2, *f3;

    // Open input file for reading
    f1 = fopen("input.txt", "r");
    if (f1 == NULL) {
        perror("Error opening input.txt");
        return EXIT_FAILURE;
    }

    // Open macro file for writing
    f2 = fopen("macro.txt", "w");
    if (f2 == NULL) {
        perror("Error opening macro.txt");
        fclose(f1);
        return EXIT_FAILURE;
    }

    // Open output file for writing
    f3 = fopen("output.txt", "w");
    if (f3 == NULL) {
        perror("Error opening output.txt");
        fclose(f1);
        fclose(f2);
        return EXIT_FAILURE;
    }

    // First Pass: Identify and store macros in macro.txt
    while (fscanf(f1, "%s%s%s", label, opcode, operand) != EOF) {
        if (strcmp(opcode, "MACRO") == 0) {
            strcpy(maclabel, label);
            fscanf(f1, "%s%s%s", label, opcode, operand);

            // Store macro lines in macro.txt until MEND is encountered
            while (strcmp(opcode, "MEND") != 0) {
                fprintf(f2, "%s\t%s\t%s\t\n", label, opcode, operand);
                fscanf(f1, "%s%s%s", label, opcode, operand);
            }
        }
    }

    // Close macro.txt after storing macros
    fclose(f2);
    rewind(f1);

    // Second Pass: Expand macros and generate output.txt
    while (fscanf(f1, "%s%s%s", label, opcode, operand) != EOF) {
        if (strcmp(opcode, "MACRO") == 0) {
            while (strcmp(opcode, "MEND") != 0) {
                fscanf(f1, "%s%s%s", label, opcode, operand);
            }
        } else if (strcmp(opcode, "END") == 0) {
            break;
        } else if (strcmp(opcode, maclabel) == 0) {
            // Expand the macro by reading from macro.txt and write to output.txt
            strcpy(l1, label);
            count = 1;
            f2 = fopen("macro.txt", "r");
            if (f2 == NULL) {
                perror("Error opening macro.txt for reading");
                fclose(f1);
                fclose(f3);
                return EXIT_FAILURE;
            }

            // Write expanded macro to output.txt
            while (fscanf(f2, "%s%s%s", label1, opcode1, operand1) != EOF) {
                if (count == 1) {
                    fprintf(f3, "%s\t%s\t%s\n", l1, opcode1, operand1);
                    count = 0;
                } else {
                    fprintf(f3, "%s\t%s\t%s\n", label1, opcode1, operand1);
                }
            }

            // Close macro.txt after expanding macro
            fclose(f2);
        } else if (strcmp(opcode, "MACRO") != 0 && strcmp(opcode, "MEND") != 0) {
            // Write non-macro lines to output.txt
            fprintf(f3, "%s\t%s\t%s\n", label, opcode, operand);
        }
    }

    // Close all open files
    fclose(f1);
    fclose(f3);

    return EXIT_SUCCESS;
}