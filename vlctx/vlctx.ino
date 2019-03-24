
#define LEDPIN 12


void CALIBRATE()
{

  Serial.println("SENDING CALIBRATION SIGNALS...");
  
  digitalWrite(LEDPIN,LOW);
  delay(1000);

  digitalWrite(LEDPIN,HIGH);
  delay(1000);

  digitalWrite(LEDPIN,LOW);
  delay(1000);

  digitalWrite(LEDPIN,HIGH);
  delay(1000);

  digitalWrite(LEDPIN,LOW);

}


void setup() {
  // put your setup code here, to run once:


  pinMode(LEDPIN,OUTPUT);
  

  Serial.begin(9600);
  delay(100); // wait for Serial

  CALIBRATE();
  delay(1000);
}


#define BIT_PERIOD 20
void bitsend(uint8_t b)
{
  if(b) digitalWrite(LEDPIN,HIGH);
  else digitalWrite(LEDPIN,LOW);

  //if(b)Serial.print("1");
  //else Serial.print("0");

  delay(BIT_PERIOD);
}

void tx(uint8_t val)
{
  //send start bit
  bitsend(1);

  //SEND MSB FIRST
  bitsend(val & 128);
  bitsend(val & 64);
  bitsend(val & 32);
  bitsend(val & 16);
  
  bitsend(val & 8);
  bitsend(val & 4);
  bitsend(val & 2);
  bitsend(val & 1);

  //reset led to off
  bitsend(0);
  
  delay(5*BIT_PERIOD); //safe delay before receiver is ready for next character
}

String readline()
{
  while(Serial.available())Serial.read();

  while(!Serial.available());
  delay(100);

  String line="";

  while (Serial.available()) line+=(char)Serial.read();
  
  return line;
  
}


void txString(String line)
{
  for (int i=0,l=line.length();i<l;i++)
  {
      tx((char)line[i]);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("ENTER TEXT TO SEND ->");
  String line = readline();
  Serial.println("GOT LINE: " + line);

  txString(line);

 
}
