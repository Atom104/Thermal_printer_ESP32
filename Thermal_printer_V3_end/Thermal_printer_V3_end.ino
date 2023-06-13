#include <Tone32.h>

#include <EEPROM.h>

#include <GParser.h>
#include "GyverEncoder.h"
#include <GyverOLED.h>
GyverOLED <SSD1306_128x64, OLED_BUFFER> oled;
Encoder enc1 (27, 26, 25);

#define BUZZER_PIN 19

#include <HardwareSerial.h>
#include "BluetoothSerial.h"
HardwareSerial MySerial(1);
#define RX 17
#define TX 16
//byte cmd1[] = {0x1B, 0x74, 0x04};
//String stringVar = String(intVar, DEC);
#define TAB '\t' //!< Horizontal tab
#define LF '\n'  //!< Line feed
#define FF '\f'  //!< Form feed
#define CR '\r'  //!< Carriage return
#define DC2 18   //!< Device control 2
#define ESC 27   //!< Escape
#define FS 28    //!< Field separator
#define GS 29    //!< Group separator
#define SO      0x0E
#define DC4     0x14

#define L 48
#define M 49
#define Q 50
#define H 51

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//======================================================================================================
//                                            МАССИВ ИКОНОК
//======================================================================================================
const uint8_t back_ico_16x16[] PROGMEM = {
  0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x38, 0x38, 0x38, 0x38, 0x78, 0xf0, 0xe0, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x07, 0x03, 0x00, 0x00
};

const uint8_t warning_ico_16x16[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0xc6, 0xc6, 0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x58, 0x46, 0x41, 0x40, 0x40, 0x5e, 0x5e, 0x40, 0x40, 0x41, 0x46, 0x58, 0x60, 0x00
};

const uint8_t well_ico_16x16[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x00,
  0x00, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
};

