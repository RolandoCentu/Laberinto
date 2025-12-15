Cómo generaste el laberinto:

Generé el laberinto usando un algoritmo de DFS recursivo (Depth‑First Search) aplicado sobre una matriz inicialmente llena de muros ('#'). El proceso funciona así:

Comienzo en una celda impar (por ejemplo, (1,1)), que será el punto inicial del laberinto.
Marco esa celda como visitada y la convierto en un camino ('-').
Elijo un orden aleatorio de direcciones (arriba, abajo, izquierda, derecha).
Me muevo dos celdas a la vez en la dirección elegida:
-La celda intermedia es un muro → lo rompo.
-La celda destino se convierte en camino.
Repito el proceso recursivamente desde la nueva celda.
Cuando ya no hay más caminos posibles, la recursión retrocede.

Este método genera un laberinto perfecto, es decir:
No tiene ciclos innecesarios.
No tiene zonas aisladas.
Siempre existe un camino entre la entrada y la salida.


Qué algoritmo usaste para resolverlo:

Para resolver el laberinto utilicé DFS recursivo, pero esta vez aplicado sobre los caminos ya generados.

El algoritmo funciona así:

Empiezo desde la entrada ('E').
Marco cada celda visitada para no repetirla.
Avanzo en las cuatro direcciones posibles (arriba, abajo, izquierda, derecha).
Solo puedo moverme a celdas que sean:
	-camino ('-')
	-o la salida ('S')

Si llego a la salida, devuelvo true y termino.
Si un camino no funciona, hago backtracking:
	-desmarco la celda
	-regreso a la celda anterior
	-pruebo otra dirección


Qué descubriste al medir tiempos y qué harías distinto la próxima vez:

Usaría BFS para resolver el laberinto, porque BFS garantiza encontrar el camino más corto, mientras que DFS no.
Mediría tiempos con chrono para obtener datos más precisos.
Probaría laberintos más grandes (por ejemplo, 501×501) para ver cómo escala el rendimiento.