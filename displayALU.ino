
// Pines para los LEDs del display de 7 segmentos.
int ledA = 2;
int ledB = 3;
int ledC = 4;
int ledD = 5;
int ledE = 6;
int ledF = 7;
int ledG = 8;

// Configuración de segmentos para cada número o letra a mostrar.
const int segmentos[16][7] = {
  {LOW, LOW, LOW, LOW, LOW, LOW, HIGH},  // 0
  {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH},  // 1
  {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW},  // 2
  {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW},  // 3
  {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW},  // 4
  {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW},  // 5
  {LOW, HIGH, LOW, LOW, LOW, LOW, LOW},  // 6
  {LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW},  // 7
  {LOW, LOW, LOW, LOW, LOW, LOW, LOW},  // 8
  {LOW, LOW, LOW, LOW, HIGH, LOW, LOW},  // 9
  {LOW, LOW, LOW, HIGH, LOW, LOW, LOW},  // A
  {HIGH, HIGH, LOW, LOW, LOW, LOW, LOW},  // B
  {LOW, HIGH, HIGH, LOW, LOW, LOW, HIGH},  // C
  {HIGH, LOW, LOW, LOW, LOW, HIGH, LOW},  // D
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},  // E
  {LOW, HIGH, HIGH, HIGH, LOW, LOW, LOW}   // F
};

// Variables para entrada de datos desde la terminal.
char data[50];  // Cadena para almacenar los datos recibidos.
int number_of_bytes_received;

void setup() {
  inicializacion();  // Configura los pines y la comunicación serial.
  Serial.println("Ingrese la operación (suma, resta, multi, div) seguida de dos números.");
  Serial.println("Ejemplo: suma 3 5");
}

void loop() {
  while (Serial.available()) {
    number_of_bytes_received = Serial.readBytesUntil('\n', data, 50);  // Leer hasta un salto de línea.
    data[number_of_bytes_received] = '\0';  // Terminar la cadena con nulo.

    // Procesar el comando recibido.
    procesarOperacion(data);
  }
}

void procesarOperacion(char* input) {
  char operacion[10];
  int num1, num2;
  int resultado = 0;

  // Leer la operación y los dos números desde la entrada.
  int argumentos = sscanf(input, "%s %d %d", operacion, &num1, &num2);

  // Validar que se ingresaron todos los datos correctamente.
  if (argumentos != 3) {
    Serial.println("Formato incorrecto. Use: <operacion> <num1> <num2>");
    return;
  }

  // Realizar la operación solicitada.
  if (strcmp(operacion, "suma") == 0) {
    resultado = num1 + num2;
    Serial.println("Operación: Suma");
  } else if (strcmp(operacion, "resta") == 0) {
    resultado = num1 - num2;
    Serial.println("Operación: Resta");
  } else if (strcmp(operacion, "multi") == 0) {
    resultado = num1 * num2;
    Serial.println("Operación: Multiplicación");
  } else if (strcmp(operacion, "div") == 0) {
    if (num2 != 0) {
      resultado = num1 / num2;
      Serial.println("Operación: División");
    } else {
      Serial.println("Error: División entre 0.");
      return;
    }
  } else {
    Serial.println("Operación no reconocida. Use: suma, resta, multi, div.");
    return;
  }

  // Mostrar el resultado en el monitor serial.
  Serial.print("Resultado: ");
  Serial.println(resultado);

  // Mostrar el resultado en el display de 7 segmentos.
  if (resultado >= 0 && resultado <= 15) {
    mostrarEnDisplay(resultado);
  } else {
    Serial.println("Resultado fuera de rango para el display (0-15).");
  }
}

void mostrarEnDisplay(int numero) {
  // Configurar los pines del display según el número dado.
  digitalWrite(ledA, segmentos[numero][0]);
  digitalWrite(ledB, segmentos[numero][1]);
  digitalWrite(ledC, segmentos[numero][2]);
  digitalWrite(ledD, segmentos[numero][3]);
  digitalWrite(ledE, segmentos[numero][4]);
  digitalWrite(ledF, segmentos[numero][5]);
  digitalWrite(ledG, segmentos[numero][6]);

  delay(9000);

  // Apagar el display después de mostrar el número.
  apagarDisplay();
}

void apagarDisplay() {
  digitalWrite(ledA, HIGH);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledC, HIGH);
  digitalWrite(ledD, HIGH);
  digitalWrite(ledE, HIGH);
  digitalWrite(ledF, HIGH);
  digitalWrite(ledG, HIGH);
}

void inicializacion() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);
  pinMode(ledF, OUTPUT);
  pinMode(ledG, OUTPUT);

  // Inicializar todos los segmentos apagados.
  apagarDisplay();

  Serial.begin(9600);
}
