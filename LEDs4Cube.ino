int cube[4][4][4] = {0}; // y x z

int verticalPin[4][4] = {
  {52,53,50,51},
  {44,45,42,43},
  {38,39,36,37},
  {30,31,28,29}
}; // x z

int layerPinRed[4] = {2,3,4,5}; // y
int layerPinBlue[4] = {9,10,11,12};

int player = 1;
int playerSignal[2] = {24,25}; // player 1 & player 2

/*
 D    cube
 2   layer1
 3   layer2
 4   layer3
 5   layer4

 ___________ . <-red black wire
 |  |  |  |  |  52 44 38 30
 |  |  |  |  |  53 45 39 31
 |  |  |  |  |  50 42 36 28
 |  |  |  |  |  51 43 37 29
 -----------
 */
int x;
int y;
int z;
int decideFlag;

int preX = -1;
int preY = -1;
int preZ = -1;
int firstSelect = 1;

int overlapFlag = 0; // overlapしてたら1
int overlapColor = 0;
int preColor = -1;

int lightSpan = 5000;
int count = lightSpan; // ダイナミック点灯用

void setup(){
  Serial.begin(9600);
  /*
  // 通信開始処理
  while(Serial.available() == 0){
  }
  //Serial.print(Serial.read());
  char tmp;
  if(Serial.available() > 0){
    tmp = Serial.read();
  }
  while(Serial.available() == 0){
    delay(100);
    Serial.print('A');
  }
  Serial.println();
  */
  // pinの設定
  for(int i=0; i<4; i++){
    pinMode(layerPinRed[i], OUTPUT);
    pinMode(layerPinBlue[i], OUTPUT);
    digitalWrite(layerPinRed[i], LOW);
    digitalWrite(layerPinBlue[i], LOW);
  }
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      pinMode(verticalPin[i][j], OUTPUT);
      digitalWrite(verticalPin[i][j], LOW);
    }
  }

  pinMode(playerSignal[0], OUTPUT);
  pinMode(playerSignal[1], OUTPUT);
  digitalWrite(playerSignal[0], HIGH);
  digitalWrite(playerSignal[1], LOW);
}

void loop(){

  if(Serial.available() > 4){
    char start = Serial.read();
    if(start == 'a'){
      x = Serial.read();
      y = Serial.read();
      z = Serial.read();
      decideFlag = Serial.read();
    }
  }
  else{
    dynamicLight();
    return;
  }

  if(x == 9 && y == 9 && z == 9 && decideFlag == 9){
    resetAll();
    return;
  }

  setLED(x,y,z,-1);
  dynamicLight();

  if(firstSelect == 0 && (x != preX || y != preY || z != preZ)){
    if (overlapFlag == 1){
      resetOverlap(preX, preY, preZ);
    }
    turnOffTrack(preX, preY, preZ);
  }

  if(isRedOrBlue(x,y,z) == 1){
    overlap(x,y,z);
  }

  if(decideFlag == 1){ // 決定された
    if(setLED(x,y,z,player) == 1){
      if(checkBingo() == 1){;
        winLight();
        resetAll();
      }
      digitalWrite(playerSignal[player-1], LOW);
      player = player == 1 ? 2 : 1;
      digitalWrite(playerSignal[player-1], HIGH);
      preX = -1;
      preY = -1;
      preZ = -1;
      firstSelect = 1;
      return;
    }
  }

  preX = x;
  preY = y;
  preZ = z;
  firstSelect = 0;
}

int setLED(int x, int y, int z, int color){
  if(cube[y][x][z] == 0 || cube[y][x][z] == -1){
    cube[y][x][z] = color;
    return 1;
  }
  else{
    return -1;
  }
}

int isRedOrBlue(int x, int y, int z){
  if(cube[y][x][z] == 1 || cube[y][x][z] == 2){
    return 1;
  }else{
    return 0;
  }
}

void overlap(int x, int y, int z){
  overlapFlag = 1;
  overlapColor = cube[y][x][z];
  preColor = overlapColor;
}

void resetOverlap(int x, int y, int z){
  overlapFlag = 0;
  cube[y][x][z] = overlapColor;
  overlapColor = 0;
  preColor = -1;
  count = lightSpan;
}

void turnOffTrack(int x, int y, int z){
  if(cube[y][x][z] == -1){
    cube[y][x][z] = 0;
  }
}

// ダイナミック点灯
void dynamicLight(){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int k=0; k<4; k++){

        if(cube[i][j][k] != 0){
          int color = cube[i][j][k];

          // 重なってたら処理
          if (overlapFlag == 1 && i == y && j == x && k == z){
            if(count == 0){
              preColor = ( preColor == -1 ? overlapColor : -1 );
              cube[i][j][k] = preColor;
              count = lightSpan;
            }else{
              count--;
            }
          }

          setLayerHigh(i, color);
          digitalWrite(verticalPin[j][k], HIGH);
          delay(0);
          setLayerLow(i, color);
          digitalWrite(verticalPin[j][k], LOW);
        }

      }
    }
  }
}

void setLayerHigh(int layerNum, int color){
  switch(color){
  case 1:
    digitalWrite(layerPinRed[layerNum], HIGH);
    break;
  case 2:
    digitalWrite(layerPinBlue[layerNum], HIGH);
    break;
  case -1:
    digitalWrite(layerPinRed[layerNum], HIGH);
    digitalWrite(layerPinBlue[layerNum], HIGH);
    break;
  }
}

void setLayerLow(int layerNum, int color){
  switch(color){
  case 1:
    digitalWrite(layerPinRed[layerNum], LOW);
    break;
  case 2:
    digitalWrite(layerPinBlue[layerNum], LOW);
    break;
  case -1:
    digitalWrite(layerPinRed[layerNum], LOW);
    digitalWrite(layerPinBlue[layerNum], LOW);
    break;
  }
}

void resetAll(){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int k=0; k<4; k++){
        cube[i][j][k] = 0;
      }
    }
  }
  preX = -1;
  preY = -1;
  preZ = -1;
  firstSelect = 1;
  player = 1;
  digitalWrite(playerSignal[0], HIGH);
  digitalWrite(playerSignal[1], LOW);
}
