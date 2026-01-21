#include <SoftwareSerial.h>

// Bluetooth Module (RX, TX)
SoftwareSerial BT(2, 3);  

// Motor Driver Pins
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

// Sensor Pins
#define GAS_SENSOR A0
#define METAL_SENSOR A1
#define FLAME_SENSOR A2
#define TEMP_SENSOR A3

void setup() {
    // Motor control pins
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    // Sensors
    pinMode(GAS_SENSOR, INPUT);
    pinMode(METAL_SENSOR, INPUT);
    pinMode(FLAME_SENSOR, INPUT);
    pinMode(TEMP_SENSOR, INPUT);
    
    // Serial communication
    Serial.begin(9600);
    BT.begin(9600);
}

void loop() {
    if (BT.available()) {
        char command = BT.read();
        controlRobot(command);
    }

    sendSensorData();
    delay(1000); 
}

void controlRobot(char command) {
    switch (command) {
        case 'F': forward(); break;
        case 'B': backward(); break;
        case 'L': left(); break;
        case 'R': right(); break;
        case 'S': stopRobot(); break;
    }
}

void forward() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void backward() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void left() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void right() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void stopRobot() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void sendSensorData() {
    int gas = analogRead(GAS_SENSOR);
    int metal = analogRead(METAL_SENSOR);
    int flame = analogRead(FLAME_SENSOR);
    int temp = analogRead(TEMP_SENSOR);

    BT.print("Gas: "); BT.print(gas);
    BT.print(" | Metal: "); BT.print(metal);
    BT.print(" | Flame: "); BT.print(flame);
    BT.print(" | Temp: "); BT.println(temp);
} 
