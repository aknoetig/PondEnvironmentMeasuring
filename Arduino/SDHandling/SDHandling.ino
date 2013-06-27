#include <SD.h>

#include "SDHandler.h"


void setup()
{
  Serial.begin(9600);
  while (!Serial); 
  
  SDHandler sd;

  // openFile Writing
  Serial.print("Opening File ...");
  if(sd.openFileWriting())
    Serial.println(" Sucessfully.");
  else
    Serial.println(" Not Sucessfully.");
  
  //Write something
  Serial.print("Writing ");
  int no = sd.writeToFile("Test 1,2,3\n", 11);
  Serial.print(no);
  Serial.println(" Bytes.");
  
  // close File
  Serial.println("Closing File.");
  sd.closeFile();
  
  //reopen Reading
  Serial.print("Opening File ...");
  if(sd.openFileReading())
    Serial.println(" Sucessfully.");
  else
    Serial.println(" Not Sucessfully.");
  
  //read all chars
  Serial.print("Reading ");
  Serial.print(sd.fileSize());
  Serial.println(" Bytes: ");
  char c = 0;
  do
  {
    char c = sd.readChar();
    if(c == -1)
      break;
    else
      Serial.print(c);
  }while(true);
    
  Serial.println("\nClose File");
  //close again
  sd.closeFile();
}

void loop()
{
  // nothing happens after setup
}


