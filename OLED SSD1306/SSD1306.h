/*
 * SSD1306.h
 *
 *  Created on: Mar 25, 2020
 *      Author: Gabriele
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include <stddef.h>
#include <_ansi.h>

#include "main.h"
#include "stm32l4xx_hal.h"
#include "ssd1306_fonts.h"


// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1306_t;

// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

//Personal function
void ssd1306_PrintLogo();
void ssd1306_FillFromTo(uint16_t from_, uint16_t to_,SSD1306_COLOR color);
uint8_t ssd1306_melt_effect(uint8_t direction);
char ssd1306_SlowWriteString(char* str, FontDef Font, SSD1306_COLOR color, uint16_t delay);
void ssd1306_gradFill(SSD1306_COLOR color, uint16_t w_delay);
char ssd1306_WriteSpecialChar(FontDef Font, SSD1306_COLOR color);


// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size);

#endif /* SSD1306_H_ */
