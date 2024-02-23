/*

30 minutes work, 6 minutes rest, 30 minutes work, 6 minutes rest, 30 minutes work, 6 minutes rest ...

Timer start from 29 minutes 59 seconds, when the countdown hits 0 minutes, 15 second
start buzzer and flash led until  countdown hits 0 minutes, 1 second. 
After, timer switch to 5 minutes 59 seconds, when the countdown hits 0 minutes, 15 second
start buzzer and flash led until  countdown hits 0 minutes, 1 second. 
And starts over.

Buttons can manualy set 30 minutes and 6 minutes timer.

*/


#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


boolean button1WasUp = true;      // переменные для считывания нажатий кнопок
boolean button2WasUp = true;
 

int TIMER_1 = 5;  // minutes + 1 minute
int TIMER_2 = 30; // minutes  + 1 minute
int CUSTOM_TIMER = 2; // minutes  выбор таймера вручную кнопкой ()

// переменные для отсчета минут и секунд
int SEC = 60;       // выводим на экран при старте
int MIN = TIMER_2;  // выводим на экран при старте
unsigned long timer;
const int buzzer = 11; //buzzer to arduino pin 11
int SWITCH_BETWEEN_MODES = 1;
int BUZZER_SOUND_INTERVAL = 15; // secunds


void setup() {

   pinMode(2, INPUT_PULLUP);   // подключаем тактовые кнопки
   pinMode(3, INPUT_PULLUP);
   pinMode(4, OUTPUT);
  timer = millis();
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

    // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Uncomment this if you are using SPI
  //if(!display.begin(SSD1306_SWITCHCAPVCC)) {
  //  Serial.println(F("SSD1306 allocation failed"));
  //  for(;;); // Don't proceed, loop forever
  //}

  // Clear the buffer.
  display.clearDisplay();
}

void loop() {

 
   boolean button1IsUp = digitalRead(2);   // узнаем текущее состояние кнопок
   boolean button2IsUp = digitalRead(3);

  display.setFont(&FreeSerif9pt7b);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 40);

   // при нажатии на первую кнопку вычитаем минуту и выводим на дисплей
   if (button1WasUp && !button1IsUp) {
      delay(10);
      button1IsUp = digitalRead(2);
      if (!button1IsUp) {
        MIN = TIMER_2; // 29 minutes
        SEC = 59;
        SWITCH_BETWEEN_MODES = 1;
        display.println(String(MIN+1)+" min");
        display.display();
        delay(200);
      }
   } 
   button1WasUp = button1IsUp; // запоминаем состояние кнопки 1 

   // при нажатии на вторую кнопку прибавляем минуту и выводим на дисплей
   if (button2WasUp && !button2IsUp) {
      delay(10); 
      button2IsUp = digitalRead(3); 
      if (!button2IsUp && CUSTOM_TIMER == 2) { 
        CUSTOM_TIMER = 5;
        //TIMER_1 = CUSTOM_TIMER;
        MIN = CUSTOM_TIMER; // 5 minutes
        SEC = 59;
        SWITCH_BETWEEN_MODES = 0;
        display.println(String(MIN+1)+" minn");
        display.display();
        //delay(200);
      }
      // устанавливаем вручную таймер на 2 минуты
      else if (!button2IsUp && CUSTOM_TIMER == 5) {
        CUSTOM_TIMER = 2;
        TIMER_1 = CUSTOM_TIMER;
        MIN = TIMER_1; // 2 minutes
        SEC = 59;
        SWITCH_BETWEEN_MODES = 0;
        display.println(String(MIN+1)+" min");
        display.display();
        //delay(200);
      }
    
   } 
   button2WasUp = button2IsUp; // запоминаем состояние кнопки 2 



  if (millis() - timer > 1000) {

    timer = millis();
    SEC = SEC - 1;

    if (SEC < 1) {
      SEC = 59;
      MIN = MIN - 1;
    }

    // выводим текущий счетчик времени на монитор порта


    display.println(String(MIN) + " : " + String(SEC));
    display.display();



    // Включение сигнала по истечении 30 минут
    // Если MIN = 0 SEC = интервалу в 10 секунд, подать звуковой сигнал в течении 10 секунд
    // Если SEC есть в интервале constrain  50 <--> 59

    // установка таймера после 30  минут на 5 минут
    if ( (MIN == 0) and (SEC == constrain(SEC, 1, BUZZER_SOUND_INTERVAL) and (SWITCH_BETWEEN_MODES == 1)   ) ) {

      mcu_scoreTone();

      if ( (MIN == 0) and (SEC == 1) ) {

        SWITCH_BETWEEN_MODES = 0;
        MIN = TIMER_1; // Установка таймера на 6 минут
        SEC = 60;

      }
    }

    // сигнал таймера после 5 минут
    // установка таймера после 5 минут на 30 минут
    if ( (MIN == 0) and  (SEC == constrain(SEC, 1, BUZZER_SOUND_INTERVAL) and (SWITCH_BETWEEN_MODES == 0)   ) ) {
      mcu_scoreTone();

      if ( (MIN == 0) and (SEC == 1) ) {

        SWITCH_BETWEEN_MODES = 1;
        MIN = TIMER_2; // Установка таймера на 30 минут 
        SEC = 60;

      }
    }
  }

}








void mcu_scoreTone()
{
  tone(buzzer, 250, 25);
  digitalWrite(4, HIGH); 
  delay(250);
  noTone(buzzer);
  delay(250);
  tone(buzzer, 200, 25);
  digitalWrite(4, LOW); 
  delay(250);
  noTone(buzzer);
  tone(buzzer, 225, 25);
  digitalWrite(4, HIGH); 
  delay(250);
  noTone(buzzer);
  digitalWrite(4, LOW);
}
