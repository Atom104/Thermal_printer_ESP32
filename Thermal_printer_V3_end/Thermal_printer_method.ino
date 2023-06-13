
//==========================================================================================================================================
//                                                    Метод для печати русского текста
//==========================================================================================================================================
char symbols[] = {
  ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')',
  '*', '+', ',', '-', '.', '/', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
  '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
  'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
  'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
  '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e',
  'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
  'z', '{', '|', '}', '~', 'А', 'Б', 'В', 'Г', 'Д',
  'Е', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О',
  'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш',
  'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я', 'а', 'б', 'в',
  'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м',
  'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц',
  'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я',
  'Ё',
  'ё',
  '\r',  
  '\n'  
};
byte symbols_byte[] =
{
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
  0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
  0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
  0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
  0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
  0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,
  0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
  0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4,
  0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0x4B, 0xCB, 0xCC, 0xCD, 0xCE,
  0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
  0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2,
  0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC,
  0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
  0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
  0xA8, //Ё
  0xB8,  //ё
  0x0D, // \r
  0x0A // \n  
};

void print_rus_symbol(String msg)
{
  for (int i = 0; i < msg.length(); i++)
  {
    int index;
    for (int j = 0; j < sizeof(symbols); j++)
    {
      if (symbols[j] == msg[i])
      {
        index = j;
        MySerial.write(symbols_byte[index]);
        break;
      }
    }
  }
}

void print_rus_symbol(char* msg, int count)
{
  for (int i = 0; i < count; i++)
  {
    int index;
    for (int j = 0; j < sizeof(symbols); j++)
    {
      if (symbols[j] == msg[i])
      {
        index = j;
        MySerial.write(symbols_byte[index]);
        break;
      }
    }
  }
}
//==========================================================================================================================================
//                                                        Метод для печати QR-кода
//==========================================================================================================================================
void thermo_printer_QR_print(String Data, uint8_t size_value, uint8_t correction_level) // данные(массив символов), размер QR кода, уровень коррекции ошибки
{
  correction_level+=48;
  Data += ' ';
  char charBuf[Data.length()];
  Data.toCharArray(charBuf, sizeof(charBuf));

  uint8_t dat[sizeof(charBuf)];
  //Serial.println(sizeof(charBuf));

  for (int i = 0; i < sizeof(charBuf); i++)
  {
    dat[i] = (uint8_t)charBuf[i];
    //Serial.println(dat[i],HEX);
  }
  thermo_set_qrcode_size(size_value);
  thermo_set_qrcode_data(dat, sizeof(dat));
  thermo_set_qrcode_correction_level(correction_level);
  //thermo_set_qrcode_info_types();
  thermo_set_qrcode_print();
}

void thermo_set_qrcode_size(uint8_t value) // установка размера
{
  if (value > 16)
    value=16;

  uint8_t buff[] = {GS, '(', 'k', 3, 0, 49, 67, value};
  MySerial.write(buff, sizeof(buff));
}

void thermo_printer_QR_print1(String Data, uint8_t correction_level) // данные(массив символов), размер QR кода, уровень коррекции ошибки
{
  correction_level+=48;
  Data += ' ';
  char charBuf[Data.length()];
  Data.toCharArray(charBuf, sizeof(charBuf));

  uint8_t dat[sizeof(charBuf)];
  //Serial.println(sizeof(charBuf));

  for (int i = 0; i < sizeof(charBuf); i++)
  {
    dat[i] = (uint8_t)charBuf[i];
    //Serial.println(dat[i],HEX);
  }
  thermo_set_qrcode_data(dat, sizeof(dat));
  thermo_set_qrcode_correction_level(correction_level);
  //thermo_set_qrcode_info_types();
  thermo_set_qrcode_print();
}

void thermo_set_qrcode_size1(uint8_t values) // установка размера
{
  if (values > 16)
    values=16;

  //uint8_t buff[] = {GS, '(', 'k', 3, 0, 49, 67, value};
  uint8_t buff[] = {0x1B, 0x23, 0x23, 0x51, 0x50, 0x49, 0x58, values};
  MySerial.write(buff, sizeof(buff));                          
}

void thermo_set_qrcode_correction_level(uint8_t level) //установка значениия коррекции ошибок 48-51, L,M,Q,H
{
  uint8_t buff[] = {GS, '(', 'k', 3, 0, 49, 69, level};
  MySerial.write(buff, sizeof(buff));
}

