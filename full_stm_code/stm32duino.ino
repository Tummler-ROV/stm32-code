 // Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <Servo.h>
#include <Wire_slave.h>
//888888888888888888888888888888888888888888888888888888888888888888
#define STM32_RCINPUT_ADDRESS             0x27
#define STM32_RCINPUT_CHANNEL_COUNT         0xfe
#define STM32_RCINPUT_REGID                 0xff
#define STM32_RCINPUT_REGID_VALUE           0x92


#define STM32_ADC_ADDRESS           0x48 // address pin low (GND)
#define STM32_ADC_I2C_BUS           0x1
#define STM32_ADC_REGID             0xff
#define STM32_ADC_REGID_VALUE       0xfe


#define STM32_RCOUT_ADDRESS             0x66
#define STM32_RCOUT_REGID                   0xff
#define STM32_RCOUT_GET_MOTOR_COUNT         0xfc
#define STM32_RCOUT_ENABLE_OUTPUT           0xfa
#define STM32_RCOUT_CHANGE_PWM_PROTOCOL     0xfe
#define STM32_RCOUT_REGID_VALUE             0x91

//888888888888888888888888888888888888888888888888888888888888888888
#define adc0             PA5
#define adc1             PA4
#define adc2             PA3
#define adc3             PA2
//000000000000000000000000000000000000000000000000000000000000000000
#define pservo1             PA8
#define pservo2             PA9
#define pservo3             PA10
#define pservo4             PB6
#define pservo5             PB7
#define pservo6             PB8
#define pservo7             PB9
#define pservo8             PB1
#define pservo9             PB0
Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7;

//888888888888888888888888888888888888888888888888888888888888888888
uint8_t motorc = 10;
int outing = 25;
void setup() {
  servo1.attach(pservo1);
  servo2.attach(pservo2);
  servo3.attach(pservo3);
  servo4.attach(pservo4);
  servo5.attach(pservo5);
  servo6.attach(pservo6);
  servo7.attach(pservo7);
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  servo3.writeMicroseconds(1500);
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1500);
  servo6.writeMicroseconds(1500);
  servo7.writeMicroseconds(1500);

  delay(2000);
  pinMode(adc0, INPUT_ANALOG);
  pinMode(adc1, INPUT_ANALOG);
  pinMode(adc2, INPUT_ANALOG);
  pinMode(adc3, INPUT_ANALOG);
  pinMode(pservo8, OUTPUT);
  pinMode(pservo9, OUTPUT);
  //  Serial.begin(115200);         // start serial for output

  Wire1.begin(STM32_ADC_ADDRESS, STM32_RCOUT_ADDRESS);               // join i2c bus with address #4
  Wire1.onReceive(receiveEvent); // register event
  Wire1.onRequest(requestEvent); // register event
}

void loop() {
  delay(1);
}

