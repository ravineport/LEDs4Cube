int cubeCluster[4][4][4] = { // y x z
  // 0 all
  // 1 fix z
  // 2 fix x
  // 3 fix y

  // layer1
  {
    {0, 1, 1, 0}, //  -> z
    {2, 3, 3, 2}, // |
    {2, 3, 3, 2}, // V
    {0, 1, 1, 0}  // x
  },
  // layer2
  {
    {3, 2, 2, 3},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {3, 2, 2, 3}
  },
  // layer3
  {
    {3, 2, 2, 3},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {3, 2, 2, 3}
  },
  // layer4
  {
    {0, 1, 1, 0},
    {2, 3, 3, 2},
    {2, 3, 3, 2},
    {0, 1, 1, 0}
  },
};

int bingoCube[4][4][4] = {0};

int checkBingo(){
  int bingo = 0;
  if(checkWidth()){
    bingo = 1;
  }
  if(checkLength()){
    bingo = 1;
  }
  if(checkHight()){
    bingo = 1;
  }

  switch(cubeCluster[y][x][z]){
  case 0:
    if(checkFixX_Slanting()){
      bingo = 1;
    }
    if(checkFixY_Slanting()){
      bingo = 1;
    }
    if(checkFixZ_Slanting()){
      bingo = 1;
    }
    if(checkNoFix_Slanting()){
      bingo = 1;
    }

    if(bingo == 1){
      return 1;
    }
    break;
  case 1:
    if(checkFixZ_Slanting()){
      return 1;
    }
  case 2:
    if(checkFixX_Slanting()){
      return 1;
    }
  case 3:
    if(checkFixY_Slanting()){
      return 1;
    }
  }

  if(bingo == 1){
    return 1;
  }
  return 0;
}

// layer内の横
int checkWidth(){
  for(int i=0; i<4; i++){
    if(cube[y][i][z] != player){
      return 0;
    }
  }

  for(int i=0; i<4; i++){
    bingoCube[y][i][z] = 5;
  }

  return 1;
}

// layer内の縦
int checkLength(){
  for(int i=0; i<4; i++){
    if(cube[y][x][i] != player){
      return  0;
    }
  }

  for(int i=0; i<4; i++){
    bingoCube[y][x][i] = 5;
  }

  return 1;
}


// 垂直方向
int checkHight(){
  for(int i=0; i<4; i++){
    if(cube[i][x][z] != player){
      return 0;
    }
  }

  for(int i=0; i<4; i++){
    bingoCube[i][x][z] = 5;
  }

  return 1;
}

// layer内の斜め
int checkFixY_Slanting(){
  int i = 0;
  for(i=0; i<4; i++){
    if(cube[y][i][i] != player){
      break;
    }
  }
  if(i == 4){
    for(i=0; i<4; i++){
      bingoCube[y][i][i] = 5;
    }
    return 1;
  }

  for(i=0; i<4; i++){
    if(cube[y][i][3-i] != player){
      return 0;
    }
  }
  for(i=0; i<4; i++){
    bingoCube[y][i][3-i] = 5;
  }

  return 1;
}

int checkFixX_Slanting(){
  int i = 0;
  for(; i<4; i++){
    if(cube[i][x][i] != player){
      break;
    }
  }
  if(i == 4){
    for(i=0; i<4; i++){
      bingoCube[i][x][i] = 5;
    }
    return 1;
  }

  for(i=0; i<4; i++){
    if(cube[i][x][3-i] != player){
      return 0;
    }
  }

  for(i=0; i<4; i++){
    bingoCube[i][x][3-i] = 5;
  }
  return 1;
}

int checkFixZ_Slanting(){
  int i = 0;
  for(; i<4; i++){
    if(cube[i][i][z] != player){
      break;
    }
  }
  if(i == 4){
    for(i=0; i<4; i++){
      bingoCube[i][i][z] = 5;
    }
    return 1;
  }

  for(i=0; i<4; i++){
    if(cube[3-i][i][z] != player){
      return 0;
    }
  }
  for(i=0; i<4; i++){
    bingoCube[3-i][i][z] = 5;
  }
  return 1;
}


int checkNoFix_Slanting(){
  int i=0;

  for(; i<4; i++){
    if(cube[i][i][i] != player) break;
  }
  if(i == 4){
    for(i=0; i<4; i++){
      bingoCube[i][i][i] = 5;
    }
    return 1;
  }

  for(i=3; i>=0; i--){
    if(cube[i][3-i][3-i] != player) break;
  }
  if(i == -1){
    for(i=3; i>=0; i--){
      bingoCube[i][3-i][3-i] = 5;
    }
    return 1;
  }

  for(i=3; i>=0; i--){
    if(cube[i][3-i][i] != player) break;
  }
  if(i == -1){
    for(i=3; i>=0; i--){
      bingoCube[i][3-i][i] = 5;
    }
    return 1;
  }

  for(i=0; i<4; i++){
    if(cube[i][i][3-i] != player) break;
  }
  if(i == 4){
    for(i=0; i<4; i++){
      bingoCube[i][i][3-i] = 5;
    }
    return 1;
  }
  return 0;
}

void winLight(){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
        for(int k=0; k<4; k++){
          if(bingoCube[i][j][k] == 5){
            cube[i][j][k] = -1;
            bingoCube[i][j][k] = 0;
          }
        }
    }
  }


  while(true){
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
    }

    if(x == 9 && y == 9 && z == 9 && decideFlag == 9){
      break;
    }

    dynamicLight();
  }
}
