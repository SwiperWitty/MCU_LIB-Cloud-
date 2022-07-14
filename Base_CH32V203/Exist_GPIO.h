#ifndef __Exist_GPIO__H_
#define __Exist_GPIO__H_

#include "Items.h"

/*
                GPIO_Init(Exist_GPIO)->
    SDK->Items->                       BASE->
                Peripheral(UART、ADC)->      \\
                                              -->[XXX]->MODE
                                             //
                        C(Lib)->Caven->API->
*/

/*
        本文件在上述关系图中属于 【GPIO_Init】
         这里存放的是【只使用GPIO外设】功能的初始化（KEY、LED、BZZ、超声波等）。
         其他功能的初始化（例如UART、IIC），除了先初始化【GPIO外设】还要【功能外设】，这种功能的初始化GPIO并不在本文件范围内。
         IIC有软件版本和硬件版本，所以它的GPIO跟本文件无关。
         但是LCD的驱动由SPI协议和DC（IO）接口组成，那么这个IO接口由本文件提供。

                                                                     ————202207.14
 */

#ifdef Exist_OLED

    #define LCD_DC_Clr() GPIOA->BCR = GPIO_Pin_10    //DC_GPIO
    #define LCD_DC_Set() GPIOA->BSHR = GPIO_Pin_10   //PA10

//    #define LCD_RES_Clr()                                     //RES               //Caven 使用硬件复位
//    #define LCD_RES_Set()
#endif

#ifdef Exist_OLED

    #define OLED_DC_Clr() GPIOA->BCR = GPIO_Pin_10    //DC_GPIO
    #define OLED_DC_Set() GPIOA->BSHR = GPIO_Pin_10   //PA10

//    #define LCD_RES_Clr()                                     //RES               //Caven 使用硬件复位
//    #define LCD_RES_Set()
#endif

#ifdef Exist_KEY
    #define KEY_Clr() GPIOA->BCR = GPIO_Pin_0    //KEY
    #define KEY_Set() GPIOA->BSHR = GPIO_Pin_0   //PA00
#endif

#ifdef Exist_LED
    #define LED_Clr() GPIOA->BCR = GPIO_Pin_1    //LED
    #define LED_Set() GPIOA->BSHR = GPIO_Pin_1   //PA01
#endif

#ifdef Exist_BZZ

#endif

#ifdef Exist_Ultrasonic

#endif

/*  Init-Function    */

void KEY_GPIO_Init(int SET);
void LED_GPIO_Init(int SET);

#endif
