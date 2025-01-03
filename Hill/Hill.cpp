#include <iostream>
#include <tuple>
#include <vector>
#include <numeric> 
#include <stdexcept>

const int m = 26; // mod

std::tuple<int, int, int> extendedGCD(int a, int b);
int modularInverse(int a, int m);
std::vector<std::vector<int>> insertMatrix();
int determinant2x2(const std::vector<std::vector<int>>& matrix);
std::vector<std::vector<int>> adjugate(const std::vector<std::vector<int>>& matrix); 
std::vector<int> messageToNumbers(const std::string& message);
std::string numbersToMessage(const std::vector<int>& numbers);
std::string encryption(const std::vector<std::vector<int>>& matrix, const std::string message); 
std::string decryption(const std::vector<std::vector<int>>& matrix, const std::string message);

int main() {

    std::vector<std::vector<int>> matrix = insertMatrix();
    std::cin.ignore(); 
    std::string message;
    std::cout << "Ingrese el mensaje: ";
    std::getline(std::cin, message);
    int flag = 0;
    std::cout << "Ingrese 0 si desea cifrar o 1 si desea decifrar: ";
    std::cin >> flag;

    if(flag){
        std::string decryptedMessage = decryption(matrix, message);
        std::cout << "Mensaje decifrado: " << decryptedMessage << "\n";

    }
    else{std::string encryptedMessage = encryption(matrix, message);
    std::cout << "Mensaje cifrado: " << encryptedMessage << "\n";}
    
    return 0;
}

std::tuple<int, int, int> extendedGCD(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};  // Caso base: gcd(a, 0) = a, x = 1, y = 0
    }
    auto [gcd, x1, y1] = extendedGCD(b, a % b);
    int x = y1;
    int y = x1 - (a / b) * y1;
    return {gcd, x, y};
}

int modularInverse(int a, int m) {
    auto [gcd, x, y] = extendedGCD(a, m);
    if (gcd != 1) {
        throw std::invalid_argument("El det de la matriz y m no son coprimos.");
    }
    // x debe ser positivo
    return (x % m + m) % m;
}

std::vector<std::vector<int>> insertMatrix() {
    std::vector<std::vector<int>> matrix(2, std::vector<int>(2));
    std::cout << "Ingrese los 4 numeros de la matriz 2x2, fila por fila : " ;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    return matrix;
}

int determinant2x2(const std::vector<std::vector<int>>& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

std::vector<std::vector<int>> adjugate(const std::vector<std::vector<int>>& matrix) {
    return {
        { matrix[1][1], -matrix[0][1] },
        { -matrix[1][0], matrix[0][0] }
    };
}

std::vector<int> messageToNumbers(const std::string& message) {
    std::vector<int> numbers;
    for (char ch : message) {
        if (std::isalpha(ch)) {
            numbers.push_back(std::toupper(ch) - 'A');
        }
    }
    if (numbers.size() % 2 != 0) {
        numbers.push_back(23); //'X'
    }
    return numbers;
}

std::string numbersToMessage(const std::vector<int>& numbers) {
    std::string message;
    for (int num : numbers) {
        message += static_cast<char>('A' + (num % 26)); // Modulo 26 ensures valid letters
    }
    return message;
}

std::string encryption(const std::vector<std::vector<int>>& matrix, const std::string message) {
    
    std::vector<int> numbers = messageToNumbers(message);

    if (matrix.size() != 2 || matrix[0].size() != 2) {
        throw std::invalid_argument("La matriz debe ser 2x2");
    }

    std::vector<int> encryptedNumbers;

    for (size_t i = 0; i < numbers.size(); i += 2) {
        int x = numbers[i];
        int y = numbers[i + 1];

        int newX = (matrix[0][0] * x + matrix[1][0] * y) % 26;
        int newY = (matrix[0][1] * x + matrix[1][1] * y) % 26;

        encryptedNumbers.push_back(newX);
        encryptedNumbers.push_back(newY);
    }
    return numbersToMessage(encryptedNumbers);
}

std::string decryption(const std::vector<std::vector<int>>& matrix, const std::string message) {
    
    std::vector<int> numbers = messageToNumbers(message);
    std::vector<std::vector<int>> adj = adjugate(matrix);

    if (matrix.size() != 2 || matrix[0].size() != 2) {
        throw std::invalid_argument("La matriz debe ser 2x2.");
    }

    int det = determinant2x2(matrix);
    int inverse = modularInverse(det, m);

    std::vector<int> decryptedNumbers;

    for (size_t i = 0; i < numbers.size(); i += 2) {
        int x = numbers[i];
        int y = numbers[i + 1];

        int newX = (adj[0][0] * x * inverse + adj[1][0] * y * inverse) % m;
        int newY = (adj[0][1] * x * inverse + adj[1][1] * y * inverse) % m;

        decryptedNumbers.push_back(newX);
        decryptedNumbers.push_back(newY);
    }
    return numbersToMessage(decryptedNumbers);
}
