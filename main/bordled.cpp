#include <Arduino.h>

#define Pin 2 // 芯片原理图引脚号 G2(GPIO2), 故为2号管脚

void setup()
{
  // 将 D1 号引脚设置为输出模式
  pinMode(Pin, OUTPUT);
}

void loop()
{
  // 打开 LED 灯
  digitalWrite(Pin, HIGH);
  delay(1000);

  // 关闭 LED 灯
  digitalWrite(Pin, LOW);
  delay(2000);
}
