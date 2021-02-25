int b = 2;
int g = 3;
int y = 4;
int r = 5;
int photocell;
int potentiometer;

void setup() {
  Serial.begin(9600);
  pinMode(r, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pinMode(y, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
}

void loop() {

  photocell = analogRead(A0);
  potentiometer = analogRead(A1);
  int redValue = digitalRead(r) ; 
  Serial.print("Photocell: ");
  Serial.print(photocell);
  Serial.print(" , ");
  Serial.print("Potenitometer: ");
  Serial.print(potentiometer);
  Serial.print(" , ");
  Serial.print("Red button: ");
  Serial.print(  redValue );
  Serial.print(" , ");
  Serial.print("Yellow button: ");
  Serial.print(digitalRead(y));
  Serial.print(" , ");
  Serial.print("Green button: ");
  Serial.print(digitalRead(g));
  Serial.print(" , ");
  Serial.print("Blue button: ");
  Serial.println(digitalRead(b));

}
