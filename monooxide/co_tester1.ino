
// include the library code:
#include <LiquidCrystal.h>

int SPEAKER =  analogRead(A6);    // The speaker is on pin A6
int freq = 5000;      // Starting frequency

// переменная для хранения значения датчика
float sensor_volt;

float RS_gas;
float R0;
float PPM;
int R2 = 1000;
float ratio = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



// контакт подключения аналогового вывода MQ7
int analogMQ7 = A0;



// значение выше 231 ppm
int maxLevelforRoom = 10;

 


float ReadR0() {
  float sensorValue = analogRead(A0);
  sensor_volt = (float)sensorValue / 1024 * 5.0;
  RS_gas = ((5.0 * R2) / sensor_volt) - R2;
  R0 = RS_gas / 1;
  return R0;

}

float PPM_r(float i) {
  float sensorValue = analogRead(A0);
  sensor_volt = sensorValue / 1024 * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt;
  ratio = RS_gas / i; //Replace R0 with the value found using the sketch above
  float x = 1538.46 * ratio;
  float ppm = pow(x, -1.709);
  return ppm;


}




void setup() {
  pinMode(SPEAKER, OUTPUT);

  // Enable transistor switch
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  
  Serial.begin(9600);

  // время прогрева
  Serial.println("warming-up");
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("WARMING-UP 60sec");

  for (int i = 0; i < 60; i++)
  {
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    delay(1000);
  }
}

void loop() {

  R0 = ReadR0();
  PPM = PPM_r(R0);
 
  lcd.clear();
  lcd.print("Level CO:");
  if (PPM >= maxLevelforRoom) // превышение уровня
  {
    lcd.setCursor(0, 1);
    lcd.print(PPM);
    lcd.setCursor(4, 1);
    lcd.print("PPM !DANGER!");
    for (int i = 0; i < 5; i++)
    {
    tone(SPEAKER, 4000);
    delay(500);//wait for 2ms
    tone(SPEAKER, freq);
    delay(500);//wait for 2ms
    tone(SPEAKER, 3000);
    delay(500);//wait for 2ms
    tone(SPEAKER, freq);
    delay(500);//wait for 2ms
    
    noTone(SPEAKER);
    delay(2000);//wait for 2ms
      //tone(SPEAKER, freq);
      //delay(100);
      //freq = 500;
 
    }
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print(PPM);
    lcd.setCursor(4, 1);
    lcd.print("PPM");
  }

  // вывести значение в последовательный порт

  Serial.print("value = " );

  Serial.println(PPM, DEC);

  Serial.print("analog A0 = " );

  Serial.println(analogRead(A0));
  
  Serial.print("value R0 = " );

  Serial.println(R0);

  // пауза перед следующим измерением

  delay(3000);

}
