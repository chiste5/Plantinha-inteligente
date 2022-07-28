//  --------  Libraries required to use the Display  ---------------
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <Wire.h>
 
// -----------  Display pins  --------------------------------------
#define TFT_CS         15      
#define TFT_RST        0
#define TFT_DC         2

//-------Informações sobre a planta--------

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para SUCULENTAS
//int u_min = 15;
//int u_max = 35;
//int t_min = 10;
//int t_max = 30;
//int l_min = 7000;
//int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para CACTOS
//int u_min = 10;
//int u_max = 40;
//int t_min = 10;
//int t_max = 30;
//int l_min = 7000;
//int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para BEGÔNIAS
int u_min = 40;
int u_max = 60;
int t_min = 20;
int t_max = 28;
int l_min = 300;
int l_max = 1000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para ROSAS
//int u_min = 20;
//int u_max = 50;
//int t_min = 25;
//int t_max = 30;
//int l_min = 7000;
//int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para ESPADA DE SÂO JORGE
//int u_min = 20;
//int u_max = 50;
//int t_min = 15;
//int t_max = 30;
//int l_min = 300;
//int l_max = 10000;
//---------DEFINIÇÃO DAS CORES -------------------------------


#define PRETO 0x0000
#define AZUL 0x001F
#define VERMELHO 0xF800
#define VERDE 0x07E0
#define CIANO 0x07FF
#define MAGENTA 0xF81F
#define AMARELO 0xFFE0
#define BRANCO 0xFFFF
#define CINZA 0xFFFF

// Caracteres externos
extern unsigned char feliz1[];
extern unsigned char feliz2[];
extern unsigned char sede1[];
extern unsigned char sede2[];
extern unsigned char enjoada1[];
extern unsigned char calor1[];
extern unsigned char calor2[];
extern unsigned char calor3[];
extern unsigned char frio1[];
extern unsigned char frio2[];
extern unsigned char vampiro1[];
extern unsigned char vampiro2[];
extern unsigned char oculos1[];
extern unsigned char oculos2[];

// Variáveis globais utilizados no código
int var_feliz   = 0;
int var_sede    = 0;
int var_enjoada = 0;
int var_calor   = 0;
int var_frio    = 0;
int var_vampiro = 0;
int var_oculos  = 0;

  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); //Those things are for the display

//--------Configurações iniciais do sensor de umidade do solo--------

int AOUT;
float umidade;
//--------Configurações iniciais do sensor de temperatura--------

#define BMP280_I2C_ADDRESS  0x76
Adafruit_BMP280 bmp280;

//--------Configurações iniciais do sensor de luminosidade--------
BH1750 lightMeter;
//_______________________________________________________________________

void setup() {
 
  tft.initR(INITR_GREENTAB);
  Wire.begin();
  lightMeter.begin();
 
 
 // --------  TEST TEXT  -------------------------------------------
//   tft.fillScreen(PRETO);
//  tft.setTextWrap(false);
//  tft.setCursor(20,5);    //Horiz/Vertic
//  tft.setTextSize(2);
//  tft.setTextColor(AMARELO);
//  tft.print("LEO");
// 
// 
//  tft.setCursor(5, 45);    //Horiz/Vertic
//  tft.setTextSize(2);
//  tft.setTextColor(AZUL);
//  tft.print("EH");
//  tft.setCursor(10, 65);
//  
// 
//  tft.setCursor(5, 93);    //Horiz/Vertic
//  tft.setTextSize(2);
//  tft.setTextColor(ST77XX_GREEN);
//  tft.print("CORNO");
//  tft.setCursor(15, 115);
//  tft.setTextColor(ST77XX_WHITE);

} 
 
