#include "lcd.h"
#include "string.h"

SSD1306_t dev;
int center, top, bottom;
char lineChar[20];

void lcd_init()
{
    top = 2;
    center = 3;
    bottom = 8;
    spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 0xff);
}

void lcd_print(char *text, int page)
{
    ssd1306_display_text(&dev, page, text, strlen(text), false);
}

void lcd_clear()
{
    ssd1306_clear_screen(&dev, false);
}