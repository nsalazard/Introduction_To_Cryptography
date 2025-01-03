#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <cctype>

class CifradoHomofonico {
private:
    int m, n;
    std::unordered_map<char, std::vector<int>> layout;

public:
    CifradoHomofonico(int m, int n, const std::unordered_map<char, std::vector<int>>& layout_predefinido = {})
        : m(m), n(n) {
        if (!layout_predefinido.empty()) {
            layout = layout_predefinido;
        } else {
            std::cout << "No se proporcionó un layout predefinido.\n";
        }
    }

    std::vector<int> cifrar(const std::string& mensaje) {
        std::vector<int> mensaje_cifrado;
        for (char letra : mensaje) {
            if (std::isalpha(letra)) {
                char letra_mayus = std::toupper(letra);
                if (layout.find(letra_mayus) != layout.end()) {
                    const auto& numeros = layout[letra_mayus];
                    int numero = numeros[std::rand() % numeros.size()];
                    mensaje_cifrado.push_back(numero);
                }
            } else if (letra == ' ') {
                mensaje_cifrado.push_back(0); 
            }
        }
        return mensaje_cifrado;
    }

    std::string decifrar(const std::vector<int>& mensaje_cifrado) {
        std::unordered_map<int, char> inverso_layout;
        for (const auto& [letra, numeros] : layout) {
            for (int numero : numeros) {
                inverso_layout[numero] = letra;
            }
        }
        std::string mensaje_descifrado;
        for (int numero : mensaje_cifrado) {
            if (numero == 0) {
                mensaje_descifrado += ' ';
            } else if (inverso_layout.find(numero) != inverso_layout.end()) {
                mensaje_descifrado += inverso_layout[numero];
            } else {
                mensaje_descifrado += '?';
            }
        }
        return mensaje_descifrado;
    }

    void imprimirLayout() {
        for (const auto& [letra, numeros] : layout) {
            std::cout << letra << ": ";
            for (int numero : numeros) {
                std::cout << numero << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    // Layout visto en clase
    std::unordered_map<char, std::vector<int>> layout_predefinido = {
        {'A', {9, 12, 33, 47, 53, 67, 78, 92}},
        {'B', {48, 81}},
        {'C', {13, 41, 62}},
        {'D', {1, 3, 45, 79}},
        {'E', {14, 16, 24, 44, 46, 55, 57, 64, 74, 82, 87, 98}},
        {'F', {10, 31}},
        {'G', {6, 25}},
        {'H', {23, 39, 50, 56, 65, 68}},
        {'I', {32, 70, 73, 83, 88, 93 }},
        {'J', {15}},
        {'K', {4}},
        {'L', {26, 37, 51, 14}},
        {'M', {22, 27}},
        {'N', {18, 58, 59, 66, 71, 91}},
        {'O', {0, 5, 7, 54, 72, 90, 99}},
        {'P', {38, 95}},
        {'Q', {94}},
        {'R', {29, 35, 40, 42, 77, 80}},
        {'S', {11, 19, 36, 76, 86, 96}},
        {'T', {17, 20, 30, 43, 49, 69, 75, 85, 97}},
        {'U', {8, 61, 63}},
        {'V', {34}},
        {'W', {60, 89}},
        {'X', {28}},
        {'Y', {21, 52}},
        {'Z', {2}}

    };

    CifradoHomofonico cifrador(100, 26, layout_predefinido);


    std::string mensaje_claro;
    std::cout << "\nIngrese el mensaje a cifrar: ";
    std::getline(std::cin, mensaje_claro);
    
    auto mensaje_cifrado = cifrador.cifrar(mensaje_claro);

    std::cout << "\nMensaje cifrado: ";
    for (int numero : mensaje_cifrado) {
        std::cout << numero << " ";
    }
    std::cout << std::endl;

    auto mensaje_descifrado = cifrador.decifrar(mensaje_cifrado);
    std::cout << "\nMensaje descifrado: " << mensaje_descifrado << std::endl;

    return 0;
}
