/*
 Project:  Intro-2-Variables         Activity: mirobo.tech/arps-intro-2
 Date:     April 3, 2024

 This introductory programming activity for the mirobo.tech ARPS circuit
 demonstrates the use of constants and variables to count button presses and 
 the use of conditions to trigger an action when a limit is reached.
 
 Additional program analysis and programming activities demonstrate the use of
 Boolean (or bool) variables to store state during successive program loops,
 the creation of a two-player rapid-clicker game, simulation of real-world
 toggle and multi-function buttons, and encourages learners to create program
 code to measure and mitigate switch contact bounce.

  See the https://mirobo.tech/arps website for more programming activities.
*/

// Define I/O pins used by ARPS human interface devices
const int SW2 = 0;      // Pushbuttons SW2 and SW3 are supported on Arduino
const int SW3 = 1;      // UNO R4 Minima and Arduino UNO R4 WiFi
const int SW4 = 2;      // Pushbuttons SW4 and SW5 work on all Arduino UNO R3
const int SW5 = 3;      // and Arduino UNO R4 circuit boards

const int LED2 = 5;     // ARPS LEDs
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;

const int BEEPER = 11;  // ARPS Piezo beeper LS1

// Define program constants
const int maxCount = 50;

// Define program variables
int SW2State;
int SW3State;
int SW4State;
int SW5State;

int SW2Count = 0;
bool SW2Pressed = false;

// Setup code runs once to configure I/O pins before running the main loop
void setup() {
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BEEPER,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  tone(BEEPER,4000,100);  // Say hello!
}

// Main loop code repeats forever
void loop() {
  SW2State = digitalRead(SW2);    // Change to SW4 for Arduino UNO R3
  SW5State = digitalRead(SW5);
  
  // Count SW2 button presses
  if(SW2State == LOW) {
    digitalWrite(LED2,HIGH);
    SW2Count = SW2Count + 1;
  }
  else {
    digitalWrite(LED2,LOW);
  }
  
  // Light LED D3 when the maximum count has been reached
  if(SW2Count >= maxCount) {
    digitalWrite(LED3,HIGH);
  }
  
  // Turn off LED D3 and reset count if SW5 is pressed
  if(SW5State == LOW) {
    digitalWrite(LED3,LOW);
    SW2Count = 0;
  }
  
  delay(10);  // Added delay helps simulators run this program
}

