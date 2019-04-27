/* Shark-O-Meter
 * FILENAME: Logger.ino
 * LAST MODIFIED: 5/7/2018
 * DESCRIPTION: The logger class provides functionality for writing sensor data to 
   File. 
*/

// prints errors related to data logging. uses the consoledebugger class
void Logger::error(MessageType messagetype, const char *message)
{
  Debug.message(messagetype, "%s (FAT16 ERROR CODE: %errorcode)", message, card.errorCode);
}

// Initialization method.
bool Logger::begin(const char *datafile, const char *logfile)
{
  this->logfile = logfile;
  this->datafile = datafile;
  Debug.message(INFO, "Initializing SD card.");
  if (!card.begin(CARD_CS)) this->error(ERROR, "Unable to initialize SD card (%s)");
  Debug.message(INFO, "Initialzing FAT16 filesystem.");
  if (!file.init(&card)) this->error(ERROR, "Unable to initialize FAT16 filesystem");
  Debug.message(INFO, "Opening %s for writing.", datafile);
  if (!file.open(datafile, O_CREAT | O_WRITE | O_APPEND)) this->error(ERROR, "Unable to open file for writing");
}

// Saves the data to buffer or writes to file if buffer is full
template <typename T> bool Logger::print(T data)
{
  file.print(data);
  r2w++;
  //Debug.message(INFO, "Writing to buffer. (%d/%d)", r2w, BUFFER_SIZE);
  if (r2w == BUFFER_SIZE)
  {
    //Debug.message(INFO, "Writing buffer to file and clearing buffer.");
    file.sync();
    r2w = 0;
  }
  return 1;
}

template <typename T> bool Logger::println(T data)
{
  this->print(data);
  this->print("\n");
  return 1;
}
