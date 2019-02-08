  /* Shark-O-Meter
   * FILENAME: sharkometer_combo.ino
   * LAST MODIFIED: 5/7/2018
   * DESCRIPTION: This is the main program file. It contains configuration definitions
     and sensing/logging logic. This is the only file that needs to be edited for
     basic operational changes like logging frequency and file output format.
  */
  
  /************/
  /* INCLUDES */
  /************/
  
  #include "Logger.h" // File logging
  #include "ConsoleDebugger.h" // Debugging and error handling
  
  /*****************/
  /* CONFIGURATION */
  /*****************/
  
  #define PRESSURE_SENSOR 3 // Pin that connects to the INA118 amp's Vout pin.
  //#define IR_LED 4 // LED power pin for the OBP625 optical switch
  #define IR_SENSOR 2 // The pin identifying low voltage interrupts triggered by the OBP625
  
  #define INTERVAL 1000  // The amount of milliseconds between each measurement/calculation interval
  
  #define SERIAL_BAUD 9600 // Baud for serial debugging/messaging
  #define DEBUG_DISPLAY 4 // What messages are displayed by error level. (1 - FATAL, 2 - ERROR, 3 - WARN, 4 - INFO, 5 - Trace)
  #define DEBUG_HALT 2 // At what level the program will halt when it encounters an exception
  
  #define DATA_FILE "DATA.CSV" // File that recorded data will be written to
  #define ERROR_FILE "ERROR.LOG" // File that errors will be written to ***NOT FUNCTIONAL***
  #define CARD_CS 4 // SPI cable select pin for the SD card module
  
  volatile int tripCounter = 0; // Counts the number of times the paddlewheel rotates. Global variables used in interrupts must be declared "volatile"
  
  // Setup routine. This runs once.
  void setup() {
    Serial.println("\n------------------");
    Debug.begin(SERIAL_BAUD, DEBUG_DISPLAY, DEBUG_HALT); // Debugging and error reporting setup
    pinMode(IR_SENSOR,INPUT);                 //Sets PIN 2 for the output of sensor as an input PIN only
    attachInterrupt(0, sensorTrip, FALLING); //ISR runs sensorTrip function everytime PIN 2
    Logger.begin(DATA_FILE, ERROR_FILE);
    Logger.println("Time(s),Pito,Paddle");
  }
  
  double timeElapsed = 0;
  int pressure; // holds amplified voltage measurement from the pitot tube assembly
  void loop() {
    timeElapsed += INTERVAL;
    pressure = analogRead(PRESSURE_SENSOR); // Read pressure sensor value
    // Print data to file in CSV format
    Serial.print("TIME: ");
    Serial.println(timeElapsed);
    Serial.print("PITOT: ");
    Serial.println(pressure);
    Serial.print("PADDLE: ");
    Serial.println(tripCounter);
    Serial.println("------------------");
    Logger.print(timeElapsed);
    Logger.print(",");
    Logger.print(pressure);
    Logger.print(",");
    Logger.println(tripCounter);
    tripCounter = 0; // Reset the trip counter
    delay(INTERVAL); // Wait for next measurement time
  }
  
  // This function is called every time the IR_SENSOR pin goes low.
  void sensorTrip()
  {
    tripCounter++; // Increment trip counter
  }
