//Programme dans le cadre de mon projet de serre automatique en Terminale STI2D - SIN 
// -Arcrow 

#include <Ethernet.h> //lib
#include <MySQL_Connection.h> //lib
#include <MySQL_Cursor.h> //lib

byte mac_addr[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xEB, 0x35 }; //On définit mac du shield

//Déclaration valeurs aléatoires des capteurs
const int temperature = random(41);
const int hygrometrie = random(101);
const int humidite = random(101);
const int co2 = random(101);
const int anenometre = random(201);
const int girouette = random(2) == 0 ? (random(2) == 0 ? "NORD" : "SUD") : (random(2) == 0 ? "EST" : "OUEST"); 
const int pluie = random(101);

//Déclaration valeurs aléatoires des actionneurs
char lucarne = random(2) == 0 ? "OUVERTE" : "FERMEE";
char pompe = random(2) == 0 ? "ON" : "OFF";
char brumisateur = random(2) == 0 ? "ON" : "OFF";
char ventilateur = random(2) == 0 ? "ON" : "OFF";
char alerte = random(2) == 0 ? "ON" : "OFF";


IPAddress server_addr(XX,XX,XX,XX);  //On rentre ip du serveur
char user[] = "XXX";              //On rentre utilisateur
char password[] = "XXX";        //On rentre mot de passe de l'utilisateur 


char Ctemperature[] = "UPDATE projet.temperature SET Valeur=(%d) WHERE id=0"; //projet = base de donnée || Potentiomètre = table 
char Chygrometrie[] = "UPDATE projet.hygrometrie SET Valeur=(%d) WHERE id=0";//|| Valeur = colonne || id=0 pour définir sur une ligne en particulier
char Chumidite[] = "UPDATE projet.humidite SET Valeur=(%d) WHERE id=0";
char Cco2[] = "UPDATE projet.co2 SET Valeur=(%d) WHERE id=0";
char Canenometre[] = "UPDATE projet.anenometre SET Valeur=(%d) WHERE id=0";
char Cgirouette[] = "UPDATE projet.girouette SET Valeur=(%d) WHERE id=0";

char Alucarne[] = "UPDATE projet.lucarne SET Valeur=(%d) WHERE id=0";
char Apompe[] = "UPDATE projet.pompeture SET Valeur=(%d) WHERE id=0";
char Abrumisateur[] = "UPDATE projet.brumisateur SET Valeur=(%d) WHERE id=0";
char Aventilateur[] = "UPDATE projet.ventilateur SET Valeur=(%d) WHERE id=0";
char Aalerte[] = "UPDATE projet.alerte SET Valeur=(%d) WHERE id=0";

char query2[128]; //Sur 128 caractères

EthernetClient client;
MySQL_Connection conn((Client *)&client);//Etablissement connexion client

void setup() {
  
  Serial.begin(9600); //vitesse pour terminal
  while (!Serial); //On attend la connexion
  Ethernet.begin(mac_addr);//on essage de se connecter avec les valeurs rentrée ci-dessus
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }else{
    Serial.println("Connection failed."); //Si erreur
  }
}


void loop() {
  delay(3000);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  sprintf(query2, Ctemperature, temperature);//Liaison du code sql à arduino
  Serial.println(temperature);//On affiche sur la console les valeurs
  sprintf(query2, Chygrometrie, hygrometrie);
  Serial.println(hygrometrie);
  sprintf(query2, Chumidite, humidite);
  Serial.println(humidite);
  sprintf(query2, Cco2, co2);
  Serial.println(co2);
  sprintf(query2, Canenometre, anenometre);
  Serial.println(anenometre);
  sprintf(query2, Cgirouette, girouette);
  Serial.println(girouette);

  sprintf(query2, Alucarne, lucarne);
  Serial.println(lucarne);
  sprintf(query2, Apompe, pompe);
  Serial.println(pompe);
  sprintf(query2, Abrumisateur, brumisateur);
  Serial.println(brumisateur);
  sprintf(query2, Aventilateur, ventilateur);
  Serial.println(ventilateur);
  sprintf(query2, Aalerte, alerte);
  Serial.println(alerte);
   
  cur_mem->execute(query2);  // On execute le code sql --> Envoie des données sur la bdd
  delete cur_mem;//Supression du curseur -> Libère mémoire 

  
}
