/*
  Edit, reduced string size to reduce memory consumption MDS
  
  This program has its origins in the sample tutorial Arduino "Temperature web interface"

 This example shows how to serve data from an analog input
 via the YunShield/Yún built-in webserver using the Bridge library.

 MDS Its been modified for the Savage 33 by Nathan and Mark S such that it reads
 motor sensor inputs from the Perkins engines etc.

 The circuit:
 * TMP36 temperature sensor on analog pin A1
 * SD card attached to SD card slot of the YunShield/Yún

 This sketch must be uploaded via wifi. REST API must be set to "open".

 Prepare your SD card with an empty folder in the SD root
 named "arduino" and a subfolder of that named "www".
 This will ensure that the Yún will create a link
 to the SD to the "/mnt/sd" path. [MDS: this is easily done by placing
 SD card in laptop]

 In this sketch folder is a basic webpage and a copy of zepto.js, a
 minimized version of jQuery.  When you upload your sketch, these files
 will be placed in the /arduino/www/TemperatureWebPanel folder on your SD card.
 [MDS Note these files are a bit hidden on the Mac, you need to go to Arduino in the 
 applications diretory and then traverse the Java and Library paths to Bridge... then AnalogTempPanel then SHOW CONTENTS. Then you can see them and copy them.
 You can also view them from Arduino environment via SKETCH and Show Sketch Folder.]

 **MDS: Note if you want to change the web URL to access this temp info
 you will need to change or copy the location of the zepto.js  

 You can then go to http://arduino.local/sd/TemperatureWebPanel
 to see the output of this sketch.

 You can remove the SD card while the Linux and the
 sketch are running but be careful not to remove it while
 the system is writing to it.

 created  6 July 2013
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/TemperatureWebPanel

 */

 /* Dad add git line
  *  and extra stuff from dad
  */

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>

// Listen on default port 5555, the webserver on the Yún
// will forward there all the HTTP requests for us.
BridgeServer server;
String startString;
long hits = 0;
double alarmVal = 0; //should probably initialise outside of loop
double alarmNum = 0;
float v0alarmsetpoint = 0.5;
float v1alarmsetpoint = 2.0;

void setup() {
  

  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  
  //think about this *************as we are using this pin below (13)********************
  digitalWrite(13, HIGH);
  delay(250); //MDS: added to set a short chirp on the external buzzer when starting the program
  digitalWrite(13, LOW); // MDS: in orig program this was set to high, but High will turn on alarm

// MDS: temporary drive input HIGH by configuring Dig 3 input internal pull up resistor. Delete this when "future" battery connected to this input.
      
      pinMode(3, INPUT_PULLUP);
  // using A0 and A2 as vcc and gnd for the TMP36 sensor:
  /*pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);
  */
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  // get the time that this sketch started:
  Process startTime;
  startTime.runShellCommand("date");
  while (startTime.available()) {
    char c = startTime.read();
    startString += c;
  }
}

