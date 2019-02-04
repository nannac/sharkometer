/* Shark-O-Meter
 * FILENAME: ConsoleDebugger.h
 * LAST MODIFIED: 5/7/2018
 * DESCRIPTION: Header file for the ConsoleDebugger. ErrorType definitions and 
   character buffer size is defined here.
*/

#ifndef ConsoleDebugger_H
  #define ConsoleDebugger_H
  
  #include "Arduino.h"
  
  #define CHAR_BUFFER_SIZE 64 // Error messages must be under this size in bytes if using variadic arguments

  // Each message object has a title and level
  struct MessageType
  {
    const char *title;
    uint8_t level;
  };

  // Message types allow different handling based on the error level
  MessageType FATAL { "FATAL", 1 };
  MessageType ERROR { "ERROR", 2 };
  MessageType WARN { "WARN", 3 };
  MessageType INFO { "INFO", 4 };
  MessageType DEBUG { "DEBUG", 5 };
  MessageType TRACE { "TRACE", 6 };
  
  class ConsoleDebugger
  {
    private:
      uint8_t debuglevel;
      uint8_t debugfatal;
      MessageType messagetype;
  
    public:
      bool begin(int baudrate, uint8_t debuglevel, uint8_t debugfatal);
      bool fatal(MessageType messagetype);
      template <typename... Subs> void message(MessageType messagetype, const char *message, Subs... subs);
      template <typename... Subs> void printMessage(const char *message, Subs... subs);
  };

// The Arduino IDE concatinates all files together. There is no need for 'extern' declarations when creating objects that will be accessed from other files.
ConsoleDebugger Debug;

#endif
