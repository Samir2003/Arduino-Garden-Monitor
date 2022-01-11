const int temperaturePin = A5; //sets temperaturePin as the variable to represent the pin that the temperature sensor is connected to
const int photoPin = A0; //sets photoPin as the variable to represent the pin that the photoresistor is connected to 
const int soilPin = A1; //sets soilPin as the variable to represent the pin that the soil moisture sensor is connected to
const int RedLedPin = 5; //sets RedLedPin as the variable to represent the pin that the red led is connected to
const int GreenLedPin = 10;//sets GreenLedPin as the variable to represent the pin that the green led is connected to
const int button = 11; //sets button as the variable to represent the pin that the button is connected to 
int soilLevel; //creates the variable soilLevel as the variable to represent the moisture % in the soil
int photoInput; //creates the variable photoInput to represent the light intensity in the area
int lastState = HIGH; //creates the variable lastState to represent the state of the button and declares it as high
int currentState; //creates the variable currentState to represent the current state of the button
int temperatureInput; //creates the variable temperatureInput to represent the 
double temperature; //creates the variable temperature to represent the temperature in C*
void setup() { //this code is run once
  Serial.begin(9600); //sets the data rate in bits/s for serial data transmission, the data rate is 9600bits/s
  pinMode(button,INPUT_PULLUP); //uses the pullup resistor on the arduino for the button

}

void loop() { //this code is constantly looped and is run infinitely
  currentState = digitalRead(button); //the state of the button is read and stored in the currentState variable
  photoInput = analogRead(photoPin); //the values of the photoresistor depending on the light intensity are read and stored 
  photoInput = constrain(photoInput,400,1023); //the values of the photoresistor are constrained between 400-1023
  photoInput = map(photoInput,400,1023,0,100);//when the photoresistor is under light it's maximum value is 1023 and this is mapped to be 100 to create a percentage scale 
  soilLevel = analogRead(soilPin); //the value of the moisture sensor is read and stored in the variable
  soilLevel = constrain(soilLevel,400,1023); //the values of the moisture sensor are constrained between 400-1023
  soilLevel = map(soilLevel,400,1023,100,0); //the values of the moisture sensor are mapped to create a percentage scale
  temperatureInput = analogRead(temperaturePin); //the voltage value of the temperature sensor is read and stored 
  temperature = (double)temperatureInput/1024; //the temperature is divided by 1024 to convert it from volts to millivolts
  temperature = temperature * 5; //the temperature variable is multiplied by 5
  temperature = (temperature - 0.5) * 100; //the temperature variable is converted into celsius degrees by using the formula
  if(currentState == LOW) //if the button is clicked the following block of code is executed                  
  {
    Serial.print("Current Temperature: "); //prints the temperature in the serial monitor
    Serial.println(temperature);
    Serial.print("Light intensity(amount of light): "); //prints the light intensity in the serial monitor
    Serial.print(photoInput);
    Serial.print("%");
    Serial.println();
    Serial.print("Soil Moisture: "); //prints the soil moisture in the serial monitor
    Serial.print(soilLevel);
    Serial.print("%");
    Serial.println();
    if((18 <= temperature) && (10 <= photoInput) && (100 == soilLevel)) //if ideal growing conditions are met the green LED will turn on
    {
      digitalWrite(RedLedPin, LOW); //red led is turned on if it was on
      analogWrite(GreenLedPin, 255); //green led is set on full brightness
    }
    else
    {
      digitalWrite(RedLedPin, HIGH); //if growing conditions aren't met the red led turns on
      analogWrite(GreenLedPin, 0);//green led turns off
    }
    delay(1000); //the loop delays for a second before continuing to loop
  }
  else if(currentState == HIGH) //if the button isn't clicked then the leds are turned off and the user is prompted to click the button
  {
    digitalWrite(RedLedPin, LOW);
    analogWrite(GreenLedPin, 0);
    Serial.println("Please hold the button for atleast 2s to start the plant monitoring!"); //the user is prompted to click the button to start the plant monitoring
    delay(2000);
  }
  lastState = currentState; //the variable lastState stores the current state of the button
}
