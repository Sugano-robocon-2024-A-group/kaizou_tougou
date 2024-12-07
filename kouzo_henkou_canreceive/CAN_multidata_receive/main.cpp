//#include <PS4Controller.h>
#include <Arduino.h>
#include <CAN.h>
#include "tuushin.h"

uint32_t id;          // CAN IDを格納する変数
uint16_t data[8]={0,0,0,0,0,0,0,0};      // 受信データを格納する配列（最大8バイト）
uint16_t length=0;       // 受信データの長さを格納する変数

// setup関数: 初期設定を行う。CANバスの初期化と、送受信の設定を呼び出す
void setup() {
  
  Serial.begin(115200);  // シリアル通信開始
   while (!Serial);  // シリアル接続待機

const int CAN_TX_PIN = 27;  // 送信ピン（GPIO27）
const int CAN_RX_PIN = 26;  // 受信ピン（GPIO26）

  Serial.println("CAN Communication");
  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  // CANバスの初期化（通信速度500kbps）
  CAN.begin(500E3);
  // CANバスの初期化。500kbpsで動作を設定
  if (!CAN.begin(500E3)) {
    // CAN初期化に失敗した場合、エラーメッセージを表示して停止
    Serial.println("CANの初期化に失敗しました！");
    while (1);  // 永久ループで停止
  }

  // 受信と送信の初期化関数を呼び出し
  setupReceiver();
  Serial.println("Start");
}


// loop関数: 受信と送信を繰り返す
void loop() {
  
receivePacket(id, data, length);
// CANメッセージを受信

int packetSize = CAN.parsePacket();
if (packetSize) { 
    Serial.print(data[0]);
    Serial.print(data[1]);
    //Serial.print(data[2]);Serial.print(data[3]);
    Serial.println();

//移動関数
    if(data[0]==1){//これでHIGHにする
        //analogWrite(PIN_SYASYUTU, dutyCycle );
        Serial.print("UP");
      }else if(data[0]==2){
        //digitalWrite(PIN_SYASYUTU,LOW);
        Serial.print("BACK");
      }

     
 
for (int i = 0; i < 8; i++) {
    data[i] = 0;
    }
}
 //delay(40);  // 1秒の遅延
}