void receiveEvent(int howMany) {
  uint16_t x = 0;
  uint8_t c = 0;

  if (howMany > 1) {
    c = Wire1.read(); // receive byte as a character

    //Serial.print(Wire1.recvSlaveAddress(), HEX);
    //Serial.print(" : ");
    //Serial.println(c);         // print the character

    int i = 0;
    while (Wire1.available()) {
      int tempin = Wire1.read();
      //Serial.print("temp in is : ");
      //Serial.println(tempin);
      for (int n = 0; n < i; n++) tempin = tempin << 8;
      x |= tempin;
      i++;
    }

    //Serial.print("res: ");
    //Serial.println(x);

    if (Wire1.recvSlaveAddress() == STM32_RCOUT_ADDRESS) {
      switch (c) {
        case STM32_RCOUT_ENABLE_OUTPUT:
          //Serial.print("STM32_RCOUT_ENABLE_OUTPUT ");
          //Serial.println(x);
          servo1.writeMicroseconds(1500);
          servo2.writeMicroseconds(1500);
          servo3.writeMicroseconds(1500);
          servo4.writeMicroseconds(1500);
          servo5.writeMicroseconds(1500);
          servo6.writeMicroseconds(1500);
          servo7.writeMicroseconds(1500);
          analogWrite(pservo8, 0);
          break;
        case STM32_RCOUT_CHANGE_PWM_PROTOCOL:
          //Serial.print("STM32_RCOUT_CHANGE_PWM_PROTOCOL ");
          //Serial.println(x);
          break;
        case 0:
          //Serial.print("chanell 0: ");
          //Serial.println(x);
          break;
        case 1:
          //Serial.print("chanell 1: ");
          //Serial.println(x);
          servo1.writeMicroseconds(x);
          break;
        case 3:
          //Serial.print("chanell 2: ");
          //Serial.println(x);
          servo2.writeMicroseconds(x);
          break;
        case 5:
          //Serial.print("chanell 3: ");
          //Serial.println(x);
          servo3.writeMicroseconds(x);
          break;
        case 7:
          //Serial.print("chanell 4: ");
          //Serial.println(x);
          servo4.writeMicroseconds(x);
          break;
        case 9:
          //Serial.print("chanell 5: ");
          //Serial.println(x);
          servo5.writeMicroseconds(x);
          break;
        case 11:
          //Serial.print("chanell 6: ");
          //Serial.println(x);
          servo6.writeMicroseconds(x);
          break;
        case 13:
          //Serial.print("chanell 7: ");
          //Serial.println(x);
          servo7.writeMicroseconds(x);
          break;
        case 15:
          //Serial.print("chanell 8: ");
          //Serial.println(map(x, 1100, 1900, 0, 255));
          analogWrite(pservo8, map(x, 1100, 1900, 0, 255));
          break;
        case 17:
          //Serial.print("chanell 9: ");
          //Serial.println(x);
          if (x <= 1500) {
            analogWrite(pservo9, 255);
          }
          else {
            analogWrite(pservo9, 0);
          }
          break;

        default:
          //Serial.print("default STM32_RCOUT_ADDRESS recive  : ");
          //Serial.print(c, HEX);
          //Serial.print(",");
          //Serial.println(x);
          break;
      }
    }
  }

}

void requestEvent()
{
  uint8_t reg = Wire1.read();
  if (Wire1.recvSlaveAddress() == STM32_RCOUT_ADDRESS) {
    switch (reg) {
      case STM32_RCOUT_REGID:
        //Serial.println(" STM32_RCOUT regid");
        Wire1.write(STM32_RCOUT_REGID_VALUE);
        break;
      case STM32_RCOUT_GET_MOTOR_COUNT:
        //Serial.print("STM32_RCINPUT_CHANNEL_COUNT : ");
        //Serial.println(motorc);
        Wire1.write(motorc);
        break;
      default:
        //Serial.print("default STM32_RCOUT_ADDRESS request  : ");
        //Serial.println(reg);
        break;
    }
  }
  if (Wire1.recvSlaveAddress() == STM32_ADC_ADDRESS) {
    uint16_t res = 0;
    switch (reg) {
      case STM32_ADC_REGID:
        //Serial.println("STM32_ADC regid");
        Wire1.write(STM32_ADC_REGID_VALUE);
        break;
      case 0:
        //Serial.print("adc0 : ");
        //Serial.println(adc0);
        res = analogRead(adc0);
        //        res = 1500;
        break;
      case 1:
        //Serial.print("adc1 : ");
        //Serial.println(adc1);
        res = analogRead(adc1);
        //        res = 1500;
        break;
      case 2:
        //Serial.print("adc2 : ");
        //Serial.println(adc2);
        res = analogRead(adc2);
        //        res = 1500;
        break;
      case 3:
        //Serial.print("adc3 : ");
        //Serial.println(adc3);
        res = analogRead(adc3);
        //        res = 1500;
        break;
      default:
        break;
    }
    Wire1.write(res);
  }
}
