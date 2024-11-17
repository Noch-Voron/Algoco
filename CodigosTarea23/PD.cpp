#include <bits/stdc++.h>

using namespace std;

/*
Como se armó este subproblema y sus respuestas?
Primero definimos que es lo que busca el problema
En este caso es Obtener la mayoría de delegados con el minimo de votos adicionales
Esto es una optimización para Minimizar los votos adicionales
Qué recursos podemos controlar? Delegados en cada estado y votos adicionales necesarios
Cuál es el estado de cada subproblema?
dp[i][j]: es el minimo numero de votos adicionales necesarios para asegurar j delegados en los primeros i estados
Cómo cambiamos de estado?
podemos no asegurar el estado, ahí tendríamos los votos adicionales para el siguiente estado = 0 y se mantienen los delegados actuales (copiar para abajo el valor actual)
Condicion inicial y resultado final?
Al inicio tenemos dp[0][0] = 0, esto es que, no podemos tener votos adicionales en el estado -1 porque no existe, por lo que no hay votos adicionales

Primero definimos lo que busca el problema completo
En este caso es obtener el costo minimo para llegar de un string a otro
Esta es una optimización para minimizar el costo total de todas las operaciones
Qué recursos podemos controlar? Qué es lo que decidimos?
En este problema, nosotros decidimos si utilizamos una operación o no,
Qué variables describen el estado en cada momento?
La única forma de hacer una tabla, es con ambos strings dp[string1+1][string2+1]
Cuál es la forma en que se representan los subproblemas?
cada celda debería indicar el costo minimo acumulado para transformar los primeros i caracteres del string 1 a los primeros j elementos del string 2
Cómo organizamos estos subproblemas en términos de variables que cambian en el tiempo o el espacio?
Qué decisiones necesitamos tomar en cada subproblema?
Qué acciones se deben tomar para ir de un estado a otro?
Cómo se combinan los subproblemas para obtener una solución general?
*/

//esta si que la voy a sufrir
//primero tengamos las funciones que llaman a los costos de las operaciones
//cada una leerá su correspondiente archivo de texto y guardará cada operación en un mapa

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


void imprimir_operaciones(string& S1, string& S2, vector<vector<int>>& dp) {
    int i = S1.size();
    int j = S2.size();
    int costoTotal = 0;
    //cout << "size of string1 " << S1 << " is " << i << " size of string2 " << S2 << " is " << j << endl;
    while (i > 0 || j > 0) {
        //cout << "Tamanios, i: " << i << "; j: " << j << endl;
        //cout << dp[i][j] << " valor de lo de arriba :)\n";
        if (i > 0 && j > 0 && S1[i-1] == S2[j-1]) {
            // Si no se necesita ninguna operación (no hay cambio)
            //cout << S1[i-1] << " " << S2[j-1] << endl;
            //cout << "not needed" << endl;
            --i;
            --j;
        } else {
            int delete_cost = (i >= 1) ? dp[i-1][j] + costo_delete(S1[i-1]) : INT_MAX;
            int insert_cost = (j >= 1) ? dp[i][j-1] + costo_insert(S2[j-1]): INT_MAX;
            int replace_cost = (i >= 1 && j >= 1) ? dp[i-1][j-1] + costo_replace(S1[i-1], S2[j-1]) : INT_MAX;
            int transpose_cost = (i > 1 && j > 1 && S1[i-1] == S2[j-2] && S1[i-2] == S2[j-1]) ? dp[i-2][j-2] + costo_transpose(S1[i-2], S1[i-1]) : INT_MAX;
            //cout << "del, ins, repl, transp: " << delete_cost << " " << insert_cost << " " << replace_cost << " " << transpose_cost << endl;
            if (dp[i][j] == delete_cost) {
                cout << "Eliminar '" << S1[i-1] << "' de la cadena base." << endl;
                cout << "Costo: " << costo_delete(S1[i-1]) << endl;
                costoTotal += costo_delete(S1[i-1]);
                --i;
            } else if (dp[i][j] == insert_cost) {
                cout << "Insertar '" << S2[j-1] << "' en la cadena base." << endl;
                cout << "Costo: " << costo_insert(S2[j-1]) << endl;
                costoTotal += costo_insert(S2[j-1]);
                --j;
            } else if (dp[i][j] == replace_cost) {
                cout << "Sustituir '" << S1[i-1] << "' por '" << S2[j-1] << "'." << endl;
                cout << "Costo: " << costo_replace(S1[i-1], S2[j-1]) << endl;
                costoTotal += costo_replace(S1[i-1], S2[j-1]);
                --i;
                --j;
            } else if (dp[i][j] == transpose_cost) {
                cout << "Transponer '" << S1[i-2] << "' y '" << S1[i-1] << "'." << endl;
                cout << "Costo: " << costo_transpose(S1[i-1], S2[j-1]) << endl;
                costoTotal += costo_transpose(S1[i-2], S1[i-1]);
                i -= 2;
                j -= 2;
            }
        }
    }
    cout << "El costo minimo encontrado es: " << costoTotal << endl;
}


