
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

//constantes para dimensiones de la pantalla
const int SCREEN_WIDTH = 640;   //largo
const int SCREEN_HEIGHT = 480; //alto
const int xinicanon = SCREEN_WIDTH/2;
const int yinicanon = SCREEN_HEIGHT;
const int xfincanon = 320;
const int yfincanon = 380;
int xprima = xfincanon;
int yprima = yfincanon;
int xactualcanon = xfincanon;
int yactualcanon = yfincanon-17;
//Starts up SDL and creates window
bool init();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init(){
	//flag para iniciar
	bool success = true;

	//Iniciar SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		//creando la ventana!!!
		gWindow = SDL_CreateWindow( "---Arkanoid---", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}else{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}else{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}
return success;
}//init


void close(){
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}//close

void rotacion(int angle, int xp, int yp){
	int xc = xinicanon;
	int yc = yinicanon;
	int x = xp;
	int y = yp;
	xprima = xc + ( (x-xc)*cos(angle/57.3) - (y-yc)*sin(angle/57.3));
	yprima = yc + ( (x-xc)*sin(angle/57.3) + (y-yc)*cos(angle/57.3));
}//rotacion

void dibujar(){
	//Clear screen
	//colocar un fondo negro
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );

	SDL_SetRenderDrawColor( gRenderer, 0xad, 0x26, 0xa7, 0xFF );
	for(int i = 10; i < 630; i+=25){
		SDL_Rect cuadrito1 = {i, 10, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 20; i < 600; i+=25){
		SDL_Rect cuadrito1 = {i, 35, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 30; i < 590; i+=25){
		SDL_Rect cuadrito1 = {i, 60, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 40; i < 570; i+=25){
		SDL_Rect cuadrito1 = {i, 85, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for

	//si dejamos un draw color asi, todos los demas
	//elementos que se dibujen seran del mismo color
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );
	SDL_Rect balita = {xfincanon, yfincanon-17, 17, 17};
	SDL_RenderFillRect( gRenderer, &balita );
	//320, 480, 320, 380 el cañon mide 100 pixeles
	SDL_RenderDrawLine(gRenderer, xinicanon, yinicanon, xfincanon, yfincanon);
	//refrescar pantalla...
	SDL_RenderPresent( gRenderer );
}//dibujar

void cuadritos(){
	//Clear screen
	//colocar un fondo negro
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );
	SDL_SetRenderDrawColor( gRenderer, 0xad, 0x26, 0xa7, 0xFF );
	for(int i = 10; i < 630; i+=25){
		SDL_Rect cuadrito1 = {i, 10, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 20; i < 600; i+=25){
		SDL_Rect cuadrito1 = {i, 35, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 30; i < 590; i+=25){
		SDL_Rect cuadrito1 = {i, 60, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	for(int i = 40; i < 570; i+=25){
		SDL_Rect cuadrito1 = {i, 85, 20, 20};
		SDL_RenderFillRect( gRenderer, &cuadrito1 );
	}//for
	SDL_RenderPresent( gRenderer );

}//cuadritos

void cambia_canon(int xp, int yp){
	//Clear screen
	//colocar un fondo negro
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );
	cuadritos();
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );

	//320, 480, 320, 380 dibujando el canon
	SDL_RenderDrawLine(gRenderer, xinicanon, yinicanon, xp, yp);
	//la balita debe seguir la punta del canñon
	xactualcanon = xprima;
	yactualcanon = yprima;
	SDL_Rect balita = {xp, yp-17, 17, 17};
	SDL_RenderFillRect( gRenderer, &balita );

	SDL_RenderPresent( gRenderer );

}//cambia

void traslada_balita_derecha(int xp, int yp){
	//Clear screen
	//colocar un fondo negro
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );
	cuadritos();
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );

	//320, 480, 320, 380 -- dibujando el cañon
	SDL_RenderDrawLine(gRenderer, xinicanon, yinicanon, xprima, yprima);
	SDL_Rect balita = {xp, yp, 17, 17};
	SDL_RenderFillRect( gRenderer, &balita );

	SDL_RenderPresent( gRenderer );
	xactualcanon +=10;
	yactualcanon -=10;
}//traslada_balita_derecha

void traslada_balita_izquierda(int xp, int yp){
	//Clear screen
	//colocar un fondo negro
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );
	cuadritos();
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );

	//320, 480, 320, 380 -- dibujando el cañon
	SDL_RenderDrawLine(gRenderer, xinicanon, yinicanon, xprima, yprima);
	SDL_Rect balita = {xp, yp, 17, 17};
	SDL_RenderFillRect( gRenderer, &balita );

	SDL_RenderPresent( gRenderer );
	xactualcanon -=10;
	yactualcanon -=10;
}//izq

int main( int argc, char* args[] ){
	//Start up SDL and create window
	if( !init() ){
		printf( "Failed to initializ!\n" );
	}else{
		dibujar();
		//Main loop flag
		bool quit = false;
		//Event handler
		SDL_Event e;
		//While application is running
		while( !quit ){
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 ){
				//User requests quit
				if( e.type == SDL_QUIT ){
					quit = true;
				}
				else if( e.type == SDL_KEYDOWN ){
					switch( e.key.keysym.sym ){
						case SDLK_UP:
						//gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
						puts("arriba, entonces se dispara");
						if(xprima >= SCREEN_WIDTH/2){
							while(xactualcanon < SCREEN_WIDTH && yactualcanon > 40){
								usleep(1000 *150);
								traslada_balita_derecha(xactualcanon, yactualcanon);
								if(xactualcanon >= SCREEN_WIDTH){
									usleep(1000 *150);
									traslada_balita_izquierda(xactualcanon, yactualcanon);

									while(xactualcanon > 0 && yactualcanon > 40){
										usleep(1000 *150);
										traslada_balita_izquierda(xactualcanon, yactualcanon);
									}

								}
							}
						}//if empieza hacia derecha
						else{//empiez hacia izquierda
							while(xactualcanon > 0 && yactualcanon > 40){
								usleep(1000 *150);
								traslada_balita_izquierda(xactualcanon, yactualcanon);
								if(xactualcanon < 0){
									//usleep(1000 *150);
									//traslada_balita_derecha(xactualcanon, yactualcanon);

									while(xactualcanon < SCREEN_WIDTH && yactualcanon > 40){
										usleep(1000 *150);
										traslada_balita_derecha(xactualcanon, yactualcanon);
										if(xactualcanon >= SCREEN_WIDTH){
											usleep(1000 *150);
											traslada_balita_izquierda(xactualcanon, yactualcanon);
										}
									}


								}
							}
						}
						break;

						case SDLK_LEFT:
						//aqui mandar a llamar rotacion
						puts("mueve canion a la izquierda");
						rotacion(-15, xprima, yprima);
						cambia_canon(xprima, yprima);
						break;

						case SDLK_RIGHT:
						rotacion(15, xprima, yprima);
						cambia_canon(xprima, yprima);
						puts("mueve cañon a la derecha");
						break;

						default:
						//gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
						//implementar para salir del juego
						//presionar cualquier tecla para salir
						//MENOS: izquiera, derecha o arriba
						quit = true;
						break;
					}
				}//else manejar evento
			}//while sdl event
		}//while aplicacion is running

	}//else si inicio SDL

	//Free resources and close SDL
	close();

	return 0;
}//main
