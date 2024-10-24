#include <bits/stdc++.h>

using namespace std;

int cs,ci,cd,ct;
//holas espero que esto no sea tan terrible :DDD

//ESTAS SERÁN LOS COSTOS DE LAS OPERACIONES PARA PODER REVISAR OTROS CASOS CAMBIAR EL CÓDIGO PARA AGREGAR LOS COSTOS MANUALMENTE
// Costo de sustitución: cambiar el carácter 'a' por 'b'
int costo_sub(char a, char b) {
    return (a != b) ? cs : 0;  // Por ejemplo, costo 2 si son diferentes, 0 si son iguales
}

// Costo de inserción: insertar el carácter 'b'
int costo_ins(char b) {
    return ci;  // Costo de inserción puede ser constante
}

// Costo de eliminación: eliminar el carácter 'a'
int costo_del(char a) {
    return cd;  // Costo de eliminación puede ser constante
}

// Costo de transposición: intercambiar los caracteres adyacentes 'a' y 'b'
int costo_trans(char a, char b) {
    return ct;  // Costo de transposición también constante, por ejemplo
}




// Función recursiva de fuerza bruta para la distancia de Damerau-Levenshtein
int damerau_levenshtein_brute(const string& S1, const string& S2, int i, int j) {
    // Caso base: si llegamos al final de una de las cadenas
    if (i == S1.length()) return (S2.length() - j) * costo_ins(' ');  // Insertar los caracteres restantes de S2
    if (j == S2.length()) return (S1.length() - i) * costo_del(' ');  // Eliminar los caracteres restantes de S1

    // Si los caracteres son iguales, no hacemos nada y avanzamos al siguiente par
    if (S1[i] == S2[j]) {
        return damerau_levenshtein_brute(S1, S2, i + 1, j + 1);
    }

    // Calcular los costos de las tres operaciones básicas
    int costo_sustitucion = costo_sub(S1[i], S2[j]) + damerau_levenshtein_brute(S1, S2, i + 1, j + 1);
    int costo_insercion = costo_ins(S2[j]) + damerau_levenshtein_brute(S1, S2, i, j + 1);
    int costo_eliminacion = costo_del(S1[i]) + damerau_levenshtein_brute(S1, S2, i + 1, j);

    // Calcular el costo de la transposición, si es posible
    int costo_transposicion = INT_MAX;  // Valor por defecto para cuando no hay transposición posible
    if (i + 1 < S1.length() && j + 1 < S2.length() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        costo_transposicion = costo_trans(S1[i], S1[i + 1]) + damerau_levenshtein_brute(S1, S2, i + 2, j + 2);
    }

    // Devuelve el mínimo de todas las operaciones posibles
    return min({costo_sustitucion, costo_insercion, costo_eliminacion, costo_transposicion});
}

int main() {
    cout << "Definamos los costos primero...\n";
    cout << "¿Cuanto deberia costar la insercion? Costo: ";
    cin >> ci;
    cout << "¿Cuanto deberia costar la substitucion? Costo: ";
    cin >> cs;
    cout << "¿Cuanto deberia costar la eliminacion? Costo: ";
    cin >> cd;
    cout << "¿Cuanto deberia costar la transposicion? Costo: ";
    cin >> ct;
    // Ejemplo de prueba
    //costos: sub = 2 o 0, ins = 1, eli = 1, trans = 1;
    string S1;
    string S2;
    int flag;
    while (true){
        cout << "Dame el string a transformar: ";
        cin >> S1;
        cout << "Dame el string objetivo: ";
        cin >> S2;
        //llegar de S1 a S2
        int resultado = damerau_levenshtein_brute(S1, S2, 0, 0);
        cout << "La distancia minima de edicion es: " << resultado << endl;
        cout << "Deseas seguir testeando? (1 = yes, 0 = no): ";
        cin >> flag;
        if (flag != 1){
            break;
        }
    }

    return 0;
}
