/* Workshop 6
Name : Ahram Lee
Email : alee239@myseneca.ca
Student ID : 133849232
Date: 2024-06-15 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stringhelp.h"
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "log4c.h"

int main(void) {

    // Open the log file
    struct Log4cStruct logFile = l4cOpen("logfile.txt", 0);
    char errMsg[L4C_ERROR_MSG_MAX + 1];

    // Check the status of the log file
    int logStatus = l4cCheck(&logFile, errMsg);
    if (logStatus != 0) {
        l4cError(&logFile, errMsg);
        return 1;
    }

    // Set the test string
    char testStr[] = "This is a\nstring with embedded newline characters\nand 12345 numbers inside it as well 7890";
    assert(testStr != NULL);

    // Create string index
    struct StringIndex index = indexString(testStr);

    // Create and log messages
    char logMessage[100];
    snprintf(logMessage, sizeof(logMessage), "Number of Lines: %d", getNumberLines(&index));
    l4cInfo(&logFile, logMessage);

    snprintf(logMessage, sizeof(logMessage), "Number of Words: %d", getNumberWords(&index));
    l4cInfo(&logFile, logMessage);

    snprintf(logMessage, sizeof(logMessage), "Number of Numbers: %d", getNumberNumbers(&index));
    l4cInfo(&logFile, logMessage);

    // Print the contents of the index
    printf("LINES\n");
    for (int i = 0; i < index.numLines; i++) {
        printUntil(index.str, index.lineStarts[i], '\n');
        printf("\n");
    }

    printf("\nWORDS\n");
    for (int i = 0; i < index.numWords; i++) {
        printUntilSpace(index.str, index.wordStarts[i]);
        printf("\n");
    }

    printf("\nNUMBERS\n");
    for (int i = 0; i < index.numNumbers; i++) {
        printUntilSpace(index.str, index.numberStarts[i]);
        printf("\n");
    }

    // Add assertions for expected results
    assert(getNumberLines(&index) == 3);
    assert(getNumberWords(&index) == 14);
    assert(getNumberNumbers(&index) == 2);

    // Close the log file
    l4cClose(&logFile);

    return 0;
}
