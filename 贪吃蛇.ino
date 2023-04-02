#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // 导入库函数

#define UP_PIN 5  // 上方向键引脚 
#define DOWN_PIN 9  // 下方向键引脚 
#define LEFT_PIN 13  // 左方向键引脚 
#define RIGHT_PIN 8  // 右方向键引脚 

#define LCD_BL               11       //定义LCD的针脚
#define LCD_CS                7
#define LCD_DC                6
#define LCD_RES              10
#define LCD_SDA               3
#define LCD_SCLK              2 
#define LCD_LD               30       //背光亮度百分比0-100%

//Adafruit_ST7735 tft = Adafruit_ST7735(A4, 13);  // 指定LCD屏幕引脚 
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS,LCD_DC,LCD_SDA,LCD_SCLK,LCD_RES);  

int x = 0, y = 0;  // 控制恐龙初始位置 
int dir = 0;  // 控制方向 0-右,1-上,2-左,3-下 
int score = 0;  // 游戏分数 
int obstacle[][10] = { 
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 第一行 
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},  // 第二行 
  {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},  // 第三行 
  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 第四行 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // 第五行 
  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0}  // 第六行 
}; 

void setup() { 
  pinMode(UP_PIN, INPUT); 
  pinMode(DOWN_PIN, INPUT); 
  pinMode(LEFT_PIN, INPUT); 
  pinMode(RIGHT_PIN, INPUT); 
  
  tft.initR(INITR_BLACKTAB);  // 配置并确定LCD屏幕 
  tft.fillScreen(ST7735_BLACK);  // 清空屏幕 

} 

void loop() { 
  if (digitalRead(UP_PIN) == HIGH && dir != 1) dir = 1;  // 上方向键按下 
  if (digitalRead(DOWN_PIN) == HIGH && dir != 3) dir = 3;  // 下方向键按下 
  if (digitalRead(LEFT_PIN) == HIGH && dir != 2) dir = 2;  // 左方向键按下 
  if (digitalRead(RIGHT_PIN) == HIGH && dir != 0) dir = 0;  // 右方向键按下 
  
  tft.fillCircle(x, y, 10, ST7735_GREEN);  // 清除原来的恐龙 
  
  switch(dir) { 
    case 0: x += 1; break;  // 右方向移 
    case 1: y -= 1; break;  // 上方向移 
    case 2: x -= 1; break;  // 左方向移 
    case 3: y += 1; break;  // 下方向移 
  } 
  
  if (obstacle[x][y] == 1) {}  // 如果移到障碍物,继续原来位置 
  else { 
    tft.drawCircle(x, y, 10, ST7735_GREEN);  // 画新的位置的恐龙 
    obstacle[x][y] = 1;  // 将恐龙位置设为障碍物 
    score++;  // 分数加一 
  } 
}
