void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) { // If data is available on the Serial port
    // String message = Serial.readString(); // Read the data
    // Serial.println(message); 
    // Serial.print("RS");  
  


  int a = 100;
  String mystr;
  mystr = String(a);

  
  while(Serial.readStringUntil('\n')!= mystr)
  // if (Serial.readStringUntil('\n') < mystr)
  {
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);  
  }

  if (Serial.readStringUntil('\n') == mystr){
    digitalWrite(13,HIGH);
    delay(500);
  }
  }
}


