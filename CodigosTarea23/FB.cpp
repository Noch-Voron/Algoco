#include <bits/stdc++.h>

using namespace std;


//holas espero que esto no sea tan terrible :DDD

//ESTAS SERÁN LOS COSTOS DE LAS OPERACIONES PARA PODER REVISAR OTROS CASOS CAMBIAR LOS ARCHIVOS PARA CAMBIAR LOS COSTOS
// los mapas serán globales
//este es con llave de una letra pq solo insertamos una letra, o eliminamos una letra
map<char,int> insertMap, deleteMap;
//este tiene llave a un par de letras, esto porque estas operaciones usan 2.
map<pair<char,char>,int> replMap, transpMap;
string alphabet = "abcdefghijklmnopqrstuvwxyz";

void generateInsertMap(){
    ifstream file("cost_insert.txt");
    int value;
    for (char c : alphabet){
        if (file >> value) {
            insertMap[c] = value;
        }
    }
}
void generateDeleteMap(){
    ifstream file("cost_delete.txt");
    int value;
    for (char c : alphabet){
        if (file >> value) {
            deleteMap[c] = value;
        }
    }
}
void generateReplaceMap(){
    ifstream file("cost_replace.txt");
    int value;
    for (char c : alphabet){
        for(char d : alphabet){
            
            if (file >> value) {
                replMap[{c,d}] = value;
            }
        } 
    }
}
void generateTransposeMap(){
    ifstream file("cost_transpose.txt");
    int value;
    for (char c : alphabet){
        for(char d : alphabet){
            if (file >> value) {
                transpMap[{c,d}] = value;
            }
        } 
    }
}
// ok parte facil lista :D :| :(
// Para resolver el problema utilizando programación dinámica recordemos las preguntas que hay que hacerse


//Estas son las funciones que encuentran los costos de las operaciones
int costo_insert(char a){
    return insertMap[a];
}
int costo_delete(char a){
    return deleteMap[a];
}
int costo_replace(char a, char b){
    return replMap[{a,b}];
}
int costo_transpose(char a, char b){
    return transpMap[{a,b}];
}


// Esta funcion va a hacer recursividad avanzando a i o j, representando un avance en S1 o S2
int damerau_levenshtein_brute(const string& S1, const string& S2, int i, int j) {
    // Caso base: si llegamos al final de una de las cadenas
    if (i == S1.length() && j == S2.length()) {
        return 0;  // Ambos strings ya fueron recorridos, no falta hacer nada
    }
    else if (i == S1.length()) {
        // Solo manejar los caracteres faltantes de S2 con inserciones
        return costo_insert(S2[j]) + 
               damerau_levenshtein_brute(S1, S2, i, j + 1);
    }
    else if (j == S2.length()) {
        // Solo manejar los caracteres faltantes de S1 con eliminaciones
        return costo_delete(S1[i]) + 
               damerau_levenshtein_brute(S1, S2, i + 1, j);
    }

    // Si los caracteres son iguales, no hacemos nada y avanzamos al siguiente par
    else if (S1[i] == S2[j]) {
        return damerau_levenshtein_brute(S1, S2, i + 1, j + 1);
    }

    // Calcular los costos de las tres operaciones básicas
    int costo_sustitucion = costo_replace(S1[i], S2[j]) + damerau_levenshtein_brute(S1, S2, i + 1, j + 1);
    int costo_insercion = costo_insert(S2[j]) + damerau_levenshtein_brute(S1, S2, i, j + 1);
    int costo_eliminacion = costo_delete(S1[i]) + damerau_levenshtein_brute(S1, S2, i + 1, j);

    // Calcular el costo de la transposición, si es posible
    int costo_transposicion = INT_MAX;  // Valor por defecto para cuando no hay transposición posible
    if (i + 1 < S1.length() && j + 1 < S2.length() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        costo_transposicion = costo_transpose(S1[i], S1[i + 1]) + damerau_levenshtein_brute(S1, S2, i + 2, j + 2);//Se calcula el costo
    }

    // Devuelve el mínimo de todas las operaciones posibles
    // Esto lo que hace es de las 4 posibles elecciones, toma la menor
    // Representemos esto en un arbol casi completo como si de cada nodo salen entre 3 y 4 hijos, cada uno con el costo de sustitucion, insercion, eliminacion y transposicion
    // Cada nodo, incluyendo padres y hojas tienen un costo.
    // Para cada PADRE se obtiene su hijo (que debe ser hoja) de costo MENOR y se suma a su costo, es decir Padre + Hijo_Costo_Menor
    // Esto se hace desde las hojas.
    // Se sigue hasta llegar a la raíz, donde se habría acumulado el costo de las 3 o 4 opciones, se obtiene el de costo menor y se suma, obteniendo el resultado.
    return min({costo_sustitucion, costo_insercion, costo_eliminacion, costo_transposicion});
}

int main() {
    generateDeleteMap();
    generateInsertMap();
    generateTransposeMap();
    generateReplaceMap();

    string S1;
    string S2;

    vector<pair<string,string>> pairs;
    string flag;
    while (true) {
        string s1, s2;
        cout << "S1 (Enter para string vacio): ";
        getline(cin, s1);
        cout << "S2 (Enter para string vacio): ";
        getline(cin, s2);
        pairs.push_back({s1,s2});
        cout << "Insertar mas casos? (1: si, 0: no): ";
        getline(cin,flag);
        if(flag != "1"){
            break;
        }
    }

    ofstream write("resultado.txt");
    for (const auto& pair : pairs) {
        S1 = pair.first;
        S2 = pair.second;
        auto start = chrono::high_resolution_clock::now();
        int resultado = damerau_levenshtein_brute(S1, S2, 0, 0);
        auto elapsed = chrono::high_resolution_clock::now() - start;

        long long time = chrono::duration_cast<chrono::milliseconds>(
        elapsed).count();

        write << "Para la cadena base S1: " << S1 << " y la cadena objetivo S2: " << S2 <<". El Tiempo de ejecución es: " << time << " ms. Costo: " << resultado << endl;
    }
    write.close();
    return 0;
}
