/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:


#define LDRPIN A0



unsigned int THRESH=400;


unsigned int FIND_THRESH()
{

  Serial.println("RECEIVING CALIBRATION SIGNALS....");
  
  unsigned int off[20],on[20];

  delay(250);
  for (int i=0;i<10;i++) 
  {
    off[i]= analogRead(LDRPIN);
    delay(50);
  }


  delay(500);
  for (int i=0;i<10;i++) 
  {
    on[i]= analogRead(LDRPIN);
    delay(50);
  }

  

  delay(500);
  for (int i=0;i<10;i++) 
  {
    off[i+10]= analogRead(LDRPIN);
    delay(50);
  }
 

  delay(500);
  for (int i=0;i<10;i++) 
  {
    on[i+10]= analogRead(LDRPIN);
    delay(50);
  }

  unsigned int xon=0,xoff=0;

  for(int i=0;i<20;i++)
  {
    Serial.print(String(i) + "\t --- ");
    Serial.println("ON: " + String(on[i]) + "\t | OFF: " + String(off[i]) );
    xon+=on[i];
    xoff+=off[i];
  }

  xon /= 20;
  xoff /= 20;

  THRESH = xon/2 + xoff/2;

  Serial.println("AVG ON:" + String(xon));
  Serial.println("THRESH: " + String(THRESH));
  Serial.println("AVG OFF:" + String(xoff));

  
  return THRESH;

  
  
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(100); // wait for Serial

  FIND_THRESH();
  
  delay(1000);
}



uint8_t getbit()
{
 
  int val = analogRead(LDRPIN);
  if (val>THRESH) return 1;
  else return 0;
  
}


#define BIT_PERIOD 20

uint8_t rx()
{
  
  uint8_t data=0; //data to recieve
  
  while(getbit()==0); //wait for startbit                  xS-----1-----2-----3-----4-----5-----6-----7-----8-----E    
  delay(BIT_PERIOD); //wait till end of startbit            S-----x-----2-----3-----4-----5-----6-----7-----8-----E
  
  delay(BIT_PERIOD/2); //wait till mid of 1st bit period    S-----1--x--2-----3-----4-----5-----6-----7-----8-----E

  for (uint8_t i=0;i<8;i++)
  {
    uint8_t thisbit=getbit();
    data <<= 1; //shift
    data |= thisbit; //read bit

    
    //Serial.print(thisbit);
    
    delay(BIT_PERIOD); //wait till mid of NEXT bit period

  }
  
  delay(2*BIT_PERIOD); //safe delay before next character receive/rx

  return data;
    
}

String rxString()
{
  Serial.println("Waiting for VLC data");
  
  char r;
  String line="";
  do
  {
    r=rx();
    line+=r;

    Serial.print(r);Serial.print("|");Serial.print((uint8_t)r,HEX);Serial.print("|");
    Serial.println((uint8_t)r,BIN);
    
  }while(r!='\n');

  Serial.println();
  return line;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:

    
    Serial.println("\n----------------------\n");
    String line=rxString();
    Serial.println("RECEIVED: " + line);
  
}
