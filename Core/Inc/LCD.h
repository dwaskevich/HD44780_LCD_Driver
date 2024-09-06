/*
 * LCD.h
 *
 *  Created on: Aug 25, 2024
 *      Author: David Waskevich
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

/***************************************
*        Function Prototypes
***************************************/

void LCD_Init(void) ;
void LCD_Enable(void) ;
void LCD_Start(void) ;
void LCD_Stop(void) ;
void LCD_WriteControl(uint8_t cByte) ;
void LCD_WriteData(uint8_t dByte) ;
void LCD_PrintString(char const string[]) ;
void LCD_Position(uint8_t row, uint8_t column) ;
void LCD_PutChar(char character) ;
void LCD_IsReady(void) ;
void LCD_SaveConfig(void) ;
void LCD_RestoreConfig(void) ;
void LCD_Sleep(void) ;
void LCD_Wakeup(void) ;

void LCD_DrawHorizontalBG(uint8_t row, uint8_t column, uint8_t maxCharacters, uint8_t value);
void LCD_DrawVerticalBG(uint8_t row, uint8_t column, uint8_t maxCharacters, uint8_t value);


/* ASCII Conversion Routines */
void LCD_PrintInt8(uint8_t value) ;
void LCD_PrintInt16(uint16_t value) ;
void LCD_PrintInt32(uint32_t value) ;
void LCD_PrintNumber(uint16_t value) ;
void LCD_PrintU32Number(uint32_t value) ;


/* Clear Macro */
#define LCD_ClearDisplay() LCD_WriteControl(LCD_CLEAR_DISPLAY)

/* Off Macro */
#define LCD_DisplayOff() LCD_WriteControl(LCD_DISPLAY_CURSOR_OFF)

/* On Macro */
#define LCD_DisplayOn() LCD_WriteControl(LCD_DISPLAY_ON_CURSOR_OFF)

#define LCD_PrintNumber(value) LCD_PrintU32Number((uint16_t) (value))

/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define LCD_DISPLAY_8_BIT_INIT       (0x03u)
#define LCD_DISPLAY_4_BIT_INIT       (0x02u)
#define LCD_DISPLAY_CURSOR_OFF       (0x08u)
#define LCD_CLEAR_DISPLAY            (0x01u)
#define LCD_CURSOR_AUTO_INCR_ON      (0x06u)
#define LCD_DISPLAY_CURSOR_ON        (0x0Eu)
#define LCD_DISPLAY_2_LINES_5x10     (0x2Cu)
#define LCD_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define LCD_RESET_CURSOR_POSITION    (0x03u)
#define LCD_CURSOR_WINK              (0x0Du)
#define LCD_CURSOR_BLINK             (0x0Fu)
#define LCD_CURSOR_SH_LEFT           (0x10u)
#define LCD_CURSOR_SH_RIGHT          (0x14u)
#define LCD_DISPLAY_SCRL_LEFT        (0x18u)
#define LCD_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define LCD_CURSOR_HOME              (0x02u)
#define LCD_CURSOR_LEFT              (0x04u)
#define LCD_CURSOR_RIGHT             (0x06u)

/* Nibble Offset and Mask */
#define LCD_NIBBLE_SHIFT             (0x04u)
#define LCD_NIBBLE_MASK              (0x0Fu)

/* STM32 16-bit GPIO port defines (shift and mask) for DB4-DB7 */
/* for IAR KickStart kit pinout ... DB4 : DB7 = LL_GPIO_PIN_0 : LL_GPIO_PIN_3 */
#define LCD_STM32_NIBBLE_SHIFT		 (0u)
#define LCD_STM32_NIBBLE_MASK        (0x000Fu)

/* LCD Module Address Constants */
#define LCD_ROW_0_START              (0x80u)
#define LCD_ROW_1_START              (0xC0u)
#define LCD_ROW_2_START              (0x94u)
#define LCD_ROW_3_START              (0xD4u)

/* Point to Character Generator Ram 0 */
#define LCD_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define LCD_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define LCD_CHARACTER_WIDTH          (0x05u)
#define LCD_CHARACTER_HEIGHT         (0x08u)


/* SHIFT must be 1 or 0 */
#if (0 == LCD_LCDPort__SHIFT)
    #define LCD_PORT_SHIFT               (0x00u)
#else
    #define LCD_PORT_SHIFT               (0x01u)
#endif /* (0 == LCD_LCDPort__SHIFT) */

/* Other constants */
#define LCD_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define LCD_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define LCD_U16_UPPER_BYTE_SHIFT     (0x08u)
#define LCD_U16_LOWER_BYTE_MASK      (0xFFu)
#define LCD_CUSTOM_CHAR_SET_LEN      (0x40u)

#define LCD_NUMBER_OF_REMAINDERS_U32 (0x0Au)
#define LCD_TEN                      (0x0Au)
#define LCD_8_BIT_SHIFT              (8u)
#define LCD_32_BIT_SHIFT             (32u)
#define LCD_ZERO_CHAR_ASCII          (48u)

#define LCD_LONGEST_CMD_US           (0x651u)
#define LCD_WAIT_CYCLE               (0x10u)
#define LCD_READY_DELAY              ((LCD_LONGEST_CMD_US * 4u)/(LCD_WAIT_CYCLE))

#define LCD_READY_BIT				 (0x08u)


#endif /* INC_LCD_H_ */
