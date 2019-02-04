/* Shark-O-Meter
 * FILENAME: Logger.h
 * LAST MODIFIED: 5/7/2018
 * DESCRIPTION: Header file for the logger class.
*/

#define BUFFER_SIZE 16

#ifndef Logger_H
  #define Logger_H

  #include <Fat16.h> // Utility for accessing FAT16 filesystems.
  #include "ConsoleDebugger.h"
  
  int r2w = 0; // Tracks how how many bytes are in the buffer
  SdCard card;  // Object for accessing the SD card over SPI
  Fat16 file; // FAT16 FS wrapper object
  
  class Logger
  {
    public:
      const char *datafile;
      const char *logfile;
      void error(MessageType messagetype, const char *message);
      bool begin(const char *datafile, const char *logfile);
      template <typename T> bool print(T data);
      template <typename T> bool println(T data);
  };

  Logger Logger;

#endif
