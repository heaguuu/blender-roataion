
#include <Servo.h>

Servo motor;

// 서보모터 신호선 연결 핀
const int MOTOR_PIN = 9;

// 정지 신호 (모터에 따라 조정 필요)
const int STOP_SIGNAL = 1500;

// 속도 명령 범위
const int MAX_SPEED = 100;

// 서보 제어 신호 범위
const int MIN_SIGNAL = 1000;
const int MAX_SIGNAL = 2000;

void setup() {
  Serial.begin(9600);

  motor.attach(MOTOR_PIN);

  // 시작할 때 정지
  motor.writeMicroseconds(STOP_SIGNAL);

  Serial.println("=== 360 Servo Motor Control ===");
  Serial.println("Enter speed from -100 to 100");
  Serial.println("0 = Stop");
  Serial.println("Positive = Direction 1");
  Serial.println("Negative = Direction 2");
  Serial.println("===============================");
}

void loop() {
  if (Serial.available() > 0) {
    int speedValue = Serial.parseInt();

    // 입력값 제한
    speedValue = constrain(speedValue, -MAX_SPEED, MAX_SPEED);

    // 속도 명령을 서보 제어 신호로 변환
    int signal = map(
      speedValue,
      -MAX_SPEED,
      MAX_SPEED,
      MIN_SIGNAL,
      MAX_SIGNAL
    );

    // 정지 명령
    if (speedValue == 0) {
      signal = STOP_SIGNAL;
    }

    // 모터 제어
    motor.writeMicroseconds(signal);

    // 결과 출력
    Serial.print("Speed command: ");
    Serial.println(speedValue);

    Serial.print("Control signal: ");
    Serial.print(signal);
    Serial.println(" us");

    // 입력 버퍼 정리
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
