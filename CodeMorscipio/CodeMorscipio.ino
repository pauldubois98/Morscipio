/*
 * Besoins:
 * -Boutons: / en 9; - en 11; . en 13
 * -Leds: / en 8; - en 10; . en 12
 * 
 */

/*
 * Actions:
 * Transforme le signal morse en texte
 * 
 */

int buts=9;//bouton slash
int butt=11;//bouton tiret
int butp=13;//bouton point

int leds=8;//LED du bouton slash
int ledt=10;//LED du bouton tiret
int ledp=12;//LED du bouton point

#include <LiquidCrystal.h>
//Permet de gérer un écran LCD
#include <QueueList.h>
//Permet de créer une pile où seront stockées les valeurs des signaux

QueueList <int> msg;
LiquidCrystal lcd(3, 2, 4, 5, 6, 7);

int nb=0;//nombre de signaux dans la liste
int colonne=0;//colonne de l'écran LCD sur laquelle est le pointeur
char* aff[17];//variable de stokage pour le défilement du texte

void setup() {
  lcd.begin(16, 2);
  delay(10);
  //démarrage de l'écran LCD
  Serial.begin(9600);
  delay(10);
  //démarrage de la liaison série s'il y en a une
  pinMode(leds, OUTPUT);
  pinMode(ledt, OUTPUT);
  pinMode(ledp, OUTPUT);

  pinMode(buts, INPUT);
  pinMode(butt, INPUT);
  pinMode(butp, INPUT);
}

void loop(){
  if (digitalRead(buts)==1){
    digitalWrite(leds, 1);
    if(nb!=0){
      int letter[]={0,0,0,0};
      for(int i=0; i<nb; i++){
        letter[i]=msg.pop();}
      decodeLetter(letter);}
    else{
      afficher(" ");//=espace}
    nb=0;
    while (digitalRead(buts)==1){}//attente du relâchement du bouton
    digitalWrite(leds, 0);
  }
  if (digitalRead(butt)==1){
    digitalWrite(ledt, 1);
    msg.push(3);
    nb++;
    while (digitalRead(butt)==1){}//attente du relâchement du bouton
    digitalWrite(ledt, 0);
  }
  if (digitalRead(butp)==1){
    digitalWrite(ledp, 1);
    msg.push(1);
    nb++;
    while (digitalRead(butp)==1){}//attente du relâchement du bouton
    digitalWrite(ledp, 0);
  }
  delay(5);//attente de 5 ms avant le retour au début de la boucle
}


void decodeLetter(int* letter){
  if (letter[0]==1){
    if (letter[1]==1){
      if (letter[2]==1){
        if (letter[3]==1){afficher("H");}//....
        else if (letter[3]==3){afficher("V");}//...-
        else {afficher("S");}}//...
      else if (letter[2]==3){
        if (letter[3]==1){afficher("F");}//..-.
        else if (letter[3]==3){afficher("?");}//..--
        else {afficher("U");}}//..-
      else {afficher("I");}}//..
      
    else if (letter[1]==3){
      if (letter[2]==1){
        if (letter[3]==1){afficher("L");}//.-..
        else if (letter[3]==3){afficher("?");}//.-.-
        else {afficher("R");}}//.-.
      else if (letter[2]==3){
        if (letter[3]==1){afficher("P");}//.--.
        else if (letter[3]==3){afficher("J");}//.---
        else {afficher("W");}}//.--
      else {afficher("A");}}//.-
      
    else {afficher("E");}}//.


  else if (letter[0]==3){
    if (letter[1]==1){
      if (letter[2]==1){
        if (letter[3]==1){afficher("B");}//-...
        else if (letter[3]==3){afficher("X");}//-..-
        else {afficher("D");}}//-..
      else if (letter[2]==3){
        if (letter[3]==1){afficher("C");}//-.-.
        else if (letter[3]==3){afficher("Y");}//-.--
        else {afficher("K");}}//-.-
      else {afficher("N");}}//-.
      
    else if (letter[1]==3){
      if (letter[2]==1){
        if (letter[3]==1){afficher("Z");}//--..
        else if (letter[3]==3){afficher("Q");}//--.-
        else {afficher("G");}}//--.
      else if (letter[2]==3){
        if (letter[3]==1){afficher("?");}//---.
        else if (letter[3]==3){afficher("Γ");}//----
        else {afficher("O");}}//---
      else {afficher("M");}}//--
      
    else {afficher("T");}}//-
    
}

void afficher(char* texte){
  Serial.println(texte);
  lcd.setCursor(colonne, 1);
  lcd.print(texte);
  aff[colonne]=texte;
  colonne+=1;
  if(colonne==16){
    lcd.setCursor(0, 0);
    for(int i=0; i<17; i++){
      lcd.print(aff[i]);
      Serial.print(aff[i]);}
    lcd.setCursor(0, 1);
    lcd.print("                ");
    Serial.println("                ");
    colonne=0;
    }
}