void loop() {
  
    // Verifica a umidade do solo
    AOUT = analogRead(A0);
    umidade = 100 * ((978-(float)AOUT) / 978);
    Serial.print("Umidade do solo = ");
    Serial.println(umidade);


    uint16_t luminosidade = lightMeter.readLightLevel();
    Serial.print("Luminosidade= "); 
    Serial.println(luminosidade);
  
    // Verifica a temperatura ambiente
    float temperatura = bmp280.readTemperature();
    Serial.print("Temperatura = ");
    Serial.println(temperatura);
    
    // Se a umidade do solo for muito baixa, a plantinha ficará com sede
    if(umidade < u_min){
      if(var_sede == 0){
        limpar();
        var_sede = 1;
      }
      sede();
    }
  
    // Se a umidade do solo for muito alta, a plantinha ficará enjoada
    else if(umidade > u_max){ 
      if(var_enjoada == 0){
        limpar();
        var_enjoada = 1;
      }
      enjoada();   
    }
      // Se a temperatura for muito baixa, a plantinha ficará com frio
  else if(temperatura < t_min){
    if(var_frio == 0){
      limpar();
      var_frio = 1;
    }
    frio();  
  }

  // Se a temperatura for muito alta, a plantinha ficará com calor
  else if(temperatura > t_max){
    if(var_calor == 0){
      limpar();
      var_calor = 1;
    }
    calor();
  }

  // Se a luminosidade for muito baixa, a plantinha virará uma vampira
  else if(luminosidade < l_min){
    if (var_vampiro == 0){
      limpar();
      var_vampiro = 1;
    }
    vampiro(); 
  }
  
  // Se a luminosidade for muito alta, a plantinha ficará com óculos escuros
  else if(luminosidade > l_max){
    if (var_oculos == 0){
      limpar();
      var_oculos = 1;
    }
    oculos();
  }

  // Se todos os parâmetros estiverem dentro dos valores ideais, a plantinha ficará feliz
  else{
    if(var_feliz == 0){
      limpar();
      var_feliz = 1;
    }
    feliz();
  }
    
}
  
  void limpar(){
       delay(500);
       tft.fillScreen(PRETO);
       delay(100);
  }
  
  //--------Função plantinha com sede--------
  
  void sede()
  {
    tft.drawBitmap(0,0,sede1, 128, 160, BRANCO);
      tft.drawBitmap(0,0,sede2, 128, 160, MAGENTA);
  
    tft.setTextColor(BRANCO);
    tft.setCursor(20,140);
    tft.println("Que seeeeeeede!");
    tft.setCursor(30,150);;
    tft.print("Me da agua?");
    
    var_feliz    = 0;
    var_enjoada = 0;
    var_calor   = 0;
    var_frio    = 0;
    var_vampiro = 0;
    var_oculos  = 0;
  }
  
  //--------Função plantinha enjoada--------
  
  void enjoada()
  {
    tft.drawBitmap(0, 0, enjoada1, 128, 160,BRANCO);
    tft.setTextColor(BRANCO);
    tft.setCursor(5,140);
    tft.println("Argh! Estou enjoada!");
    tft.setCursor(7,150);
    tft.print("Nao quero mais agua");
    
    var_feliz   = 0;
    var_sede    = 0;
    var_calor   = 0;
    var_frio    = 0;
    var_vampiro = 0;
    var_oculos  = 0; 
  }
  
  //--------Função plantinha com frio--------
  
  void frio()
  {
    tft.drawBitmap(0, 0, frio1, 128, 160, AZUL);
    tft.drawBitmap(0, 0, frio2, 128, 160, BRANCO);
    tft.setTextColor(BRANCO);
    tft.setCursor(50,140);
    tft.println("Brrr!");
    tft.setCursor(10,150);
    tft.print("Estou com friiiio");
    
    var_feliz   = 0;
    var_sede    = 0;
    var_enjoada = 0;
    var_calor   = 0;
    var_vampiro = 0;
    var_oculos  = 0;  
  }
  
  //--------Função plantinha com calor--------
  
  void calor()
  {
    tft.drawBitmap(0, 0, calor1, 128, 160, BRANCO);
    tft.drawBitmap(0, 0, calor2, 128, 160, AZUL);
    tft.drawBitmap(0, 0, calor3, 128, 160, MAGENTA);
    tft.setTextColor(BRANCO);
    tft.setCursor(25,140);
    tft.println("Ai! Que calor!");
    tft.setCursor(15,150);
    tft.print("Esta muito quente");
      
    var_feliz   = 0;
    var_sede    = 0;
    var_enjoada = 0;
    var_frio    = 0;
    var_vampiro = 0;
    var_oculos  = 0;  
  }
  
  //--------Função plantinha vampira--------
  
  void vampiro()
  {
    tft.drawBitmap(0, 0, vampiro1, 128, 80, VERMELHO);
    tft.drawBitmap(0, 80, vampiro2, 128, 80, BRANCO);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(4,140);
    tft.println("Cuidado! Sem luz vou");
    tft.setCursor(15,150);
    tft.print("virar uma vampira");
    
    var_feliz   = 0;
    var_sede    = 0;
    var_enjoada = 0;
    var_calor   = 0;
    var_frio    = 0;
    var_oculos  = 0;
  }
  
  //--------Função plantinha com óculos--------
  
  void oculos()
  {
    tft.drawBitmap(0, 0, oculos1, 128, 160, BRANCO);
    tft.drawBitmap(0, 0, oculos2, 128, 160, CINZA);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(7,140);
    tft.println("Olha esse Sol! Cade");
    tft.setCursor(13,150);
    tft.print("o protetor solar?");
    
    var_feliz   = 0;
    var_sede    = 0;
    var_enjoada = 0;
    var_calor   = 0;
    var_frio    = 0;
    var_vampiro = 0;
  }
  
  //--------Função plantinha feliz--------
  
  void feliz()
  {
    tft.drawBitmap(0, 0, feliz1, 128, 160, BRANCO);
    tft.drawBitmap(0, 0, feliz2, 128, 160, VERMELHO);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(20,140);
    tft.println("Hum! Esta tudo");
    tft.setCursor(10,150);
    tft.print("perfeito. Obrigada!");
    
    var_sede    = 0;
    var_enjoada = 0;
    var_calor   = 0;
    var_frio    = 0;
    var_vampiro = 0;
    var_oculos  = 0;
    
  }
