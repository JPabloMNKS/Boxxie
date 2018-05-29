#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
// macros utiles
// valores maximos
#define MAX_X ILI9341_TFTHEIGHT
#define MAX_Y ILI9341_TFTWIDTH
#define X_DIVISION ((3 * MAX_X) / 4)
#define X_CABEZA (MAX_X / 2)
#define Y_CABEZA (MAX_Y / 2)
#define R_CABEZA ((2 * MAX_X) / 42)


#define CURSOR_J1_X (X_DIVISION + 20)
#define CURSOR_J1_Y 20

#define CURSOR_J2_X (X_DIVISION + 20)
#define CURSOR_J2_Y (MAX_Y - 20 - 7)
// valores iniciales del juego

// pines del proyecto
#define X_JOYSTICK_1_PIN A8
#define Y_JOYSTICK_1_PIN A9

#define X_JOYSTICK_2_PIN A10
#define Y_JOYSTICK_2_PIN A11


// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// variables globales
// posiciones iniciales
uint16_t x0_jugador1 = (MAX_X * 3) / 8;
uint16_t y0_jugador1 = (MAX_Y  / 3);


uint16_t x0_jugador2 = (MAX_X * 3) / 8;
uint16_t y0_jugador2 = (MAX_Y ) / 3;


// variables del jugador
uint16_t pos_x_jugador1, pos_y_jugador1; // valor en pixeles

uint16_t pos_x_jugador2, pos_y_jugador2; // valor en pixeles



// valores de los sensores

uint16_t x_joystick1, y_joystick1;
uint16_t x_joystick2, y_joystick2;



