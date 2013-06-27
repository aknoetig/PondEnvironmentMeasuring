#ifndef SDHANDLER_H
#define SDHANDLER_H

#include "Arduino.h"
#include <SD.h>


/***********************************************************/
/*                                                         */
/* SDHandler Library                                       */
/*                                                         */
/* A Library that takes care of everything the             */
/* collecting Node has to do with the SD Card.             */
/*                                                         */
/***********************************************************/


// Enumeration Type for describing the State of a file
//
typedef enum FileState
{
  CLOSED = 1,
  OPEN_READING = 2,
  OPEN_WRITING = 3
};

// SDHandler Class. Responsible for providing the necessary functionalities
// for using the SD Card
class SDHandler
{
  public:
  // Constructor & Destructor
  SDHandler();
  ~SDHandler();
  
  // opens the file for reading
  // return: success or not
  boolean openFileReading();
  
  // opens the file for writing
  // return: success or not
  boolean openFileWriting();
  
  // closes the file (if it is open)
  void closeFile();
  
  // returns the number of bytes in the byte
  // return: no of bytes, or -1 for error
  long fileSize();
  
  // reads a char from the file
  // return: the char,
  //         or -1 if file there are no more chars left,
  //         or -2 if file is not opened for reading
  char readChar();
  
  // writes a string to the end of the file
  // params: * str = Adress of string to write
  //         * length = no of bytes to write
  // return: no of bytes written, or -1 for error
  int writeToFile(char* str, int length);
  
  
  private:
  
  // State of the file
  FileState filestate;
  // The File (What this Library is all about)
  File myFile;
  
};


#endif
