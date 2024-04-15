#define facilite 50       
#define nbDeCasesASauter 3 
#define limiteGauche 1     
#define limiteDroite 2     
#define nombreNote 38      
#define longueurNote 2     
#define bas 0
#define haut 1
#define boutonJump 13
#define speaker 6
#define RESET 7

//'마리오' 멜로디와 템포
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define melodyPin 6

unsigned long prevPlayTime = 0;
unsigned long playDuration = 0;
int currentMelody = 0;
int melodySize = 75;
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//마리오 멜로디 재생
void sing() {
    if(millis() < prevPlayTime + playDuration) {
        return;
    }
    noTone(8);
    if(currentMelody >= melodySize)
        currentMelody = 0;
    int noteDuration = 1000/tempo[currentMelody];
    tone(melodyPin, melody[currentMelody], noteDuration);
    prevPlayTime = millis();
    playDuration = noteDuration * 1.30;
    buzz(melodyPin, 0, noteDuration);
    currentMelody++;
}

//게임코드
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
  pinMode(melodyPin, OUTPUT); //부저에서 멜로디 재생
  pinMode(8, OUTPUT);        //LED출력
  
  Serial.begin(38400);
  pinMode(boutonJump,INPUT); // 버튼 = 점프
  lcd.begin(16,2);   
  randomSeed(analogRead(0));
  for(int i=0;i<2;i++){
    lcd.setCursor(0,0);
    lcd.print("1 TEAM");
    lcd.setCursor(0,1);
    lcd.print("Runningman Game");
    delay(1000);
    lcd.clear(); //화면 초기설정(초기화)
    delay(200);
    if(digitalRead(boutonJump))
      break;
  }

  for(int i=0;i<3;i++){
    lcd.setCursor(0,0);
    lcd.print("Press to button ");
    lcd.setCursor(0,1);
    lcd.print("     To Jump    ");
    delay(500);
    lcd.clear();
    delay(200);
    if(digitalRead(boutonJump))
      break;
  }  

  lcd.setCursor(12,0);
  lcd.print("Member: Gyeong Hwa");
  lcd.setCursor(16,1);
  lcd.print("Dong Yeong, Dong Jun");

  //게임오버시 계속진행하지않고 break
  for (int positionCounter = 0; positionCounter < nombreNote; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(250);
    if(digitalRead(boutonJump))
      break;
  }
  CGRAM(); // 공룡출력
  lcd.clear();
  delay(1000);
  afficheScore(0); //점수 0부터 표시
}

void loop(){
  sing(); //위에 작성한 sing이 끝나도 처음부터 반복
  bool positionPerso;
  //장애물1,2,3(3은 점수+1,$)
  int positionCible1;
  int positionCible2;
  int positionCoin;
  static bool memoBouton=0;
  static byte longueurSaut=0;
  static unsigned int boucle=0;
  static unsigned int score=0;

  acceleration();
  if(memoBouton==0){                   
    memoBouton=digitalRead(boutonJump);                  
  }
  if(memoBouton && longueurSaut<=nbDeCasesASauter){
    positionPerso=haut;
    longueurSaut=longueurSaut+1;
  }
  else{
    positionPerso=bas;
    longueurSaut=0;
    memoBouton=0;
  }
  affichePersonnage(0,positionPerso);
  acceleration();
  if(memoBouton==0){
    memoBouton=digitalRead(boutonJump);
  }
//장애물
  positionCible1=cible1(positionPerso); // 선인장1
  positionCible2=cible2(positionPerso); // 선인장2
  positionCoin=coin(positionPerso); // +1동전($)

  if(positionPerso==bas && ((positionCoin<=limiteDroite && positionCoin>=limiteGauche) )){
    score = score+1;
    afficheScore(score);
  }//점수 저장
  
  if (positionPerso==bas && ((positionCible1<=limiteDroite && positionCible1>=limiteGauche) || (positionCible2<=limiteDroite && positionCible2>=limiteGauche))){
    gameOver();
  }//충돌하면 게임오버
  
  if(memoBouton && ((positionCible1<=(limiteGauche+1) && positionCible1>=limiteGauche) || (positionCible2<(limiteGauche+1) && positionCible2>=limiteGauche) )){
    score=score+1;
    afficheScore(score);// 점수표시
  }//장애물 지나면 점수추가
  
  acceleration();
  if(memoBouton==0){                    
    memoBouton=digitalRead(boutonJump); 
  }
  boucle=boucle+1;
}
//공룡 이미지
void CGRAM(void){                                                                           
  byte pictogramme0[8] = {                                                                          
    0,   0,   0,   0,   4,   6,   7,   7                                                      
  };                                                                           
  byte pictogramme1[8] = {                                                                            
    0,   0,   0,   0,   0,   0,   0,   17                                                      
  };                                                                           
  byte pictogramme2[8] = {                                                                             
    7,   13,   15,   15,   15,   15,   31,   31                                                      
  };                                                                           
  byte pictogramme3[8] = {                                                                            
    30,   31,   31,   31,   16,   30,   0,   0                                                      
  };                                                                           
  byte pictogramme4[8] = {                                                                             
    3,   1,   0,   0,   0,   0,   0,   0                                                      
  };                                                                           
  byte pictogramme5[8] = {                                                                             
    31,   31,   31,   31,   15,   6,   2,   3                                                      
  };                                                                           
  byte pictogramme6[8] = {                                                                             
    31,   30,   30,   28,   24,   16,   16,   24                                                      
  };                                                                           
  byte pictogramme7[8] = {                                                                             
    24,   8,   0,   0,   0,   0,   0,   0                                                      
  };                                                                           
  lcd.createChar(0, pictogramme0);                                                                           
  lcd.createChar(1, pictogramme1);                                                                        
  lcd.createChar(2, pictogramme2);                                                                         
  lcd.createChar(3, pictogramme3);                                                                            
  lcd.createChar(4, pictogramme4);                                                                            
  lcd.createChar(5, pictogramme5);                                                                            
  lcd.createChar(6, pictogramme6);                                                                            
  lcd.createChar(7, pictogramme7);                                                                            
}                                                                           
//공룡 이미지
void affichePersonnage(byte x,bool y){
  if(y==bas){
    lcd.setCursor(x,0);        
    lcd.write((unsigned char)0);
    lcd.write(1);               
    lcd.write(2);              
    lcd.write(3);               
    lcd.setCursor(x,1);         
    lcd.write(4);               
    lcd.write(5);               
    lcd.write(6);               
    lcd.write(7);               
  }
  else{
    lcd.setCursor(x,1);         
    lcd.print(" ");             
    lcd.print(" ");           
    lcd.print(" ");          
    lcd.print(" ");             
    lcd.setCursor(x,0);        
    lcd.write(4);               
    lcd.write(5);             
    lcd.write(6);              
    lcd.write(7);             
  } 
}
//장애물 조정
int cible1(bool PersoHaut){
  static int x=random(15,25);
  lcd.setCursor(x,1);
  if(x>3){
    lcd.print(" ");
  }
  else if(x<=3 && !PersoHaut){
    lcd.write((unsigned char)x+4);
  }                           
  if(x>=0){
    x=x-1;
    lcd.setCursor(x,1);
    lcd.write(221); //lcd.write(아스키코드)
  }
  else{
    x=random(15,20); //등장위치
  }
  return x;
}