void thermo_set_qrcode_data(uint8_t *pBuff, uint16_t len) // загрузка данных для печати QR кода
{
  uint8_t buff[] = {GS, '(', 'k', (len + 3) & 0xFF, (len + 3) >> 8, 49, 80, 48};
  MySerial.write(buff, sizeof(buff));
  MySerial.write(pBuff, len);
}

void thermo_set_qrcode_info_types()
{
  uint8_t buff[] = {GS, '(', 'k', 3, 0, 49, 82, 48};
  MySerial.write(buff, sizeof(buff));
}

void thermo_set_qrcode_print() // печать QR кода
{
  uint8_t buff[] = {GS, '(', 'k', 3, 0, 49, 81, 48};
  MySerial.write(buff, sizeof(buff));
}

//==========================================================================================================================================
//                                                     Метод для печати картинки
//==========================================================================================================================================
void Thermal_printer_Bitmap_print(uint8_t *Bitmap_Data, uint16_t bitmap_width, uint16_t bitmap_heigth)
{
  for (int i = 0; i < bitmap_heigth; i++)
  {
    thermo_bitmap_fill(Bitmap_Data + i * bitmap_width, bitmap_width);
    thermo_bitmap_print(0);
  }
}

void thermo_bitmap_fill(uint8_t *pBuff, uint16_t width)
{
  uint8_t buff[] = {ESC, '*', 0, width % 256, width / 256};
  MySerial.write(buff, sizeof(buff));
  MySerial.write(pBuff, width);
}

void thermo_bitmap_print(uint8_t modes)
{
  uint8_t buff[] = {GS, '/', modes};
  MySerial.write(buff, sizeof(buff));
}

