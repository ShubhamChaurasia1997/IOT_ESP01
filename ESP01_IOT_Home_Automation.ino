#include <ESP8266WiFi.h>
#include<PubSubClient.h>

const char* mqtt_server="54.83.102.107";
WiFiClient espclient;
void callback(char* topic, byte* payload, unsigned int length);
PubSubClient client(mqtt_server,1883,callback,espclient);


void setup() {
  
   pinMode(0,OUTPUT);
  Serial.begin(115200);
  Serial.print("connecting");
  WiFi.begin("Temporary","12345678");         //SSID,PASSWORD 
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  reconnect();

}


void callback(char* topic,byte* payload,unsigned int length1){    
Serial.print("message arrived[");
Serial.print(topic);
Serial.println("]");

for(int i=0;i<length1;i++){
  Serial.print(payload[i]); 
  
}
if(payload[0]==49) digitalWrite(0,HIGH);    //ASCII VALUE OF '1' IS 49
else if(payload[0]==50)digitalWrite(0,LOW);//ASCII VALUE OF '2' IS 50
Serial.println();
}


void reconnect(){
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  while(!client.connected()){
  if(client.connect("ESP8266Client123456789")){
    Serial.println("connected");
    client.subscribe("ledcontrol");
  }
    else{
      Serial.print("failed,rc=");
      Serial.println(client.state());
      delay(500);
    }
  } 
}
void loop() {
    if(!client.connected()){
      reconnect();
    }
    
    client.loop();

}
