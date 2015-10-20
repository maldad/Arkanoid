
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

int matriz[5][26];
int indice = 0;
int px[50];
int py[50];

//Starts up SDL and creates window
bool init();
//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

void color_purple(){
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );
	SDL_SetRenderDrawColor( gRenderer, 0xad, 0x26, 0xa7, 0xFF );
}//set color purple

void cuadritos(){
	color_purple();
	int xcoor = 10;
	int ycoor = 10;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 25; j++){
			if(matriz[i][j] == 0){//dibuja cuadrito si hay un 1 en esa posicion
				if(xcoor == 10 && ycoor == 10){//para el primer cuadrito
					SDL_Rect cuadrito1 = {xcoor, ycoor, 20, 20};
					SDL_RenderFillRect( gRenderer, &cuadrito1 );
					xcoor += 25;
				}else{//para los siguientes cuadritos horizontales
					SDL_Rect cuadrito1 = {xcoor, ycoor, 20, 20};
					SDL_RenderFillRect( gRenderer, &cuadrito1 );
					xcoor += 25;
				}
			}else{//no dibuja cuadrito, pero avanza x
				xcoor += 25;
			}
		}//termina la primera fila, reiniciamos coordenada X, aumentamos Y
		xcoor = 10;
		ycoor += 25;
	}//for para dibujar los cuadritos
}//cuadritos

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

void colocar(int x, int y){
	if(indice == 50){
		return;
	}else{
		px[indice] = x;
		py[indice] = y;
	}
}//colocar

void reset(){//vaciar los arreglos de coordenadas y el indice
	indice = 0;
	for(int i = 0; i < 50; i++){
		px[i] = 0;
		py[i] = 0;
	}
}//reset

void mover_balita(int xp, int yp){
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
	//xactualcanon +=10;
	//yactualcanon -=10;
}//mover_balita


void bresenham(int x2, int y2, int xl, int yl){
	reset();
    int xi = x2;
    int yi = y2;
    int xf = xl;
    int yf = yl;

    //calculando DELTAS
    int deltax = xf-xi;
    int deltay = yf-yi;

	if(deltay < 0 && deltax > 0 && abs(deltax) > abs(deltay)){
        printf("CASO 1\n" );
        int A = -2*deltay;
        int B = -2*deltay - 2*deltax;
        int pi = -2*deltay - deltax;
        printf("inicio (%d, %d)\n", xi, yi);
        int xk = xi;
        int yk = yi;

        while (xk <= xf-10 && yk >= yf) {
            if(pi > 0){
                xk+=10; //en vez de mover 1 pixel, movemos 10
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+B;
            }//if
            else{
                xk+=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+A;
            }//else
        }//while
		printf("final: %d %d\n", xk, yk);
		return;
    }//if caso 1

if(deltay < 0 && deltax > 0 && abs(deltax) <= abs(deltay)){
        printf("CASO 2\n" );
        int A = -2*deltax;
        int B = -2*deltax - 2*deltay;
        int pi = -2*deltax - deltay;
        printf("inicio (%d, %d)\n", xi, yi);
        int xk = xi;
        int yk = yi;

        while (xk <= xf-10 && yk >= yf) {
            if(pi > 0){
                //xk++;
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+A;
            }//if
            else{
                xk+=10;
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+B;
            }//else
        }//while
    }//if caso 2

if(deltay < 0 && deltax < 0 && abs(deltay) > abs(deltax)){
        printf("CASO 3\n");
        int A = 2*deltax;
        int B = 2*deltax - 2*deltay;
        int pi = 2*deltax - deltay;
        printf("inicio (%d, %d)\n", xi, yi);
        int xk = xi;
        int yk = yi;

        while (xk >= xf && yk >= yf+10) {
            if(pi > 0){
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+A;
            }//if
            else{
                xk-=10;
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+B;
            }//else
        }//while
    }//if caso 3

if(deltay < 0 && deltax < 0 && abs(deltay) <= abs(deltax)){
        printf("CASO 4\n" );
        int A = 2*deltay;
        int B = 2*deltay - 2*deltax;
        int pi = 2*deltay - deltax;
        printf("inicio (%d, %d)\n", xi, yi);
        int xk = xi;
        int yk = yi;

        while (xk >= xf && yk >= yf+10) {
            if(pi > 0){
                xk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+A;
            }//if
            else{
                xk-=10;
                yk-=10;
                colocar(xk, yk);
				indice++;
                printf("punto (%d, %d)\n", xk, yk);
                pi = pi+B;
            }//else
        }//while
    }//if caso 2


}//bresenham

