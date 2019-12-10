/*
 * Web-Controlled LIGHTS 
 * V1
 * 86kanth@gmail.com
 * Opensource
 */
 
#include <ESP8266WiFi.h>


const char* ssid        = "YOUR_WIFI_SSID_NAME";
const char* password    = "YOUR_WIFI_PASSWORD";

int ledPin        = 5;
int LED           = 5;
int state         = HIGH;
int brightness    = 1024; 
int fadeAmount    = 100; 
int done          = 1;
String Getstat    = "0";
int LED2          = 6;


WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  analogWrite(LED,714);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(NODE_NAME);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to control the light: http://");
  Serial.print(WiFi.localIP());

  analogWrite(LED,0);

}



//STEADY CONTROL SECTION  <<STARTS
void steady_on(int value){
 Serial.println("At Fucntion steady");
 if (value ==  0 ){ digitalWrite(LED,HIGH);}
 if (value ==  1 ){ digitalWrite(LED,LOW);} 
}
//STEADY CONTROL SECTION  <<OFF



//FADE CONTROL SECTION  <<STARTS
void fade_Control(int value){
 Serial.println("At function Fade");

 if (value == 0 ){ 

  Serial.println("10 % PWM");

  analogWrite(LED,1024);
  delay(500);

  Serial.println("20 % PWM");
  analogWrite(LED,714);
  delay(100);

  Serial.println("40 % PWM");
  analogWrite(LED,410);
  delay(100);

  Serial.println("70 % PWM");
  analogWrite(LED,205);
  delay(100);

  Serial.println("90 % PWM");
  analogWrite(LED,102);
  delay(100);

  Serial.println("100 % PWM");
  analogWrite(LED,0);
  delay(100);

}


if (value ==  1 ){ 


  Serial.println("10 % PWM");
  analogWrite(LED,102);
  delay(100);

  Serial.println("20 % PWM");
  analogWrite(LED,205);
  delay(100);

  Serial.println("40 % PWM");
  analogWrite(LED,410);
  delay(100);

  Serial.println("70 % PWM");
  analogWrite(LED,714);
  delay(100);

  Serial.println("100 % PWM");
  analogWrite(LED,1024);
  delay(100);
}    
}
//FADE CONTROL SECTION  <<ENDS



//FADE TIMER SECTION  <<STARTS
void fade_timer(){


  Serial.println("100 % PWM");
  analogWrite(LED,1024);
  delay(300000);


  Serial.println("20 % PWM");
  analogWrite(LED,714);
  delay(100);

  Serial.println("40 % PWM");
  analogWrite(LED,410);
  delay(100);

  Serial.println("70 % PWM");
  analogWrite(LED,205);
  delay(100);

  Serial.println("90 % PWM");
  analogWrite(LED,102);
  delay(100);


  Serial.println("100 % PWM");
  analogWrite(LED,0);
  delay(100);


  Serial.println("Fade Timer Off");
  
}

//FADE TIMER SECTION  <<ENDS

void loop()
{

  WiFiClient client = server.available();

  if (!client)
    return;

  while (client.connected() && !client.available())
    delay(1);

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


  if (request.indexOf("/LED=ON") != -1){
    state = 0;   }

    if (request.indexOf("/LED_TEMP=ON") != -1){
      state = 3;  }

      if (request.indexOf("/LED=OFF") != -1){
        state = 1;   }

        if (request.indexOf("/LED_STEADY=ON") != -1){
          state = 4;   }

          if (request.indexOf("/LED_STEADY=OFF") != -1){
            state = 5;   }



    // Change LED the state  STARTS
            if (state == 4 ){
             Serial.println("SteadyLight State to ON");
             steady_on(0);
             }

             if (state == 5 ){
              Serial.println("SteadyLight State to OFF");
              steady_on(1);
              }

              if (state == 0 ){
                Serial.println("LED to off");
                fade_Control(1);
                }

                if (state == 1 ){
                 Serial.println("LED to on");
                 fade_Control(0);
                 }

                  if (state == 3 ){
                   Serial.println("Fade Timer On");
                   fade_timer();
                   }
    // Change LED the state  ENDS
    
    
    
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html><head><title>WEBLight-Controller</title></head><body><style>body{color:white;background:black;}</style>");
    client.println("<style>.container{margin: auto 0;padding:10%;border-radius:15px 15px;}</style>");
    client.println("<div class='container' id='container'>");

    if (state == 0)
      client.print("<p>Led-Fader pin is now on.</p>");

      if (state == 3)
        client.print("<p>Led-Fader Limer light is on.</p>");

        if (state == 1)
          client.print("<p>Led-Fader is now off.</p>");

          if (state == 4)
            client.print("<p>Steady Led pin is now on.</p>");

            if (state == 5)
              client.print("<p>Steady Led pin is now off.</p>");


    client.println("</div>");
    client.println("</body></html>");
    delay(1);

  }
