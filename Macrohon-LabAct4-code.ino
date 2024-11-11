#define LDR_PIN A2
#define LED_PIN 13


const int BRIGHTNESS_THRESHOLD = 123; 
bool loopingControl = true;


void setup() {
  pinMode(LED_PIN, OUTPUT);  // Make the led pin an output
  Serial.begin(9600); 
  
}

// gets the brightness from the photoresistor
int readBrightness() {
  int analogBrightness = analogRead(LDR_PIN); //reads analog photoresistor reading
  int mapBrightness = map(analogBrightness, 0, 1023, 0, 255); //transform analog values into digital values
  return mapBrightness;
}

void loop(){
  if(loopingControl == true){
    int brightness = readBrightness();  
    Serial.print("Brightness: ");
    Serial.println(brightness);

    if (brightness >= BRIGHTNESS_THRESHOLD || brightness < BRIGHTNESS_THRESHOLD) {
      digitalWrite(LED_PIN, HIGH);  // turn on the led
      delay(100);  
      digitalWrite(LED_PIN, LOW);  // turn it off
      delay(100);  
    }
  }
  
  if(Serial.available() > 0){
  	String isOpen = Serial.readStringUntil('\n');
    isOpen.toLowerCase();
    
    if(isOpen == "stop"){
      loopingControl = false;
    }
  }
}