#include "Menu.h"
// typedef struct _menuItem
//{
//     char menuName[20];
//     struct menuItem *next;
//     struct menuItem *back;
//     int sonNum;
//     struct menuItem *son;
//     void(*action)();
// }menuItem;
struct _menuItem *showMenuer = NULL;
struct _menuItem *getEnd = NULL;
doubleNum numFKey ; 
uint8_t exitMenu = 0;
uint8_t mainMenuKey = 0;
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
    oledShowStr(0, choosePoint+2, POINT, 1);
}

void mainMenuAction(menuItem *t)
{
    int mainMenuPoint = 0;
    uint8_t isChange = 0;
    exitMenu = 0;
    while (1)
    {
        mainMenuKey = remoteScan();
        if (mainMenuKey)
        {
            switch (mainMenuKey)
            {
                case 82:                        /*下按钮*/
                    mainMenuPoint++;
                    if (mainMenuPoint >= t->sonNum){
                        mainMenuPoint = 0;
                    } 
                    showMenu(showMenuer, mainMenuPoint);
                    HAL_Delay(100);
                    beepBeep(1);
                    break;
                case 24:                        /*上按钮*/
                    mainMenuPoint--;
                    if (mainMenuPoint < 0){
                        mainMenuPoint = t->sonNum-1;
                    }
                    showMenu(showMenuer, mainMenuPoint);
                    HAL_Delay(100);
                    break;
                case 28:                        /*确定按钮*/
                    //showMenu(showMenuer, mainMenuPoint);
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
                case 13:                        /*返回按钮#*/
                    if (t->back != NULL){
                        showMenuer = t->back;
                    }else {
                        exitMenu = 1;
                    }
                    isChange = 1;
                    break;
                default:
                    break;
            }
        }
        else
        {
            HAL_Delay(10);
            lastSta = 0;
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

void getNumFKey(doubleNum *num){
    uint8_t numKey = 0;
    //char *stre;
    uint8_t inum = 0; /*每次输入的值*/
    uint8_t isfloat = 0;
    float fnum = 1; /*每次的累乘*/
    float res = 0;
    while (1)
  {
      
        numKey = remoteScan();
        if (numKey)
        {
            switch (numKey)
            {
            case 69:
                //stre = "1    ";
                inum = 1; 
                break;
            case 70:
                //stre = "2    ";
                inum = 2; 
                break;
            case 71:
                //stre = "3    ";
                inum = 3; 
                break;
            case 68:
                //stre = "4    ";
                inum = 4; 
                break;
            case 64:
                //stre = "5    ";
                inum = 5; 
                break;
            case 67:
                //stre = "6    ";
                inum = 6; 
                break;
            case 7:
                //stre = "7    ";
                inum = 7; 
                break;
            case 21:
                //stre = "8    ";
                inum = 8; 
                break;
            case 9:
                //stre = "9    ";
                inum = 9; 
                break;
            case 25:
                //stre = "0    ";
                inum = 0; 
                break;
            case 13:
                //stre = "#    ";   /*小数点*/
                isfloat = 1;
                break;
            case 22:
               // stre = "*    ";
                break;
            case 24:
                //stre = "UP   ";
                break;
            case 82:
                //stre = "DOWM ";
                break;
            case 8:
                //stre = "LEFT ";
                break;
            case 90:
                //stre = "RIGHT";
                break;
            case 28:
                //stre = "OK   ";   /*确认*/
                break;
            default:
               // stre = "NULL ";
                break;
            }
            if (isfloat){
                
            
            }else{
                res = res*10+inum*fnum;
            }
            
            oledCLS();
            oledShowFloat(32,  7, res, 1);

        }
        else
        {
            HAL_Delay(10);
        }
  }
}
