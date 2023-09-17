import processing.serial.*; // imports library for serial communication
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;
Serial myPort; // defines Object Serial
// defubes variables
String angle="";
String distance="";
String distance2="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance, iDistance2;
int index1=0;
int index2=0;
PFont orcFont;
void setup() {
  
 //size (1920, 1080);
 size (1320,780);
 smooth();
 myPort = new Serial(this,"COM8", 9600); // starts the serial communication
 myPort.bufferUntil('.'); // reads the data from the serial port up to the character '.'. So actually it reads this: angle,distance.
 orcFont = loadFont("Arial-Black-20.vlw");
}
void draw() {
  
  fill(98,245,31);
  //fill(0, 0, 209);
  textFont(orcFont);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0,4); 
  rect(0, 0, width, 1010); 
  
  fill(28,245,31); // green color
  // calls the functions for drawing the radar
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}
void serialEvent (Serial myPort) { // starts reading data from the Serial Port
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('.');
  data = data.substring(0,data.length()-1);
  
  index1 = data.indexOf(","); // find the character ',' and puts it into the variable "index1"
  index2 = data.indexOf("!");
  angle= data.substring(0, index1); // read the data from position "0" to position of the variable index1 or thats the value of the angle the Arduino Board sent into the Serial Port
  //distance= data.substring(index1+1, data.length()); // read the data from position "index1" to the end of the data pr thats the value of the distance
  distance= data.substring(index1+1, index2);
  distance2= data.substring(index2+1, data.length());
  
  
  // converts the String variables into Integer
  iAngle = int(angle);
  iDistance = int(distance);
  iDistance2 = int(distance2);
}
void drawRadar() {
  pushMatrix();
  translate(600,350); // moves the starting coordinats to new location
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  // draws the circle lines
  circle(0,0,100);
  circle(0,0,200);
  circle(0,0,300);
  circle(0,0,400);
  circle(0,0,500);
 
  // draws the angle lines

  line(0,0,-250*cos(radians(30)),-250*sin(radians(30)));
  line(0,0,-250*cos(radians(60)),-250*sin(radians(60)));
  line(0,0,-250*cos(radians(90)),-250*sin(radians(90)));
  line(0,0,-250*cos(radians(120)),-250*sin(radians(120)));
  line(0,0,-250*cos(radians(150)),-250*sin(radians(150)));
  
  line(0,0,-250*cos(radians(210)),-250*sin(radians(210)));
  line(0,0,-250*cos(radians(240)),-250*sin(radians(240)));
  line(0,0,-250*cos(radians(270)),-250*sin(radians(270)));
  line(0,0,-250*cos(radians(300)),-250*sin(radians(300)));
  line(0,0,-250*cos(radians(330)),-250*sin(radians(330)));
  
  line(-280*cos(radians(30)),0,250,0);
  popMatrix();
}
void drawObject() {
  pushMatrix();
  translate(600,350); // moves the starting coordinats to new location
  strokeWeight(15);
  stroke(255,10,10); // red color
  pixsDistance = iDistance*10; // covers the distance from the sensor from cm to pixels
  // limiting the range to 50 cms
  if(iDistance<50){
    // draws the object according to the angle and the distance
  point(pixsDistance*cos(radians(iAngle*-1)),-pixsDistance*sin(radians(iAngle*-1)));
  }
  
    strokeWeight(15);
  stroke(255,10,10); // red color
  pixsDistance = iDistance2*10; // covers the distance from the sensor from cm to pixels
  
    // limiting the range to 50 cms
  if(iDistance2<50){
    // draws the object according to the angle and the distance
  point(pixsDistance*cos(radians(iAngle*-1)),-pixsDistance*sin(radians(iAngle*-1)));
  }
  popMatrix();
}
void drawLine() {
  pushMatrix();
  strokeWeight(5);
  stroke(30,250,60);
  translate(600,350); // moves the starting coordinats to new location
  line(0,0,500*cos(radians(iAngle*-1)),-500*sin(radians(iAngle*-1))); // draws the line according to the angle
  popMatrix();
}
void drawText() { // draws the texts on the screen
  
  pushMatrix();
  if(iDistance>50) {
  noObject = "";
  }
  else {
  noObject = "Aircraft detected";
  }
  if(iDistance2>50) {
  noObject = "";
  }
  else {
  noObject = "Aircraft detected";
  }
  fill(0,0,0);
  noStroke();
  rect(0, 1010, width, 1080);
  fill(98,245,31);
  textSize(15);
  text("5cm",620,345);
  text("10cm",660,345);
  text("15cm",710,345);
  text("20cm",760,345);
  text("30cm",810,345);
  textSize(25);
  text("" + noObject, 150, 670);
  text("Angle: " + iAngle +" °", 500, 670);
  text("Distance: ", 700, 670);
  if(iDistance<50) {
  text(iDistance +"  cm", 840, 670);
  }
  textSize(25);
  text("" + noObject, 150, 670);
  if(iDistance2<50) {
  text(iDistance2 +"  cm", 840, 670);
  }
  textSize(25);
  //fill(98,245,60);
  fill(204, 102, 0);
  //translate(960+500*cos(radians(30)),500-500*sin(radians(30)));
  translate(820,210);
  rotate(-radians(-60));
  text("60°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(60)),500-500*sin(radians(60)));
  translate(720,120);
  rotate(-radians(-30));
  text("30°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(90)),990-960*sin(radians(90)));
  translate(595,90);
  rotate(radians(0));
  text("0°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(120)),500-500*sin(radians(120)));
  translate(440,140);
  rotate(radians(-30));
  text("330°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(150)),500-500*sin(radians(150)));
  translate(360,240);
  rotate(radians(-60));
  text("300°",0,0);
  //translate(450-500*cos(radians(30)),750+500*sin(radians(30)));
  translate(50,520);
  rotate(-radians(+180));
  text("120°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(60)),500+500*sin(radians(60)));
  translate(745,565);
  rotate(-radians(-150));
  text("150°",0,0);
  resetMatrix();
  //translate(960-970*cos(radians(90)),500+500*sin(radians(90)));
  translate(630,605);
  rotate(radians(-180));
  text("180°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(240)),500-500*sin(radians(240)));
  translate(480,590);
  rotate(radians(+210));
  text("210°",0,0);
  resetMatrix();
  //translate(960+500*cos(radians(150)),500+600*sin(radians(150)));
  translate(380,500);
  rotate(radians(+240));
  text("240°",0,0);
  resetMatrix();
  translate(340,360);
  rotate(radians(-90));
  text("270°",0,0);
  resetMatrix();
  //translate(1462,500);
  translate(860,330);
  rotate(radians(+90));
  text("90°",0,0);
  popMatrix(); 
}