int cible2(bool PersoHaut){
  static int x=random(20,30);
  lcd.setCursor(x,1);
  if(x>3){
    lcd.print(" ");
  }
  else if(x<=3 && !PersoHaut){
    lcd.write((unsigned char)x+4);
  }
  if(x>=0){
    x=x-1;
    lcd.setCursor(x,1);
    lcd.write(243);
  }
  else{
    x=random(25,30); //등장위치
  }
  return x;
}

//새로추가
//$, 1점추가
int coin(bool PersoHaut){
  static int x=random(15,20);
  lcd.setCursor(x,1);
  if(x>3){
    lcd.print(" ");
  }
  else if(x<=3 && !PersoHaut){
    lcd.write((unsigned char)x+4);
  }
  if(x>=0){
    x=x-1;
    lcd.setCursor(x,1);
    lcd.write(36);  //36 = $
  }
  else{
    x=random(20,25);
  }
  return x;
}

//점수관련
void afficheScore(int score){
  lcd.setCursor(6,0);
  lcd.print("Score:");
//3자리 점수표현 (예시 : 007)
  if(score<10){     
    lcd.print("00"); 
  }
  else if(score<100){
    lcd.print("0");
  }
  lcd.print(score);
}

//게임오버후 꾹 눌렀을 때(대기화면)
void nouvellePartie(void) 
{  
  for(int i=0;i<3;i++){
    lcd.clear();
    lcd.setCursor(0,0),
    lcd.print("    Restart?    ");
    lcd.setCursor(0,1),
    lcd.print("    Press Button    ");
    delay(500);
    lcd.clear();
    delay(200);
  }
//재시작과 초기화
  pinMode(RESET, OUTPUT); 
  digitalWrite(RESET, LOW);
}

//게임오버 반응
void gameOver(void){

  lcd.setCursor(4,1);
  lcd.print("  Game Over "); //게임오버 출력
  delay(500);
  if(digitalRead(boutonJump)){
    nouvellePartie();
  }
  lcd.setCursor(4,1);
  lcd.print("            "); //게임오버시 깜빡임
  delay(200);
  if(digitalRead(boutonJump)){
    nouvellePartie(); 
  }
  lcd.setCursor(4,1);
  lcd.print("Press Button"); //버튼을 꾹 누르면 재시작화면
  delay(500);             //1초정도?
  if(digitalRead(boutonJump)){
    nouvellePartie();
  }
  lcd.setCursor(4,1);
  lcd.print("            "); 
  delay(200);
  if(digitalRead(boutonJump)){
    nouvellePartie(); 
  }
}

void acceleration(void){
  static unsigned int variation=10; 
  static unsigned int vitesse=0;   
  if(variation==0){       
    if(vitesse<facilite){ 
      vitesse=vitesse+1;
    }
    variation=10;
  }
  delay((facilite-vitesse)+1); 
  variation=variation-1;
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(8, HIGH);
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
  digitalWrite(8, LOW);
}

long mesureIntervalleDeTemps(){
  static long lastMillis=0; 
  long now = millis();
  long intervalle= now-lastMillis;
  lastMillis = now;
  return intervalle;
}