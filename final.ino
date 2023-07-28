#include <SoftwareSerial.h>

// 핀번호 설정
SoftwareSerial BTSerial(2, 3); //bluetooth module Tx:Digital 2 Rx:Digital 3
int analpin0 = A0;
int analpin1 = A1;
int analpin2 = A2;
int switch1 = 5;

// 시리얼 속도, 센서 설정
void setup(){
  BTSerial.begin(9600); 
  Serial.begin(9600);
  pinMode(switch1, INPUT);
}

// 마이크로컨트롤러 동작
void loop(){
  //변수 설정
  int sum = 0;
  int avg = 0;  

  if(BTSerial.available()){                         //블루투스 연결 확인
    if(digitalRead(switch1)==HIGH){              //스위치가 ON됐을 때
      if(BTSerial.read() == 'a'){          //앱에서 측정하기 버튼 눌렸을　때
        for(int i=0;i<300;i++){            //3초동안 악력측정
    //센서값의 범위 재설정 :　0~1024 -> 0~20
          int anal0 = map(analogRead(analpin0), 0, 1024, 0, 20);
          int anal1 = map(analogRead(analpin1), 0, 1024, 0, 20);
          int anal2 = map(analogRead(analpin2), 0, 1024, 0, 20);
          sum = sum+anal0+anal1+anal2;       //3개의 압력센서 값 더하기
          delay(10);
        }
        avg = sum / 300;           //3초 동안 센서 값 평균
        BTSerial.println(avg);           //블루투스로 평균 값 보내기
      }
    }
  }
}
