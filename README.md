# HD44780_LCD_Driver
Hitachi HD44780-based LCD driver/library

Description: Hitachi HD44780-based LCD driver/library (adapted/ported from Cypress PSoC Creator v2.20 LCD component).

Hardware: Tested on IAR-STM32-SK Kickstart Kit (STM32F103RBTx) with 2-line 40-character LCD module.

https://www.digikey.com/en/products/detail/stmicroelectronics/STM3210B-SK-IAR/1646326?s=N4IgTCBcDaIMoBUCyBmMBGADAIQLRwGkB6ASQEEAlEAXQF8g


IDE:	STM32CubeIDE Version 1.16.0

GPIO:	Low level driver - STM32F1xx_LL_Driver (CubeMX Advanced Settings)

Wiring:	4-bit nibble-mode parallel data bus to display (upper nibble):

	DB[7:4] - GPIOC[3:0]
 
	RS (Register Select) - GPIOC_8 (0 = command, 1 = data)
 
	R/nW (Read/~Write) - GPIOC_9
 
	E (Clock Enable) - GPIOC_12 (falling edge triggered)
 
	Backlight - GPIOB_0 (1 = ON, 0 = OFF)

 
