#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


int flag = 0; // Si flag es 0 la llave es solo letras y numeros

//Cifrar el mensaje
std::string encrypt(const std::string& plaintext, const std::string& key) {
    if (plaintext.length() != key.length()) {
        throw std::invalid_argument("La longitud de la llave debe ser igual a la longitud del mensaje");
    }

    std::string ciphertext;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        // Realiza XOR entre cada carácter del mensaje y la llave
        ciphertext += plaintext[i] ^ key[i];
    }
    return ciphertext;
}

//Descifrar el mensaje
std::string decrypt(const std::string& ciphertext, const std::string& key) {
    if (ciphertext.length() != key.length()) {
        throw std::invalid_argument("La longitud de la llave debe ser igual a la longitud del mensaje cifrado");
    }

    std::string decryptedMessage;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        // Realiza XOR entre cada carácter del mensaje cifrado y la llave
        decryptedMessage += ciphertext[i] ^ key[i];
    }
    return decryptedMessage;
}

// Genera la llave aleatoria (Pueden ser solo letras/numeros o un carácter aleatorio (byte) entre 0 y 255)
std::string generateRandomKey(size_t length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string key;
    if (flag == 0){
    for (size_t i = 0; i < length; ++i) {
        key += characters[rand() % characters.length()]; // Se escojen caracteres aleatorios de characters
    }
    }
    else{
    for (size_t i = 0; i < length; ++i) {
        key += rand() % 256; 
    }
    }
    return key;
}


// Imprime una cadena en formato hexadecimal
void printHex(const std::string& str) {
    for (unsigned char c : str) {
        std::cout << std::hex << (int)c << " ";
    }
    std::cout << std::dec << '\n'; // Regresa a decimal para otros cout
}

int main() {
    std::srand(std::time(0));

    std::string plaintext;
    std::cout << "Ingrese el mensaje en texto claro: ";
    std::getline(std::cin, plaintext);

    std::string key = generateRandomKey(plaintext.length());

    // Cifrado
    std::string ciphertext = encrypt(plaintext, key);
    
    std::cout << "Llave (texto): " << key << '\n';
    std::cout << "Llave (hex): ";
    printHex(key);

    std::cout << "Mensaje cifrado: ";
    printHex(ciphertext);

    // Descifrado
    std::string decryptedMessage = decrypt(ciphertext, key);
    std::cout << "Mensaje descifrado: " << decryptedMessage << '\n';

    return 0;
}
