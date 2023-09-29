int reserve = 20;
int a = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {

while(!Serial.available()){}

// Take off for 25 seconds
for(int i = 0; i<=100 ; i+=2){
  int amplitude = i;
  // Serial.print("Amplitude:");  
  Serial.println(amplitude);
  // Serial.print(",");
  // Serial.print("Reserve:");
  // Serial.println(reserve);

  while(!Serial.available()){}
  // String receivedString = Serial.readStringUntil('\n');
  delay(500); 
}

// Level flight for 50 seconds
int count = 0;
while (count!=100){
  int amplitude = 100;
  count +=2;
  // Serial.print("Amplitude:");  
  Serial.println(amplitude);  
  // Serial.print(",");
  // Serial.print("Reserve:");
  // Serial.println(reserve);

  while(!Serial.available()){}
  // String receivedString = Serial.readStringUntil('\n');

delay(500);
}



// Landing for 10 seconds
for(int i = 100; i>=0 ; i-=2){
  int amplitude = i;
  // Serial.print("Amplitude:");  
  Serial.println(amplitude);
  // Serial.print(",");
  // Serial.print("Reserve:");
  // Serial.println(reserve);

  while(!Serial.available()){}
  // String receivedString = Serial.readStringUntil('\n');

  delay(500); 
}

while(Serial.available()!=0){}

}