#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <string>

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(
    U8G2_R0,
    /* clock=*/22,
    /* data=*/21,
    /* reset=*/U8X8_PIN_NONE);

const char *ssid = "浮生阁2.4";
const char *password = "18216548093";
const char *ntpServer = "pool.ntp.org";
const long utcOffsetInSeconds = 28800; // Beijing: UTC +8  -- 获取东八区时间(默认以英国格林威治天文台所在地的本初子午线为基准线的)

String getTime(time_t *now, String format = "%Y-%m-%d %H:%M")
{
  char tmp[64];
  const char *cStr = format.c_str();
  strftime(tmp, sizeof(tmp), cStr, localtime(now));
  return tmp;
}

String int_to_string(int s)
{
  char buffer[20];
  return itoa(s, buffer, 10);
}

void display(String text, uint8_t x = 0, uint8_t y = 20)
{
  u8g2.setFont(u8g2_font_unifont_t_chinese2); // 含有中文的字库
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(x, y); // 动态改变位置
    u8g2.print(text);     // 中文
  } while (u8g2.nextPage());
}

void displayTime(String day, String week)
{
  u8g2.setFont(u8g2_font_unifont_t_chinese2); // 含有中文的字库
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(0, 20); // 动态改变位置
    u8g2.print(day);       // 中文
    u8g2.setCursor(0, 40); // 动态改变位置
    u8g2.print(week);      // 中文
  } while (u8g2.nextPage());
}

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print(); // 中文必要设置
  int s = u8g2.getWidth();
  // 连接wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    display("connect wifi");
  }
  display("wifi ok!");
  // 获取时间
  configTime(utcOffsetInSeconds, 0, ntpServer);
  while (!time(nullptr))
  {
    delay(1000);
    display("time sync");
  }
  display("time sync ok!");
}

void loop()
{
  time_t now = time(nullptr);
  displayTime(getTime(&now), getTime(&now, "%A")); // 打印时间
  delay(1000);
}
