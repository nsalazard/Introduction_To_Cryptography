#include <iostream>
#include <string>
using namespace std;

string encrypt(const string &message, int k);
string decrypt(const string &encrypted_message, int k);
string encryptPrint(const string &encrypted_message, int rotation);


int main() {
    string message;
    int k, M;

    cout << "Ingresa el mensaje a encriptar: ";
    getline(cin, message);

    cout << "Ingresa la clave (k: un numero): ";
    cin >> k;

    cout << "Ingresa el tamano de los Strings(M: un numero): ";
    cin >> M;

    // El mensaje se deja en mayuscula
    for (char &charac : message) {
        charac = toupper(charac);
    }

    // Se encripta el mensaje
    string encrypted_message = encrypt(message, k);
    string output_encrypted_message = encryptPrint(encrypted_message, M);
    cout << "El mensaje a cifrar: " << output_encrypted_message << endl;

    // Se decripta el mensaje
    string decrypted_message = decrypt(encrypted_message, k);
    cout << "El mensaje decifrado: " << decrypted_message << endl;

    return 0;
}

string encrypt(const string &message, int k) {
    string encrypted_message = "";
    for (char charac : message) {
        if (isalpha(charac)) { 
            int shift = k % 26; 
            if (islower(charac)) {
                encrypted_message += char((charac - 'a' + shift) % 26 + 'a');
            } else {
                encrypted_message += char((charac - 'A' + shift) % 26 + 'A');
            }
        } 
    }
    return encrypted_message;
}

string decrypt(const string &encrypted_message, int k) {
    string decrypted_message = "";
    for (char charac : encrypted_message) {
        if (isalpha(charac)) {
            int shift = k % 26;
            if (islower(charac)) {
                decrypted_message += char((charac - 'a' - shift + 26) % 26 + 'a');
            } else {
                decrypted_message += char((charac - 'A' - shift + 26) % 26 + 'A');
            }
        } else {
            decrypted_message += charac; 
        }
    }
    return decrypted_message;
}

string encryptPrint(const string &encrypted_message, int rotation) {
    string result = "";
    for (size_t i = 0; i < encrypted_message.size(); ++i) {
        result += encrypted_message[i];
        if ((i + 1) % rotation == 0 && i != encrypted_message.size() - 1) {
            result += " ";
        }
    }
    return result;
}
