//Configuración de pines
int relay = 3; //En este pin va conectado el relay
int proy = 4; //En esste pin va conectado el proyector

//Tiempos
const double TIEMPO_ENCENDIDO = 15000; // Tiempo que dura echando humo (15 seg)
const double TIEMPO_APAGADO = 15000; // Tiempo que dura sin echar humo (15 seg)
const int CICLOS = 15; // Cuantas veces se activa en esa cantidad de segundos (15 clics)
const double ARRANQUE_FRIO = 150000; // Tiempo de arranque frio (2 min 30)
const double INTERVALO = 300000; // Tiempo entre cada activación (5 min)
const double DURACION_FUNCION = 75000; //Tiempo que se queda encendida la secuencia (1 min 15 seg
double timeNow, timeLast, timeFunc;

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

  timeNow = millis ();
  timeLast = timeNow + ARRANQUE_FRIO;
  timeFunc = timeLast + DURACION_FUNCION;
  
}

//Programa
void loop() {
  timeNow = millis ();

  if (timeNow > timeLast) {
    if (timeNow < timeFunc) {
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
    if (timeNow > timeFunc) {
      timeNow = millis ();
      timeLast = timeNow + INTERVALO;
      timeFunc = timeLast + DURACION_FUNCION;
    }
  }
}
