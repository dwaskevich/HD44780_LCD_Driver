/*
 * LCD.c
 *
 *  Created on: Aug 25, 2024
 *      Author: dwask
 */
#include "main.h"
#include "LCD.h"

static void LCD_WrDatNib(uint8_t nibble) ;
static void LCD_WrCntrlNib(uint8_t nibble) ;

/* Stores state of component. Indicates whether component is or not
* in enable state.
*/
uint8_t LCD_enableState = 0u;

uint8_t LCD_initVar = 0u;

/*******************************************************************************
* Function Name: LCD_Init
********************************************************************************
*
* Summary:
*  Performs initialization required for the components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enables a 4-bit interface
*        Clears the display
*        Enables the auto cursor increment
*        Resets the cursor to start position
*  Also, it loads a custom character set to the LCD if it was defined in the customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Init(void)
{
    /* INIT CODE */
    HAL_Delay(40);                             /* Delay 40 ms */
    LCD_WrCntrlNib(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    HAL_Delay(5u);                             /* Delay 5 ms */
    LCD_WrCntrlNib(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    HAL_Delay(15u);                            /* Delay 15 ms */
    LCD_WrCntrlNib(LCD_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    HAL_Delay(1u);                             /* Delay 1 ms */
    LCD_WrCntrlNib(LCD_DISPLAY_4_BIT_INIT);    /* Selects 4-bit mode */
    HAL_Delay(5u);                             /* Delay 5 ms */

    LCD_WriteControl(LCD_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    LCD_WriteControl(LCD_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    LCD_WriteControl(LCD_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    LCD_WriteControl(LCD_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    LCD_WriteControl(LCD_CLEAR_DISPLAY);          /* Clear LCD Screen */
    LCD_WriteControl(LCD_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    LCD_WriteControl(LCD_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    HAL_Delay(5u);

    #if(LCD_CUSTOM_CHAR_SET != LCD_NONE)
        LCD_LoadCustomFonts(LCD_customFonts);
    #endif /* LCD_CUSTOM_CHAR_SET != LCD_NONE */
}


/*******************************************************************************
* Function Name: LCD_Enable
********************************************************************************
*
* Summary:
*  Turns on the display.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
* Theory:
*  This function has no effect when it is called the first time as
*  LCD_Init() turns on the LCD.
*
*******************************************************************************/
void LCD_Enable(void)
{
    LCD_DisplayOn();
    LCD_enableState = 1u;
}

/*******************************************************************************
* Function Name: LCD_Start
********************************************************************************
*
* Summary:
*  Performs initialization required for the components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enables 4-bit interface
*        Clears the display
*        Enables auto cursor increment
*        Resets the cursor to start position
*  Also, it loads a custom character set to the LCD if it was defined in the customizer.
*  If it was not the first call in this project, then it just turns on the
*  display
*
*
* Parameters:
*  LCD_initVar - global variable.
*
* Return:
*  LCD_initVar - global variable.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Start(void)
{
    /* If not initialized, perform initialization */
    if(LCD_initVar == 0u)
    {
        LCD_Init();
        LCD_initVar = 1u;
    }

    /* Turn on the LCD */
    LCD_Enable();
}


/*******************************************************************************
*  Function Name: LCD_WriteData
********************************************************************************
*
* Summary:
*  Writes a data byte to the LCD module's Data Display RAM.
*
* Parameters:
*  dByte: Byte to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_WriteData(uint8_t dByte)
{
    uint8_t nibble;

//    LCD_IsReady();
    delay_us(1000);

    nibble = dByte >> LCD_NIBBLE_SHIFT;

    /* Write high nibble */
    LCD_WrDatNib(nibble);

    nibble = dByte & LCD_NIBBLE_MASK;
    /* Write low nibble */
    LCD_WrDatNib(nibble);
}


/*******************************************************************************
*  Function Name: LCD_WriteControl
********************************************************************************
*
* Summary:
*  Writes a command byte to the LCD module.
*
* Parameters:
*  cByte:  The byte to be written to theLCD module
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_WriteControl(uint8_t cByte)
{
    uint8_t nibble;

//    LCD_IsReady();
    delay_us(1000);

    nibble = cByte >> LCD_NIBBLE_SHIFT;

    /* WrCntrlNib(High Nibble) */
    LCD_WrCntrlNib(nibble);
    nibble = cByte & LCD_NIBBLE_MASK;

    /* WrCntrlNib(Low Nibble) */
    LCD_WrCntrlNib(nibble);
}



/*******************************************************************************
*  Function Name: LCD_WrDatNib
********************************************************************************
*
* Summary:
*  Writes a data nibble to the LCD module.
*
* Parameters:
*  nibble:  Byte containing nibble in the least significant nibble to be
*           written to the LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
static void LCD_WrDatNib(uint8_t nibble)
{
	uint16_t gpioPortData;

    /* RS should be high to select data register */
	LL_GPIO_SetOutputPin(RS_GPIO_Port, RS_Pin);
//	HAL_GPIO_WritePin(RS_djjw_GPIO_Port, RS_djjw_Pin, 1);
//    LCD_PORT_DR_REG |= LCD_RS;
    /* Reset RW for write operation */
	LL_GPIO_ResetOutputPin(RnW_GPIO_Port, RnW_Pin);
//	HAL_GPIO_WritePin(RnW_djjw_GPIO_Port, RnW_djjw_Pin, 0);
//    LCD_PORT_DR_REG &= ((uint8_t)(~LCD_RW));

    /* Guaranteed delay between Setting RS and RW and setting E bits */
    delay_us(2u);

    /* Clear data pins, write nibble data */
//    LCD_PORT_DR_REG &= ((uint8_t)(~LCD_DATA_MASK));
	gpioPortData = (uint16_t) LL_GPIO_ReadOutputPort(DB4_GPIO_Port);
	gpioPortData &= ~(uint16_t) LCD_NIBBLE_MASK;
	gpioPortData |= (uint16_t) (nibble & LCD_NIBBLE_MASK);
	LL_GPIO_WriteOutputPort(DB4_GPIO_Port, (uint32_t) gpioPortData);

    /* , bring E high */
	LL_GPIO_SetOutputPin(E_GPIO_Port, E_Pin);
//	HAL_GPIO_WritePin(E_djjw_GPIO_Port, E_djjw_Pin, 1);
//    #if(0u != LCD_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
//        LCD_PORT_DR_REG |=
//            (LCD_E | ((uint8_t)(((uint8_t) nibble) << LCD_PORT_SHIFT)));
//    #else
//        LCD_PORT_DR_REG |= (LCD_E | nibble);
//    #endif /* (0u != LCD_PORT_SHIFT) */

    /* Minimum of 230 ns delay */
	delay_us(1u);

	/* , bring E low */
//    LCD_PORT_DR_REG &= ((uint8_t)(~LCD_E));
	LL_GPIO_ResetOutputPin(E_GPIO_Port, E_Pin);
//    HAL_GPIO_WritePin(E_djjw_GPIO_Port, E_djjw_Pin, 0);
}


/*******************************************************************************
*  Function Name: LCD_WrCntrlNib
********************************************************************************
*
* Summary:
*  Writes a control nibble to the LCD module.
*
* Parameters:
*  nibble: The byte containing a nibble in the four least significant bits.????
*
* Return:
*  None.
*
*******************************************************************************/
static void LCD_WrCntrlNib(uint8_t nibble)
{
	uint16_t gpioPortData;

    /* RS and RW should be low to select instruction register and write operation respectively */
//    LCD_PORT_DR_REG &= ((uint8_t)(~(LCD_RS | LCD_RW)));
	LL_GPIO_ResetOutputPin(RS_GPIO_Port, RS_Pin);
//    HAL_GPIO_WritePin(RS_djjw_GPIO_Port, RS_djjw_Pin, 0);
	LL_GPIO_ResetOutputPin(RnW_GPIO_Port, RnW_Pin);
//    HAL_GPIO_WritePin(RnW_djjw_GPIO_Port, RnW_djjw_Pin, 0);

    /* Two following lines of code will give 40ns delay */
    /* Clear data pins */
//    LCD_PORT_DR_REG &= ((uint8_t)(~LCD_DATA_MASK));
    gpioPortData = (uint16_t) LL_GPIO_ReadOutputPort(DB4_GPIO_Port);
	gpioPortData &= ~(uint16_t) LCD_NIBBLE_MASK;
	gpioPortData |= (uint16_t) (nibble & LCD_NIBBLE_MASK);
	LL_GPIO_WriteOutputPort(DB4_GPIO_Port, (uint32_t) gpioPortData);

    /* Write control data and set enable signal */
	LL_GPIO_SetOutputPin(E_GPIO_Port, E_Pin);
//	HAL_GPIO_WritePin(E_djjw_GPIO_Port, E_djjw_Pin, 1);
//    #if(0u != LCD_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
//        LCD_PORT_DR_REG |=
//            (LCD_E | ((uint8_t)(((uint8_t) nibble) << LCD_PORT_SHIFT)));
//    #else
//        LCD_PORT_DR_REG |= (LCD_E | nibble);
//    #endif /* (0u != LCD_PORT_SHIFT) */


    /* Minimum of 230 ns delay */
    delay_us(1u);

//    LCD_PORT_DR_REG &= ((uint8_t)(~LCD_E));
    LL_GPIO_ResetOutputPin(E_GPIO_Port, E_Pin);
//    HAL_GPIO_WritePin(E_djjw_GPIO_Port, E_djjw_Pin, 0);
}

/*******************************************************************************
*  Function Name: LCD_Position
********************************************************************************
*
* Summary:
*  Moves the active cursor location to a point specified by the input arguments
*
* Parameters:
*  row:    Specific row of LCD module to be written
*  column: Column of LCD module to be written
*
* Return:
*  None.
*
* Note:
*  This only applies for LCD displays that use the 2X40 address mode.
*  In this case Row 2 starts with a 0x28 offset from Row 1.
*  When there are more than 2 rows, each row must be fewer than 20 characters.
*
*******************************************************************************/
void LCD_Position(uint8_t row, uint8_t column)
{
    switch (row)
    {
        case (uint8_t) 0:
            LCD_WriteControl(LCD_ROW_0_START + column);
            break;
        case (uint8_t) 1:
            LCD_WriteControl(LCD_ROW_1_START + column);
            break;
        case (uint8_t) 2:
            LCD_WriteControl(LCD_ROW_2_START + column);
            break;
        case (uint8_t) 3:
            LCD_WriteControl(LCD_ROW_3_START + column);
            break;
        default:
            /* if default case is hit, invalid row argument was passed.*/
            break;
    }
}


/*******************************************************************************
* Function Name: LCD_PrintString
********************************************************************************
*
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string: Pointer to head of char8 array to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PrintString(char const string[])
{
    uint8_t indexU8 = 1u;
    char current = *string;

    /* Until null is reached, print next character */
    while((char) '\0' != current)
    {
        LCD_WriteData((uint8_t)current);
        current = string[indexU8];
        indexU8++;
    }
}


/*******************************************************************************
*  Function Name: LCD_PutChar
********************************************************************************
*
* Summary:
*  Writes a single character to the current cursor position of the LCD module.
*  Custom character names (_CUSTOM_0 through
*  _CUSTOM_7) are acceptable as inputs.
*
* Parameters:
*  character: Character to be written to LCD
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PutChar(char character)
{
    LCD_WriteData((uint8_t)character);
}


/*******************************************************************************
*  Function Name: LCD_PrintInt8
********************************************************************************
*
* Summary:
*  Print a byte as two ASCII characters.
*
* Parameters:
*  value: The byte to be printed out as ASCII characters.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PrintInt8(uint8_t value)
{
    static char const LCD_hex[16u] = "0123456789ABCDEF";

    LCD_PutChar((char) LCD_hex[value >> LCD_BYTE_UPPER_NIBBLE_SHIFT]);
    LCD_PutChar((char) LCD_hex[value & LCD_BYTE_LOWER_NIBBLE_MASK]);
}


/*******************************************************************************
*  Function Name: LCD_PrintInt16
********************************************************************************
*
* Summary:
*  Print a uint16 as four ASCII characters.
*
* Parameters:
*  value: The uint16 to be printed out as ASCII characters.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PrintInt16(uint16_t value)
{
    LCD_PrintInt8((uint8_t)(value >> LCD_U16_UPPER_BYTE_SHIFT));
    LCD_PrintInt8((uint8_t)(value & LCD_U16_LOWER_BYTE_MASK));
}


/*******************************************************************************
*  Function Name: LCD_PrintInt32
********************************************************************************
*
* Summary:
*  Print a uint32 hexadecimal number as eight ASCII characters.
*
* Parameters:
*  value: The uint32 to be printed out as ASCII characters.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PrintInt32(uint32_t value)
{
    uint8_t shift = LCD_32_BIT_SHIFT;

    while (shift != 0u)
    {
        /* "shift" var is to be subtracted by 8 prior shifting. This implements
        * shifting by 24, 16, 8 and 0u.
        */
        shift -= LCD_8_BIT_SHIFT;

        /* Print 8 bits of uint32 hex number */
        LCD_PrintInt8((uint8_t) ((uint32_t) (value >> shift)));
    }
}


/*******************************************************************************
*  Function Name: LCD_PrintNumber
********************************************************************************
*
* Summary:
*  Print an uint16 value as a left-justified decimal value.
*
* Parameters:
*  value: A 16-bit value to be printed in ASCII characters as a decimal number
*
* Return:
*  None.
*
* Note:
*  This function is implemented as a macro.
*
*******************************************************************************/


/*******************************************************************************
*  Function Name: LCD_PrintU32Number
********************************************************************************
*
* Summary:
*  Print an uint32 value as a left-justified decimal value.
*
* Parameters:
*  value: A 32-bit value to be printed in ASCII characters as a decimal number
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_PrintU32Number(uint32_t value)
{
    uint8_t tmpDigit;
    char number[LCD_NUMBER_OF_REMAINDERS_U32 + 1u];
    uint8_t digIndex = LCD_NUMBER_OF_REMAINDERS_U32;

    /* This API will output a decimal number as a string and that string will be
    * filled from end to start. Set Null termination character first.
    */
    number[digIndex] = (char) '\0';
    digIndex--;

    /* Load these in reverse order */
    while(value >= LCD_TEN)
    {
        /* Extract decimal digit, indexed by 'digIndex', from 'value' and
        * convert it to ASCII character.
        */
        tmpDigit = (uint8_t) (((uint8_t) (value % LCD_TEN)) + (uint8_t) LCD_ZERO_CHAR_ASCII);

        /* Temporary variable 'tmpDigit' is used to avoid Violation of MISRA rule
        * #10.3.
        */
        number[digIndex] = (char) tmpDigit;
        value /= LCD_TEN;
        digIndex--;
    }

    /* Extract last decimal digit 'digIndex', from the 'value' and convert it
    * to ASCII character.
    */
    tmpDigit = (uint8_t) (((uint8_t)(value % LCD_TEN)) + (uint8_t) LCD_ZERO_CHAR_ASCII);
    number[digIndex] = (char) tmpDigit;

    /* Print out number */
    LCD_PrintString(&number[digIndex]);
}



