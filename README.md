#### Pequeña adaptación del juego Arkanoid en lenguaje C.

##### Requerimientos:
* SDL2

##### Compilado:
```$ g++ -o arka arkanoid.cpp -lSDL2 ```

```$ ./arka ```

##### CONTROLES:

Flecha derecha: (→) mueve el cañon a la derecha.

Flecha izquierda: (←) mueve el cañon a la izquierda.

Espacio: realiza un disparo.

##### Presiona cualquier otra tecla para salir.

TODO:
* [x] control de colisiones para que al tocar un bloque morado desaparezca
* [x] agregar diferente movimiento cuando se dispare cercano a los 90°, significa mover la balita de acuerdo al angulo, no siempre de 1 en X y 1 en Y
* [x] recalcular algoritmo bresenham para que haga la animacion de rebote en las paredes
* [x] aplicar un escalado para desintegrar la balita al final de su recorrido
