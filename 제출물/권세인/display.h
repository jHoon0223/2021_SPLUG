#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>

#define DISPLAY_TITLE       L" 2021 SPLUG "
#define DISPLAY_LINE_CHAR   '='
#define DISPLAY_WIDTH       30
#define MENU_CONTENT_MARGIN 5

void displayClear();
void displayPrints(char m, int times);
void displayPrintMid(wchar_t *msg, char space, int width);
void displayPrintMenu(char* id, char* contents[], int count);
void displayPrintMenuHeader(char* id);
void displayPrintMenuContent(char* contents[], int count);
void displayPrintMenuFooter(void);
bool displayPrompt(wchar_t *msg);
void displayPrintInput();
