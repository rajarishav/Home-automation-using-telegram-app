 /*******************************************************************
 *  Modified by Raja Rishav thakur ,https://www.facebook.com/profile.php?id=100008188006861
   follow my official page for more such type of projects https://www.facebook.com/yourselectronics/
 *  This code is modified to control a light and a fan using Relay
 *  An example of bot that receives commands and turns on and off  *
 *  an LED.                                                        *                                                               *
 *  written by Giacarlo Bacchio (Gianbacchio on Github)            *
 *  adapted by Brian Lough                                         
 *  *******************************************************************/

 #include <WiFi.h>
 #include <WiFiClientSecure.h>
 #include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "Rishav";     // your network SSID (name)
char password[] = "rajarishav"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1203588903:AAEsoARiAYh-NIZISFdLWRB"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

const int ledPin =13; // Bulb pin
int ledStatus = 0;
   const int fanPin =12; //Fan pin
   int fanStatus = 0;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "Lo") {
      digitalWrite(ledPin, HIGH);   // turn the Light on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }
                if (text == "Fo") {
                digitalWrite(fanPin, HIGH);   // turn the fan on (HIGH is the voltage level)
                fanStatus = 1;
                bot.sendMessage(chat_id, "Fan is ON", "");
                }

    

    if (text == "Lf") {
      ledStatus = 0;
      digitalWrite(ledPin, LOW);    // turn the light off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

                   if (text == "Ff") {
                   fanStatus = 0;
                   digitalWrite(fanPin, LOW);    // turn the fan off (LOW is the voltage level)
                   bot.sendMessage(chat_id, "Fan is OFF", "");
                   }

    if (text == "Status") {
      if(ledStatus){
        bot.sendMessage(chat_id, "Led is ON", "");
      } else {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }

       if(fanStatus){
        bot.sendMessage(chat_id, "Fan is ON", "");
      } else {
        bot.sendMessage(chat_id, "Fan is OFF", "");
      }
    }

    if (text == "Start") {
      String welcome = "Welcome to Telegram Bot , " + from_name + ".\n";
      welcome += "This is My Home.\n\n";
      welcome += "Lo : to switch the Led ON\n";
      welcome += "Lf : to switch the Led OFF\n";

      welcome += "Fo : to switch the Fan ON\n";
      welcome += "Ff : to switch the Fan OFF\n";
      
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup() {
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as light output.
  delay(10);
  digitalWrite(ledPin, LOW); //  initialize pin as off
        pinMode(fanPin, OUTPUT); // initialize digital ledPin as fan output.
        delay(10);
        digitalWrite(fanPin, LOW); // initialize pin as fan off
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