//1D 76 30 00 14 00 A0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 FF FF 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FE 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F FF FF FF FF E0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 7F FF FF FF FF FC 00 00 00 00 00 00 00 00 00 00 00 00 00 03 FF FF FF FF FF FF 80 00 00 00 00 00 00 00 00 00 00 00 00 0F FF FF FF FF FF FF F0 00 00 00 00 00 00 00 00 00 00 00 00 3F FF FF FF FF FF FF FC 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 00 03 FF FF FF FF FF FF FF FF C0 00 00 00 00 00 00 00 00 00 00 0F FF FF FF FF FF FF FF FF F0 00 00 00 00 00 00 00 00 00 00 3F FF FF FF FF FF FF FF FF F8 00 00 00 00 00 00 00 00 00 00 7F FF FF FF FF FF FF FF FF FE 00 00 00 00 00 00 00 00 00 01 FF FF FF FF C0 0F FF FF FF FF 00 00 00 00 00 00 00 00 00 03 FF FF FF C0 00 00 3F FF FF FF C0 00 00 00 00 00 00 00 00 0F FF FF FC 00 00 00 07 FF FF FF E0 00 00 00 00 00 00 00 00 1F FF FF E0 00 00 00 00 FF FF FF F0 00 00 00 00 00 00 00 00 3F FF FF 00 00 00 00 00 1F FF FF FC 00 00 00 00 00 00 00 00 7F FF FC 00 00 00 00 00 07 FF FF FE 00 00 00 00 00 00 00 01 FF FF F0 00 00 00 00 00 01 FF FF FF 00 00 00 00 00 00 00 03 FF FF C0 00 00 00 00 00 00 3F FF FF 80 00 00 00 00 00 00 07 FF FF 80 00 00 00 00 00 00 0F FF FF C0 00 00 00 00 00 00 0F FF FE 00 00 00 00 00 00 00 03 FF FF E0 00 00 00 00 00 00 1F FF FC 00 00 00 00 00 00 00 01 FF FF F0 00 00 00 00 00 00 1F FF F8 00 00 00 00 00 00 00 00 7F FF F8 00 00 00 00 00 00 3F FF E0 00 00 00 00 00 00 00 00 1F FF FC 00 00 00 00 00 00 7F FF C0 00 00 00 00 00 00 00 00 07 FF FE 00 00 00 00 00 00 FF FF 80 00 00 00 00 00 00 00 00 03 FF FF 00 00 00 00 00 01 FF FF 80 00 00 00 0F C0 00 00 00 00 FF FF 00 00 00 00 00 03 FF FF 00 00 00 07 FF FF 00 00 00 00 FF FF 80 00 00 00 00 03 FF FE 00 00 00 3F FF FF E0 00 00 00 FF FF C0 00 00 00 00 07 FF FC 00 00 00 FF FF FF F8 00 00 00 FF FF E0 00 00 00 00 0F FF FC 00 00 01 FF FF FF FF 00 00 00 FF FF E0 00 00 00 00 0F FF F8 00 00 03 FF FF FF FF C0 00 00 FF FF F0 00 00 00 00 1F FF F0 00 00 07 FF FF FF FF E0 00 00 FF FF F8 00 00 00 00 3F FF F0 00 00 07 FF FF FF FF F8 00 00 FF FF F8 00 00 00 00 3F FF E0 00 00 0F FF FF FF FF FE 00 00 FF FF FC 00 00 00 00 7F FF E0 00 00 0F FF FF FF FF FF 00 00 FF FF FC 00 00 00 00 7F FF E0 00 00 0F FF FF FF FF FF C0 00 FF FF FE 00 00 00 00 FF FF C0 00 00 0F FF FF FF FF FF E0 00 FF FF FE 00 00 00 00 FF FF C0 00 00 0F FF FF FF FF FF F0 00 FF FF FF 00 00 00 01 FF FF C0 00 00 0F FF FF FF FF FF FC 00 FF FF FF 00 00 00 01 FF FF 80 00 00 0F FF FF FF FF FF FE 00 FF FF FF 80 00 00 03 FF FF 80 00 00 07 FF FF FF FF FF FF 00 FF FF FF 80 00 00 03 FF FF 80 00 00 07 FF FF FF FF FF FF C0 FF FF FF C0 00 00 07 FF FF 80 00 00 03 FF FF FF FF FF FF E0 FF FF FF C0 00 00 07 FF FF 80 00 00 03 FF FF FF FF FF FF F0 FF FF FF E0 00 00 0F FF FF 80 00 00 01 FF FF FF FF FF FF F8 FF FF FF E0 00 00 0F FF FF 80 00 00 00 FF FF FF FF FF FF FC FF FF FF E0 00 00 0F FF FF 80 00 00 00 3F FF FF FF FF FF FF FF FF FF F0 00 00 1F FF FF 80 00 00 00 1F FF FF FF FF FF FF FF FF FF F0 00 00 1F FF FF 80 00 00 00 07 FF FF FF FF FF FF FF FF FF F0 00 00 1F FF FF 80 00 00 00 01 FF FF FF FF FF FF FF FF FF F8 00 00 3F FF FF 80 00 00 00 00 7F FF FF FF FF FF FF FF FF F8 00 00 3F FF FF 80 00 00 00 00 0F FF FF FF FF FF FF FF FF F8 00 00 3F FF FF 80 00 00 00 00 00 FF FF FF FF FF FF FF FF F8 00 00 3F FF FF C0 00 00 00 00 00 1F FF FF FF FF FF FF FF FC 00 00 7F FF FF C0 00 00 00 00 00 01 FF FF FF FF FF FF FF FC 00 00 7F FF FF C0 00 00 00 00 00 00 3F FF FF FF FF FF FF FC 00 00 7F FF FF E0 00 00 00 00 00 00 07 FF FF FF FF FF FF FC 00 00 7F FF FF E0 00 00 00 00 00 00 00 FF FF FF FF FF FF FC 00 00 7F FF FF F0 00 00 00 00 00 00 00 3F FF FF FF FF FF FE 00 00 7F FF FF F0 00 00 00 00 00 00 00 07 FF FF FF FF FF FE 00 00 7F FF FF F8 00 00 00 00 00 00 00 01 FF FF FF FF FF FE 00 00 FF FF FF F8 00 00 00 00 00 00 00 00 3F FF FF FF FF FE 00 00 FF FF FF FC 00 00 00 00 00 00 00 00 0F FF FF FF FF FE 00 00 FF FF FF FE 00 00 00 00 00 00 00 00 03 FF FF FF FF FE 00 00 FF FF FF FF 00 00 00 00 00 00 00 00 00 FF FF FF FF FE 00 00 FF FF FF FF 00 00 00 00 00 00 00 00 00 7F FF FF FF FE 00 00 FF FF FF FF 80 00 00 00 00 00 00 00 00 1F FF FF FF FE 00 00 FF FF FF FF C0 00 00 00 00 00 00 00 00 0F FF FF FF FE 00 00 FF FF FF FF E0 00 00 00 00 00 00 00 00 07 FF FF FF FF 00 00 FF FF FF FF F0 00 00 00 00 00 00 00 00 01 FF FF FF FF 00 00 FF FF FF FF F8 00 00 00 00 00 00 00 00 00 FF FF FF FF 00 00 FF FF FF FF FE 00 00 00 00 00 00 00 00 00 FF FF FF FF 00 00 FF FF FF FF FF 00 00 00 00 00 00 00 00 00 7F FF FF FE 00 00 FF FF FF FF FF 80 00 00 00 00 00 00 00 00 3F FF FF FE 00 00 FF FF FF FF FF E0 00 00 00 00 00 00 00 00 1F FF FF FE 00 00 FF FF FF FF FF F0 00 00 00 00 00 00 00 00 1F FF FF FE 00 00 FF FF FF FF FF FC 00 00 00 00 00 00 00 00 0F FF FF FE 00 00 FF FF FF FF FF FF 00 00 00 00 00 00 00 00 0F FF FF FE 00 00 FF FF FF FF FF FF C0 00 00 00 00 00 00 00 07 FF FF FE 00 00 7F FF FF FF FF FF F0 00 00 00 00 00 00 00 07 FF FF FE 00 00 7F FF FF FF FF FF FC 00 00 00 00 00 00 00 03 FF FF FE 00 00 7F FF FF FF FF FF FF 00 00 00 00 00 00 00 03 FF FF FE 00 00 7F FF FF FF FF FF FF E0 00 00 00 00 00 00 03 FF FF FC 00 00 7F FF FF FF FF FF FF FC 00 00 00 00 00 00 03 FF FF FC 00 00 7F FF FF FF FF FF FF FF 80 00 00 00 00 00 03 FF FF FC 00 00 3F FF FF FF FF FF FF FF F8 00 00 00 00 00 01 FF FF FC 00 00 3F FF FF FF FF FF FF FF FF C0 00 00 00 00 01 FF FF FC 00 00 3F FF FF DF FF FF FF FF FF FC 00 00 00 00 01 FF FF F8 00 00 3F FF FF DF FF FF FF FF FF FF C0 00 00 00 01 FF FF F8 00 00 1F FF FF CF FF FF FF FF FF FF F0 00 00 00 01 FF FF F8 00 00 1F FF FF C7 FF FF FF FF FF FF F8 00 00 00 01 FF FF F0 00 00 1F FF FF C3 FF FF FF FF FF FF FE 00 00 00 01 FF FF F0 00 00 0F FF FF C1 FF FF FF FF FF FF FF 00 00 00 01 FF FF F0 00 00 0F FF FF C0 FF FF FF FF FF FF FF 00 00 00 01 FF FF F0 00 00 0F FF FF C0 7F FF FF FF FF FF FF 80 00 00 03 FF FF E0 00 00 07 FF FF C0 3F FF FF FF FF FF FF 80 00 00 03 FF FF E0 00 00 07 FF FF C0 1F FF FF FF FF FF FF 80 00 00 03 FF FF C0 00 00 07 FF FF C0 0F FF FF FF FF FF FF C0 00 00 03 FF FF C0 00 00 03 FF FF C0 03 FF FF FF FF FF FF C0 00 00 03 FF FF C0 00 00 03 FF FF C0 01 FF FF FF FF FF FF C0 00 00 07 FF FF 80 00 00 01 FF FF C0 00 FF FF FF FF FF FF C0 00 00 07 FF FF 80 00 00 01 FF FF C0 00 3F FF FF FF FF FF 80 00 00 07 FF FF 00 00 00 00 FF FF C0 00 1F FF FF FF FF FF 80 00 00 0F FF FF 00 00 00 00 FF FF C0 00 07 FF FF FF FF FF 80 00 00 0F FF FE 00 00 00 00 7F FF C0 00 03 FF FF FF FF FF 00 00 00 1F FF FE 00 00 00 00 7F FF C0 00 00 FF FF FF FF FE 00 00 00 1F FF FC 00 00 00 00 3F FF C0 00 00 3F FF FF FF FC 00 00 00 3F FF F8 00 00 00 00 1F FF C0 00 00 0F FF FF FF F8 00 00 00 7F FF F8 00 00 00 00 1F FF C0 00 00 03 FF FF FF F0 00 00 00 7F FF F0 00 00 00 00 0F FF C0 00 00 00 7F FF FF C0 00 00 00 FF FF F0 00 00 00 00 07 FF C0 00 00 00 0F FF FF 00 00 00 01 FF FF E0 00 00 00 00 07 FF C0 00 00 00 00 7F F0 00 00 00 03 FF FF C0 00 00 00 00 03 FF E0 00 00 00 00 00 00 00 00 00 07 FF FF 80 00 00 00 00 01 FF F0 00 00 00 00 00 00 00 00 00 0F FF FF 80 00 00 00 00 00 FF F8 00 00 00 00 00 00 00 00 00 1F FF FF 00 00 00 00 00 00 FF FE 00 00 00 00 00 00 00 00 00 3F FF FE 00 00 00 00 00 00 7F FF 00 00 00 00 00 00 00 00 00 7F FF FC 00 00 00 00 00 00 3F FF C0 00 00 00 00 00 00 00 00 FF FF F8 00 00 00 00 00 00 1F FF E0 00 00 00 00 00 00 00 03 FF FF F0 00 00 00 00 00 00 0F FF F8 00 00 00 00 00 00 00 07 FF FF F0 00 00 00 00 00 00 07 FF FE 00 00 00 00 00 00 00 0F FF FF C0 00 00 00 00 00 00 03 FF FF 00 00 00 00 00 00 00 3F FF FF C0 00 00 00 00 00 00 01 FF FF C0 00 00 00 00 00 00 FF FF FF 00 00 00 00 00 00 00 00 FF FF F8 00 00 00 00 00 03 FF FF FE 00 00 00 00 00 00 00 00 7F FF FE 00 00 00 00 00 0F FF FF FC 00 00 00 00 00 00 00 00 3F FF FF C0 00 00 00 00 7F FF FF F8 00 00 00 00 00 00 00 00 0F FF FF F8 00 00 00 03 FF FF FF F0 00 00 00 00 00 00 00 00 07 FF FF FF C0 00 00 7F FF FF FF C0 00 00 00 00 00 00 00 00 03 FF FF FF FF FF FF FF FF FF FF 80 00 00 00 00 00 00 00 00 00 FF FF FF FF FF FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 7F FF FF FF FF FF FF FF FF FC 00 00 00 00 00 00 00 00 00 00 1F FF FF FF FF FF FF FF FF F0 00 00 00 00 00 00 00 00 00 00 07 FF FF FF FF FF FF FF FF E0 00 00 00 00 00 00 00 00 00 00 01 FF FF FF FF FF FF FF FF 80 00 00 00 00 00 00 00 00 00 00 00 7F FF FF FF FF FF FF FE 00 00 00 00 00 00 00 00 00 00 00 00 1F FF FF FF FF FF FF F8 00 00 00 00 00 00 00 00 00 00 00 00 07 FF FF FF FF FF FF C0 00 00 00 00 00 00 00 00 00 00 00 00 00 FF FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 1F FF FF FF FF F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 FF FF FF FF 80 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F FF FF F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 03 C0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
//GS v 0 \0 DC


