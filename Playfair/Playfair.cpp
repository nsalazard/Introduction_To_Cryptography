#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cctype>

using namespace std;

vector<vector<char>> generateKey(const string& key) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string keyString = key;
    keyString.erase(remove(keyString.begin(), keyString.end(), 'J'), keyString.end()); // Remove 'J'
    keyString += alphabet;

    // remove duplicates
    string finalKey;
    for (char c : keyString) {
        if (finalKey.find(toupper(c)) == string::npos) {
            finalKey += toupper(c);
        }
    }

    // Matrix 5x5
    vector<vector<char>> keySquare(5, vector<char>(5));
    int index = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            keySquare[i][j] = finalKey[index++];
        }
    }
    return keySquare;
}

pair<int, int> findTheLetter(char ch, const vector<vector<char>>& keySquare) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (keySquare[row][col] == ch) {
                return {row, col};
            }
        }
    }
    return {-1, -1}; 
}

vector<string> prepareText(const string& text, bool encrypt) {
    string filteredText;
    for (char ch : text) {
        if (isalpha(ch)) { // Solo letras
            filteredText += toupper(ch == 'J' ? 'I' : ch); 
        }
    }

    vector<string> digraphs;
    for (size_t i = 0; i < filteredText.length(); i += 2) {
        char first = filteredText[i];
        char second = (i + 1 < filteredText.length() && filteredText[i] != filteredText[i + 1]) ? filteredText[i + 1] : 'X';
        digraphs.push_back({first, second});
        if (first == second) i--; 
    }
    return digraphs;
}

string Cipher(const string& text, const string& key, int mode) {
    vector<vector<char>> keySquare = generateKey(key);
    vector<string> digraphs = prepareText(text, mode == 1);
    string result;

    for (const string& digraph : digraphs) {
        auto [row1, col1] = findTheLetter(digraph[0], keySquare);
        auto [row2, col2] = findTheLetter(digraph[1], keySquare);

        // Cifrar

        if (mode == 1) {

            if (row1 == row2) {
                result += keySquare[row1][(col1 + 1) % 5];
                result += keySquare[row2][(col2 + 1) % 5];
            }
            // Misma columna
            else if (col1 == col2) {
                result += keySquare[(row1 + 1) % 5][col1];
                result += keySquare[(row2 + 1) % 5][col2];
            }
            // Rectangulo
            else {
                result += keySquare[row1][col2];
                result += keySquare[row2][col1];
            }
        } 

        // Decifar
        else {
            // Same row
            if (row1 == row2) {
                result += keySquare[row1][(col1 + 4) % 5];
                result += keySquare[row2][(col2 + 4) % 5];
            }
            // Same column
            else if (col1 == col2) {
                result += keySquare[(row1 + 4) % 5][col1];
                result += keySquare[(row2 + 4) % 5][col2];
            }
            // Rectangle swap
            else {
                result += keySquare[row1][col2];
                result += keySquare[row2][col1];
            }
        }
    }

    return result;
}

void CapitalLetters(std::string &message) {
    for (char &c : message) {
        c = std::toupper(c);
    }
}

void RemoveSpaces(std::string &str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

int main() {
    string message, key;
    int mode;

    cout << "Ingresa un mensaje: ";
    getline(cin, message);
    cout << "Ingresa la clave: ";
    getline(cin, key);
    cout << "Ingresa 1 para cifrar 0 para descifrar : ";
    cin >> mode;

    // Para evitar errores se deja en mayuscula
    CapitalLetters(message);
    CapitalLetters(key);
    RemoveSpaces(key);

    string result = Cipher(message, key, mode);

    if (mode == 1) {
        cout << "Mensaje encriptado: " << result << endl;
    } else {
        cout << "Mensaje descifrado: " << result << endl;
    }

    return 0;
}
