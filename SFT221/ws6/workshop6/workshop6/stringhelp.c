/* Workshop 6
Name : Ahram Lee
Email : alee239@myseneca.ca
Student ID : 133849232
Date: 2024-06-15 */

#define _CRT_SECURE_NO_WARNINGS
#include "stringhelp.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int nextWhite(const char* str) {
    int i, result = -1;
    for (i = 0; result < 0 && str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            result = i; // Found a whitespace character, record its position
        }
    }
    return (result < 0) ? i : result; // Return the position of the whitespace or the end of the string
}

int isNumber(const char* str, const int len) {
    int i, result = 1;
    for (i = 0; i < len && result; i++) {
        result = result && isdigit(str[i]); // Check if all characters are digits
    }
    return result;
}

struct StringIndex indexString(const char* str) {
    struct StringIndex result = { {0}, {0}, {0}, 0, 0, 0 };
    char buf[MAX_WORD_SIZE + 1] = { 0 };
    int i, sp;

    // Copy the input string to the result structure
    strcpy(result.str, str);
    if (str[0] != '\0') {
        result.lineStarts[result.numLines++] = 0; // Initialize the first line start position if the string is not empty
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            result.lineStarts[result.numLines++] = i + 1; // Correctly record the start of a new line after a newline character
        }

        // Skip over any whitespace characters
        while (str[i] != '\0' && isspace(str[i])) {
            i++;
        }

        // Calculate the length of the current word or number
        for (sp = 0; str[sp + i] != '\0' && !isspace(str[sp + i]); sp++);

        if (isNumber(str + i, sp)) {
            result.numberStarts[result.numNumbers++] = i; // Record the start position if it's a number
        }
        else {
            result.wordStarts[result.numWords++] = i; // Record the start position if it's a word
        }

        // Move the index to the end of the current word or number
        i += sp - 1;
    }
    return result;
}

int getNumberLines(const struct StringIndex* idx) {
    return idx->numLines; // Return the number of lines
}

int getNumberWords(const struct StringIndex* idx) {
    return idx->numWords; // Return the number of words
}

int getNumberNumbers(const struct StringIndex* idx) {
    return idx->numNumbers; // Return the number of numbers
}

void getWord(char word[], const struct StringIndex* idx, int wordNum) {
    int i, sp, start;
    word[0] = '\0';
    if (wordNum < idx->numWords && wordNum >= 0) {
        start = idx->wordStarts[wordNum];
        sp = nextWhite(idx->str + start);
        for (i = 0; i < sp; i++) {
            word[i] = idx->str[start + i]; // Copy the word from the start position
        }
        word[sp - start] = '\0'; // Null-terminate the word correctly
    }
}

void getNumber(char word[], const struct StringIndex* idx, int numberNum) {
    int i, sp, start;
    word[0] = '\0';
    if (numberNum < idx->numNumbers && numberNum >= 0) {
        start = idx->numberStarts[numberNum];
        sp = nextWhite(idx->str + start);
        for (i = 0; i < sp; i++) {
            word[i] = idx->str[start + i]; // Copy the number from the start position
        }
        word[sp - start] = '\0'; // Null-terminate the number correctly
    }
}

char* getLine(struct StringIndex* idx, int lineNum) {
    char* result = NULL;
    if (lineNum < idx->numLines && lineNum >= 0) {
        result = idx->str + idx->lineStarts[lineNum]; // Return a pointer to the start of the line
    }
    return result;
}

void printUntil(const char* s, const int start, const char terminator) {
    int i;
    for (i = start; s[i] != '\0' && s[i] != terminator; i++)
        printf("%c", s[i]); // Print characters until the terminator is found
}

void printUntilSpace(const char* s, const int start) {
    int i;
    for (i = start; s[i] != '\0' && !isspace(s[i]); i++)
        printf("%c", s[i]); // Print characters until a space is found
}
