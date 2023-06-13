void main_page(int print_status)
{
  val = 0;
  scroll =  0;

  float buff = float(power_voltage)/10;
  oled.clear();
  oled.setScale(1);
  oled.setCursorXY(90, 1);
  oled.print(buff,1);
  oled.setCursorXY(113, 1);
  drawBattery(power_percent);
  draw_ble(ble_status, 0, 4);
  draw_settings(2, 45);
  oled.setCursorXY(24, 50);
  oled.setScale(1);
  oled.print("Меню");
  oled.roundRect(0, 43, 127, 63, OLED_STROKE);

  if(print_status==0)
  {
    oled.drawBitmap(21, 18, well_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(20, 17, 37, 34, OLED_STROKE);
    oled.setScale(2);
    oled.setCursorXY(45, 19);
    oled.print("Готов");
  }
  if(print_status==1)
  {
    oled.drawBitmap(24, 18, warning_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(23, 17, 40, 34, OLED_STROKE);
    oled.setCursorXY(48, 16);
    oled.print("Печать");
    oled.setCursorXY(48, 28);
    oled.print("Текста");
  }
  if(print_status==2)
  {
    oled.drawBitmap(24, 18, warning_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(23, 17, 40, 34, OLED_STROKE);
    oled.setCursorXY(48, 16);
    oled.print("Печать");
    oled.setCursorXY(45, 28);
    oled.print("QR кода");
  }
  if(print_status==3)
  {
    oled.drawBitmap(21, 18, warning_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(20, 17, 37, 34, OLED_STROKE);
    oled.setCursorXY(48, 16);
    oled.print("Печать");
    oled.setCursorXY(42, 28);
    oled.print("Штрихкода");
  }
  if(print_status==4)
  {
    oled.drawBitmap(24, 18, warning_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(23, 17, 40, 34, OLED_STROKE);
    oled.setCursorXY(48, 16);
    oled.print("Печать");
    oled.setCursorXY(54, 28);
    oled.print("Чека");
  }
  if(print_status==5)
  {
    oled.drawBitmap(24, 18, warning_ico_16x16, 16, 16, BITMAP_INVERT, BUF_REPLACE);
    oled.roundRect(23, 17, 40, 34, OLED_STROKE);
    oled.setCursorXY(54, 16);
    oled.print("SELF");
    oled.setCursorXY(54, 28);
    oled.print("TEST");
  }
  oled.update();
}

void print_org_info(int y)
{
  oled.clear();
  oled.setScale(1);
  oled.autoPrintln(true);
  oled.setCursorXY(32, 0);
  oled.print("Информация");
  if (y == 0)
    oled.drawBitmap(0, 0, back_ico_8x8, 8, 8, BITMAP_INVERT, BUF_REPLACE);
  else
    oled.drawBitmap(0, 0, back_ico_8x8, 8, 8, BITMAP_NORMAL, BUF_REPLACE);
  oled.fastLineH(10, 0, 127);
  oled.setCursorXY(0, 16);
  if (y < 2) {
    oled.print("ИНН: ");
    oled.println(org_data.INN_data);
    oled.println();
  }
  if (y < 3) {
    oled.print("ФН: ");
    oled.println(org_data.FN_data);
    oled.println();
  }
  if (y < 4) {
    oled.print("ФД: ");
    oled.println(org_data.FD_data);
    oled.println();
  }
  if (y < 5) {
    oled.print("ФП: ");
    oled.println(org_data.FP_data);
    oled.println();
  }
  if (y < 6) {
    oled.print("РН-ККТ: ");
    oled.println(org_data.RNKKT_data);
    oled.println();
  }
  if (y < 7) {
    oled.print("ЗН-ККТ: ");
    oled.println(org_data.ZNKKT_data);
    oled.println();
  }
  if (y < 8) {
    oled.print("Адресс: ");
    oled.println(org_data.Adress_data);
    oled.println();
  }
  if (y < 9) {
    oled.print("Орг-ция: ");
    oled.println(org_data.Name_data);
    oled.println();
  }
  if (y <= 10) {
    oled.print("СНО: ");
    oled.println(org_data.SNO_data);
  }
  if(y==9)
  {
    oled.roundRect(0, 54, 127, 63, OLED_STROKE);
    oled.setCursorXY(2,55);
    oled.print("     Распечатать      ");
  }
  else if(y==10)
  {
    oled.roundRect(0, 54, 127, 63, OLED_STROKE);
    oled.setCursorXY(2,55);
    oled.invertText(true);
    oled.print("     Распечатать      ");
  }
  oled.update();
  oled.invertText(false);
}

void print_self_test()
{
  main_page(5);
  thermo_set_text_align(1);
  print_rus_symbol("            SELF TEST           ");
  MySerial.println("");
  print_rus_symbol("--------------------------------");
  MySerial.println("");
  print_rus_symbol("0 1 2 3 4 5 6 7 8 9 ! \" # $ % & ");
  MySerial.println("");
  print_rus_symbol("\' ( ) * + , - . / : ; < = > ? @ ");
  MySerial.println("");
  print_rus_symbol("A B C D E F G H J K L M N O P Q ");
  MySerial.println("");
  print_rus_symbol("R S T U V W X Y Z [ ] ^ _ ~ `   ");
  MySerial.println("");
  print_rus_symbol("a b c d e f g h j k l m n o p q ");
  MySerial.println("");
  print_rus_symbol("r s t u v w x y z { | } ~       ");
  MySerial.println("");
  print_rus_symbol("А Б В Г Д Е Ж З И Й К Л М Н О П ");
  MySerial.println("");
  print_rus_symbol("Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я ");
  MySerial.println("");
  print_rus_symbol("а б в г д е ж з и й к л м н о п ");
  MySerial.println("");
  print_rus_symbol("р с т у ф х ц ч ш щ ъ ы ь э ю я ");
  MySerial.println("");
  print_rus_symbol("--------------------------------");
  MySerial.println("");
  MySerial.println("");
  thermo_set_qrcode_size1(5);
  thermo_set_text_align(1);
  thermo_printer_QR_print1("Thermal printer", 1);
  thermo_set_qrcode_size1(6);
  print_rus_symbol("--------------------------------");
  MySerial.println("");
  thermo_set_barcode_text_position(2);
  thermo_set_barcode_width(1);
  thermo_set_barcode_height(80);
  thermo_set_text_align(1);
  thermo_print_barcode(73, "Thermal printer");
  print_rus_symbol("--------------------------------");
  MySerial.println("");
  MySerial.println("");
  thermo_set_text_align(0);
  pages = 0;
  scroll = 0;
  main_page(0);
}

void settings_page(int select_item) {
  oled.clear();
  oled.drawBitmap(0, 0, back_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);
  oled.setScale(1);
  oled.setCursorXY(38, 4);
  oled.print("Настройки");
  oled.setCursorXY(22, 20);
  oled.print("Инфо об орг-ции");
  oled.setCursorXY(22, 36);
  oled.print("SELF Тест");
  oled.setCursorXY(22, 52);
  if (buz)
    oled.print("Звук вкл.");
  else
    oled.print("Звук выкл.");
  draw_inform(1, 16);
  draw_self_test(1, 32);
  draw_dinamic(buz, 1, 48);
  //draw_dinamic(false, 1, 48);
  if (select_item == 0)
    oled.roundRect(0, 0, 16, 15, OLED_STROKE);
  else
    oled.roundRect(0, select_item * 16, 127, select_item * 16 + 15, OLED_STROKE);
  oled.update();
}


void drawBattery(byte percent) {
  oled.setScale(1);
  oled.drawByte(0b11111111);  // стенка
  for (byte i = 0; i < 10; i++) {
    if (i < (percent) / 8) oled.drawByte(0b11111111);
    else oled.drawByte(0b10000001);
  }
  if (percent > 80)
    oled.drawByte(0b11111111);  // попка
  else
    oled.drawByte(0b11100111);  // попка

  if (percent > 90)
    oled.drawByte(0b00111100);  // попка
  else
    oled.drawByte(0b00100100);  // попка
  oled.drawByte(0b00111100);
  oled.setScale(2);
}

void draw_ble(bool power, int x, int y)  // heigth 11 px
{
  oled.setCursorXY(x, y);
  oled.setScale(1);
  if (power) {
    oled.drawByte(0b10000100);
    oled.drawByte(0b01001000);
    oled.drawByte(0b00110000);
    oled.drawByte(0b11111111);
    oled.drawByte(0b00100001);
    oled.drawByte(0b01010010);
    oled.drawByte(0b10001100);

    oled.setCursorXY(x, y + 8);

    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000111);
    oled.drawByte(0b00000100);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000001);
  } else {
    oled.drawByte(0b00000001);
    oled.drawByte(0b00000010);
    oled.drawByte(0b10000100);
    oled.drawByte(0b01001000);
    oled.drawByte(0b00110000);
    oled.drawByte(0b11111111);
    oled.drawByte(0b00100001);
    oled.drawByte(0b01010010);
    oled.drawByte(0b10001100);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);

    oled.setCursorXY(x, y + 8);

    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000000);
    oled.drawByte(0b00000111);
    oled.drawByte(0b00000100);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000001);
    oled.drawByte(0b00000001);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000100);
  }
  oled.setScale(2);
}

