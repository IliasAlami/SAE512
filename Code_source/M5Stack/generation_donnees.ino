#include <M5Stack.h>

bool voletsOuverts = true;



void setup() {

  M5.begin();

  Serial.begin(115200);

  M5.Lcd.clear();

  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(10, 10);

  M5.Lcd.println("Simulation des donnees...");



}



void loop() {



  if (M5.BtnA.wasPressed()) {

    voletsOuverts = false;

    Serial.println("Les volets sont fermés.");

    M5.Lcd.clear();

    M5.Lcd.setCursor(10, 10);

    M5.Lcd.println("Les volets sont fermes.");

  }



  if (M5.BtnB.wasPressed()) {

    voletsOuverts = true;

    Serial.println("Les volets sont ouverts.");

    M5.Lcd.clear();

    M5.Lcd.setCursor(10, 10);

    M5.Lcd.println("Les volets sont ouverts.");

  }



  float temperature = random(0, 40);

  int luminosite = random(10, 1000);



  Serial.printf("Température: %.2f°C, Luminosité: %d lux\n", temperature, luminosite);



  M5.Lcd.setCursor(10, 30);

  M5.Lcd.printf("Temperature: %.2f C", temperature);

  M5.Lcd.setCursor(10, 60);

  M5.Lcd.printf("Luminosite: %d lux", luminosite);





  if (temperature < 10.0) {

    Serial.println("ALERTE : Température trop basse !");

    M5.Lcd.setTextColor(TFT_RED, TFT_BLACK);

    M5.Lcd.setCursor(10, 100);

    M5.Lcd.print("ALERTE : T < 10C");

    M5.Speaker.tone(1000, 200);

    delay(200);

    M5.Speaker.mute();

  } else {

    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  }

  delay(10000);

}