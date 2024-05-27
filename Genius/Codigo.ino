// Davi_Puddo_853355
//

#define GREEN_LED 2
#define GREEN_BUTTON 6

#define RED_LED 3
#define RED_BUTTON 7

#define YELLOW_LED 4
#define YELLOW_BUTTON 8

#define BLUE_LED 5
#define BLUE_BUTTON 9

#define SOUND_PIN 13

// Inicio
void setup()
{
  // Inicializar codigo serial
  Serial.begin(9600);
  
  // Controle de inicio do jogo
  pinMode(10, INPUT);
  
  // Controle do LED verde
  pinMode(GREEN_LED, OUTPUT);
  pinMode(GREEN_BUTTON, INPUT);
  
  // Controle do LED vermelho
  pinMode(RED_LED, OUTPUT);
  pinMode(RED_BUTTON, INPUT);
  
  // Controle do LED amarelo
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  
  // Controle do LED azul
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BLUE_BUTTON, INPUT);
  
  // Controle do som
  pinMode(SOUND_PIN, OUTPUT);
  
  // Gerar semente aleatoria
  randomSeed(analogRead(0));
  
  // Começar jogo
  WaitStart();
}

void loop()
{
  delay(10);
}

// Jogo
void StartGame()
{
  // Identificação de dados
  int sequencia[50];
  int resposta [50];
  int n = 0;
  int errado = 0;
  
  // Iniciar
  	// Desligar LEDs
  digitalWrite(SOUND_PIN, LOW);
  ALEDs(0); 
  
    // Animação de inicio
  delay(1000);
  StartAnimation();
  delay(1000);
  
  // Jogo
  while(n <= 100)
  {
    // Escolher um valor aleatorio para a sequencia
    sequencia[n] = random(1,5);
    for (int i = 0; i < n; i++)
    {
      // Mostar sequencia completa
      Sound(sequencia[i]);
      NLED (sequencia[i], 1, 6);
      delay(200);
    }
    delay(400);
  	for (int i = 0; i < n; i++)
  	{
      // Ler resposta
      resposta[i] = ReadButtons();
      if (resposta[i] != sequencia[i])
      {
      	errado = 1;
      }
      if (errado > 0)
  	  {
        // Reiniciar
        ALEDs(1);
        Sound(3);
        delay(100);
        Sound(1);
        delay(80);
        Sound(1);
        ALEDs(0);
    	WaitStart();
  	  }
    }
    // Adicionar mais valor para a sequencia
  	n++;
   }
  ERROR();
}

// Animação de inicio
void StartAnimation()
{
  NLED (1, 1, 1); // Ligar LED verde
  Sound(1);
  delay(300);
  NLED (2, 1, 1); // Ligar LED vermelho
  Sound(2);
  delay(300);
  NLED (3, 1, 1); // Ligar LED amarelo
  Sound(3);
  delay(300);
  NLED (4, 1, 1); // Ligar LED azul
  Sound(4);
  delay(300);
  ALEDs(0);   // Desligar LEDs
  delay(500);
  Sound(1);
  delay(80);
  Sound(2);
  delay(80);
  Sound(3);
  delay(80);
  Sound(4);
  ALEDs(1);   // Ligar LEDs
  delay(500);
  ALEDs(0);   // Desligar LEDs
}

// Controlar todos os LEDs
void ALEDs(int valor)
{
  digitalWrite(GREEN_LED, valor);
  digitalWrite(RED_LED, valor);
  digitalWrite(YELLOW_LED, valor);
  digitalWrite(BLUE_LED, valor);
}

// Esperar começo do jogo
void WaitStart()
{
  delay(500);
  bool GameStart = false;
  while(GameStart == false)
  {
    GameStart = digitalRead(10);
    ALEDs(1);
 	delay(10);
  }
  StartGame();
}

// Controlar um LED específico
void NLED(int n, int valor, int d)
{
  if (n == 1)
  { 
  	digitalWrite(GREEN_LED, valor);
  }
  else if (n == 2)
  {
  	digitalWrite(RED_LED, valor);  
  }
  else if (n == 3)
  {
    digitalWrite(YELLOW_LED, valor);
  }
  else if (n == 4)
  {
    digitalWrite(BLUE_LED, valor);
  }
  else
  {
    Serial.print(n);
    ERROR();
  }
  delay(d*(100));
  ALEDs(0);
}

// Ler um Botão
int NButton(int n)
{
  int x = 0;
  if (n == 1)
  { 
  	x = digitalRead(GREEN_BUTTON);
  }
  else if (n == 2)
  {
  	x = digitalRead(RED_BUTTON);  
  }
  else if (n == 3)
  {
    x = digitalRead(YELLOW_BUTTON);
  }
  else if (n == 4)
  {
    x = digitalRead(BLUE_BUTTON);
  }
  else
  {
    ERROR();
  }
  return(x);
}

// Esperar um botao ser precionado e retornar qual botao foi
// presionado
int ReadButtons()
{
  ALEDs(0);
  delay(100);
  int x = 0;
  while (x == 0)
  {
    if (NButton(1) == 1)
    {
      x = 1;
    }
   	else if (NButton(2) == 1)
    {
      x = 2;
    }
    else if (NButton(3) == 1)
    {
      x = 3;
    }
    else if (NButton(4) == 1)
    {
      x = 4;
    }
    delay(100);
  }
  Sound(x);
  NLED(x, 1, 6);
  delay(150);
  ALEDs(0);
  return(x);
}

// Barulho
void Sound(int hz)
{
  if (hz <= 0)
  {
    hz = 1;
  }
  tone(SOUND_PIN, (110*hz), 50);
}

// Barulho para indicar erro
void ERROR()
{
  Serial.print("ERROR\n");
  for (int i = 0; i < 5; i++)
  {
  	Sound(1);
  	delay(200);
  }
}