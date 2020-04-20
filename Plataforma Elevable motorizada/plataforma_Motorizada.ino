
/*Sketch simple para motorizar la base elevable de nuestro laser de Co2 By Sr.Ferrete
Para usar este firmware hemos usado un arduino UNO, cnc Shield y un driver A4988.
Nos facilita el poder interconexionar todo sin necesida de realizar PCBs alternativas.
Ademas permite ampliar funcionalidades en un futuro.
Visita mi canal de YouTube para más información. https://www.youtube.com/srferrete */


/*Declaramos los botones necesarios*/
#define buttonUP 11 //el boton de subir lo conectaremos en el pin Z+ de la CNC shield
#define buttonDown 10 //el boton de bajar lo conectaremos en el pin Y+ de la CNC shield

/*El control de cambio de dirección del motor tambien depende del orden de las bobinas,
 *y es posible que el orden de los botones varie, es decir, que el de subir baje y viceversa.
 *No pasa nada, con uno va a subir y con el otro bajar, pero es importante saber cual es cual, 
 *a la hora de colocar los botones en el panel de la máquina.
 */


/*Declaramos los pines para el control del motor, usaremos el driver y conxion del X de la CNC Shield*/
#define dirPin 5
#define stepPin 2
#define enablePin 8

/*Son 2 variables para comprobar el estado de los botones, en esta versión se podrian no usar, pero las dejamos para el futuro*/
int buttonUpState = 0;
int buttonDownState = 0;

/*SETUP*/
void setup() {
  
pinMode(dirPin, OUTPUT);
pinMode(stepPin, OUTPUT);
pinMode(enablePin, OUTPUT);
pinMode(buttonUP, INPUT);
pinMode(buttonDown, INPUT);

digitalWrite(buttonUP, HIGH);
digitalWrite(buttonDown, HIGH);
}
/*FIN DEL SETUP*/

/*LOOP*/
void loop() {

int StepDelay = 100; // Con este delay podemos controlar la velocidad del motor, se expresa en microSegundos. 
buttonUpState = digitalRead(buttonUP); //leemos los botones
buttonDownState = digitalRead(buttonDown);

while(digitalRead(buttonUP) == LOW){
      digitalWrite(enablePin,LOW); // habilitamos el motor
      digitalWrite(dirPin,LOW); //indicamos la otra dirección direccion
      digitalWrite(stepPin, HIGH); //Movemos el motor
      delayMicroseconds(StepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(StepDelay);
}
while(digitalRead(buttonDown) == LOW){
      digitalWrite(enablePin,LOW); //Habilitamos
      digitalWrite(dirPin,HIGH); // indicamos la otra dirección direccion
      digitalWrite(stepPin, HIGH); //Movemos el motor
      delayMicroseconds(StepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(StepDelay);
}
if(buttonDownState == HIGH && buttonUpState == HIGH) digitalWrite(enablePin,HIGH); //Cuando ningun boton esté pulsado deshabilitamos el motor para que no consuma
if(buttonDownState == LOW && buttonUpState == HIGH) digitalWrite(enablePin,LOW); // Si los dos estan pulsados a la vez, tambien deshabilitamos para evitar errores
}
/*FIN DEL LOOP*/
