#define RXD1 16
#define TXD1 17

char dataBuffer[35];
double temp;

void getBuffer()
{
  int index;
  for (index=0;index<35; index ++)
  {
    if (Serial1.available())
    dataBuffer[index]=Serial1.read();
    if (dataBuffer[0] != 'c')
    {
      index=-1;
    }
    else
    {
    index --;  
    }
  }
}

int transCharToInt(char *_buffer, int _start, int _stop)
{
  int _index;
  int result=0;
  int num=_stop-_start+1;
  int _temp[num];
  for(_index=_start;_index<=_stop;_index ++)
  {
    _temp[_index-_start]=_buffer[_index]-'0';
    result=10*result+_temp[_index-_start];
  }
  return result;
}

int windDirection()
{
  return transCharToInt(dataBuffer,1,3);
}

float windSpeedAverage()
{
    temp = 0.44704 * transCharToInt(dataBuffer,5,7);
  return temp;
}

float windSpeedMax()
{
    temp = 0.44704 * transCharToInt(dataBuffer,9,11);
  return temp;
}

float temperature()
{
   temp = (transCharToInt(dataBuffer,13,15)-32.00)*5.00/9.00;
  return temp;
}

float rainfallOneHour()                                                              //Rainfall (1 hour)
{
  temp = transCharToInt(dataBuffer,17,19)*25.40*0.01;
  return temp;
}

float rainfallOneDay()                                                               //Rainfall (24 hours)
{
  temp = transCharToInt(dataBuffer,21,23)*25.40*0.01;
  return temp;
}

int humidity()                                                                       //Humidity
{
  return transCharToInt(dataBuffer,25,26);
}

float barPressure()                                                                  //Barometric Pressure
{
  temp = transCharToInt(dataBuffer,28,32);
  return temp / 10.00;
}


void setup() {
Serial.begin(9600);
Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
}

void loop() {
getBuffer();
Serial.print("arah angin: ");
Serial.print(windDirection());
Serial.println(" ");
Serial.print("kecepatan angin rata-rata: ");
Serial.print(windSpeedAverage());
Serial.println(" ");
Serial.print("kecepatan angin maksimal :");
Serial.print(windSpeedMax());
Serial.println(" ");
Serial.print("curah hujan (1 jam): ");
Serial.print(rainfallOneHour());
Serial.println(" ");
Serial.print("curah hujan (24 jam): ");
Serial.print(rainfallOneDay());
Serial.println(" ");
Serial.println("temperatur: ");
Serial.print(temperature());
Serial.println(" ");
Serial.println("kelembaban: ");
Serial.print(humidity());
Serial.println(" ");
Serial.print("tekanan barometrik: ");
Serial.print(barPressure());
Serial.println(" ");

}
