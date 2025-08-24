/*

Copyright (c) 2025 I8ZSE, Giorgio L. Rutigliano
(www.i8zse.it, www.i8zse.eu, www.giorgiorutigliano.it)

This is free software released under LGPL License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

TEST Windows: rigctl -m 2009 -r \\.\COMxx -s 9600 --set-conf=serial_handshake=None T [0|1]
TEST Linux: rigctl -m 2009 -r /dev/TTYUSBx -s 9600 --set-conf=serial_handshake=None T [0|1]

*/

const int txPin = 8;
const int ledPin = LED_BUILTIN;
String command = "";
String mode = "0";
unsigned long txStartTime = 0;
const unsigned long txTimeout = 30000; // 30 secondi

void setup() {
  Serial.begin(9600);
  pinMode(txPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(txPin, LOW);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // watchdog
  if (mode == "1" && (millis() - txStartTime > txTimeout)) {
    digitalWrite(txPin, LOW);
    digitalWrite(ledPin, LOW);
    mode = "0";
  }

  if (Serial.available()) {
    char c = Serial.read();

    if (c == ';') {
      command.trim();
      if (command.startsWith("FA") && command.length() > 2) {
         Serial.print(command + ";");
      }
      else if (command.startsWith("FB") && command.length() > 2) {
          Serial.print(command + ";");
      }
      else if (command == "ID") Serial.print("ID009;");
      else if (command == "FA") Serial.print("FA00014074000;");
      else if (command == "FB") Serial.print("FB00014074000;");
      else if (command == "FL") Serial.print("FL001001;");
      else if (command == "MD") Serial.print("MD2;");
      else if (command == "IF" || command == "AI0") {
        Serial.print("IF00014074000");
        Serial.print("     ");
        Serial.print("+0000");
        Serial.print("00 00");
        Serial.print(mode);
        Serial.print("0000000 ;");
      }
      else if (command == "PS") Serial.print("PS1;");
      else if (command == "TRN") Serial.print("TRN0;");
      else if (command == "TX") {
        digitalWrite(txPin, HIGH);
        digitalWrite(ledPin, HIGH);
        mode = "1";
        txStartTime = millis(); // set watchdog
      }
      else if (command == "RX") {
        digitalWrite(txPin, LOW);
        digitalWrite(ledPin, LOW);
        mode = "0";
      }
      else Serial.print("E;");

      command = "";
    } else {
      command += c;
    }
  }
}
