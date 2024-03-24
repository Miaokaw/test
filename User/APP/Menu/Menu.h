#ifndef __MENU_H__
#define __MENU_H__
#include "main.h"
typedef struct _menuItem
{
    char menuName[15];
    struct _menuItem *next;
    struct _menuItem *back;
    uint8_t sonNum;
    struct _menuItem *son;
    void (*action)();
} menuItem;

extern menuItem *head;
extern menuItem *showMenuer;

menuItem *createMenu(char *name, menuItem *father, int sonnum, void (*action)());
void showMenu(menuItem *shower);
void mainMenAction(menuItem *t);
#endif /* __MENU_H__ */
