#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string UpperCase(const string& text);
string encryption(const string& message, const string& key, int t);
string decryption(const string& encrypted, const string& key, int t);

/*
Para usar el cifrado de Vigenere no necesitamos construir la matriz, sino que podemos usar la formula
Ci = (Pi + Ki) mod 26
Pi = (Ci - Ki) mod 26
Donde C es el mensaje cifrado, P el mensaje inicial y K la llave.
*/

int main() {
    string key, message;
    int t, Flag;

    cout << "Selecciona una opcion:\n";
    cout << "0 - Cifrar un mensaje\n";
    cout << "1 - Descifrar un mensaje\n";
    cin >> Flag;
    cin.ignore(); 

    cout << "Ingresa la llave (k): ";
    getline(cin, key);

    if (Flag == 0) { // Cifrar
        cout << "Ingresa el mensaje a cifrar: ";
        getline(cin, message);

        cout << "Ingresa el valor de t: ";
        cin >> t;

        string encrypted = encryption(message, key, t);
        cout << "Mensaje cifrado: " << encrypted << endl;

    } else if (Flag == 1) { // Descifrar
        cout << "Ingresa el mensaje cifrado: ";
        getline(cin, message);

        cout << "Ingresa el valor de t: ";
        cin >> t;

        string decrypted = decryption(message, key, t);
        cout << "Mensaje descifrado: " << decrypted << endl;

    } else {
        cout << "Opción no válida." << endl;
    }

    return 0;
}

string UpperCase(const string& text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    return result;
}

string encryption(const string& message, const string& key, int t) {
    string newMessage = UpperCase(message);
    string newKey = UpperCase(key);
    string encrypted;

    int keyIndex = 0;
    for (char c : newMessage) {
        int m = c - 'A';
        int k = newKey[keyIndex % newKey.size()] - 'A';
        encrypted += (m + k) % 26 + 'A';
        keyIndex++;
    }

    if (t > 0) {
        string withSpaces;
        for (size_t i = 0; i < encrypted.size(); ++i) {
            if (i > 0 && i % t == 0) {
                withSpaces += ' ';
            }
            withSpaces += encrypted[i];
        }
        return withSpaces;
    }

    return encrypted;
}

string decryption(const string& encrypted, const string& key, int t) {
    string newMessage = UpperCase(encrypted);
    string newKey = UpperCase(key);
    string decrypted;

    int keyIndex = 0;
    for (char c : newMessage) {
        int e = c - 'A';
        int k = newKey[keyIndex % newKey.size()] - 'A';
        decrypted += (e - k + 26) % 26 + 'A';
        keyIndex++;
    }

    if (t > 0) {
        string withSpaces;
        for (size_t i = 0; i < decrypted.size(); ++i) {
            if (i > 0 && i % t == 0) {
                withSpaces += ' ';
            }
            withSpaces +=decrypted[i];
        }
        return withSpaces;
    }

    return decrypted;
}