// variables del marcador
uint8_t puntos1 = 0;
uint8_t puntos2 = 0;
//---------------------
void setup()
{
  // inicializacion de la pantalla
  tft.begin();
  tft.setRotation(1); // horizontal}
  tft.fillScreen(0);
  // interfaz estatica de la aplicacion
  // division ring-marcador
  tft.drawLine(X_DIVISION, 0, X_DIVISION, MAX_Y, WHITE);
  // ring
  tft.drawRect(8, 8, X_DIVISION - 16, MAX_Y - 16, YELLOW);
  tft.drawRect(9, 9, X_DIVISION - 18, MAX_Y - 18, YELLOW);
  tft.drawRect(10, 10, X_DIVISION - 20, MAX_Y - 20, YELLOW);
  // dibujar el marcador
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  // para el jugador 1
  tft.setCursor(CURSOR_J1_X, CURSOR_J1_Y);
  tft.print(puntos1,2);
  // para el jugador 2
  tft.setCursor(CURSOR_J2_X, CURSOR_J2_Y);
  tft.print(puntos2,2);
  
}
void loop()
{
  // lectura de los sensores
  x_joystick1 = analogRead(X_JOYSTICK_1_PIN);
  y_joystick1 = analogRead(Y_JOYSTICK_1_PIN);
 
  x_joystick2 = analogRead(X_JOYSTICK_2_PIN);
  y_joystick2 = analogRead(Y_JOYSTICK_2_PIN);
 
  
  // posicion absoluta del jugador
  uint16_t x_jugador1_nueva = map(x_joystick1, 0, 1023, 60, X_DIVISION - 60);
  uint16_t y_jugador1_nueva = map(y_joystick1, 0, 1023,MAX_Y - 40, 40);
 
  uint16_t x_jugador2_nueva = map(x_joystick2, 0, 1023, 60, X_DIVISION - 60);
  uint16_t y_jugador2_nueva = map(y_joystick2, 0, 1023, 40, MAX_Y - 40);
 
  
  
  // posicion relativa del jugador
//  uint16_t x_jugador1_nueva = x_joystick1 > 512 ? pos_x_jugador1 + 1 : pos_x_jugador1 -1;

//  uint16_t y_jugador1_nueva = y_joystick1 > 512 ? pos_y_jugador1 + 1 : pos_y_jugador1 -1;
  
  if(x_jugador1_nueva == pos_x_jugador1 && y_jugador1_nueva == pos_y_jugador1)
  {
    drawPlayer(pos_x_jugador1, pos_y_jugador1-40, RED, 1);
  }
  else
  {
    drawPlayer(pos_x_jugador1, pos_y_jugador1, RED, 1);
    drawPlayer(pos_x_jugador1, pos_y_jugador1, 0, 1);
 // }
  

  pos_x_jugador1 = x_jugador1_nueva;
  pos_y_jugador1 = y_jugador1_nueva;


  if(x_jugador2_nueva == pos_x_jugador2 && y_jugador2_nueva == pos_y_jugador2)
  {
    drawPlayer(pos_x_jugador2, pos_y_jugador2, RED, 0);
  }
  else
  {
    drawPlayer(pos_x_jugador2, pos_y_jugador2, RED, 0);
    drawPlayer(pos_x_jugador2, pos_y_jugador2, 0, 0);
  }
  

  pos_x_jugador2 = x_jugador2_nueva;
  pos_y_jugador2 = y_jugador2_nueva;






}
// funciones utiles
void drawLineG(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, uint8_t grosor)
{
  if(x0 < x1)
  {
    for( uint8_t i = 0; i < grosor; i++)
    {
      tft.drawLine(x0 + i, y0 + i, x1 + i, y1 + i, color);
    }
  }
  else
  {
    for( uint8_t i = 0; i < grosor; i++)
    {
      tft.drawLine(x0 + i, y0 - i, x1 + i, y1 - i, color);
    }
  }
  
}

void drawPlayer(uint16_t x0, uint16_t y0_jugador1, uint16_t color, uint8_t orientacion)
{
  if(orientacion == 0)
  {
      // cabeza
      tft.fillCircle(x0, y0_jugador1, R_CABEZA, color);
      // punho derecho
      tft.fillCircle(x0 + 40, y0_jugador1 - 20, R_CABEZA / 2, color);
      // punho izquierdo
      tft.fillCircle(x0 - 40, y0_jugador1 - 20, R_CABEZA / 2, color);
      //brazo izquierdo
      drawLineG(x0 - R_CABEZA, y0_jugador1, x0 - R_CABEZA - 15, y0_jugador1 + R_CABEZA + 5, color, 5);
      //antebrazo izquierdo
      drawLineG(x0 - R_CABEZA - 15, y0_jugador1 + R_CABEZA + 5, x0 - 40, y0_jugador1 - 20, color, 5);
      //brazo derecho
      drawLineG(x0 + R_CABEZA, y0_jugador1, x0 + R_CABEZA + 15, y0_jugador1 + R_CABEZA + 5, color, 5);
      //antebrazo derecho
      drawLineG(x0 + R_CABEZA + 15, y0_jugador1 + R_CABEZA + 5, x0 + 40, y0_jugador1 - 20, color, 5);
  }
  else if(orientacion == 1)
  {
    // cabeza
      tft.fillCircle(x0, y0_jugador1, R_CABEZA, color);
      // punho derecho
      tft.fillCircle(x0 + 40, y0_jugador1 + 20, R_CABEZA / 2, color);
      // punho izquierdo
      tft.fillCircle(x0 - 40, y0_jugador1 + 20, R_CABEZA / 2, color);
      //brazo izquierdo
      drawLineG(x0 - R_CABEZA, y0_jugador1, x0 - R_CABEZA - 15, y0_jugador1 - R_CABEZA - 5, color, 5);
      //antebrazo izquierdo
      drawLineG(x0 - R_CABEZA - 15, y0_jugador1 - R_CABEZA + 5, x0 - 40, y0_jugador1 + 20, color, 5);
      //brazo derecho
      drawLineG(x0 + R_CABEZA, y0_jugador1, x0 + R_CABEZA + 15, y0_jugador1 - R_CABEZA - 5, color, 5);
      //antebrazo derecho
      drawLineG(x0 + R_CABEZA + 15, y0_jugador1 - R_CABEZA - 5, x0 + 40 , y0_jugador1 +20, color, 5);
  }


}
/*
void drawPla(uint16_t x0, uint16_t y0, uint16_t color, uint8_t orientacion)
{
  if(orientacion == 0)
  {
      // cabeza
      tft.fillCircle(x0, y0, R_CABEZA, color);
      // punho derecho
      tft.fillCircle(x0 + 40, y0 - 20, R_CABEZA / 2, color);
      // punho izquierdo
      tft.fillCircle(x0 - 40, y0 - 20, R_CABEZA / 2, color);
      //brazo izquierdo
      drawLineG(x0 - R_CABEZA, y0, x0 - R_CABEZA - 15, y0 + R_CABEZA + 5, color, 5);
      //antebrazo izquierdo
      drawLineG(x0 - R_CABEZA - 15, y0 + R_CABEZA + 5, x0 - 40, y0 - 20, color, 5);
      //brazo derecho
      drawLineG(x0 + R_CABEZA, y0, x0 + R_CABEZA + 15, y0 + R_CABEZA + 5, color, 5);
      //antebrazo derecho
      drawLineG(x0 + R_CABEZA + 15, y0 + R_CABEZA + 5, x0 + 40, y0 - 20, color, 5);
  }
  else if(orientacion == 1)
  {
    // cabeza
      tft.fillCircle(x0, y0, R_CABEZA, color);
      // punho derecho
      tft.fillCircle(x0, y0 + 35, R_CABEZA / 2, color);
      // punho izquierdo
      tft.fillCircle(x0 - 40, y0 + 20, R_CABEZA / 2, color);
      //brazo izquierdo
      drawLineG(x0 - R_CABEZA, y0, x0 - R_CABEZA - 15, y0 - R_CABEZA - 5, color, 5);
      //antebrazo izquierdo
      drawLineG(x0 - R_CABEZA - 15, y0 - R_CABEZA + 5, x0 - 40, y0 + 20, color, 5);
      //brazo derecho
      drawLineG(x0 + R_CABEZA, y0, x0 + R_CABEZA + 15, y0 - R_CABEZA + 35, color, 5);
      //antebrazo derecho
      drawLineG(x0 + R_CABEZA + 15, y0 - R_CABEZA + 40, x0 , y0 +35, color, 5);
  }






*/

