char mp3name[5][15] = {"move.mp3", "decide1.mp3", "decide2.mp3", "reset.mp3", "win.mp3"};

void music_move(){
  player.playOne(mp3name[0]);
  player.play();
}

void music_decide1(){
  player.playOne(mp3name[1]);
  player.play();
}

void music_decide2(){
  player.playOne(mp3name[2]);
  player.play();
}

void music_reset(){
  player.playOne(mp3name[3]);
  player.play();
}

void music_win(){
  player.playOne(mp3name[4]);
  player.play();
}
