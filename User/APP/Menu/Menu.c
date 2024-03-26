#include "Menu.h"
#define KEY_EXIT 3
// typedef struct _menuItem
//{
//     char menuName[20];
//     struct menuItem *next;
//     struct menuItem *back;
//     int sonNum;
//     struct menuItem *son;
//     void(*action)();
// }menuItem;
struct _menuItem *head = NULL;
struct _menuItem *showMenuer = NULL;
struct _menuItem *getEnd = NULL;
/**
 * 创建一个菜单项并将其添加到父菜单中
 *
 * @param name 菜单项的名称
 * @param father 父菜单项的指针
 * @param sonNum 子菜单项的数量
 * @param action 菜单项被选中时执行的函数指针
 * @return 创建的菜单项的指针
 */
menuItem *createMenu(char *name, menuItem *father, int sonNum, void (*action)())
{
    // 分配内存给新的菜单项
    menuItem *temp = (menuItem *)malloc(sizeof(menuItem));
    if (temp == NULL)
    {
        // 分配失败时的错误处理，例如打印错误日志
        return NULL;
    }
    strcpy(temp->menuName, name); // 复制菜单项名称
    temp->next = NULL;            // 初始化下一个菜单项为空
    temp->action = action;        // 设置菜单项的动作函数
    temp->back = father;          // 设置父菜单项
    temp->sonNum = 0;             // 初始化子菜单项数量为0
    temp->son = NULL;             // 初始化子菜单项为空

    if (father != NULL)
    {
        if (father->son != NULL)
        {
            getEnd = father->son;
            while (1)
            {
                if (getEnd->next != NULL)
                    getEnd = getEnd->next;
                else
                {
                    getEnd->next = temp;
                    break;
                }
            }
        }
        else
        {
            father->son = temp;
        }
        father->sonNum++;
    }
    return temp; // 返回新创建的菜单项
}

void showMenu(menuItem *shower, uint8_t choosePoint)
{
    oledCLS();
    HAL_Delay(10);
    oledShowStr(6, 0, (uint8_t *)shower->menuName, 1);
    uint8_t hang = 2;
    if (shower->son != NULL)
    {
        getEnd = shower->son;
        do{
            oledShowStr(18, hang, (uint8_t *)getEnd->menuName, 1);
            hang++;
            getEnd = getEnd->next;
        } while (getEnd != NULL);
    }
    if (choosePoint != 0) oledShowStr(0, choosePoint+1, (uint8_t *)">>", 1);
}

void mainMenuAction(menuItem *t)
{
    uint8_t mainMenuKey = 0;
    int mainMenuPoint = 0;
    uint8_t isChange = 0;
    while (1)
    {
        mainMenuKey = remoteScan();
        if (mainMenuKey)
        {
            switch (mainMenuKey)
            {
                case 82:
                    mainMenuPoint++;
                    if (mainMenuPoint){
                        mainMenuPoint = 1;
                    } 
                    showMenu(showMenuer, mainMenuPoint);
                    HAL_Delay(100);
                    beepBeep(1);
                    break;
                case 24:
                    mainMenuPoint--;
                    if (mainMenuPoint == 0){
                        mainMenuPoint = t->sonNum;
                    }
                    showMenu(showMenuer, mainMenuPoint);
                    HAL_Delay(100);
                    break;
                case 28:
                    showMenu(showMenuer, mainMenuPoint);
                    if (t->son != NULL)
                    {
                        getEnd = t->son;
                    }
                    while (mainMenuPoint && getEnd->next != NULL)
                    {
                        getEnd = getEnd->next;
                        mainMenuPoint--;
                    }
                    showMenuer = getEnd;
                    isChange = 1;
                    break;
                case 13:
                    showMenuer = t->back;
                    showMenu(showMenuer, 0);
                    isChange = 1;
                    break;
                default:
                    break;
            }
        }
        else
        {
            HAL_Delay(10);
            static uint8_t toggleCont = 0;
            if (++toggleCont >= 50)
            {
                LED_TOGGLE();
                toggleCont = 0;
            }
        }
        if (isChange)
            break;
    }
}