/* Learn More -- Program Analysis Activities
 * 
 * 1. The 'SW2Count' variable is created as a 16-bit memory location within the
 *    microcontroller's RAM by the program declaration: 'int SW2Count = 0;'
 * 
 *    What is the range of numbers a 16-bit int variable can store? What will
 *    happen if you try to store a number larger than the upper limit of an
 *    'int' in the SW2Count variable? 
 * 
 * 2. The program constant 'maxCount' is defined using a declaration similar to
 *    that used for the I/O pin constants. How does the Arduino IDE know that
 *    'SW2' is a hardware I/O pin, and that 'maxCount' is a number?
 *
 * 3. The maxCount constant is used by the statement 'if(SW2Count >= maxCount)'
 *    to check if the maximum count has been reached. It seems like a lot of
 *    work to define a constant when the program could have simply been written
 *    to use the statement 'if(SW2Count >= 50)' instead. 
 * 
 *    Can you think of any advantages of going to the trouble of declaring the
 *    maxCount constant in the program header, rather than just embedding the
 *    value of the desired constant into the program code?
 * 
 * 4. This program should light LED D2 every time SW2 is pressed, and light
 *    LED D3 once the count reaches 50. Try the program, mentally counting how
 *    many times the button has been pressed before LED D3 turns on. SW5
 *    resets the count so you can perform repeated attempts.
 * 
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: Compare what happens when you press and quickly release the 
 *    button, with what happens when you press and slowly release the button.)
 * 
 * 5. Let's add some debugging code after the second conditional block to help
 *    us figure out exactly what this program is doing. We can add a new 'if'
 *    structure to the program to override the LED D3 output if the SW2Count
 *    variable goes way out of range – let's make it a value that is 10 times
 *    larger than the count we are expecting. Here is what your code should
 *    look like with the second 'if' condition added:

  // Light LED D3 when the maximum count has been reached
  if(SW2Count >= maxCount) {
    digitalWrite(LED3,HIGH);
  }
  // Turn off LED D3 if the real count is huge.
  if(SW2Count >= maxCount * 10) {
    digitalWrite(LED3,LOW);
  }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D3. When the value of SW2Count becomes higher than maxCount, LED D3
 *    should stay lit until it reaches ten times maxCount. Does the count go
 *    that high? If it does, can you explain how that could possibly happen
 *    while SW2 is only being pressed once?
 * 
 * 6. One fundamental challenge with many microcontroller programs is that the
 *    statements in the loop() function run repeatedly, meaning that the state
 *    of any inputs (for example pushbutton SW2) will be checked every time
 *    the program re-runs the loop. This is not a problem if the program uses
 *    SW2 to turn an LED on or off as Activity 1 did, but it is a problem if
 *    the program is trying to count button presses since another count will
 *    be added for every loop that SW2 is still pressed. In other words, the
 *    SW2Count variable in this program is not counting each SW2 press, but is
 *    instead counting the number of loops during which SW2 remains pressed.
 *    Since microcontrollers are fast, this count adds up very quickly!
 * 
 *    How can we solve this problem? Instead of responding to the state of a
 *    button, the program will have to be made to respond to a *change* of 
 *    state. It would be ideal if the the program could be (re-)written
 *    to sense the change from the not-pressed state to the pressed state.
 *
 *    Just as the program uses a variable to store the current state of SW2,
 *    a second variable can be added to store the prior state, allowing a 
 *    change of state can be detected by comparing the two over time. Below
 *    is the program code to do just just that using the SW2Pressed Boolean
 *    (bool) variable previously defined in the program header. Boolean
 *    variables can store one of two values, either 'false' or 'true'.
 *
 *    Check the program header to see the value that SW2Pressed is initialized
 *    with, and then replace the initial SW2 'if-else' conditional structure 
 *    with the following two if condition structures:

  // Count SW2 button presses
  if(SW2State == LOW && SW2Pressed == false) {
    digitalWrite(LED2,HIGH);
    SW2Pressed = true;
    SW2Count += 1;
  }

  if(SW2State == HIGH) {
    digitalWrite(LED2,LOW);
    SW2Pressed = false;
  }
        
 *    The first 'if' condition now uses two conditions that must both be true
 *    (using the logical AND operator introduced in Activity 1). In this case
 *    SW2 must be pressed, and the SW2Pressed variable must be false, in order
 *    to count as a new button press. After turning LED2 on, the SW2Pressed
 *    Boolean variable is set to be true before the SW2Count is incremented
 *    using the compound operator in the statement 'SW2Count += 1;' (this
 *    produes the same result as the original SW2Count = SW2Count + 1; 
 *    statement, but with less code.
 * 
 *    After the SW2Pressed variable has been set to true, the next loop
 *    during which SW2 is stil pressed will cause the 'if' condition to be
 *    false, and won't count the same SW2 press a second time. Unfortunately,
 *    it will also fail to detect the next legitimate SW2 press. A second
 *    'if' condition is used instead of the original 'else' statement to turn
 *    off the LED and to reset the SW2Pressed Boolean to false once SW2 is
 *    released. This allows the count to increase only when SW2 is first
 *    pressed after being released. Try this modified program code to verify
 *    that it works, and that it properly counts every individual SW2 press.
 * 
 * 7. The conditional statement in the first if condition can also be written:

  if(SW2State == LOW && !SW2Pressed) {

 *    The '!SW2Pressed' expression is read as 'not SW2Pressed' and is equivalent
 *    to SW2Pressed being false (or *not* true). Similarly, using a Boolean
 *    variable's name by itself in a conditional statement (eg. SW2Pressed)
 *    would be equivalent to checking it for being true. Try this expression in
 *    your program and verify that it works as expected.
 * 
 * 8. The pushbutton's state can also be re-defined using a constant declaration
 *    to help make the code more readable. Add the following lines to the
 *    'Define program constants' section in the program header:
 
const int pressed = LOW;
const int notPressed = HIGH;

 *    Now, instead of comparing the state of the button to Low or HIGH, the
 *    button input can be compared to the newly-named definitions. Doing this 
 *    can help to make programs more readable, at the expense of using extra
 *    code (and potentially introducing problems with pushbutton circuits that
 *    activate using a HIGH level when pressed).
 * 
 *    Try this code in your program, and then modify the SW3 reset button code 
 *    to use the same 'pressed' and 'notPressed' definitions.
 
  // Count SW2 button presses
  if(SW2State == pressed && !SW2Pressed) {
    digitalWrite(LED2,HIGH);
    SW2Pressed = true;
    SW2Count += 1;
  }

  if(SW2State == notPressed) {
    digitalWrite(LED2,LOW);
    SW2Pressed = false;
  }
  
 * 9. Can you create similar constants for the terms 'on' and 'off' so that
 *    the LEDs in your circuit can be controlled using statements like
 *    'digitalWrite(LED2,on);' instead of 'digitalWrite(LED2,HIGH);'? Try it!
 * 
 * Programming Activities
 * 
 * 1. Make a two-player rapid-clicker style game using this program as a
 *    starting point. The purpose of the game will be to see which user can
 *    press their button the fastest and be first to reach the maximum count
 *    in the game!
 *
 *    Begin by planning which button to use for the second player, and which
 *    LEDs to light as they play. Then start by duplicating the required
 *    variables in the program. If using SW5 for the second player, for 
 *    example, duplicate player one's SW2Count and SW2Pressed variables to
 *    create similar SW5count and SW5pressed variables for player two. Then,
 *    duplicate the if condition structures in the program loop and modify
 *    them to use the new variables representing the second player.
 *
 *    Decide if LED D3 will still be the one that lights if player one wins, or 
 *    choose a different LED for player 1. Then pick an LED to light if player
 *    two reaches maxCount first to become the winner. Use a conditional
 *    statement to reset the game, remembering to turn off the winner's LED
 *    and to clear both players' count variables if either of the other
 *    pushbuttons is pressed.
 * 
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button must 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.) Pressing and holding the
 *    toggle button should only cause the LED to toggle once, and not keep
 *    toggling or switching the output between on and off continuously, until
 *    the button is released and pressed again.
 * 
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when it is held. A multi-function button can
 *    be implemented by using a variable that counts loop cycles (exactly as this
 *    original program did unitentionally for counting button presses). Make a
 *    multifunction button that lights one LED as soon as a button is pressed,
 *    lights a second LED if the button is held for more that one second, and
 *    turns off both LEDs after the button is released.
 * 
 * 4. Do your pushbuttons bounce? Switch bounce is the term used to describe
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, because we wouldn't notice the lights rapidly flashing
 *    before staying on. But, switch bounce is an issue in a microcontroller
 *    toggle button program because the fast speed of a microcontroller lets
 *    it see each bounce as a new, separate event, potentially making it 
 *    perform multiple actions in response to a single button press.
 * 
 *    Create a program that uses a variable to count the number of times a
 *    pushbutton's contacts close and then display the count on the LEDs.
 *    Comment-out the delay(10); statement in the main loop to ensure short
 *    bounce events won't be missed. Use a second pushbutton to reset the 
 *    count and turn off the LEDs so that the test can be repeated. To
 *    determine if your pushbuttons bounce, try pressing them at various 
 *    speeds and with different amounts of force. Most of the small
 *    pushbuttons on circuits such as ARPS are very reliable and won't
 *    bounce, or will occasionally bounce just once. Try each of the 
 *    pushbuttons on your circuit to see if any exhibit switch bounce.
 * 
 * 5. Did any of your pushbuttons bounce? Typical switch bounces appear as
 *    multiple switch activations within an approximatley 20ms time span after
 *    being pressed. Can you think of a simple software technique that could
 *    be implemented to ignore multiple switch activations within a 20ms span?
 *
 *    External switches can be connected to the ARPS header pins or optical
 *    floor module I/O pins to check for bounce as well. Try to find a switch
 *    that exhibits switch bounce and then add your de-bouncing code to the
 *    bounce counting program, above, to verify the effectiveness of your
 *    de-bouncing code.
 */

