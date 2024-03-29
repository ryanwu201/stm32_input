//
// Created by qin on 2019/6/5.
//

//#ifndef INPUT_BSP_KEY_H
//#define INPUT_BSP_KEY_H

#include <stdint.h>
#include "stm32f10x.h"
#include "code.h"
#define      column(x)                x % (LCD_X_LENGTH / WIDTH_CH_CHAR)
#define      row(x)                x / (LCD_X_LENGTH / WIDTH_CH_CHAR)
static int shift = 0;
/*buffer计数*/
static uint8_t bufferCount = 0;
/*content计数*/
static uint8_t contentCount = 0;
/*光标类型*/
static uint8_t cursorType = 0;
void KEY_Init(void);

int Key_Scan(void);

int Key_Scan2(void);

uint8_t *keyHandler(uint8_t key, uint8_t *pBuffer, uint64_t *pBuffer_start);

void showCursor();
//#endif //INPUT_BSP_KEY_H
