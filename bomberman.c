#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "zelda.h"
#include "marco.h"
#define ALTO 20
#define LARGO 20
typedef struct Personaje{
  int x;
  int y;
  int vidas;
  int puntos;
  int estado;
}PERSONAJE;
typedef struct Bomba{
  int tiempo;
  int x;
  int y;
}BOMBA;
ALLEGRO_DISPLAY * display = NULL;
ALLEGRO_EVENT_QUEUE * event_queue = NULL;
ALLEGRO_BITMAP * imagen = NULL;
ALLEGRO_BITMAP * explosion = NULL;
ALLEGRO_PATH * path = NULL;
BOMBA bombas[10];
int contador_bombas = 0;
int tablero[20][20];

PERSONAJE personaje;
int init(){
  int i, j;
  ALLEGRO_TIMER * timer = NULL;

  if(!al_init())printf("No se pudo");
  if(!al_init_image_addon())printf("No se pudo abrir el gestor de imagenes\n");
  if(!al_install_keyboard()) printf("No se pudo iniciar el teclado\n");
  display = al_create_display(400, 400);
  event_queue = al_create_event_queue();

  path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_change_directory(al_path_cstr(path, '/'));
  al_destroy_path(path);
  timer = al_create_timer(1.0 / 60);
  imagen = al_load_bitmap("img/zelda.gif");
  explosion = al_load_bitmap("img/marco.png");
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  for (i = 0; i < ALTO; ++i){
    for (j = 0; j < LARGO; ++j)
    {
      tablero[i][j] = 0;
    }
  }
  personaje.x = 2;
  personaje.y = 2;
  personaje.vidas = 3;
  personaje.puntos = 0;
  tablero[personaje.x][personaje.y] = 1;
  al_start_timer(timer);
  return 1;
}
int entrada(ALLEGRO_EVENT * event){
  BOMBA bomba;
  switch(event->keyboard.keycode){
    case ALLEGRO_KEY_RIGHT:
      if(personaje.x < LARGO-1){
        personaje.x++;
        personaje.estado = 0;
      }
    break;
    case ALLEGRO_KEY_LEFT:
      if(personaje.x > 0){
        personaje.x--;
        personaje.estado = 8;
      }
    break;
    case ALLEGRO_KEY_DOWN:
      if(personaje.y < ALTO-1){
        personaje.y++;
        personaje.estado = 4;
      }
    break;
    case ALLEGRO_KEY_UP:
      if(personaje.y > 0){
        personaje.y--;
        personaje.estado = 1;
      }
    break;
    case ALLEGRO_KEY_B:
    case ALLEGRO_KEY_X:
      bomba.x = personaje.x;
      bomba.y = personaje.y;
      bomba.tiempo = 3;
      bombas[contador_bombas] = bomba;
      contador_bombas++;
    break;
  }
  
  return 0;
}
void logica(int x){
  int i;
  switch(x){
    case 1://Tiempo de bomba
      for (i = 0; i < contador_bombas; ++i){
        bombas[i].tiempo--;
      }
    break;
  }
}
void dibujo(){
  int i;
  al_clear_to_color(al_map_rgb(0, 0 ,255));
  al_draw_bitmap_region(imagen, sprites[personaje.estado][0], sprites[personaje.estado][1], 
    sprites[personaje.estado][2], sprites[personaje.estado][3], personaje.x*20, personaje.y*20, 0);

  for(i=0; i<contador_bombas; i++){
    fprintf(stderr, "%s %d \n", "Bomba", bombas[i].tiempo);
    if(bombas[i].tiempo > 0 )
      al_draw_bitmap_region(imagen, sprites[100][0], sprites[100][1], 
        sprites[100][2], sprites[100][3], bombas[i].x*20, bombas[i].y*20, 0);
    else{
      al_draw_bitmap_region(explosion, ex[70][0], ex[70][1], 
        ex[70][2], ex[70][3], bombas[i].x*20, bombas[i].y*20, 0);
    }

  }
  al_flip_display();
}
int main(int argc, char const *argv[])
{
  ALLEGRO_EVENT event;
  int salida = 0;
  int contador = 1;
  init();
  while(!salida){
    al_get_next_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      salida = 1;
    }
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
      entrada(&event);
    }
    if(event.type == ALLEGRO_EVENT_TIMER){
      dibujo();
      contador++;
    }
    if(contador% 800 == 0 )
    {
      logica(1);
    }
  }
  return 0;
}