void calcula_limites(int xp, int yp){//xprima, yprima
	//popsible RETURN en cada IF?
	int x = xinicanon; //base del canon
	int y = yinicanon;
	int x2 = xp;
	int y2 = yp;
	//para el 1er caso, xl =640
	if(x2 > 377){
		int xl = 640; //limite SCREEN_WIDTH
		//ahora calculamos el limite Y
		//este sirve para el caso 1 y 4, (rebota en pared izq o der)
		int yl = ( ( (y2-y)*(xl-x) )/(x2-x)  ) + y; //una regla de 3
		printf("origen: %d %d, finCanon: %d %d, limite: %d %d\n", x, y, x2, y2, xl, yl);
		bresenham(x2, y2, xl, yl);
	}//caso 1
	if(x2 < 265){
		int xl = 0; //limite SCREEN_WIDTH hacia la izquierda
		//ahora calculamos el limite Y
		//este sirve para el caso 1 y 4, (rebota en pared izq o der)
		int yl = ( ( (y2-y)*(xl-x) )/(x2-x)  ) + y; //una regla de 3
		printf("origen: %d %d, finCanon: %d %d, limite: %d %d\n", x, y, x2, y2, xl, yl);
		bresenham(x2, y2, xl, yl);
	}//caso 4
	if(x2 <= 377 && x2 > 320){
		int yl = 0;
		int xl = ( ( (x2-x)*(yl-y) )/(y2-y)  ) + x;
		printf("origen: %d %d, finCanon: %d %d, limite: %d %d\n", x, y, x2, y2, xl, yl);
		bresenham(x2, y2, xl, yl);
	}//caso 2
	if(x2 < 320 && x2 >= 265){
		int yl = 0;
		int xl = ( ( (x2-x)*(yl-y) )/(y2-y)  ) + x;
		printf("origen: %d %d, finCanon: %d %d, limite: %d %d\n", x, y, x2, y2, xl, yl);
		bresenham(x2, y2, xl, yl);
	}
}//calcula_limites



void rotacion(int angle, int xp, int yp){
	int xc = xinicanon;
	int yc = yinicanon;
	int x = xp;
	int y = yp;
	xprima = xc + ( (x-xc)*cos(angle/57.3) - (y-yc)*sin(angle/57.3));
	yprima = yc + ( (x-xc)*sin(angle/57.3) + (y-yc)*cos(angle/57.3));
	printf("xprima, yprima: %d %d\n", xprima, yprima);

}//rotacion

void dibujar(){
	cuadritos();
	SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xFF );
	SDL_Rect balita = {xfincanon, yfincanon-17, 17, 17};
	SDL_RenderFillRect( gRenderer, &balita );
	//320, 480, 320, 380 el cañon mide 100 pixeles
	SDL_RenderDrawLine(gRenderer, xinicanon, yinicanon, xfincanon, yfincanon);
	//refrescar pantalla...
	SDL_RenderPresent( gRenderer );
}//dibujar



void cambia_canon(int xp, int yp){//dibuja el canon y la balita en su nueva posicion
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

void dormir(){
	usleep(1000 *25);
}

bool zona_bloques(int y){
	if(y <= 105){ //es la zona donde empiezan los bloques, 85+20=105
		return true;
	}
	return false;
}//zona_bloques

void quita_bloques(int x, int y){
	puts("entro a la zona de bloques");
	printf("x, y actual: %d %d\n", x, y);
	//obteniendo coordenadas reales para borrar el cuadrito
	x = (x-10)/25;
	y = (y-10)/25;
	printf("x, y a borrar: %d %d\n", x, y);
	//asignamos 1, para que no dibuje cuadrito en esa zona
	matriz[y][x] = 1;
}//quita_bloques

int main( int argc, char* args[] ){
	//Start up SDL and create window
	//asignar();
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
						case SDLK_SPACE:
						puts("espacio, entonces se dispara");

						for(int i = 0; i < 50; i++){
							dormir();
							if(px[i] == 0 && py[i] == 0 && i > 0){
								break;
							}else{
								mover_balita(px[i], py[i]);
								printf("%d %d \n", px[i], py[i]);
							}
						}//for

						break;

						case SDLK_LEFT:
						//aqui mandar a llamar rotacion
						puts("mueve canion a la izquierda");
						rotacion(-15, xprima, yprima);
						cambia_canon(xprima, yprima);

						calcula_limites(xprima, yprima);
						break;

						case SDLK_RIGHT:
						rotacion(15, xprima, yprima);
						cambia_canon(xprima, yprima);
						puts("mueve cañon a la derecha");
						calcula_limites(xprima, yprima);
						break;

						default:
						//salir del juego con cualquier tecla
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
