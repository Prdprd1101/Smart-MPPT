/*
 
struct tm 
{
   int tm_sec;         /* วินาที,     range 0 to 59         
   int tm_min;         /* นาที,      range 0 to 59           
   int tm_hour;        /* ชั่วโมง,    range 0 to 23              
   int tm_mday;        /* วันที่,      range 1 to 31   
   int tm_mon;         /* เดือน,     range 0 to 11             
   int tm_year;        /* ปีคริสศักราช ตั้งแต่ 1900    
   int tm_wday;        /* วัน,       range 0 to 6     
   int tm_yday;        /* วันใน 1 ปี, range 0 to 365   
   int tm_isdst;       /* daylight saving time            
};

*/



#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
WiFiClient   espClient;
PubSubClient client(espClient);                     

char  ssid[]             = "ppethh";           //Wifi user
char  password[]         = "123456789";           // Wifi password
const char* mqttserver   = "172.20.10.3";
const int   mqttPort     = 1883;
const char* mqttclient   = "1";             //กรณีมีบอร์ดหลายตัวจำเป็นต้องตั้งชื่อ client ให้แตกต่างกันเพื่อส่งไป mqtt
const char* mqttUser     = "konlawat";
const char* mqttPassword = "@Prdprd1101";
const char* Topic        = "test";             //ชื่อ topic ที่จะส่งไปยัง mqtt

////////////////////////////////////////////////////////

char ntp_server1[20] = "1.asia.pool.ntp.org";
char ntp_server2[20] = "1.th.pool.ntp.org";
char ntp_server3[20] = "time.navy.mi.th";

int  timezone = 7 * 3600;                     //timezone for Thailand is +7
int  dst = 0;

String  Month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char    daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 
String  Day,DATE1,DATE2,TIME,myIP,SignalStrength ;
int     Signal;


////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void Wificonnection()
{
  WiFi.begin(ssid, password);
  int count = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Wifi Connecting");
    client.setServer(mqttserver, mqttPort);
    while (!client.connected()) 
    {
      Serial.println("connecting mqtt");
      Serial.println(WiFi.status());
      if (client.connect(mqttclient, mqttUser, mqttPassword)) 
      {
        Serial.println("mqttconnect");
      } 
      else 
      {
        Serial.print("failed to connect");
        Serial.println(client.state());
        delay(2000);
      }
    }
    Serial.println("Connected");
  }
}

void TomqttVal(const char* Name, float value)     //Function นี้จะส่งข้อมูลทีละตัวเป็นไฟล์ json ไปยัง mqtt 
{
  StaticJsonDocument<300> tomqtt;
  tomqtt[Name] = value;
  char mqtt[100];
  serializeJsonPretty(tomqtt, mqtt);
  client.publish(Topic, mqtt);                    //(ชื่อ topic ที่จะส่งไปยัง mqtt, ชุดข้อมูล json ที่จะส่ง) โดยใน function นี้จะส่งข้อมูลทีละตัว
  serializeJsonPretty(tomqtt, Serial);
  Serial.println();
}

void TomqttMSG(const char* Name, String value)    //Function นี้จะส่งข้อมูลทีละตัวเป็นไฟล์ json ไปยัง mqtt 
{
  StaticJsonDocument<300> tomqtt;
  tomqtt[Name] = value;
  char mqtt[100];
  serializeJsonPretty(tomqtt, mqtt);
  client.publish(Topic, mqtt);                    //(ชื่อ topic ที่จะส่งไปยัง mqtt, ชุดข้อมูล json ที่จะส่ง) โดยใน function นี้จะส่งข้อมูลทีละตัว
  serializeJsonPretty(tomqtt, Serial);
  Serial.println();
}


/////////////////////////////////////////////

void setup() 
{
  Serial.begin(9600);

  Wificonnection();
  myIP = String (WiFi.localIP()); 
  configTime(timezone, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) 
  {
    Serial.print(".");
    delay(1000);
  }   
  Serial.println();     
}


void loop() 
{
  Serial.println("IP Address      : " + myIP);
  Signal  = WiFi.RSSI();
  SignalStrength = String(Signal) + " dBm";
  Serial.println("Signal Strength : "+ SignalStrength);  
  Serial.println(Day);
  Serial.println(DATE1);
  Serial.println(DATE2);
  Serial.println(TIME);
  Serial.println();
  
  if (WiFi.status() != WL_CONNECTED || !client.connected())
  {
    Wificonnection();
  }

  TomqttMSG("DD"    ,DATE1);
  TomqttMSG("TT"    ,TIME);
  TomqttVal("WiFI"  ,Signal);
  Serial.println("-----------------------------------");  
  Serial.println();
  delay(1000);
}












////////////////////////////////////////////////////////

String zero(byte num)
{
  if ( num<10 )
  { 
    return "0" + String(num);
  }
  else
  { 
    return String(num);
  }
}

String ipToString(IPAddress ip)
{
  String s="";
  for (int i=0; i<4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

////////////////////////////////////////////////////////

String TimeSync()
{
  int     h,m,s,md,mo,y,wd,yd;
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  h  = p_tm->tm_hour; 
  m  = p_tm->tm_min; 
  s  = p_tm->tm_sec;  
  md = p_tm->tm_mday; 
  mo = p_tm->tm_mon  + 1;
  y  = p_tm->tm_year + 1900;
  wd = p_tm->tm_wday;
  yd = p_tm->tm_yday;
  
  Day   = String(daysOfTheWeek[wd]); 
  DATE1 = String(md)+ " " + Month[mo-1] + " " + String(y);
  DATE2 = String(md)+ "/" + zero(mo)    + "/" + String(y);
  TIME  = zero(h) + ":" + zero(m) + ":" + zero(s);

  return DATE1 + "  " + TIME;
}




////////////////////////////////////////////////////////
