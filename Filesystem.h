#ifndef Filesystem_h
#define Filesystem_h

#include "FS.h"

class Filesystem{
  private:
      bool lightState;
      int bright;
      int pin;

  public:
    Filesystem(){
      if(!SPIFFS.begin()){
        //Serial.println("Erro ao abrir o sistema de arquivos");
      } else {
        //Serial.println("Sistema de arquivos aberto com sucesso!");
      }
    }

    void format(){
      SPIFFS.format();
    }

    void createFile(String fileName){
      File wFile;
      //Cria o arquivo se ele não existir
      if(SPIFFS.exists("/" + fileName)){
        //Serial.println("Arquivo ja existe!");
      } else {
        //Serial.println("Criando o arquivo...");
        wFile = SPIFFS.open("/" + fileName,"w+");

        //Verifica a criação do arquivo
        if(!wFile){
          //Serial.println("Erro ao criar arquivo " + fileName + "!");
        } else {
          //Serial.println("Arquivo " + fileName + " criado com sucesso!");
        }
      }
      wFile.close();
    }

    void writeFile(String fileName ,String msg) {
      //Abre o arquivo para adição (append)
      //Inclue sempre a escrita na ultima linha do arquivo
      File rFile = SPIFFS.open("/" + fileName,"a+");

      if(!rFile){
        //Serial.println("Erro ao abrir arquivo " + fileName + "!");
      } else {
        rFile.println(msg);
        //Serial.println(msg);
      }
      rFile.close();
    }

    void deleteFile(String fileName) {
      //Remove o arquivo
      if(SPIFFS.remove("/" + fileName)){
        //Serial.println("Erro ao criar arquivo " + fileName + "!");
      } else {
        //Serial.println("Arquivo " + fileName + " criado com sucesso!");
      }
    }

    String readFile(String fileName) {
      String buf;
      //Faz a leitura do arquivo
      File rFile = SPIFFS.open("/" + fileName,"r");
      //Serial.println("Reading file...");
      while(rFile.available()) {
        String line = rFile.readStringUntil('\n');
        buf += line;
        buf += "<br />";
      }
      rFile.close();
      return buf;
    }

    void closeFileSystem(){
      SPIFFS.end();
    }

    int info(String option){
      FSInfo fs_info;
      SPIFFS.info(fs_info);

      if(option == "totalBytes") return fs_info.totalBytes;
      if(option == "usedBytes") return fs_info.usedBytes;
      if(option == "blockSize") return fs_info.blockSize;
      if(option == "pageSize") return fs_info.pageSize;
      if(option == "maxOpenFiles") return fs_info.maxOpenFiles;
      if(option == "totalBytes") return fs_info.totalBytes;
      if(option == "maxPathLength") return fs_info.maxPathLength;
      return -1;
    }

    bool exists(String fileName){
      if(SPIFFS.exists("/" + fileName)){
        return true;
      } else {
        return false;
      }
    }

};
#endif
