#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
typedef struct Personaje{
  int x;
  int y;
  int vidas;
  int puntos;
}PERSONAJE;
ALLEGRO_DISPLAY * display = NULL;
ALLEGRO_EVENT_QUEUE * event_queue = NULL;
int tablero[20][20];

PERSONAJE personaje;
int init(){
  int i, j;

  if(!al_init())printf("No se pudo");
  display = al_create_display(400, 400);
  event_queue = al_create_event_queue();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  for (i = 0; i < 20; ++i){
    for (j = 0; j < 20; ++j)
    {
      tablero[i][j] = 0;
    }
  }
  personaje.x = 2;
  personaje.y = 2;
  personaje.vidas = 3;
  personaje.puntos = 0;
  tablero[personaje.x][personaje.y] = 1;
  return 1;
}
int entrada(){
  
  
  return 0;
}
void logica(int x){

}
void dibujo(){
  al_clear_to_color(al_map_rgb(0, 0 ,255));
  al_flip_display();
  al_rest(1);
}
int main(int argc, char const *argv[])
{
  ALLEGRO_EVENT event;
  int salida = 0;
  init();
  while(!salida){
    al_get_next_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      salida = 1;
    }
    entrada();
    logica(2);
    dibujo();
  }
  return 0;
}