void draw_settings(int x, int y) {
  oled.setCursorXY(x, y);

  oled.drawBitmap(x, y, settings_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);
  /*
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b11110000);
  oled.drawByte(0b11111100);
  oled.drawByte(0b10001110);
  oled.drawByte(0b10000110);
  oled.drawByte(0b10000010);
  oled.drawByte(0b11000000);
  oled.drawByte(0b11100000);
  oled.drawByte(0b01110000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);

  oled.setCursorXY(x, y + 8);

  oled.drawByte(0b00000000);
  oled.drawByte(0b00110000);
  oled.drawByte(0b00111000);
  oled.drawByte(0b00011100);
  oled.drawByte(0b00001110);
  oled.drawByte(0b00000111);
  oled.drawByte(0b00000011);
  oled.drawByte(0b00000001);
  oled.drawByte(0b00000001);
  oled.drawByte(0b00000001);
  oled.drawByte(0b00000001);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  oled.drawByte(0b00000000);
  */
}
void draw_self_test(int x, int y) {
  oled.setCursorXY(x, y);
  
  oled.drawBitmap(x, y, self_test_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);
  /*
  oled.drawByte(0b00000000);
  oled.drawByte(0b11111000);
  oled.drawByte(0b00000100);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b10000010);
  oled.drawByte(0b11000010);
  oled.drawByte(0b00000100);
  oled.drawByte(0b11111000);
  oled.drawByte(0b00000000);

  oled.setCursorXY(x, y + 8);

  oled.drawByte(0b00000000);
  oled.drawByte(0b00011111);
  oled.drawByte(0b00100000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000011);
  oled.drawByte(0b01000110);
  oled.drawByte(0b01001100);
  oled.drawByte(0b01011000);
  oled.drawByte(0b01001100);
  oled.drawByte(0b01000110);
  oled.drawByte(0b01000011);
  oled.drawByte(0b01000001);
  oled.drawByte(0b01000000);
  oled.drawByte(0b00100000);
  oled.drawByte(0b00011111);
  oled.drawByte(0b00000000);
  */
}