void loop() {
  // Get clients coming from server
  BridgeClient client = server.accept();
  
  

  // There is a new client?
  if (client) {
    // read the command
    String command = client.readString();
    client.println(command);
    command.trim();        //kill whitespace



    if (command.startsWith("setalarm")){
      parseAlarmString(client, command, &alarmNum, &alarmVal);
      switch((int)(alarmNum)){
          case 1:
            v0alarmsetpoint = alarmVal;
            client.println("Set v0alarm setpoint to ");
            client.println(alarmVal);
            break;

          case 2:
            v1alarmsetpoint = alarmVal;
            break;
            
          default:
            //client.println("Not a valid number");
            break;
      }
      client.println("Finished function");
      client.println(alarmVal);
    }
    // is "temperature" command?
    else if (command == "temperature") {
      // get the time from the server:
      Process time;
      time.runShellCommand("date");
      String timeString = "";
      while (time.available()) {
        char c = time.read();
        timeString += c;
      }
 
      
      
      //analog inputs using analog pins
      int sensorValue0 = analogRead(A0);
      int sensorValue1 = analogRead(A1);
      int sensorValue2 = analogRead(A2);
      int sensorValue3 = analogRead(A3);
      int sensorValue4 = analogRead(A4);
      int sensorValue5 = analogRead(A5);
      //analog inputs using digital pins (this is ok)
      int sensorValue6 = analogRead(A6);
      int sensorValue7 = analogRead(A7);
      int sensorValue8 = analogRead(A8);   //19-5-19 MDS:This caused compiler to error message, due to wrong board selected in compiler enviro
      int sensorValue9 = analogRead(A9);   //19-5-19 MDS: This caused compiler to error message, due to wrong board selected in compiler enviro
      int sensorValue10 = analogRead(A10);   //19-5-19 MDS: This caused compiler to error message, due to wrong board selected in compiler enviro
      int sensorValue11 = analogRead(A11);   //19-5-19 MDS: This caused compiler to error message, due to wrong board selected in compiler enviro
      //digital inputs
      int dig2 = digitalRead(2);
      int dig3 = digitalRead(3);
      int dig5 = digitalRead(5);
      int dig11 = digitalRead(11);
     
      
      //do something to these
      
      
      // convert the reading to millivolts:
      float voltage0 = sensorValue0 * (5.0f / 1024.0f);
      float voltage1 = sensorValue1 * (5.0f / 1024.0f);
      float voltage2 = sensorValue2 * (5.0f / 1024.0f);
      float voltage3 = sensorValue3 * (5.0f / 1024.0f);
      float voltage4 = sensorValue4 * (5.0f / 1024.0f);
      float voltage5 = sensorValue5 * (5.0f / 1024.0f);
      float voltage6 = sensorValue6 * (5.0f / 1024.0f);
      float voltage7 = sensorValue7 * (5.0f / 1024.0f);
      float voltage8 = sensorValue8 * (5.0f / 1024.0f);
      float voltage9 = sensorValue9 * (5.0f / 1024.0f);
      float voltage10 = sensorValue10 * (5.0f / 1024.0f);
      float voltage11 = sensorValue11 * (5.0f / 1024.0f);


      char RX_byte = 0; //MDS: initialise the byte before any web keyboard input
      
      
     

      // print the voltage
      client.println("<BODY style='background-color:black'>"); //MDS added to test fonts etc
      //client.println("<font style='color:green'>"); //MDS added to test fonts etc
       client.println("<font style='font-family:electric toaster'>");
           client.println("<center>");
           client.println("<H1 style='font-size:400%;'>Savage 33 (DP)</H1>");
           client.println("<p style='font-size:150%'>Engine + Gearbox 12/12/2019</p>"); //end of font testing
            client.println("</center>"); // MDS this should end the centering of text
            
      client.print("Current time on the Y&uacute;n: ");
      client.println(timeString);


 //MDS:ends the above character experiment     
      
      //MDS: tidy up display
      /*
      client.print("<br>Current voltage on A0: P Engine Temperature: ");
      client.print(voltage0);
      client.print("<br>Current voltage on A1: S Engine Temperature: ");
      client.print(voltage1);
      client.print("<br>Current voltage on A2: P Oil Pressure: ");
      client.print(voltage2);
      client.print("<br>Current voltage on A3: S Oil Pressure: ");

//client.println("<font style='color:red'>"); //MDS added to test fonts etc
      
      client.print(voltage3);
      client.print("<br>Current voltage on A4: P GBox Pressure: ");
      client.print(voltage4);

//client.println("<font style='color:black'>"); //MDS added to test fonts etc
      client.print("<br>Current voltage on A5: S GBox Pressure: ");
      client.print(voltage5);
      //client.print("<br>Current voltage on A6: Future P ALT AMPS ");
      //client.print(voltage6);
      //client.print("<br>Current voltage on A7: Future House Battery Current ");
      //client.print(voltage7);
      //client.print("<br>Current voltage on A8: Future Battery Charge Voltage ");
      //client.print(voltage8);
      //client.print("<br>Current voltage on A9: Future Start Battery Voltage ");
      //client.print(voltage9);
      client.print("<br>Current voltage on A10: P GBox Temp: ");
client.println("<blink>"); //MDS: not sure if blink works on html???
      client.print(voltage10);
     
      client.print("<br>Current voltage on A11: S GBox Temp: ");
      client.print(voltage11);
client.print("</blink>"); //MDS: not sure if blink works on html???
      
      */
      
      
      if(dig5 == HIGH){
          digitalWrite(13, HIGH);
          client.println("<font style='color:red'>"); //MDS set alarm state text to red
           client.print("<br>D5 BILGE PUMP 1 ON ");
           client.println("<font style='color:green'>"); //MDS added to test fonts etc
           
      }
      else{
        client.println("<font style='color:green'>"); //MDS set text to green ie no alarm
        client.print("\n<br>D5 BILGE PUMP 1 OFF ");   //MDS: What is the \n doing here on this line??????
      }
          
      if(dig11 == HIGH){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS set alarm state text to red
         client.print("<br>D11 BILGE PUMP 2 ON ");
         client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{ 
        client.println("<font style='color:green'>"); //MDS set text to green ie no alarm
        client.print("<br>D11 BILGE PUMP 2 OFF");
        
      }
      if(dig2 == HIGH){
          digitalWrite(13,HIGH);
          client.println("<font style='color:red'>"); //MDS set alarm state text to red
          client.print("<br>D2 Future BILGE PUMP 3 ON ");
          client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else {
        client.println("<font style='color:green'>"); //MDS set text to green ie no alarm
        client.print("<br>D2 Future BILGE PUMP 3 Off ");
        
      }
      
      if(dig3 == LOW){
          digitalWrite(13,HIGH);
          client.println("<font style='color:red'>"); //MDS set alarm state text to red
          client.print("<br>D3 NA Start Battery needs Charging ");
          client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{ 
        client.println("<font style='color:green'>"); //MDS set text to green ie no alarm
        client.print("<br>D3 NA Start Battery is good ");
      }
        
      
      
          
      
      
      if(voltage0 > v0alarmsetpoint){    //MDS Doing some testing here to see if this prints out. 1.0 was previously 2.0
        digitalWrite(13, HIGH); //MDS: set buzzer to alarm
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("<br>High Alarm on Port Engine Temp: "); 
        client.print(voltage0);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW); //MDS: turn buzzer off
        client.print("<br>1. Voltage on A0: P Engine Temperature: ");

        client.print(voltage0);
        client.println("<input id=\"A0Voltage\" value=\"50\"> </input>"); 
      }
      

 if(voltage1 > v1alarmsetpoint){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("HI ALARM D13 Voltage on A1: Stb Engine Temp: ");
        client.print(voltage1);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>2. Voltage on A1: S Engine Temperature: ");
      client.print(voltage1);
      }
      

       if(voltage2 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Port Engine Oil Press: ");
        client.print(voltage2);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>3. Voltage on A2: P Oil Pressure: ");
      client.print(voltage2);
      }

     
       if(voltage3 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Stb Engine Oil Press: ");
        client.print(voltage3);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>4. Voltage on A3: S Oil Pressure: ");
        client.print(voltage3);
      }

      
       if(voltage4 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Port GBox Press: ");
        client.print(voltage4);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>5. Voltage on A4: P GBox Pressure: ");
      client.print(voltage4);
      }

      
       if(voltage5 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Stb GBox Press");
        client.print(voltage5);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>6. Voltage on A5: S GBox Pressure: ");
      client.print(voltage5);
      }

      
       if(voltage10 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Port GBox Temp");
        client.print(voltage10);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>7. Voltage on A10: P GBox Temp: ");
//client.println("<blink>"); //MDS: not sure if blink works on html???
      client.print(voltage10);
      }

      
       if(voltage11 > 2.0f){
        digitalWrite(13, HIGH);
        client.println("<font style='color:red'>"); //MDS added to test fonts etc
        client.print("ALARM D13 High Alarm Stb Gbox Temp");
        client.print(voltage11);
        client.println("<font style='color:green'>"); //MDS added to test fonts etc
      }
      else{
        digitalWrite(13, LOW);
        client.print("<br>8. Voltage on A11: S GBox Temp: ");
      client.print(voltage11);
      }

     

  /* if(V //Insert an IF Statement to detect if an analog voltage is in alarm 
     ie above or below a certain limit
      client.print("<br>Current voltage on A0: P Engine Temperature: ");
      client.print(voltage0);

     */ 
      //client.print(" &deg;C");
      client.print("<br>This sketch has been running since ");
      client.print(startString);
      client.print("<br>Hits so far: ");
      client.print(hits);
      
    }

    // Close connection and free resources.
    client.stop();
    hits++;
  }

  delay(50); // Poll every 50ms
}
  // Owen Silver, 24/12/2019 Set variables via textbox input.
  // CURRENTLY WORKS!
  // HAD LOTS OF TROUBLE WITH STR.REPLACE()
  // Could optimise to only have one holder and put the values in and then reset

  void parseAlarmString(BridgeClient client, String command, double * alarmNum, double * alarmVal){
      client.println("In function");
      char * holder = &command[10]; //set holder to be a string that starts after the "setalarm::" part.

      //Holders to get the values as chars first
      char alarmNumHolder [6];
      char alarmValHolder [6]; //can shorten these assuming either preprocessing in javascript or valid input assumed.

      //The final values after converting to double/number
      //double alarmVal; //can make this a float to save space if not necessary
      //double alarmNum; //can make this an int to save space.

      //counters for while loops
      int i = 0; 
      int j = 0;

      //get first number as a character array
      while (holder[i] != ':'){ 
        alarmNumHolder[j] = holder[i];
        i++;
        j++;
      }
      alarmNumHolder[j] = '\0'; //null terminate the character array

      //move across colons to start at next number.
      i = i+2;


      //get second number as char array, stop at the 'E' which marks the end of the string.
      j = 0;
      while (holder[i] != 'E'){ 
          alarmValHolder[j] = holder[i];
          i++;
          j++;
      }
      alarmValHolder[j] = '\0'; //null terminate array
      //client.println(alarmValHolder);

      //convert to string first so we can use toDouble string method.
      *alarmNum = (String(alarmNumHolder)).toDouble(); //should make this an int for space reasons.
      *alarmVal = (String(alarmValHolder)).toDouble();
       
  }
