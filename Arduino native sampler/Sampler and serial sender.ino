unsigned long timer = 0;
long loopTime = 1;   // microseconds

void setup() {
  Serial.begin(115200);
  timer = micros();
}

void loop() {
  timeSync(loopTime);
  //int val = analogRead(0) - 512;
  double valx = (analogRead(0) -512) / 512.0;
  double valy = (analogRead(1) -512) / 512.0;
  double valz = (analogRead(2) -512) / 512.0;
  sendToPC(&valx, &valy, &valz);
}

void timeSync(unsigned long deltaT)
{
  unsigned long currTime = micros();
  long timeToDelay = deltaT - (currTime - timer);
  if (timeToDelay > 1)
  {
    delay(timeToDelay / 1000);
    delayMicroseconds(timeToDelay % 1000);
  }
  else if (timeToDelay > 0)
  {
    delayMicroseconds(timeToDelay);
  }
  else
  {
    // timeToDelay is negative so we start immediately
  }
  timer = currTime + timeToDelay;
}

void sendToPC(int* data1, int* data2, int* data3)
{
  byte* byteData1 = (byte*)(data1);
  byte* byteData2 = (byte*)(data2);
  byte* byteData3 = (byte*)(data3);
  byte buf[6] = {
    byteData1[0], byteData1[1],
    byteData2[0], byteData2[1],
    byteData3[0], byteData3[1]  };
  Serial.write(buf, 6);
}

void sendToPC(double* data1, double* data2, double* data3)
{
  byte* byteData1 = (byte*)(data1);
  byte* byteData2 = (byte*)(data2);
  byte* byteData3 = (byte*)(data3);
  byte buf[12] = {
    byteData1[0], byteData1[1], byteData1[2], byteData1[3],
    byteData2[0], byteData2[1], byteData2[2], byteData2[3],
    byteData3[0], byteData3[1], byteData3[2], byteData3[3]  };
  Serial.write(buf, 12);
}

