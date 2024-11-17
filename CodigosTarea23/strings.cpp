#include <bits/stdc++.h>

using namespace std;

int main(){
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int size;
    cout << "De que tamaño quieres hacer las pruebas?\n Tamaño: ";
    cin >> size;
    int amount;
    cout << "Cuantas pruebas quieres hacer?\n Pruebas: ";
    cin >> amount;
    srand(time(0));

    ofstream file("pruebas.txt");
    for (int i = 0; i < amount; i++){
        string S1, S2;
        
        for(int j = 0; j < size; j++){
            int num = rand() % 26;
            S1.push_back(alphabet[num]);
        }
        for(int k = 0; k < size; k++){
            int num = rand() % 26;
            S2.push_back(alphabet[num]);
        }
        cout << "Caso " << i + 1 << " las cadenas son S1: " << S1 << " y S2: " << S2 << endl;
        file << "Caso " << i + 1 << ": S1: " << S1 << " S2: " << S2 << endl; 
    }
    file.close();
    return 0;
}