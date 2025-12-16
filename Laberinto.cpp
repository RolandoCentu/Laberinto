#include <iostream> // Para std::cout, std::endl
#include <vector>  // Para std::vector
#include <algorithm> // Para std::shuffle
#include <cstdlib> // Para rand() y srand()
#include <ctime>  // Para time() en random
#include <random> // Para random_shuffle
#include <chrono> // Para medir tiempo


using namespace std;

// Tamaño del laberinto (debe ser impar para DFS de 2 en 2)
int filas = 11;
int columnas = 11;

// Tablero y estructuras de datos
vector<vector<char>> tablero;
vector<vector<bool>> visitados;
vector<vector<bool>> visitadosResolver;

// Movimientos posibles para generar (saltos de 2)
int dirFila[] = {-2, 2, 0, 0};
int dirColumna[] = {0, 0, -2, 2};


// Inicializa el tablero lleno de muros '#'

void inicializarTableroLleno() {
    tablero.assign(filas, vector<char>(columnas, '#'));
    visitados.assign(filas, vector<bool>(columnas, false));
}


// Coloca un caracter en una posición específica

void posicionarCaracter(int fila, int columna, char caracter) {
    tablero[fila][columna] = caracter;
}


// Genera laberinto usando DFS recursivo
// x,y deben ser posiciones IMPARES

void generarLaberintoDFS(int x, int y) {
    visitados[x][y] = true;
    tablero[x][y] = '-';  // abrir celda actual

    vector<int> direcciones = {0, 1, 2, 3};

    static default_random_engine rng(time(0));
    shuffle(direcciones.begin(), direcciones.end(), rng);

    for (int i = 0; i < 4; i++) {
        int nx = x + dirFila[direcciones[i]];
        int ny = y + dirColumna[direcciones[i]];

        // Evitar bordes y visitar solo celdas no visitadas
        if (nx > 0 && nx < filas - 1 && ny > 0 && ny < columnas - 1 && !visitados[nx][ny]) {

            // Abrir muro intermedio
            int muroX = x + dirFila[direcciones[i]] / 2;
            int muroY = y + dirColumna[direcciones[i]] / 2;

            tablero[muroX][muroY] = '-';
            tablero[nx][ny] = '-';

            generarLaberintoDFS(nx, ny);
        }
    }
}


// Resolver laberinto usando DFS (buscar la SALIDA 'S')

bool resolverDFS(int x, int y) {
    int dxf[] = {-1, 1, 0, 0};
    int dyf[] = {0, 0, -1, 1};

    // Si encontramos la salida 'S', terminamos
    if (tablero[x][y] == 'S') return true;

    visitadosResolver[x][y] = true;

    // Marcar camino recorrido (excepto la entrada 'E')
    if (tablero[x][y] != 'E') {
        tablero[x][y] = '*';
    }

    // Intentar moverse en las 4 direcciones
    for (int i = 0; i < 4; i++) {
        int nx = x + dxf[i];
        int ny = y + dyf[i];

        if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas &&
            !visitadosResolver[nx][ny] &&
            (tablero[nx][ny] == '-' || tablero[nx][ny] == 'S')) {

            if (resolverDFS(nx, ny)) return true;
        }
    }

    // Backtracking: si no sirve este camino, lo desmarcamos
    if (tablero[x][y] != 'E') {
        tablero[x][y] = '-';
    }

    return false;
}


void imprimirTablero() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << "  " << tablero[i][j];
        }
        cout << endl;
    }
}
int main(int argc, char* argv[]) {

    // permitir tamaño desde parámetros externos
    // Ejemplo: ./laberinto 25 25
    if (argc >= 3) {
        filas = atoi(argv[1]);
        columnas = atoi(argv[2]);
    }
    srand(time(0));

    inicializarTableroLleno();

    // Generar laberinto desde (1,1) — posición impar
    auto inicioGen = chrono::high_resolution_clock::now();

    generarLaberintoDFS(1, 1);

    auto finGen = chrono::high_resolution_clock::now();
    auto tiempoGen = chrono::duration_cast<chrono::milliseconds>(finGen - inicioGen).count();

    cout << "Tiempo de generación: " << tiempoGen << " ms\n";



    
    posicionarCaracter(1, 1, 'E');  // entrada
    posicionarCaracter(filas - 2, columnas - 2, 'S');  // salida

    cout << "Laberinto generado:\n";
    imprimirTablero();

    cout << "\nCamino resuelto:\n";
    visitadosResolver.assign(filas, vector<bool>(columnas, false));

    // Resolver desde la entrada (1,1)
    auto inicioSol = chrono::high_resolution_clock::now();

    resolverDFS(1, 1);

    auto finSol = chrono::high_resolution_clock::now();
    auto tiempoSol = chrono::duration_cast<chrono::milliseconds>(finSol - inicioSol).count();

    cout << "Tiempo de resolución: " << tiempoSol << " ms\n";


    imprimirTablero();

    return 0;
}
