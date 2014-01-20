#include <SoftwareSerial.h>

SoftwareSerial lcd(2, 3);  // This is required, to start an instance of an LCD
int year = 11;  // Enter the current year here, 11 = 2011
int month = 6;  // Enter the current month here, 6 = June
int date = 20;  // Enter the current date here
int day = 1;  // 0 = Sunday, 6 = Saturday
int hours = 23;  // Enter the hours here
int minutes = 59;  // Enter the minutes here
int seconds = 50;  // Enter the seconds here

void setup()
{
  lcd.begin(9600);  // Start the LCD at 9600 baud
  clearDisplay();  // Clear the display
  setLCDCursor(2);  // Set cursor to the 3rd spot, 1st line
  lcd.print("Hello, world");
  setLCDCursor(16);  // Set the cursor to the beginning of the 2nd line
  lcd.print("Running clock...");
  
  // Flash the backlight:
  for (int i=0; i<3; i++)
  {
    setBacklight(0);
    delay(250);
    setBacklight(255);
    delay(250);
  }
}

void loop()
{
  if (!(millis() % 1000))  // If it's been 1 second
  {
    checkTime();  // this function increases the time and date if necessary
    clearDisplay();  // Clear the display
    setLCDCursor(1);  // set cursor to 2nd spot, 1st row
    printDay();  // print the day
    lcd.print(" ");
    lcd.print(month);  // print the date:
    lcd.print("/");
    lcd.print(date);
    lcd.print("/");
    lcd.print(year);
    
    setLCDCursor(20);  // set the cursor to the 5th spot, 2nd row
    lcd.print(hours);  // print the time:
    lcd.print(":");
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);
  }
}

void setBacklight(byte brightness)
{
  lcd.write(0x80);  // send the backlight command
  lcd.write(brightness);  // send the brightness value
}

void clearDisplay()
{
  lcd.write(0xFE);  // send the special command
  lcd.write(0x01);  // send the clear screen command
}

void setLCDCursor(byte cursor_position)
{
  lcd.write(0xFE);  // send the special command
  lcd.write(0x80);  // send the set cursor command
  lcd.write(cursor_position);  // send the cursor position
}

void printDay()
{
  switch(day)
  {
    case 0:
      lcd.print("Sun.");
      break;
    case 1:
      lcd.print("Mon.");
      break;
    case 2:
      lcd.print("Tue.");
      break;
    case 3:
      lcd.print("Wed.");
      break;
    case 4:
      lcd.print("Thur.");
      break;
    case 5:
      lcd.print("Fri.");
      break;
    case 6:
      lcd.print("Sat.");
      break;
  }
}
      
void checkTime()
{
  seconds++;  // increase seconds
  if (seconds == 60)  // If it's been a minute
  {
    seconds = 0;  // start over seconds
    minutes++;  // Increase minutes
    if (minutes == 60)  // If it's been an hour
    {
      minutes = 0;  // start over minutes
      hours++;  // increase hours
      if (hours == 24)  // If it's been a day
      {
        hours = 0;  // start the day over
        day++;  // increase the day
        if (day == 7)  // if it's been a week
          day = 0;  // start the week over
        date++;  // increase the date
        checkDate();  // this function increases the date/month/year if necessary
      }
    }
  }
}

void checkDate()
{
  // 30 days has sept. apr. jun. and nov.
  if (((month == 9)||(month == 4)||(month == 6)||(month == 11))&&
      (date > 30))
  {
    date = 1;
    month++;
  }
  else if ((month == 2)&&(date > 28))
  {
    date = 1;
    month++;
  }
  else if (date > 31)
  {
    date = 1;
    month++;
    if (month > 12)
    {
      month = 1;
      year++;  // happy new year!
      clearDisplay();
      lcd.print("Happy New Year!");
      delay(5000);
      seconds+=5;
    }
  }
}
