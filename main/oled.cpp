#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(
    U8G2_R0,
    /* clock=*/22,
    /* data=*/21,
    /* reset=*/U8X8_PIN_NONE);

void setup(void)
{
  u8g2.begin();
  u8g2.enableUTF8Print(); // 中文必要设置
}

uint8_t z_y = 20;
uint8_t z_x = 0;

void loop(void)
{
  u8g2.setFont(u8g2_font_unifont_t_chinese2); // 含有中文的字库
  // u8g2.setFont(u8g2_font_ncenB14_tr);          //没有中文的字库
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(z_x, z_y); // 动态改变位置
    u8g2.print("你好,世界!"); // 中文
    u8g2.setCursor(10, 40);
    u8g2.print("Hello,world!"); // 普通英文
  } while (u8g2.nextPage());
}