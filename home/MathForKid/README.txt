Project Name: Addition application with Arduino
By: Vedat Ozan Oner

Description:
This application is for kids to help them to study math. This version starts with addition/subtraction operation.
Addition:
1- Basic: addition of same numbers like 2+2, 3+3 etc. And addition of multiples of 2 and 3 like 2+4, 2+6, 3+6, 3+9 etc.
2- Intermediate: addition of one digit numbers
3- Advanced: addition of 2 digit numbers
4- Time-limited quiz.
Subtraction:
1- Basic: 1 digit subtraction
2- Intermediate: 1 digit result
3- Advanced: 2 digit operations
4- Time-limited quiz.

Requirements:
1- When someone approaches (detection by PIR motion sensor), take attention by using buzzer and LED.
2- When a key pressed on keypad, show add/subtract selection, acc.to selection
 show level menu and wait for selection ('1', '2', or '3', and then '*'. '*' means enter in this application)
3- According to selection, randomize a question and wait for an answer. (answer + '*')
4- ask for answer until it is correct. at most 3 try. if still false, then show the correct answer
5- upon entering an answer, show different signalling accr.to correctness. if the answer is correct, 2 beep+blink led. if wrong, 3 secs single beep with led on.
6- there will be no signalling in quiz. just show the numbers on the second line of LCD.
7- '#' returns to one-level up menu.
8- if remains idle for 5 minutes, turn LCD off, and begin to monitor environment by PIR sensor.
9- ADKeyboard is just for fun. you can show random messages, or ask for singing, or stg else whatever you like :) 
