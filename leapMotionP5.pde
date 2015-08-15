// シリアルライブラリを取り入れる
import processing.serial.*;

//leapmotion
import com.leapmotion.leap.Finger;
import com.leapmotion.leap.Hand;
import com.onformative.leap.LeapMotionP5;
import ddf.minim.*;

LeapMotionP5 leap;
Serial serial;

final int xsize = 100;
final int ysize = 100;

PVector fingerPos = new PVector(0,0,0);  // 現フレームの指座標
int preFinNum = 0;
String ack = "";

void setup(){
  // 画面サイズ
  size(xsize,ysize);
  background(255);
  noStroke();
  leap = new LeapMotionP5(this);
  
  serial = new Serial(this, "/dev/cu.usbmodem1411", 9600);
  /*
  serial.write('s');
  while (!ack.equals("A")){
    delay(1000);
    println("sleeping");
  }
  //ack = serial.readString();
  serial.write('B');
  */
  delay(1500);
  serial.clear();
}

void draw(){
  delay(200);
  background(255);
  ArrayList<Finger> fingers = leap.getFingerList();
  // reset
  if (fingers.size() == 10){
    println("reset");
    serial.write('a');
    serial.write(9);
    serial.write(9);
    serial.write(9);
    serial.write(9);
    return;
  }
  
  if (fingers.size() > 2 || fingers.size() == 0){
    return;
  }
  
  fingerPos = leap.getTip(fingers.get(fingers.size()-1));
  int decideFlag = 0;
  int fingersNum = fingers.size();
  PVector vs = leap.getVelocity(fingers.get(fingers.size()-1));
  float vSum = vs.x + vs.y + vs.z;
  
  if(fingersNum == 1 && preFinNum == 2 && vSum < 30){
     decideFlag = 1;
  }else{
     decideFlag = 0; 
  }
  preFinNum = fingersNum;
  
  int x = round(map(fingerPos.x,0,xsize,0,3));
  x = boundLowUp(x);
  int y = round(map(ysize - fingerPos.y,30,ysize,0,3));
  y = boundLowUp(y);
  int z = round(map(fingerPos.z,-80,80,0,3));
  z = boundLowUp(z);
  println(x+" "+y+" "+z);
  
  serial.write('a');
  serial.write(x);
  serial.write(y);
  serial.write(z);
  serial.write(decideFlag);
  ack = "";
  
  if(decideFlag == 1){
    println("decide");
    delay(1000); 
  }
  
  // debug
  noStroke();
  textSize(18);          // 文字サイズ
  textAlign(LEFT);       // 文字揃え
  fill(0, 0, 0);         // 黒ß
  text("X " + x, 15, 15);
  text("Y " + y, 15, 45);
  text("Z " + z, 15, 75);
  text("F " + decideFlag, 15, 100);
  text("V " + vSum, 15, 100);
  //println("ok2");
}

int boundLowUp(int a){
  if (a > 3){
    return 3;
  }
  if (a < 0){
    return 0;
  }
  return a;
}
