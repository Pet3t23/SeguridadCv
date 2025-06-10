#pragma once
#include "Prerequisites.h"

/*
 * Esta clase te ayuda a convertir texto en binario y binario en texto.
 * Por ejemplo, puedes convertir la palabra "Hola" en ceros y unos,
 * y luego volverla a convertir a texto normal.
 */
class AsciiBinary {
public:
    // Constructor (no hace nada especial, solo se necesita para crear el objeto)
    AsciiBinary() = default;

    // Destructor (tampoco hace nada especial en este caso)
    ~AsciiBinary() = default;

    /*
     * Convierte un solo carácter (como 'A') a binario.
     * Ejemplo: 'A' -> "01000001"
     */
    std::string bitset(char c) {
        std::string result(8, '0');
        int value = static_cast<unsigned char>(c);
        for (int i = 7; i >= 0; --i) {
            result[i] = (value % 2) + '0'; // Si es 1 o 0, lo convertimos a carácter
            value /= 2;
        }
        return result;
    }

    /*
     * Convierte una palabra o frase a binario.
     * Ejemplo: "Hi" -> "01001000 01101001"
     */
    std::string stringToBinary(const std::string& input) {
        std::ostringstream oss;
        for (char c : input) {
            oss << bitset(c) << ' ';
        }

        std::string output = oss.str();
        if (!output.empty()) {
            output.pop_back(); // Quitamos el último espacio
        }

        return output;
    }

    /*
     * Convierte 8 bits (como "01000001") a un solo carácter.
     * Ejemplo: "01000001" -> 'A'
     */
    char binaryToChar(const std::string& binary) {
        int value = 0;
        for (char bit : binary) {
            value = (value << 1) + (bit - '0'); // Multiplica por 2 y suma el bit
        }
        return static_cast<char>(value);
    }

    /*
     * Convierte una frase en binario a texto normal.
     * Ejemplo: "01001000 01101001" -> "Hi"
     */
    std::string binaryToString(const std::string& binaryInput) {
        std::istringstream iss(binaryInput);
        std::string result;
        std::string binary;

        while (iss >> binary) {
            result += binaryToChar(binary);
        }

        return result;
    }

private:
    // No hay variables privadas, solo funciones
};
