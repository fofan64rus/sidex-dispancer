#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <iarduino_RTC.h>

// Дисплей подключается к портам SCL - A5, SOA - A4
LiquidCrystal_I2C lcd(0x3F,16,2);  

// часы RST, CLK, DAT
iarduino_RTC watch(RTC_DS1302, 7, 5, 6);

//  Определяем системное время:                             // Время загрузки скетча.
const char* strM="JanFebMarAprMayJunJulAugSepOctNovDec";    // Определяем массив всех вариантов текстового представления текущего месяца находящегося в предопределенном макросе __DATE__.
const char* sysT=__TIME__;                                  // Получаем время компиляции скетча в формате "SS:MM:HH".
const char* sysD=__DATE__;                                  // Получаем дату  компиляции скетча в формате "MMM:DD:YYYY", где МММ - текстовое представление текущего месяца, например: Jul.
//  Парсим полученные значения в массив:                    // Определяем массив «i» из 6 элементов типа int, содержащий следующие значения: секунды, минуты, часы, день, месяц и год компиляции скетча.
const int i[6] {(sysT[6]-'0')*10+(sysT[7]-'0'), (sysT[3]-'0')*10+(sysT[4]-'0'), (sysT[0]-'0')*10+(sysT[1]-'0'), (sysD[4]-'0')*10+(sysD[5]-'0'), ((int)memmem(strM,36,sysD,3)+3-(int)&strM[0])/3, (sysD[9]-'0')*10+(sysD[10]-'0')};

void setup()
{
  delay(300);
  watch.begin();
  watch.settime(i[0],i[1],i[2],i[3],i[4],i[5]); 

  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("iarduino.ru");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");
}

void loop()
{
    if(millis()%1000==0){
        lcd.setCursor(0, 0);
        lcd.print(watch.gettime("d-m-Y, H:i:s, D"));
        delay(1);
    }
}