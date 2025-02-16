#include <Arduino_JSON.h>

#include <ArduinoHttpClient.h>

#include <WiFi.h>

#include <String.h>

//ordinea ledurilor 13,23,25,26,27,32,33

char* ssid = "B100";
char* password = "";

String ora[10];

uint16_t nr[20][20] = {
{1, 1, 1, 1, 1, 1, 0, 0},  
{0, 1, 1, 0, 0, 0, 0, 0},  
{1, 1, 0, 1, 1, 0, 1, 0},  
{1, 1, 1, 1, 0, 0, 1, 0}, 
{0, 1, 1, 0, 0, 1, 1, 0},  
{1, 0, 1, 1, 0, 1, 1, 0},  
{1, 0, 1, 1, 1, 1, 1, 0},  
{1, 1, 1, 0, 0, 0, 0, 0},  
{1, 1, 1, 1, 1, 1, 1, 0},  
{1, 1, 1, 1, 0, 1, 1, 0},  
};
void stingereLeduri()
{
  digitalWrite(13, LOW);
  digitalWrite(23, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
}
void aprindereLeduri(int i)
{
  if(i==0)
    digitalWrite(13, HIGH);
  if(i==1)
    digitalWrite(23, HIGH);
  if(i==2)
    digitalWrite(25, HIGH);
  if(i==3)
    digitalWrite(26, HIGH);
  if(i==4)
    digitalWrite(27, HIGH);
  if(i==5)
    digitalWrite(32, HIGH);
  if(i==6)
    digitalWrite(33, HIGH);
}
void displayInchis()
{
  digitalWrite(2, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(4, 0);
  digitalWrite(16, 0);
  digitalWrite(17, 0);
  digitalWrite(5, 0);
  digitalWrite(18, 0);
  digitalWrite(19, 0);
  digitalWrite(21, 0);
  digitalWrite(22, 0);
  delay(5);
  digitalWrite(2, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(4, 0);
  digitalWrite(16, 0);
  digitalWrite(17, 0);
  digitalWrite(5, 0);
  digitalWrite(18, 0);
  digitalWrite(19, 0);
  digitalWrite(21, 0);
  digitalWrite(22, 0);
  delay(5);
  digitalWrite(15, LOW);
}
void afisareOre(String a)
{
  char caracter_1 = a.charAt(0);  
  char caracter_2 = a.charAt(1); 
  digitalWrite(2, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(4, nr[String(caracter_1).toInt()][0]);
  digitalWrite(16, nr[String(caracter_1).toInt()][1]);
  digitalWrite(17, nr[String(caracter_1).toInt()][2]);
  digitalWrite(5, nr[String(caracter_1).toInt()][3]);
  digitalWrite(18, nr[String(caracter_1).toInt()][4]);
  digitalWrite(19, nr[String(caracter_1).toInt()][5]);
  digitalWrite(21, nr[String(caracter_1).toInt()][6]);
  digitalWrite(22, nr[String(caracter_1).toInt()][7]);
  delay(5);
  digitalWrite(2, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(4, nr[String(caracter_2).toInt()][0]);
  digitalWrite(16, nr[String(caracter_2).toInt()][1]);
  digitalWrite(17, nr[String(caracter_2).toInt()][2]);
  digitalWrite(5, nr[String(caracter_2).toInt()][3]);
  digitalWrite(18, nr[String(caracter_2).toInt()][4]);
  digitalWrite(19, nr[String(caracter_2).toInt()][5]);
  digitalWrite(21, nr[String(caracter_2).toInt()][6]);
  digitalWrite(22, nr[String(caracter_2).toInt()][7]);
  delay(5);
  digitalWrite(15, LOW);
}

void prelucrare(String aux)
{
  char caracter1 = aux.charAt(0);  
  char caracter2 = aux.charAt(1); 
  char caracter3 = aux.charAt(2); 
  char caracter4 = aux.charAt(3); 
  char caracter5 = aux.charAt(4);  
  unsigned long timp2=millis();
  while(millis() - timp2 < 4500)
  {
    unsigned long timp = millis();
    while (millis() - timp < 2000)
      afisareOre(String(caracter1) + String(caracter2));
    unsigned long timp3=millis();
    while(millis() - timp3 < 2000)
    {
      timp = millis();
      while (millis() - timp < 500)
        afisareOre(String(caracter4) + String(caracter5));
      timp = millis();
      while (millis() - timp < 500)
        displayInchis();
    }
  }
}
void setup() {
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("PIA - Echipa 511");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
  }
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.RSSI());
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    String url = "https://api.open-meteo.com/v1/forecast?latitude=44.43&longitude=26.14&timezone=auto&current_weather=true&daily=sunrise";

    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) 
    {
      String payload = http.getString();
      //Serial.println(payload);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);
      JsonArray vectorSun = doc["daily"]["sunrise"];
      for (size_t i = 0; i < vectorSun.size(); i++)
      {
        String  V = vectorSun[i].as<String>();
        ora[i] = V.substring(V.length() - 5);
        if(i<vectorSun.size()-1)
        {
          Serial.print(ora[i]);
          Serial.print("-");
        }
        else
          Serial.print(ora[i]);
      }   
   }
   http.end();
  }
  Serial.println();
  int i=0;
  int n=7;
  for(i=0;i<n;i++)
  {
    Serial.print("Z");Serial.print(i+1);Serial.print(" - ");Serial.println(ora[i]);
    aprindereLeduri(i);
    prelucrare(ora[i]);
  }
  stingereLeduri();
}
  
void loop() 
{
  
}
