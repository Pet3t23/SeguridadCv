#include "Prerequisites.h"
#include "DES.h"

int main() {
    // Clave de 64 bits en binario para usar en el cifrado DES
    std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

    // Frase que vamos a cifrar con DES
    std::string phrase = "Estamos en una simulacion, wake up, wake up";

    // Aseguramos que la frase tenga un número de caracteres múltiplo de 8 (DES trabaja con bloques de 64 bits = 8 bytes)
    while (phrase.size() % 8 != 0) {
        phrase += '\0'; // Agregamos caracteres nulos al final si hace falta
    }

    // Aquí vamos a guardar los bloques cifrados
    std::vector<std::bitset<64>> cipherBlocks;

    std::cout << "Texto original: " << phrase << std::endl;
    std::cout << "Cifrado en hexadecimal:\n";

    // Creamos un objeto DES con la clave definida
    DES des(key);

    // Recorremos la frase por bloques de 8 caracteres
    for (size_t i = 0; i < phrase.size(); i += 8) {
        std::string block = phrase.substr(i, 8);               // Tomamos un bloque de 8 caracteres
        auto blockBits = des.stringToBitset64(block);          // Lo convertimos a bits
        auto encrypted = des.encode(blockBits);                // Lo ciframos usando DES
        cipherBlocks.push_back(encrypted);                     // Guardamos el bloque cifrado

        // Mostramos el bloque cifrado en formato hexadecimal
        std::cout << std::hex << std::uppercase << std::setw(16) << std::setfill('0')
            << encrypted.to_ullong() << " ";
    }

    std::cout << std::endl;

    // Descifrado de los bloques
    std::string output;
    for (const auto& block : cipherBlocks) {
        auto decrypted = des.decode(block);                     // Desciframos el bloque
        output += des.bitset64ToString(decrypted);              // Lo convertimos a texto
    }

    std::cout << "Texto descifrado: " << output << std::endl;

    return 0;
}
