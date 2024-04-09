#include "Tools.h"

uint8_t* float2str(double num,int n)
{
    int i = 0;
    static uint8_t num_str[13] = {'\0'}; 
    uint8_t len = 0;
    uint8_t n_max = 0; //小数点最大位数

    for(i = 0;i<13;i++) //字符串清空
      num_str[i] = '\0';
    //确定符号
    if(num > 0){

      num_str[0] = '+';
    }
    else if(num < 0){

      num_str[0] = '-';
      num = -num;
    }

    //确定整数部分长度
    if((int)(num/100000) != 0){ //6位数
      len = 7;
      n_max = 4;
    }
    else if((int)(num/10000) != 0){ //5位数 
        len = 6;
        n_max = 5;
    }
    else if((int)(num/1000) != 0){ //4位数   
        len = 5;
        n_max = 6;
    }
    else if((int)(num/100) != 0){  //3位数
        len = 4;
        n_max = 7;
    }
    else if((int)(num/10) != 0){ //2位数
        len = 3;
        n_max = 8;
    }
    else{ //1位数
        len = 2;
        n_max = 9;
    }

    //小数点限幅
    if(n > n_max)
        n = n_max;
    len+=n; //确定长度

    //变成整数
    i = n;
    while(i--)
        num = (num*10);

    //inum = num;

    //转换小数
    while(n--){ 

        num_str[len--] = (int)num%10+0x30;
        num = num/10;
    }
    num_str[len] = '.';

    //转换整数
    while(len--){ 

        num_str[len] = (int)num%10+0x30;
        num = num/10;
        if(len == 1)
          break;
    }
    return num_str;
}


