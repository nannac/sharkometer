/* Shark-O-Meter
 * FILENAME: ConsoleDebugger.ino
 * LAST MODIFIED: 5/7/2018
 * DESCRIPTION: The debugger provides console logging and error handling functionality.
   It is not necessary for logging operation, but it can be very useful when diagnosing
   problems.
*/

// Setup method for the debugger.
bool ConsoleDebugger::begin(int baudrate, uint8_t debuglevel, uint8_t debugfatal) // debuglevel sets when messages will be written to console and debugfatal sets what message level will cuase the program to halt
{
  this->debuglevel = debuglevel;
  this->debugfatal = debugfatal;
  Serial.begin(baudrate);
  return 1;
}

// Check if the current message level is configured to halt program execution
bool ConsoleDebugger::fatal(MessageType messagetype)
{
  if (messagetype.level <= this->debugfatal)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// Creates a message and calls the print method based on the result of ::fatal. This method can take variadic substitutions after the message argument (like sprintf)
template <typename... Subs> void ConsoleDebugger::message(MessageType messagetype, const char *message, Subs...subs)
{
  this->messagetype = messagetype;
  if (this->fatal(messagetype))
  {
    this->printMessage(message, subs...);
    this->printMessage("A FATAL ERROR OCCURED. HALTING PROGRAM!\n*****************************");
    delay(1000);
    exit(0);
  }
  else
  {
    this->printMessage(message, subs...);
  }
}

// Print the errorlevel and message to console. This method can take variadic substitutions after the message argument (like sprintf)
template <typename... Subs> void ConsoleDebugger::printMessage(const char *message, Subs... subs)
{
  if (sizeof...(Subs) > 0) // if there are variadic arguments build a new string in buffer, else just print the message
  {
    char buffer[CHAR_BUFFER_SIZE];
    Serial.print(this->messagetype.title);
    Serial.print(": ");
    sprintf(buffer, message, subs...);
    Serial.println(buffer);
  }
  else
  {
    Serial.print(this->messagetype.title);
    Serial.print(": ");
    Serial.println(message);
  }
}