void printTable(const vector<vector<int>> &cache){
    int r = 0;
    for(auto row : cache){
        int c = 0;
        for (auto cell : row){
            cout << cell << " ";
            c++; // XD
        }
        cout << endl;
        r++;
    }
}


//https://stackoverflow.com/questions/73021792/the-damerau-levenshtein-distance-in-c
//                 tomados como referencia para ahorrar memoria
int dist_damlev(string& S1, string& S2){
    int n = S1.size();
    int m = S2.size();
    //creamos la tabla 
    vector<vector<int>> dp(n + 1,vector<int>(m + 1,0));

    //aquí inicializamos el costo para eliminar cada caracter del string 1
    for (int i = 1; i <= n; ++i) {
        //cout << "Costo para eliminar el caracter "<< S1[i-1] <<  " es " << costo_delete(S1[i - 1]) << endl; 
        dp[i][0] = dp[i - 1][0] + costo_delete(S1[i - 1]);
    }
    //y acá se inicializa el costo para insertar todos los elementos del string 2
    for (int j = 1; j <= m; ++j) {
        //cout << "Costo para insertar el caracter "<< S2[j-1] <<  " es " << costo_insert(S2[j - 1]) << endl; 
        dp[0][j] = dp[0][j - 1] + costo_insert(S2[j - 1]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int costSubstitute = (S1[i - 1] == S2[j - 1]) ? 0 : costo_replace(S1[i - 1], S2[j - 1]);
            //calculamos el costo de cada una de las operaciones y guardamos el minimo
            dp[i][j] = min({
                dp[i - 1][j] + costo_delete(S1[i - 1]),     // Costo para eliminar
                dp[i][j - 1] + costo_insert(S2[j - 1]),     // Costo para insertar
                dp[i - 1][j - 1] + costSubstitute             // Costo para sustituir
            });

            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + costo_transpose(S1[i - 2], S1[i - 1])); // Costo para transposición
            }
            //cout << "Costo encontrado minimo para " << S1[i - 1] << " y " << S2[j - 1] << " es: " << dp[i][j] << endl;
            //este print no fue probado
        }
    }
    //printTable(dp); quitar // si se quiere ver la tabla
    //imprimir_operaciones(S1, S2, dp); //si se quieren ver las operaciones quitar comentario
    return dp[n][m];
    
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
    // UNA VEZ SE HAYA CREADO ESTE ARCHIVO CAMBIAR EL NOMBRE ANTES DE HACER OTRAS PRUEBAS O LOS RESULTADOS SE PERDERÁN
    ofstream write("resultado.txt");
    for (const auto& pair : pairs) {
        S1 = pair.first;
        S2 = pair.second;
        auto start = chrono::high_resolution_clock::now();
        int resultado = dist_damlev(S1, S2);
        auto elapsed = chrono::high_resolution_clock::now() - start;

        long long time = chrono::duration_cast<chrono::milliseconds>(
        elapsed).count();

        write << "Para la cadena base S1: " << S1 << " y la cadena objetivo S2: " << S2 <<". El Tiempo de ejecución es: " << time << " ms. Costo: " << resultado << endl;
    }
    write.close();
    return 0;
}

