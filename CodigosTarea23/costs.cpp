#include <bits/stdc++.h>

using namespace std;

void crearmatrix(int choice, string nombre){
    //si es constante se pedirá un numero
    if (choice == 1){
        cout << "Que costo tendra el archivo " << nombre << "?\n";
        int num;
        cin >> num;
        ofstream file(nombre);
        vector<vector<int>> matrix(26,vector<int>(26,num));
        for (int i = 0; i < 26; ++i) {
        matrix[i][i] = 0;
        }
        for (const auto& fila : matrix) {
            for (const auto& elemento : fila) {
                file << elemento << " ";
            }
            file << "\n";
        }
        file.close();
    }
    else if (choice == 2){
        int lim1, lim2;
        cout << "Ingresar rango de valores para el archivo " << nombre << endl;
        cout << "Limite inferior: ";
        cin >> lim1;
        cout << "Limite superior: ";
        cin >> lim2;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(lim1,lim2);
        ofstream file(nombre);
        vector<int> row;
        for(int i = 0; i < 26; i++){
            for (int j = 0; j < 26; j++){
                if (i != j){
                    file << distr(gen) << " ";
                } else {
                    file << 0 << " "; 
                }
            }
            file << "\n";
        }
        file.close();
    }
}
void crearRow(int choice, string nombre){
    if (choice == 1){
        cout << "Que costo tendra el archivo " << nombre << "?\n";
        int num;
        cin >> num;
        ofstream file(nombre);
        vector<int> row(26,num);
        for (const auto& valor : row) {
            file << valor << " ";
        }
        file.close();
    }
    else if (choice == 2){
        int lim1, lim2;
        cout << "Ingresar rango de valores para el archivo " << nombre << endl;
        cout << "Limite inferior: ";
        cin >> lim1;
        cout << "Limite superior: ";
        cin >> lim2;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(lim1,lim2);
        ofstream file(nombre);
        vector<int> row;
        for(int i = 0; i < 26; i++){
            file << distr(gen) << " "; 
        }
        file.close();
    }
}

int main(){
    //Lo que hace este código es generar los 4 archivos de texto que contienen los costos.
    //Primero se decide lo siguiente para cada archivo: Será aleatorio? O se escoge el costo?
    int choice = - 1;
    while(choice != 1 && choice != 2){
        cout << "¿Como se armaran los costos?\n";
        cout << "1: Constante, 2: Aleatorio\n";
        cout << "Decision: ";
        cin >> choice;
        if (choice != 1 && choice != 2){
            cout << "Decision no valida.\n";
        }
    }
    if (choice == 1){
        cout << "Los archivos se armaran con costos constantes\n";
        crearmatrix(choice,"cost_replace.txt");
        crearmatrix(choice,"cost_transpose.txt");
        crearRow(choice,"cost_insert.txt");
        crearRow(choice,"cost_delete.txt");
    }
    if (choice == 2){
        cout << "Los archivos se armaran con costos aleatorios\n";
        crearmatrix(choice,"cost_replace.txt");
        crearmatrix(choice,"cost_transpose.txt");
        crearRow(choice,"cost_insert.txt");
        crearRow(choice,"cost_delete.txt");
    }
}