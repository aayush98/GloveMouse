#include <Mouse.h>
//#include <Math.h>

const int xIn = 4;              // X output
const int yIn = 8;              // Y output
const int leftPin = A2;
const int rightPin = A0;
int countLeft;
int countRight;
void setup()
{
  countLeft = 0;
  countRight = 0;
  Serial.begin(9600);
  Mouse.begin();
}

void loop()
{
  // variables to read the pulse widths:
  int pulseX, pulseY;


  pulseX = (pulseIn(xIn, HIGH)); //Read value from X-axis sensor
  pulseY = (pulseIn(yIn, HIGH)); //Read value from Y-axis sensor
  pulseX = map(pulseX, 4200, 6200, -5, 5);
  pulseY = map(pulseY, 4500, 5700, -5, 5);
  pulseX = (!(abs(pulseX) < 2)*pulseX);
  pulseY = (!(abs(pulseY) < 2)*pulseY);

  /*Serial.print(pulseX);	       // Display X and Y values <-Serial moniter test lines
  Serial.print("\t");
  Serial.println(pulseY);
*/

  Mouse.move(pow(2,pulseX), pow(2,pulseY), 0);
  boolean leftClick = (analogRead(leftPin) > 1015);
  boolean rightClick = (analogRead(rightPin) > 1015);
  if(leftClick)
  {
    if(countLeft > 10)
    {
      Mouse.press(MOUSE_LEFT);
    }
    else if(!Mouse.isPressed())
    {
      countLeft++;
    }
  }
  else
  {
    Mouse.release(MOUSE_LEFT);
    countLeft = 0;
  }

  if(rightClick)
  {
  if(countRight > 10)
  {
    Mouse.press(MOUSE_RIGHT);
  }
  else if(!Mouse.isPressed())
  {
    countRight++;
  }
  }
  else
  {
    Mouse.release(MOUSE_RIGHT);
    countRight = 0;
  }

  delayMicroseconds(500);
}
