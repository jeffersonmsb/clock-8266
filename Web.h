#ifndef Web_h
#define Web_h

#include <ESP8266WebServer.h>
#include "Light.h"
#include "Ldr.h"
#include "DHT.h"
#include "Filesystem.h"

class Web{
  private:
    String buf;
    ESP8266WebServer server;
    Light *light;
    Ldr *ldr;
    DHT *dht;
    Filesystem *filesystem;

  public:
    Web(Light *lightOut, Ldr *ldrOut, DHT *dhtOut, Filesystem *filesystemOut){
      ESP8266WebServer server(80);
      light = lightOut;
      ldr = ldrOut;
      dht = dhtOut;
      filesystem = filesystemOut;
    }

    void index() {

      if (server.arg("light")!= ""){
    		if(server.arg("light").toInt()){
    			light->on();
    		}else{
    			light->off();
    		}
    	}

      if (server.arg("lightIntensity")!= ""){
    	   light->setBrightness(server.arg("lightIntensity").toInt());
    	}

      if (server.arg("format")!= ""){
    		filesystem->format();
        filesystem->createFile("log");
        filesystem->createFile("alarmlog");
    	}

      buf = "";
    	buf += "<!DOCTYPE HTML>";
    	buf += "<meta http-equiv='Content-Type' name='viewport' content='width=device-width, initial-scale=1.0' charset='utf-8'>";
    	buf += "<title>Clock-8266</title>";
      buf += "<a href=\"/\">Início</a>";
      buf += " <a href=\"/log\">Main log</a>";
      buf += " <a href=\"/logsensors\">Sensors log</a>";
      buf += " <a href=\"/alarmlog\">Alarm log</a><br>";
      buf += "<h1>Clock-8266</h1>";
    	buf += "Tempo atual: " + String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" +String(minute()) + ":" + String(second()) + "<br>";
    	buf += "Ligado há " + String(millis()/1000) + " segundos.<br>";
    	buf += "Temperatura: " + String(dht->readTemperature()) + " °C<br>";
    	buf += "LDR: " + String(ldr->read());

    	buf += "<h3>Lâmpada</h3>";
    	buf += "<p><a href=\"?light=1\"><button>Ligar</button></a> <a href=\"?light=0\"><button>Desligar</button></a></p>";
    	if(light->state()){
    		buf += "Lâmpada acesa";
    	}else{
    		buf += "Lâmpada apagada";
    	}
    	/*buf += "<p><a href=\"?lightMode=1\"><button>Automático</button></a> <a href=\"?lightMode=0\"><button>Manual</button></a></p>";
    	if(lightMode==0){
    		buf += "Modo Manual";
    	}else{
    		buf += "Modo Automático";
    	}*/
    	buf += "<p><a href=\"?lightIntensity=50\"><button>Fraquinha</button></a> <a href=\"?lightIntensity=450\"><button>Meia bomba</button></a> <a href=\"?lightIntensity=1023\"><button>Estilo sol</button></a></p>";
    	if(light->readBrightness() == 50) buf += "Intesidade fraquinha";
    	if(light->readBrightness() == 450) buf += "Meia bomba";
    	if(light->readBrightness() == 1023) buf += "Estilo sol";

      buf += "<h3>Sistema de Arquivos</h3>";
      buf += "Espaço total: " + String(filesystem->info("totalBytes")) + " bytes<br>";
      buf += "Espaço usado: " + String(filesystem->info("usedBytes")) + " bytes<br>";
      buf += "<p><a href=\"?format=1\"><button>Formatar</button></a></p>";
      buf += "</html>";
      server.send(200, "text/html", buf);
    }

    void mainLog() {
      buf = "";
      buf += "<!DOCTYPE HTML>";
    	buf += "<meta http-equiv='Content-Type' name='viewport' content='width=device-width, initial-scale=1.0' charset='utf-8'>";
    	buf += "<title>Clock-8266</title>";
      buf += " <a href=\"/\">Início</a>";
      buf += " <a href=\"/log\">Main log</a>";
      buf += " <a href=\"/logsensors\">Sensors log</a>";
      buf += " <a href=\"/alarmlog\">Alarm log</a><br>";
      buf += "<h1>Clock-8266</h1>";
      buf += "Tempo atual: " + String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" +String(minute()) + ":" + String(second()) + "<br>";
      buf += "<h3>Main log</h3>";
      buf += "<p>";
      buf += filesystem->readFile("log");
      buf += "</p>";
      buf += "</html>\n";
      server.send(200, "text/html", buf);
    }

    void alarmLog() {
      buf = "";
      buf += "<!DOCTYPE HTML>";
    	buf += "<meta http-equiv='Content-Type' name='viewport' content='width=device-width, initial-scale=1.0' charset='utf-8'>";
    	buf += "<title>Clock-8266</title>";
      buf += " <a href=\"/\">Início</a>";
      buf += " <a href=\"/log\">Main log</a>";
      buf += " <a href=\"/logsensors\">Sensors log</a>";
      buf += " <a href=\"/alarmlog\">Alarm log</a><br>";
      buf += "<h1>Clock-8266</h1>";
      buf += "Tempo atual: " + String(day()) + "/" + String(month()) + "/" + String(year()) + " " + String(hour()) + ":" +String(minute()) + ":" + String(second()) + "<br>";
      buf += "<h3>Alarm log</h3>";
      buf += "<p>";
      buf += filesystem->readFile("alarmlog");
      buf += "</p>";
      buf += "</html>\n";
      server.send(200, "text/html", buf);
    }

    void begin(){
      //Que sacada louca esse std::bind(&Web::index, this) hahaha
      server.on("/", std::bind(&Web::index, this));
      server.on("/log", std::bind(&Web::mainLog, this));
      server.on("/alarmlog", std::bind(&Web::alarmLog, this));
      server.begin();
    }

    void run(){
      server.handleClient();
    }

};
#endif
