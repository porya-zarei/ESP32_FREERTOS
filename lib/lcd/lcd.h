#include "ssd1306.h"
#include "font8x8_basic.h"

#define CONFIG_MOSI_GPIO 23
#define CONFIG_SCLK_GPIO 18
#define CONFIG_CS_GPIO 5
#define CONFIG_DC_GPIO 16
#define CONFIG_RESET_GPIO 17

void lcd_init();
void lcd_print(char *text, int page);
void lcd_clear();