//==========================================================================================================================================
//                                                     Метод для печати Штрих-кода
//==========================================================================================================================================
void thermo_print_barcode(uint8_t barCodeType, String Data)// m, n, data uint16_t dataLen
{
  Data += ' ';
  char charBuf[Data.length()];
  Data.toCharArray(charBuf, sizeof(charBuf));

  uint8_t dat[sizeof(charBuf)];
  //Serial.println(sizeof(charBuf));

  for (int i = 0; i < sizeof(charBuf); i++)
  {
    dat[i] = (uint8_t)charBuf[i];
    //Serial.println(dat[i],HEX);
  }

  uint16_t idx = 0;
  uint8_t buff[270];
  buff[idx++] = GS;
  buff[idx++] = 'k';
  buff[idx++] = barCodeType;

  if (barCodeType > 6)
    buff[idx++] = Data.length() - 1; //buff[idx++] = dataLen;

  for (uint16_t dataIdx = 0; dataIdx < Data.length(); dataIdx++)
    buff[idx++] = dat[dataIdx];//*(dat++);

  if (barCodeType < 7)
    buff[idx++] = 0x00;

  MySerial.write(buff, idx);
}

//==============================================================================
// Процедура установки высоты штрихкода (от 1 до 255)
// По документации значение по умолчанию = 162, по факту = 80 (10мм).
//==============================================================================
void thermo_set_barcode_height(uint8_t value)
{
  if(value>255)
    value = 255;
  uint8_t buff[] = {GS, 'h', value};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура установки ширины штрихкода (от 2 до 6)
// По документации значение по умолчанию = 3, по факту = 2.
//==============================================================================
void thermo_set_barcode_width(uint8_t value)
{
  if ((value < 1) || (value > 6))
    return;

  uint8_t buff[] = {GS, 'w', value};
  MySerial.write(buff, sizeof(buff));
}

//==============================================================================
// Процедура установки положения текста штрихкода (от 0 до 3)
//==============================================================================
void thermo_set_barcode_text_position(uint8_t value)
{
  uint8_t buff[] = {0x1D, 0x48, value};
  MySerial.write(buff, sizeof(buff));
}

/*
1D 48 00 не печатать код
1D 48 01 печатать до
1D 48 02 печатать после
1D 48 03 печатать и до и после
*/

/*
   UPC-A          m=65    n=11,12
   UPC-E          m=66    6<=n<=8, n=11,12 только 6 чисел
   JAN13(EAN13)   m=67    n=12,13
   JAN8(EAN8)     m=68    n=7,8
   CODE39         m=69    1<=n<=255
   ITF            m=70    1<=n<=255
   CODABAR        m=71    1<=n<=255
   CODE93         m=72    1<=n<=255
   CODE128        m=73    2<=n<=255
   UCC/EAN128     m=74    2<=n<=255
*/






// =================================== Методы для форматирования текста ==========================================

//==============================================================================
// Процедура управления толщиной линии подчёркивания (0, 1 или 2 точки)
//==============================================================================
void thermo_set_underlined_height(uint8_t value)
{
  if (value > 2)
    value = 2;

  uint8_t buff[] = {ESC, '-', value};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура выбора режима работы принтера. mode - сумма из констант PRINTMODE_***
//==============================================================================
void thermo_select_print_mode(uint8_t mode)
{
  uint8_t buff[] = {ESC, '!', mode};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура выбора размера шрифта (0..7 по вертикали, 0..7 по горизонтали
//==============================================================================
void thermo_select_character_size(uint8_t height_size, uint8_t width_size)
{
  if (height_size > 7)
    height_size = 7;
  if (width_size > 7)
    width_size = 7;

  uint8_t buff[] = {GS, '!', height_size | (width_size << 4)};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура управляет режимом поворота текста на 90 градусов
//==============================================================================
void thermo_set_rotation_90_mode(uint8_t mode)
{
  uint8_t buff[] = {ESC, 'V', mode ? 1 : 0};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура управления режимом двойной ширины текста
//==============================================================================
void thermo_double_width(uint8_t state)
{
  uint8_t buff[] = {ESC, state ? SO : DC4};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Функция установки позиций табуляции (до 16 позиций)
//==============================================================================
int8_t thermo_set_tab_positions(uint8_t *pTable, uint8_t tabNum)
{
  if (tabNum > 16)
    return -1;

  uint8_t buff[19];
  buff[0] = ESC;
  buff[1] = 'D';

  for (uint8_t tabIdx = 0; tabIdx < tabNum; tabIdx++)
    buff[2 + tabIdx] = *(pTable++);

  return MySerial.write(buff, tabNum + 2);
}
//==============================================================================

//==============================================================================
// Процедура управления режимом выравнивания текста в строке 0,1,2;  48,49,50  left, center, rigth
//==============================================================================
void thermo_set_text_align(uint8_t align)
{
  uint8_t buff[] = {ESC, 'a', align};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура выбора отступа по горизонтали между соседними символами
// value - в точках (0.125 мм). По умолчанию = 0.
//==============================================================================
void thermo_set_column_character_spacing(uint8_t value)
{
  uint8_t buff[] = {ESC, ' ', value};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура устанавливает отступ по вертикали начала печати очередной строки
// относительно точки начала печати пердыдущей.
// Если устанавливаемое значение меньше высоты шрифта, то устанавливается
// значение = высоте шрифта. Значение по умолчанию = 32 (4 мм).
// Высота дефолтного шрифта ~2.3 мм
//==============================================================================
void thermo_set_row_spacing(uint8_t points)
{
  uint8_t buff[] = {ESC, '3', points};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура пропуска x строк
//==============================================================================
void thermo_skip_lines(uint8_t x)
{
  uint8_t buff[] = {ESC, 'd', x};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура выбора параметров нагрева при печати
// heatPoints - 0-255 maximum number of heating points, the unit (8 dots), the default value of 9 (80 points)
// heatTime - 0-255 heating time, unit (10us), default value 80
// heatInterval - 0-255 heating interval time, unit (10us), default value 2
//==============================================================================
void thermo_set_print_concentration(uint8_t heatPoints, uint8_t heatTime, uint8_t heatInterval)
{
  uint8_t buff[] = {ESC, '7', heatPoints, heatTime, heatInterval};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Управление китайским режимом (печать иероглифов)
//==============================================================================
void thermo_china_mode(uint8_t state)
{
  uint8_t buff[] = {FS, state ? '&' : '.'};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Процедура инициализациии принтера и сброс настроек
//==============================================================================
void thermo_printer_initCmd()
{
  uint8_t buff[] = {ESC, '@'};
  MySerial.write(buff, sizeof(buff));
}
//==============================================================================

//==============================================================================
// Функция чтения статуса принтера
//==============================================================================
int8_t thermo_get_status(uint8_t *pStatus)
{
  uint8_t buff[] = {ESC, 'v', 1};
  MySerial.write(buff, sizeof(buff));
  return MySerial.read(pStatus, 1);
}
//==============================================================================

//==============================================================================
// Функция вывода строки на печать
//==============================================================================
void thermo_print(char *Str)
{
  MySerial.write((uint8_t *)Str, strlen((char *)Str));
}
//==============================================================================

//==============================================================================
// Процедура форматированного вывода на печать
//==============================================================================
void thermo_printf(const char *args, ...)
{
  char StrBuff[256];

  va_list ap;
  va_start(ap, args);
  char len = vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
  va_end(ap);

  thermo_print(StrBuff);
}

void anti_white_mode(uint8_t value)
{
  uint8_t buff[] = {GS, 'B', value};
  MySerial.write(buff, sizeof(buff));
}
//1D  42  n
//==============================================================================
/*
  //==============================================================================
  // Инициализация принтера
  //==============================================================================
  void thermal_printer_init(uint32_t BaudRate)
  {
  // Инициализируем UART
  UART_Init(BaudRate);

  thermo_printer_initCmd();
  thermo_china_mode(0);
  thermo_set_codepage(WCP1251);
  }
  //==============================================================================

  /*
  //==============================================================================
  // Процедура управляющая режимом OVERLAP
  // Из описания команды не понятно, но OVERLAP MODE делает текст жирным
  //==============================================================================
  void thermo_overlap_mode(uint8_t state)
  {
  uint8_t buff[] = {ESC, 'G', state ? '1' : '0'};
  MySerial.write(buff, sizeof(buff));
  }
  //==============================================================================

  //==============================================================================
  // Процедура управляющая режимом жирного текста
  // Закомментирован т.к. этим режимом можно управлять управляя режимом печати
  // процедурой thermo_select_print_mode
  //==============================================================================
  void thermo_bold_mode(uint8_t state)
  {
  uint8_t buff[] = {ESC, 'E', state ? '1' : '0'};
  MySerial.write(buff, sizeof(buff));
  }
  //==============================================================================

  //==============================================================================
  // Процедура управления работой кнопки
  // На практике не понятно на что влияет
  //==============================================================================
  void thermo_button_mode(uint8_t state)
  {
  uint8_t buff[] = {ESC, 'c', '5', state ? 1 : 0};
  MySerial.write(buff, sizeof(buff));
  }
  //==============================================================================
*/





/*
    Простой и быстрый парсер строк в отдельные подстроки и числа для Arduino
    Документация: 
    GitHub: https://github.com/GyverLibs/GParser
    Возможности:
    - Работает с указанным буфером (строкой), не создаёт свой
    - Разделяет строку на подстроки по указанному символу
    - Позволяет обращаться к подстрокам, переводить их в числа и сравнивать со строками
    - Доступ к подстрокам через []
    - Может распарсить строку в массив int или byte
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/
