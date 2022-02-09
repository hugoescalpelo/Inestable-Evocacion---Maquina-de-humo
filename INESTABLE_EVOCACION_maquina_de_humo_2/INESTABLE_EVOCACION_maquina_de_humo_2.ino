//Configuración de pines
int relay = 3; //En este pin va conectado el relay
int proy = 4; //En esste pin va conectado el proyector

//Tiempos
const double TIEMPO_ENCENDIDO = 15000;
const double TIEMPO_APAGADO = 15000;
const int CICLOS = 15; // Cuantas veces se activa en esa cantidad de segundos
const double ARRANQUE_FRIO = 120000;

const double DUTY_CYCLE = TIEMPO_ENCENDIDO / (CICLOS * 2);
//Parte del programa que se ejecuta una vez
//al encender el microcontrolador
void setup() {
  //Inicia la comunicación
  Serial.begin (9600);
  Serial.println ("Inicio");

  //Se configura el pin y se inicia apagado
  pinMode (relay, OUTPUT);
  pinMode (proy, OUTPUT);
  digitalWrite (relay, LOW);
  digitalWrite (proy, LOW);

  //delay (ARRANQUE_FRIO);
}

//Programa
void loop() {
  digitalWrite (proy, HIGH);
  for (int i = 0; i < CICLOS; i++) {
    Serial.println ("Encendido");
    digitalWrite (relay, HIGH);
    delay (DUTY_CYCLE);
    Serial.println ("Apagado");
    digitalWrite (relay, LOW);
    delay (DUTY_CYCLE);
  }
  digitalWrite (proy, LOW);
  Serial.println ("Espera");
  delay (TIEMPO_APAGADO);
}
