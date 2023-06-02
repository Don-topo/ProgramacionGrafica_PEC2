## Índice
- [1. Carga del mapa](#1-carga-del-mapa)
- [2. Mostrar el mapa](#2-mostrar-el-mapa)
- [3. Estados del jugador](#3-estados-del-jugador)
- [4. Animaciones del jugador](#4-animaciones-del-jugador)
- [5. Movimientos del jugador](#5-movimiento-del-jugador)
- [6. Game manager](#6-game-manager)
- [7. Texture manager](#7-texture-manager)
- [8. Audio manager](#8-audio-manager)
- [9. Comer objetos](#9-comer-objetos)
  - [9.1. Puntos](#91-puntos)
  - [9.2. Píldoras](#92-píldoras)
- [10. Colisiones con el fantasma](#10-colisiones-con-el-fantasma)  
- [11. Muerte del jugador](#11-muerte-del-jugador)
- [12. Movimiento del fantasma](#12-movimiento-del-fantasma)
- [13. Enemy manager](#13-enemy-manager)
- [14. Cosas pendientes/mejoras](#14-cosas-pendientesmejoras)

# 1. Carga del mapa

Para generar el tilemap he utilizado el programa Tiled. Los valores de las texturas las genera desde el índice 0.
En cuanto al mapa de colisiones lo he tenido que hacer a mano. He decidido cambiar las zonas transitables a 0 y las paredes a 1 porque me resultaba más fácil diferenciar los caminos.
Finalmente el mapa de objetos lo he hecho a partir del mapa de colisiones, en este caso he optado por utilizar el (-1) para indicar que allí no hay nada.
Para la carga del mapa de juego he re aprovechado el método LoadTileMap de los ejemplos. Aparte he añadido una iteración más para añadir los objetos. El funcionamiento es similar al ejemplo,
en este caso lo que hago es reemplazar el valor de la textura con el que tenía antes. No se toca el collider ni ningún otro valor.

# 2. Mostrar el mapa

Para mostrar el mapa por pantalla recorro todos los valores que tengo del tilemap y dibujo el rectangulo que le toca a esa posición. En este caso la hoja de sprites tiene 10 columnas y 3 filas.
Por lo tanto el rango de representación irá desde 0 a 9 en caso de las columnas y de 0 a 2 en el caso de las filas.
En mi caso el Tilemap se empieza a escribir desde la posición (50, 50).
Por lo que a partir de aquí le añado la posición que toca pintar por el tamaño de la tile ((50 + num_tileX * 32),(50 + num_tileY * 32 * maxTilesFila)).
En el caso del eje Y el tile map es como si fuera un array unidimensional por lo que no es una matriz. Por eso cada Y se tiene que calcular con el número de columnas total que tengo en el mapa para acceder a la posición
correcta.
La fórmula de arriba tal como esta no funciona y al eje de las X se le debe añadir el desplazamiento de la Y también:
((50 + num_tileX * 32 * (num_tileY * maxTilesFilaX)),(50 + num_tileY * 32 * maxTilesFila)).

# 3. Estados del jugador

Para controlar los estados del jugador he definido un emun con todos ellos. Seguidamente tengo unos métodos en la misma clase del jugador para ir cambiando de estado cuando se produzca un evento en el Screen_Gameplay.
En el update del jugador he puesto un switch para realizar las diferentes acciones dependiendo del estado del jugador. En este caso los estados que afectan al sprite que se tiene que mostrar por pantalla.
En terminos de movimiento en todos los estados se aplica el movimiento que ha indicado el jugador (si se puede) y en el caso de la animación de muerte se restringe el movimiento a 0.

# 4. Animaciones del jugador

El jugador en todas las animaciones de movimiento tiene solo dos Sprites y cada estado esta reprentado en una fila de la sprite sheet. He definido en cada estado los valores de los índices a los que ha de apuntar
para cargar el sprite correcto. Esta acción solo la hago si el nuevo estado es diferente al anterior porque también reseteo el contador de frames para empezar una animación nueva. De este modo si el estado no cambia,
por ejemplo porque el jugador se esta moviendo a la derecha lo que se va a hacer es ir cambiando de sprite cada 60 frames.
A parte esta la animación de muerte, esta es un poco diferente y se encuentra sola en un sprite sheet a parte. Además de estar contenida toda la animación en una sola fila. Aquí el funcionamiento es el mismo que en
el resto de casos la diferencia es que el número de frames máximo que puede representar es más alto.

# 5. Movimiento del jugador

El jugador siempre va a tener un movimiento incremental de +-2 puntos en los ejes. Este valor se indica dependiendo de que tecla a sido pulsada por el jugador. En el caso en el que el jugador quiera ir a una dirección 
que tenga un collider el movimiento no se producirá. Para hacer esto cojo la posición actual del jugador, le añado el movimiento que ha indicado el usuario y miro todas las tiles del tile map.
En cada tile compruebo si esa tile tiene un collider a 1 y si esta en colisión con el jugador. Siempre tomando como punto el centro de ambos sprites (posX + movementX + (Size / 2), posY + movementY + (Size / 2)).
Si se produce una colisión con una pared el movimiento de los ejes pasa a 0. Para economir un poco la operación en el momento en el que se produce una colisión saldo del método con un return.


# 6. Game Manager

Para esta práctica el control de todas las transiciones de pantallas y datos se realizan a través del Game Manager. También dispone de una instancia de cada manager sumado a un singleton para tener 
solo una instancia y poder acceder al resto de componentes desde las clases Screen_XXX.

# 7. Texture Manager

En la práctica anterior no implementé el Texture Manager. En esta si, solo dispone de una inicialización que carga todas las texturas, un método para devolver la textura que necesito y un método para eliminar
las texturas de memoria al finalizar la aplicación. Tengo a parte un método para la carga del Tilemap.

# 8. Audio Manager

Como en el caso anterior, en la primera práctica no implementé el Audio Manager, tiene un funcionamiento parecido al Texture Manager pero en este caso para Sonidos y Música.

# 9. Comer objetos

Esta funcionalidad se revisa después de calcular y aplicar el movimiento de PACMAN. Se que es poco eficiente pero lo que hago es recorrer todo el mapa de tiles. Para saber si PACMAN se encuentra delante de un
punto o píldora miro el valor de la tile y si esta en colisión con PACMAN (la colisión siempre a partir de la posición del sprite mas un offset XY de la mitad del tamaño del sprite para estar en el centro).
Con estos requisitos no se puede dar el caso de que pacman se coma más de un objeto a la vez por lo que si encuentro que se ha comido uno simplemente hago un return y no miro el resto de posiciones.

## 9.1. Puntos

Al comer un punto cambio el valor de esa textura por el de camino vacío. Le indico al Game Manager que incremente en 10 la puntuación y le indico al Audio Manager que ponga el Sonido Waka.

## 9.2. Píldoras

Al comer una píldora a parte de cambiar el valor de la tile y incrementar la puntuación tengo que cambiar el estado del fantasma a Frightened. También le indico al Audio Manager que ponga el Sonido de Sirena.

# 10. Colisiones con el fantasma

En este caso es un poco más simple que con los objetos, simplemente miro desde el centro del jugador y el enemigo si hay colisión. En el caso de haberla miro el estado del enemigo. Si esta asustado y no ha sido comido
cambio su estado a comido, indico al Game Manager que incremente la puntuación y indico al Audio Manager que ponga el sonido de muerte del fantasma.
En el caso de que el fantasma este en Chase cambio el estado del jugador a muerto, le resto una vida y indico al Audio Manager que ponga el sonido de muerte de PACMAN.

# 11. Muerte del jugador

En el momento en el que se muere PACMAN el bucle principal de la pantalla espera 10 segundos antes de volver a iniciar la partida.
Para iniciar la partida lo que hago es resetear al jugador y al enemigo para que vuelvan a sus posiciones iniciales. El mapa no cambia.
En el caso de que no queden más vidas pasaremos a la pantalla de finalización y el jugador puede volver a jugar. En el caso de volver a jugar una partida nueva se resetea el jugador y el enemigo, los valores score y life del Game Manger
y el tile map (para que aparezcan todos los elementos).

# 12. Movimiento del fantasma

Para movimiento del fantasma utilizo varias variables:
  - Movimiento anterior
  - Posición destino
  - Posición siguiente tile
  - Array de posibles direcciones

En función del movimiento anterior lleno el array de direcciones con todas las direcciones menos la opuesta a la que acabo de realizar. Si he llegado al punto que señala la siguiente tile calculo una tile nueva,
si no incremento el movimiento.
Para calcular la nueva tile asigno la siguiente posición en cada una de las direcciones posibles. Por ejemplo en la dirección Up tendré la posición actual menos 32 en el eje de las Y.
Seguidamente tengo que decartar las direcciones que tienen una colisión. Para esto miro si hay alguna tile en el tile map que haga colisión con ella. Si se da el caso marco la dirección como colisionada.
En pasos posteriores no se usará.
Una vez que tengo las direcciones sin colisiones toca calcular cual de ellas es la que tiene menos recorrido para ello cojo la posición de la nueva dirección y le resto el destino. Como esto puede dar lugar
a valores negativos me quedo con el valor absoluto. Finalmente pongo los valores de los ejes al cuadrado y miro de entre todas las direcciones válidas la mímina.
Una vez que tengo la dirección con el camino mínimo pongo esa posición como destino de la próxima tile.

Hay un caso especial que es el inicial, este solo se produce al empezar la partida y después de la muerte del jugador. Aquí por defecto establezco que la siguiente tile es la que tiene arriba el fantasma así me evito que tenga
que dar vueltas de más dentro de la caja inicial.

# 13. Enemy Manager

Como en este caso solo tenemos un enemigo no he incluido el Enemy Manager, si se hubiera requerido implementar los demás fantasmas si que hubiera sido necesario implementarlo.

# 14. Cosas pendientes/mejoras

El control de PACMAN no es todo lo preciso que me gustaría, a veces se puede quedar enganchado en algún giro si no giramos en el margen adecuado.
Por otro lado el movimiento del fantasma a veces no es todo lo preciso que debería. hay algunas veces en la que puede tomar un camino más largo que el que debería.


