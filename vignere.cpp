/*

 VIGNERE CIPHER C++ PROGRAM (OOP)
 AUTHOR :   ANUP KODLEKERE 
 INPUT  :   KeyVector, PlainText
 OUTPUT :   CipherText 
 
*/

#include <iostream>
#include <string>
#include <ctype.h>

class VignereCipher {
    
    std::string key;
    
    public:
    
    VignereCipher(std::string, std::string);
    
    std::string chars = "abcdefghijklmnopqrstuvwxyz";
    std::string inputString;
    std::string plaintext;
    std::string ciphertext;
    
    int findIndex(char);
    void removeSpaces();
    void Encrypt(std::string);
    
};

// Constructor that initializes the key and the inputString 
VignereCipher :: VignereCipher(std::string key, std::string inputString) {
    for(int i = 0; i < inputString.length(); i++) inputString[i] = tolower(inputString[i]); 
    this->key = key;
    this->inputString = inputString;
}

// Find the index of the input character from the assigned values in chars string 
int VignereCipher :: findIndex(char letter) {
    int pos = 0;
    for(int i=0; i< chars.length(); i++) if (chars[i] == letter) pos = i;
    return pos;
}

// Removes the white spaces and pushes the new string into plaintext variable
void VignereCipher :: removeSpaces() {
    for(int i = 0; i < inputString.length(); i++) {
        if(inputString[i] == ' ') continue;
        else plaintext.push_back(inputString[i]);
    }
}

// Encryption function 
void VignereCipher :: Encrypt(std::string key = "animal") {
    int k = 0;
    for(int i = 0; i < plaintext.length(); i++) {
        if (k == key.length()) k = 0;
        ciphertext.push_back(chars[(findIndex(plaintext[i]) + findIndex(key[k])) % 26]);
        k++;
    }
    for(int i = 0; i < ciphertext.length(); i++) ciphertext[i] = toupper(ciphertext[i]);
}

int main() {
    
    // First argument is the default key and the second is the input to be crypted. 
    VignereCipher Encrypter("key", "Here is how it works");
    
    // Removes the spaces from the input string and turns in into lower case plaintext
    Encrypter.removeSpaces();
    
    // Encrypts the plaintext into cipher text 
    // It takes 0 or 1 argument. If no argument is given, the default key is used to encrypt the 
    // plaintext. If one argument is given (string), then that acts as the new key 
    Encrypter.Encrypt("vector");

    std::cout << "Plain Text : " << Encrypter.inputString << "\n";
    std::cout << "Cipher Text: " << Encrypter.ciphertext  << "\n";
    
    return 0;
}