const uint8_t settings_ico_16x16[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFC, 0x8E, 0x86, 0x82, 0xC0, 0xE0, 0x70, 0x00, 0x00,
  0x00, 0x30, 0x38, 0x1C, 0x0E, 0x07, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t self_test_ico_16x16[] PROGMEM = {
  0x00, 0xF8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x82, 0xC2, 0x04, 0xF8, 0x00,
  0x00, 0x1F, 0x20, 0x40, 0x43, 0x46, 0x4C, 0x58, 0x4C, 0x46, 0x43, 0x41, 0x40, 0x20, 0x1F, 0x00
};

const uint8_t inform_ico_16x16[] PROGMEM = {
  0x00, 0xf8, 0x04, 0x02, 0x02, 0x02, 0x02, 0x62, 0x62, 0x02, 0x02, 0x02, 0x02, 0x04, 0xf8, 0x00,
  0x00, 0x1f, 0x20, 0x40, 0x40, 0x40, 0x40, 0x5f, 0x5f, 0x40, 0x40, 0x40, 0x40, 0x20, 0x1f, 0x00
};

const uint8_t yes_dinamic_ico_16x16[] PROGMEM = {
  0x00, 0xf8, 0x04, 0x02, 0xc2, 0xc2, 0xc2, 0xe2, 0xf2, 0xfa, 0x02, 0x02, 0x02, 0x04, 0xf8, 0x00,
  0x00, 0x1f, 0x20, 0x40, 0x43, 0x43, 0x43, 0x47, 0x4f, 0x5f, 0x40, 0x40, 0x40, 0x20, 0x1f, 0x00
};

const uint8_t no_dinamic_ico_16x16[] PROGMEM = {
  0x00, 0xf8, 0x04, 0x0e, 0xda, 0xf2, 0xe2, 0xe2, 0xf2, 0xfa, 0x02, 0x02, 0x02, 0x04, 0xf8, 0x00,
  0x00, 0x1f, 0x20, 0x40, 0x43, 0x43, 0x43, 0x47, 0x4f, 0x5f, 0x46, 0x4c, 0x58, 0x30, 0x1f, 0x00
};

const uint8_t back_ico_8x8_5[] = {
  0x00, 0x44, 0x4e, 0x44, 0x44, 0x6c, 0x38, 0x00
};

const uint8_t back_ico_8x8[] = {
  0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00
};
//======================================================================================================

struct Organization_Data {
  char INN_data [50];
  char FN_data [50];
  char FD_data [50];
  char FP_data [50];
  char RNKKT_data [50];
  char ZNKKT_data [50];
  char Adress_data [150];
  char Name_data [150];
  char SNO_data [50];
};

Organization_Data org_data;

bool disp = 1;
bool buz = 1;
int pages = 0;
bool ble_status = true;
int scroll = 0;
int val = 1;

unsigned long timeout = 0;

void setup() {
  EEPROM.begin(1000);
  EEPROM.get(1, org_data);
  EEPROM.get(0, buz);

  Serial.begin(9600);
  
  SerialBT.begin("Thermal Printer");
  MySerial.begin(9600, SERIAL_8N1, RX, TX);
  enc1.setType(TYPE2);  
  oled.init();
  oled.textMode(BUF_ADD);
  oled.flipH(true);       // true/false - отзеркалить по горизонтали
  oled.flipV(true);
  oled.clear();
  oled.home();
  oled.clear();
  //oled.println("Thermo");
  //oled.print("Printer");
}

int power_voltage = 0;
int power_percent = 0;

void loop() {
  // put your main code here, to run repeatedly:
  enc1.tick();

  if(millis()-timeout>1000 && pages==0)
  {
    MySerial.write(0x1D);
    MySerial.write(0x67);
    MySerial.write(0x6C);

    String voltage;
    char mass [100];
    bool st = 1;
    while(st)
    {
      if(MySerial.available())
      {
        int ammm = MySerial.readBytesUntil('V', mass, 100);
        mass[ammm] = NULL;
        voltage = (String)mass;
        st = 0;
      }
    }
    voltage.replace("Power: ","");
    voltage.replace("m","");
    voltage.replace("V","");
    power_voltage = round(voltage.toFloat()/100);
    power_percent = round((power_voltage-60)*100/24);
    //power_percent = (power_voltage,60,84,0,100);
    main_page(0);
    Serial.println(mass);
    Serial.println(power_voltage);
    Serial.println(power_percent);
    timeout = millis();
  }
  
  switch (pages) {
    case 0:
      {
        main_page(0);
        if (enc1.isClick())
        {
          if (buz)
            tone(19, 4000, 80, 0);
        }
        if (enc1.isSingle())
        {
          pages = 1;
          val = 1;
          settings_page(val);
        }
      }
      break;
    case 1:
      {
        if (enc1.isTurn())
        {
          if (enc1.isRight())
          {
            val++;
          }
          if (enc1.isLeft())
          {
            val--;
          }
          if (val > 3) {
            val = 0;
          } else if (val < 0)
          {
            val = 3;
          }
          settings_page(val);
        }

        if (enc1.isDouble())
        {
          val = 0;
          pages = 0;
        }

        if (enc1.isClick())
        {
          if (buz)
            tone(19, 4000, 80, 0);
        }
        if (enc1.isSingle())
        {
          switch (val)
          {
            case 0:
              {
                val = 0;
                pages = 0;
              }
              break;
            case 1:
              {
                //print_org_info(0);
                scroll = 0;
                pages = 2;
                print_org_info(scroll);
              }
              break;
            case 2:
              {
                print_self_test();
              }
              break;
            case 3:
              {
                Serial.println("Click_buz");
                buz = !buz;
                settings_page(val);
                Serial.println(buz);
                EEPROM.put(0, buz);
                EEPROM.commit();
              }
              break;
          }
        }
      }
      break;
    case 2:
      {
        if (enc1.isTurn())
        {
          if (enc1.isRight())
          {
            scroll++;
          }
          if (enc1.isLeft())
          {
            scroll--;
          }
          if (scroll > 10)
          {
            scroll = 10;
          }
          if (scroll < 0)
          {
            scroll = 0;
          }
          print_org_info(scroll);
        }
        if (enc1.isSingle())
        {
          if(scroll == 0)
          {
            pages = 1;
            //val = 1;
            settings_page(val);
          }
          else if(scroll == 10)
          {
            
          }
        }

        if (enc1.isDouble())
        {
          scroll == 0;
          pages = 0;
        }

        if (enc1.isClick())
        {
          if (buz)
            tone(19, 4000, 80, 0);
        }
      }
  }
  
  if (SerialBT.available()) {
    //t += SerialBT.readString();
    char dat[1000];
    int am = SerialBT.readBytesUntil('>', dat, 1000);
    dat[am] = NULL;

    GParser data(dat, '@');
    data.split();

    if (data.equals(0, "text"))
    {
      main_page(1);
      Serial.println("вошел в режим печати текста");
      char dat1[data.getInt(7) * 2];
      //String txt;
      bool starts = 1;
      if (data.getInt(7) != 0)
      {
        while (starts)
        {
          //int txt_length;
          if (SerialBT.available())
          {
            int amm = SerialBT.readBytes(dat1, data.getInt(7) * 2);
            dat1[amm] = NULL;
            //txt += SerialBT.readString();
            //txt_length = txt.length();
            //Serial.println(dats);

            if (data.equals(2, "true")) {
              MySerial.write(0x1B);  //Установка подчеркивания
              MySerial.write(0x2D);
              MySerial.write(0x02);
            }
            thermo_set_text_align(data.getInt(3));                                                            //Установка выравнивания
            if (data.equals(1, "true")) thermo_select_print_mode(8);                                          //Установка жирного шрифта
            thermo_select_character_size(data.getInt(5), data.getInt(4));                                     //Изменение размера символа
            if (data.equals(6, "true")) {
              MySerial.write(0x1D);  //Установка инверсии цветов
              MySerial.write(0x42);
              MySerial.write(0x01);
            }

            print_rus_symbol(dat1, strlen(dat1)); //Печать текста
            MySerial.println("");
            Serial.println("напечатал текст");

            // Сброс настроек
            starts = 0;
            thermo_select_print_mode(0);
            thermo_select_character_size(0, 0);

            MySerial.write(0x1B);
            MySerial.write(0x2D);
            MySerial.write(0x00);

            MySerial.write(0x1D);
            MySerial.write(0x42);
            MySerial.write(0x00);
          }
        }
      }
      main_page(0);
    }
    else if (data.equals(0, "QR"))
    {
      main_page(2);
      Serial.println("вошел в режим печати QR кода");
      char QR_text[data.getInt(7) * 2];
      //String txt;
      bool starts = 1;
      while (starts)
      {
        //int txt_length;
        if (SerialBT.available())//|| data.getInt(7) == 0
        {
          thermo_set_qrcode_size1(data.getInt(1));
          int amm = SerialBT.readBytes(QR_text, data.getInt(7) * 2);
          QR_text[amm] = NULL;
          //txt += SerialBT.readString();
          //txt_length = txt.length();
          //Serial.println(dats);
          GParser data2(QR_text, '#');
          data2.split();

          String inform_data = data2[0];
          String text_data = data2[1];


          for (int i = 0; i < data.getInt(3); i++)
          {
            if (data.equals(6, "true") && data.getInt(5) == 1)
            {
              thermo_set_text_align(data.getInt(4));
              print_rus_symbol(text_data); //Печать текста
              MySerial.println("");
              MySerial.println("");
            }

            thermo_set_text_align(1);
            thermo_printer_QR_print1(inform_data, data.getInt(2));                                                        //Установка выравнивания
            Serial.println("напечатал QR код");

            if (data.equals(6, "true") && data.getInt(5) == 0)
            {
              thermo_set_text_align(data.getInt(4));
              print_rus_symbol(text_data); //Печать текста
              MySerial.println("");
            }
            //print_rus_symbol(data2[1], strlen(dat1)); //Печать текста
            MySerial.println("");
          }
          MySerial.println("");
          thermo_set_qrcode_size1(6);

          // Сброс настроек
          starts = 0;
          thermo_set_text_align(0);
        }
      }
      main_page(0);
    }
    else if (data.equals(0, "Barcode"))
    {
      main_page(3);
      int barcode_width = data.getInt(2);
      switch (data.getInt(1))
      {
        case 0:
          {
            if (barcode_width > 3)
              barcode_width = 3;
          }
          break;
        case 2:
          {
            if (data.getInt(2) > 3)
              barcode_width = 3;
          }
          break;
        case 3:
          {
            if (data.getInt(2) > 4)
              barcode_width = 4; //data[10]
          }
          break;
        case 4:
          {
            if (strlen(data[10]) > 10 && strlen(data[10]) <= 25 && barcode_width > 1)
              barcode_width = 1;
            else if (strlen(data[10]) > 6 && strlen(data[10]) <= 10 && barcode_width > 2)
              barcode_width = 2;
            else if (strlen(data[10]) > 3 && strlen(data[10]) <= 6 && barcode_width > 3)
              barcode_width = 3;
            else if (strlen(data[10]) > 2 && strlen(data[10]) <= 3 && barcode_width > 4)
              barcode_width = 4;
            else if (strlen(data[10]) > 1 && strlen(data[10]) <= 2 && barcode_width > 5)
              barcode_width = 5;
          }
          break;
        case 5:
          {
            if (strlen(data[10]) > 18 && strlen(data[10]) <= 28 && barcode_width > 1)
              barcode_width = 1;
            else if (strlen(data[10]) > 12 && strlen(data[10]) <= 18 && barcode_width > 2)
              barcode_width = 2;
            else if (strlen(data[10]) > 8 && strlen(data[10]) <= 12 && barcode_width > 3)
              barcode_width = 3;
            else if (strlen(data[10]) > 6 && strlen(data[10]) <= 8 && barcode_width > 4)
              barcode_width = 4;
            else if (strlen(data[10]) > 4 && strlen(data[10]) <= 6 && barcode_width > 5)
              barcode_width = 5;
          }
          break;
        case 7:
          {
            if (strlen(data[10]) > 16 && strlen(data[10]) <= 28 && barcode_width > 1)
              barcode_width = 1;
            else if (strlen(data[10]) > 9 && strlen(data[10]) <= 16 && barcode_width > 2)
              barcode_width = 2;
            else if (strlen(data[10]) > 5 && strlen(data[10]) <= 9 && barcode_width > 3)
              barcode_width = 3;
            else if (strlen(data[10]) > 3 && strlen(data[10]) <= 5 && barcode_width > 4)
              barcode_width = 4;
            else if (strlen(data[10]) > 1 && strlen(data[10]) <= 3 && barcode_width > 5)
              barcode_width = 5;
          }
          break;
        case 8:
          {
            if (strlen(data[10]) > 14 && strlen(data[10]) <= 28 && barcode_width > 1)
              barcode_width = 1;
            else if (strlen(data[10]) > 8 && strlen(data[10]) <= 14 && barcode_width > 2)
              barcode_width = 2;
            else if (strlen(data[10]) > 5 && strlen(data[10]) <= 8 && barcode_width > 3)
              barcode_width = 3;
            else if (strlen(data[10]) > 3 && strlen(data[10]) <= 5 && barcode_width > 4)
              barcode_width = 4;
            else if (strlen(data[10]) > 2 && strlen(data[10]) <= 3 && barcode_width > 5)
              barcode_width = 5;
          }
          break;
      }

      thermo_set_text_align(1);
      thermo_set_barcode_text_position(data.getInt(4));
      thermo_set_barcode_width(barcode_width);
      thermo_set_barcode_height(8 * data.getInt(3));
      Serial.println("вошел в режим печати штрих кода");
      char Barcode_text[data.getInt(9) * 2];
      //String txt;
      bool starts = 1;
      while (starts)
      {
        //int txt_length;
        if (SerialBT.available()) //|| data.getInt(9) == 0
        {
          //thermo_set_qrcode_size1(data.getInt(1));

          int amm = SerialBT.readBytes(Barcode_text, data.getInt(9) * 2);
          Barcode_text[amm] = NULL;

          Serial.println(Barcode_text);

          for (int i = 0; i < data.getInt(5); i++)
          {
            if (data.equals(8, "true") && data.getInt(7) == 1)
            {
              thermo_set_text_align(data.getInt(6));
              print_rus_symbol(Barcode_text, strlen(Barcode_text)); //Печать текста
              MySerial.println("");
              MySerial.println("");
            }

            Serial.println(data.getInt(1));
            thermo_print_barcode(65 + data.getInt(1), data[10]);
            //thermo_printer_QR_print1(inform_data, data.getInt(2));                                                        //Установка выравнивания
            Serial.println("напечатал штрих код");

            if (data.equals(8, "true") && data.getInt(7) == 0)
            {
              thermo_set_text_align(data.getInt(6));
              print_rus_symbol(Barcode_text, strlen(Barcode_text)); //Печать текста
              MySerial.println("");
            }
            //print_rus_symbol(data2[1], strlen(dat1)); //Печать текста
            MySerial.println("");
          }
          //thermo_set_qrcode_size1(6);
          MySerial.println("");

          // Сброс настроек
          starts = 0;
          thermo_set_text_align(0);
        }
      }
      main_page(0);
    }
    else if (data.equals(0, "Cheque_print"))
    {
      main_page(4);
      Serial.println("вошел в режим печати чека");
      char packet_text_length[data.getInt(7) * 2];
      //String txt;
      bool starts = 1;
      if (data.getInt(7) != 0)
      {
        while (starts)
        {
          //int txt_length;
          if (SerialBT.available())
          {
            int amm = SerialBT.readBytesUntil('<', packet_text_length, data.getInt(7) * 2);
            packet_text_length[amm] = NULL;

            for (int i = 0; i < 12; i++)
            {
              Serial.println(data[i]);
            }
            Serial.println(packet_text_length);
            
            GParser data_chek(packet_text_length, '@');
            data_chek.split();

            String Date_time[] = {data[8], data[9], data[10], data[11], data[12]};

            String products_name[data.getInt(6)];
            float products_price[data.getInt(6)];
            float products_nds[data.getInt(6)];
            float products_count[data.getInt(6)];

            for (int i = 0; i < data.getInt(6); i++)
            {
              products_name[i] = data_chek[i];
              products_price[i] = data_chek.getFloat(i + data.getInt(6)); //data_chek[i + data.getInt(6)].toFloat();
              products_nds[i] = data_chek.getFloat(i + 2 * data.getInt(6)); //data_chek[i + 2 * data.getInt(6)].toFloat();
              products_count[i] = data_chek.getFloat(i + 3 * data.getInt(6)); //data_chek[i + 3 * data.getInt(6)].toFloat();
              Serial.print(data_chek[i]);
              Serial.print(" ");
              Serial.print(data_chek.getFloat(i + data.getInt(6)));
              Serial.print(" ");
              Serial.print(data_chek.getFloat(i + 2 * data.getInt(6)));
              Serial.print(" ");
              Serial.println(data_chek.getFloat(i + 3 * data.getInt(6)));
            }
            //EEPROM.get(0, org_data);

            float no_nalicka_summa = data.getFloat(4);
            float yes_nalicka_summa =  data.getFloat(5);

            print_chek(
              (String)data[1],
              String(org_data.INN_data),
              String(org_data.FN_data),
              String(org_data.FD_data),
              String(org_data.FP_data),
              String(org_data.RNKKT_data),
              String(org_data.ZNKKT_data),
              data.getInt(6),
              products_name,
              products_count,
              products_price,
              products_nds,
              Date_time,
              yes_nalicka_summa,
              no_nalicka_summa,
              String(org_data.Adress_data),
              String(org_data.Name_data),
              String(org_data.SNO_data),
              (String)data[2],
              (String)data[3]);

            starts = 0;
          }
        }
      }
      main_page(0);
    }
    else if (data.equals(0, "Cheque_set"))
    {
      String buff = data[1];
      buff.toCharArray(org_data.INN_data, 50);
      buff = data[2];
      buff.toCharArray(org_data.FN_data, 50);
      buff = data[3];
      buff.toCharArray(org_data.FD_data, 50);
      buff = data[4];
      buff.toCharArray(org_data.FP_data, 50);
      buff = data[5];
      buff.toCharArray(org_data.RNKKT_data, 50);
      buff = data[6];
      buff.toCharArray(org_data.ZNKKT_data, 50);
      buff = data[7];
      buff.toCharArray(org_data.Adress_data, 150);
      buff = data[8];
      buff.toCharArray(org_data.Name_data, 150);
      buff = data[9];
      buff.toCharArray(org_data.SNO_data, 50);
      EEPROM.put(1, org_data);
      EEPROM.commit();
    }
  }
}
