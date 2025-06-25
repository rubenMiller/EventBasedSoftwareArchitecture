const int sensorPin = 3;  
const int analogPin = A0;


void setup() {
  //start serial connection
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  Serial.println("Hello");
}

void loop() {
  printf("Starting");


  digitalWrite(13, LOW);
  delay(1000);
  Serial.println("shouldn't shine");
  digitalWrite(13, HIGH);
  delay(1000);
  Serial.println("should shine");

}