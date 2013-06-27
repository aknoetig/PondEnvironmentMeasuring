#include "SDHandler.h"

#include <SD.h>

SDHandler::SDHandler()
{
  
  
  // Pin 10 must be Output or the SD library functions will not work. 
  pinMode(10, OUTPUT);
  
  filestate = CLOSED;
  
  //  
  if (!SD.begin(4)) {
    // SD Library failed to begin
    return;
  }
}

SDHandler::~SDHandler()
{
  if(filestate != CLOSED)
    myFile.close();
}


boolean SDHandler::openFileReading()
{
  if(filestate != CLOSED)
    closeFile();
  
  myFile = SD.open("data.csv", FILE_READ);
  
  if(myFile)
  {
    filestate = OPEN_READING;
    return true;
  }
  else
    return false;
}


boolean SDHandler::openFileWriting()
{
  if(filestate != CLOSED)
    closeFile();
  
  myFile = SD.open("data.csv", FILE_WRITE);
  
  if(myFile)
  {
    filestate = OPEN_WRITING;
    return true;
  }
  else
    return false;
}

void SDHandler::closeFile()
{
  myFile.close();
  filestate = CLOSED;
}

long SDHandler::fileSize()
{
  if(filestate != CLOSED)
    return myFile.size();
  else
    return -1;
}
  
char SDHandler::readChar()
{
  if(filestate == OPEN_READING)
    return myFile.read();
  else
    return -2;
}
  
int SDHandler::writeToFile(char* str, int length)
{
  if(filestate == OPEN_WRITING)
  {
    int i;
    for(i=0; i<length; i++)
      myFile.write(str[i]);
    return i;
  }
  else
    return -1;
}
