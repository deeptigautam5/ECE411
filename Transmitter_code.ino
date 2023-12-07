#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int x_out = A0;
const int y_out = A1;
const int left  = A2;
const int right = A3;
const int back  = A4;


RF24 radio(9, 10);
const byte address[6] = "00001";

struct data {
  int xAxis;
  int yAxis;
};
data send_data;

void setup() {
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(back, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  Serial.begin(9600); 
}

void loop() {
  send_data.xAxis = analogRead(x_out);
  send_data.yAxis = analogRead(y_out);

  if (analogRead(x_out)<299) {

    digitalWrite(left, HIGH);
    delay(100);
    digitalWrite(left, LOW);

  }

  else if (analogRead(x_out)>399) {
    digitalWrite(right, HIGH);
    delay(100);
    digitalWrite(right, LOW);
  }

  else {
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
  }

  if (analogRead(y_out)<300) {
    digitalWrite(back, HIGH);
    delay(100);
    digitalWrite(back, LOW);
  }

  else if (analogRead(y_out)>410) {
  digitalWrite(back, LOW);
  }

  else {
    digitalWrite(back, LOW);
  }

  

  radio.write(&send_data, sizeof(data));

  Serial.print("X-Axis: ");
  Serial.print(send_data.xAxis);
  Serial.print("\tY-Axis: ");
  Serial.println(send_data.yAxis);

  delay(1000);  
}
