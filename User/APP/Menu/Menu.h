#ifndef __MENU_H__
#define __MENU_H__

#include "main.h"

#define POINT (uint8_t *)">>" 

typedef struct _menuItem
{
    char menuName[15];
    struct _menuItem *next;
    struct _menuItem *back;
    uint8_t sonNum;
    struct _menuItem *son;
    void (*action)();
} menuItem;

typedef struct _doubleNum
{
    int integer;
    float demical;
} doubleNum;

extern menuItem *head;
extern menuItem *showMenuer;
extern uint8_t exitMenu;
extern doubleNum numFKey;

menuItem *createMenu(char *name, menuItem *father, int sonnum, void (*action)());
void showMenu(menuItem *shower, uint8_t choosePoint);
void mainMenuAction(menuItem *t);
void getNumFKey(doubleNum *num);

#endif /* __MENU_H__ */
