#include <SoftwareSerial.h>
const byte RX = D6;
const byte TX = D7;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
long lastUART = 0;
void Read_Uart();    // UART STM
String LED1 = "OFF", LED2 = "OFF";
void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200);

  Serial.println("UART Start");

  lastUART = millis();
}
void loop()
{
  Read_Uart();
  if (millis() - lastUART > 1000)
  {
    mySerial.print("1ON2ON3OFF4");
    Serial.println("Truyen : 1ON2ON3OFF4");
    lastUART = millis();
  }
}
void Read_Uart()
{
  String st = "";
  while (mySerial.available())
  {
    char inChar = (char)mySerial.read();
    st +=  inChar;
    if (inChar == 'C')
    {
      Serial.println("Nhan : " + st);
      int A = st.indexOf("A");
      int B = st.indexOf("B");
      int C = st.indexOf("C");

      LED1 = st.substring(A + 1, B);
      LED2 = st.substring(B + 1, C);
      Serial.println("LED1 : "+LED1+ "  LED2: "+  LED2 );
      break;
    }
  }
}

char Rx_data[11] = { 0 };
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(&huart1, (uint8_t*) Rx_data, 11);
  HAL_UART_Transmit(&huart1, (uint8_t*) "AOFFBONC", 8, 1000);
}
 HAL_UART_Receive_IT(&huart1, (uint8_t*) Rx_data, 11); // Nhận Data
