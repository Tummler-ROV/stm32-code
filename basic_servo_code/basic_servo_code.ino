#include <Servo.h>
class Motor {
  public:
    int pin;
    Servo brushless;
    Motor(int pin) {
      this->pin = pin;
      brushless.attach(pin);
    }
    void state(int pwm) {
      brushless.writeMicroseconds(pwm);
    }
    void off() {
      brushless.writeMicroseconds(1500);
    }
};
void setup() {
  // put your setup code here, to run once:
Serial.
}

void loop() {
  // put your main code here, to run repeatedly:

}