void draw_inform(int x, int y) {
  oled.setCursorXY(x, y);
  
  oled.drawBitmap(x, y, inform_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);

/*
  oled.drawByte(0b00000000);
  oled.drawByte(0b11111000);
  oled.drawByte(0b00000100);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b01100010);
  oled.drawByte(0b01100010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000010);
  oled.drawByte(0b00000100);
  oled.drawByte(0b11111000);
  oled.drawByte(0b00000000);

  oled.setCursorXY(x, y + 8);

  oled.drawByte(0b00000000);
  oled.drawByte(0b00011111);
  oled.drawByte(0b00100000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01011111);
  oled.drawByte(0b01011111);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b01000000);
  oled.drawByte(0b00100000);
  oled.drawByte(0b00011111);
  oled.drawByte(0b00000000);
  */
}

void draw_dinamic(bool zvuk, int x, int y) {
  oled.setCursorXY(x, y);
  if (zvuk) {
    oled.drawBitmap(x, y, yes_dinamic_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);
    /*
    oled.drawByte(0b00000000);
    oled.drawByte(0b11111000);
    oled.drawByte(0b00000100);
    oled.drawByte(0b00000010);
    oled.drawByte(0b11000010);
    oled.drawByte(0b11000010);
    oled.drawByte(0b11000010);
    oled.drawByte(0b11100010);
    oled.drawByte(0b11110010);
    oled.drawByte(0b11111010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000100);
    oled.drawByte(0b11111000);
    oled.drawByte(0b00000000);

    oled.setCursorXY(x, y + 8);

    oled.drawByte(0b00000000);
    oled.drawByte(0b00011111);
    oled.drawByte(0b00100000);
    oled.drawByte(0b01000000);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000111);
    oled.drawByte(0b01001111);
    oled.drawByte(0b01011111);
    oled.drawByte(0b01000000);
    oled.drawByte(0b01000000);
    oled.drawByte(0b01000000);
    oled.drawByte(0b00100000);
    oled.drawByte(0b00011111);
    oled.drawByte(0b00000000);
    */
  } else {
    oled.drawBitmap(x, y, no_dinamic_ico_16x16, 16, 16, BITMAP_NORMAL, BUF_REPLACE);
    /*
    oled.drawByte(0b00000000);
    oled.drawByte(0b11111000);
    oled.drawByte(0b00000100);
    oled.drawByte(0b00000010);
    oled.drawByte(0b11001010);
    oled.drawByte(0b11010010);
    oled.drawByte(0b11100010);
    oled.drawByte(0b11100010);
    oled.drawByte(0b11110010);
    oled.drawByte(0b11111010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000010);
    oled.drawByte(0b00000100);
    oled.drawByte(0b11111000);
    oled.drawByte(0b00000000);

    oled.setCursorXY(x, y + 8);

    oled.drawByte(0b00000000);
    oled.drawByte(0b00011111);
    oled.drawByte(0b00100000);
    oled.drawByte(0b01000000);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000011);
    oled.drawByte(0b01000111);
    oled.drawByte(0b01001111);
    oled.drawByte(0b01011111);
    oled.drawByte(0b01000010);
    oled.drawByte(0b01000100);
    oled.drawByte(0b01001000);
    oled.drawByte(0b00100000);
    oled.drawByte(0b00011111);
    oled.drawByte(0b00000000);
    */
  }
}
