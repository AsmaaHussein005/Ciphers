//Name: Asmaa Hussein Omar
//email : asmaahlal123456789@gmail.com

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Function prototypes
void routeCipher();
void polybiusSquareCipher();
void Affine();
void vignere();
void encryptMessage();
void decryptMessage();
void Astbash();
void Baconian();
void displayMenu() {
    cout << "Cipher Menu:\n";
    cout << "1. Route Cipher\n";
    cout << "2. Affine Cipher\n";
    cout << "3. Polybius Square Cipher\n";
    cout << "4. Astbash\n";
    cout << "5. Baconian\n";
    cout << "6. vignere\n";
    cout << "7. Exit\n";
}

int main() {
    int choice;

    while (true) {
        // Display menu
        displayMenu();
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        if (cin.fail()) {
            // Clear error state
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Display error message
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue; // Skip to the next iteration of the loop
        }

        // Process user's choice
        switch (choice) {
            case 1:
                routeCipher();
                break;
            case 2:
                Affine();
                break;
            case 3:
                polybiusSquareCipher();
                break;
            case 4:
                Astbash();
                break;
            case 5:
                Baconian();
                break;
            case 6:
                vignere();
                break;
            case 7:
                cout << "Exiting program. Goodbye!\n";
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    }
    
}

// Your Route Cipher code goes here

using namespace std;
void routeCipher() {
    string choice;
    int choiceNum; // Define choiceNum outside the loop

    // Main menu loop
    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        cout << "Choice entered: " << choice << endl; // Debugging print

        if (cin.fail()) {
            // Clear error state
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Display error message
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue; // Skip to the next iteration of the loop
        }

        // Convert choice to integer
        try {
            choiceNum = stoi(choice);
        } catch (const std::invalid_argument& e) {
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        // Process the chosen option
        switch (choiceNum) {
            case 1:
                encryptMessage();
                break;
            case 2:
                decryptMessage();
                break;
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

    } while (choiceNum != 3); // Use choiceNum instead of stoi(choice)
}


void encryptMessage() {
    cin.ignore();
    string Msg;
    int key;
    cout << "Welcome to Route cipher ";
    cout << "please enter your message \n";
    getline(cin, Msg);
    // taking only letters and capitalizing them along with removing spaces and any other non_letter characters
    string message;
    for (char ch : Msg) {
        if (isalpha(ch)) {
            message += toupper(ch);
        }
    }
    while (true) {
        cout << "please enter your secret key: \n";
        cin >> key;
        if (cin.fail() || (key < 2 && key > (Msg.length()/2))) {
            cout << "Invalid input. Please enter a non-negative integer: ";
            cin.clear();
            cin.ignore();

        } else {
            break;
        }
    }


    int Msg_size = message.size();
    int l = Msg_size / key;
    int rows = ceil(l);

    // to insert the input of the message into an array in order to route over it later
    vector<vector<char>> array(rows, vector<char>(key));
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < key; ++j) {
            if (index < message.length()) {
                array[i][j] = message[index++];
            } else {
                array[i][j] = 'X';
            }
        }
    }

    string encryptedMessage = " ";
    int startRow = 0, endRow = rows - 1;
    int startCol = 0, endCol = key - 1;

    // the snippet responsible for routing over the array of letters
    while (startRow <= endRow && startCol <= endCol) {
        // Move down
        for (int i = startRow; i <= endRow; ++i)
            encryptedMessage += array[i][endCol];
        endCol--;

        // Move left
        if (startRow <= endRow) {
            for (int i = endCol; i >= startCol; --i)
                encryptedMessage += array[endRow][i];
            endRow--;
        }

        // Move up
        if (startCol <= endCol) {
            for (int i = endRow; i >= startRow; --i)
                encryptedMessage += array[i][startCol];
            startCol++;
        }

        // Move right
        for (int i = startCol; i <= endCol; ++i)
            encryptedMessage += array[startRow][i];
        startRow++;
    }


    string finalEncryptedMessage = " ";
    for (char ch : encryptedMessage) {
            finalEncryptedMessage += ch;

    }
    // displaying the final encrypted message
    cout << "encrypted message: " << finalEncryptedMessage << endl;
}

void decryptMessage() {
    cin.ignore();
    string Msg;

    int key;
    cout << "Welcome to Route cipher ";
    cout << "please enter your message \n";
    getline(cin, Msg);
    // taking only letters and capitalizing them along with removing spaces and any other non_letter characters
    string message;
    for (char ch: Msg) {
        if (isalpha(ch)) {
            message += toupper(ch);
        }
    }
    while (true) {
        cout << "please enter your secret key: \n";
        cin >> key;
        if (cin.fail() || (key < 2 &&(Msg.size()/2)) ) {
            cout << "Invalid input. Please enter a non-negative integer: ";
            cin.clear();
            cin.ignore();
        } else if (key == 0) {
            // handle the case when the user enters 0
        } else {
            break;
        }
    }

    int Msg_size = message.size();
    float l = Msg_size / (float) key;
    float rows = ceil(l);

    // Create and initialize the 2D vector to store the encrypted message
    vector<vector<char>> array(rows, vector<char>(key, ' '));

    int j = 0;
    int strt_Row = 0, end_Row = rows - 1;
    int strt_Clm = 0, end_Clm = key - 1;

    // the snippet responsible for routing over the array of letters
    while (strt_Row <= end_Row && strt_Clm <= end_Clm) {
        // Move down
        for (int i = strt_Row; i <= end_Row; ++i)
            array[i][end_Clm] = message[j++];
        end_Clm--;

        // Move left
        if (strt_Row <= end_Row) {
            for (int i = end_Clm; i >= strt_Clm; --i)
                array[end_Row][i] = message[j++];

            end_Row--;
        }

        // Move up
        if (strt_Clm <= end_Clm) {
            for (int i = end_Row; i >= strt_Row; --i)
                array[i][strt_Clm] = message[j++];
            strt_Clm++;
        }

        // Move right
        for (int i = strt_Clm; i <= end_Clm; ++i)
            array[strt_Row][i] = message[j++];
        strt_Row++;
    }

    // Print the encrypted message
    cout << "Decrypted message:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
                cout << array[i][j];
        }
    }
    cout << endl;
}
#include <iostream>
#include <string>

using namespace std;

// Function to perform Affine encryption
string Affine_encryption(string message, int a, int b) {
    string encrypted_message = "";
    // Loop through each character in the message
    for (char letter : message) {
        // Check if the character is a letter or a space
        if (isalpha(letter) || letter == ' ') {
            // If it's a letter, convert to uppercase and calculate the encrypted letter
            if (isalpha(letter)) {
                int x = toupper(letter) - 'A';
                int encrypted_letter = (a * x + b) % 26;
                encrypted_message += char(encrypted_letter + 'A');
            }
                // If it's a space, simply add it to the encrypted message
            else {
                encrypted_message += letter;
            }
        }
    }
    return encrypted_message;
}

// Function to perform modular arithmetic
int mod(int a, int b) {
    return (a % b + b) % b;
}

// Function to perform Affine decryption
string Affine_decryption(string message, int a, int b, int c) {
    string decrypted_message = "";
    int c_inverse = mod(c, 26);
    // Loop through each character in the message
    for (char letter : message) {
        // Check if the character is a letter or a space
        if (isalpha(letter) || letter == ' ') {
            // If it's a letter, convert to uppercase and calculate the decrypted letter
            if (isalpha(letter)) {
                int y = toupper(letter) - 'A';
                int decrypted_letter = mod(c_inverse * (y - b), 26);
                decrypted_message += char(decrypted_letter + 'A');
            }
                // If it's a space, simply add it to the decrypted message
            else {
                decrypted_message += letter;
            }
        }
    }
    return decrypted_message;
}

void Affine() {
    int choice;
    int a, b, c;
    cout << "Welcome to Affine Cipher!" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            while (true) {
                cout << "Enter parameters a, b, c: ";
                cin >> a >> b >> c;

                if ((a * c) % 26 == 1) {
                    break;
                }
                else {
                    cout << "Invalid parameters. (a * c) mod 26 must equal 1. Please try again." << endl;
                    cin.clear(); // Clear the input stream
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
                }
            }

            cin.ignore(); // Clear the newline character from the buffer
            string plaintext;
            cout << "Enter the message: ";
            getline(cin, plaintext);

            string ciphertext = Affine_encryption(plaintext, a, b);
            cout << "Encrypted text: " << ciphertext << endl;
        }
        else if (choice == 2) {
            while (true) {
                cout << "Enter parameters a, b, c: ";
                cin >> a >> b >> c;

                if ((a * c) % 26 == 1) {
                    break;
                }
                else {
                    cout << "Invalid parameters. (a * c) mod 26 must equal 1. Please try again." << endl;
                    cin.clear(); // Clear the input stream
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
                }
            }

            cin.ignore(); // Clear the newline character from the buffer
            string ciphertext;
            cout << "Enter the ciphertext: ";
            getline(cin, ciphertext);

            string decryptedText = Affine_decryption(ciphertext, a, b, c);
            cout << "Decrypted text: " << decryptedText << endl;
        }
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter a valid option (1, 2, or 3)." << endl;
        }
    }

}

#include <iostream>
#include <unordered_set>
#include <limits>
#include <string>
#include <cctype>
using namespace std;

const int ArraySize = 6;

// Function to initialize the array with unique numbers and letters
void array_of_key(char array[ArraySize][ArraySize]) {
    cout << "Enter 5 unique numbers from (1, 2, 3, 4, 5) for the first row:" << endl;

    // Set to ensure unique numbers
    unordered_set<int> uniqueNumbers;

    // Input and validation loop for the first row
    for (int i = 0; i < ArraySize - 1; ++i) {
        int number;

        // Validate input for uniqueness and range
        while (!(cin >> number) || number < 1 || number > 5 || uniqueNumbers.count(number) > 0) {
            cout << "Invalid input! Please enter a unique number from (1, 2, 3, 4, 5): ";

            // Clear input and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Insert unique number into the set and assign to array
        uniqueNumbers.insert(number);
        array[0][i + 1] = '0' + number;
    }

    // Set the first column values equal to the first row values
    for (int i = 0; i < ArraySize; ++i) {
        array[i][0] = array[0][i];
    }

    // Populate the remaining cells with letters starting from 'A'
    char letter = 'A';
    for (int i = 1; i < ArraySize; ++i) {
        for (int j = 1; j < ArraySize; ++j) {
            // Skip 'J' and continue with the next letter
            if (letter == 'J') {
                letter++;
            }
            array[i][j] = letter++;
        }
    }
}

// Function to encrypt a message using the initialized array
void encrypt_message() {
    char array[ArraySize][ArraySize];
    array_of_key(array);

    cout << "Enter a message to encrypt: ";
    cin.ignore();
    string message;
    getline(cin, message);

    cout << "Encrypted message: ";

    bool space_encountered = false;

    // Loop through each character in the message
    for (char ch : message) {
        if (ch == ' ') {
            // Handle spaces
            space_encountered = true;
            cout << " ";
        }
        else if (isalpha(ch)) {
            // Handle alphabetic characters
            if (ch == 'J') {
                ch = 'I'; // Replace 'J' with 'I'
            }
            ch = toupper(ch); // Convert to uppercase
            int row, col;

            // Find the row and column of the character in the array
            for (int i = 0; i < ArraySize; ++i) {
                for (int j = 0; j < ArraySize; ++j) {
                    if (array[i][j] == ch) {
                        row = i;
                        col = j;
                        break;
                    }
                }
            }

            // Print the encrypted characters
            if (space_encountered) {
                cout << " ";
                space_encountered = false;
            }
            cout << array[row][0] << array[0][col];
        }
    }

    cout << endl;
}

// Function to decrypt a message
string decrypt_message() {
    char array[ArraySize][ArraySize];
    array_of_key(array);

    cout << "Enter the encrypted message: ";
    cin.ignore();
    string encrypted_message;
    getline(cin, encrypted_message);
    string decrypted_message;

    // Loop through pairs of characters in the encrypted message
    for (size_t i = 0; i < encrypted_message.length(); i += 2) {
        char encryptedChar1 = encrypted_message[i];
        char encryptedChar2 = encrypted_message[i + 1];

        // Handle spaces
        if (encryptedChar1 == ' ' || encryptedChar2 == ' ') {
            decrypted_message += " ";
        }
        else {
            int row, col;

            // Find the row and column of each character in the array
            for (int j = 0; j < ArraySize; ++j) {
                if (array[j][0] == encryptedChar1) {
                    row = j;
                }

                if (array[0][j] == encryptedChar2) {
                    col = j;
                }
            }

            // Append the decrypted character to the result
            decrypted_message += array[row][col];
        }
    }

    return decrypted_message;
}

void polybiusSquareCipher() {
    int choice;

    // Main menu loop
    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit the program\n";
        cout << "Enter your choice between 1 and 3: ";
        cin >> choice;

        if (cin.fail()) {
            // Clear error state
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Display error message
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue; // Skip to the next iteration of the loop
        }


        // Process the chosen option
        switch (choice) {
            case 1:
                encrypt_message();
                break;
            case 2: {
                // Decrypt and display the decrypted message
                string decryptedMessage = decrypt_message();
                cout << "Decrypted message: " << decryptedMessage << endl;
                break;
            }
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

    } while (choice != 3);

}

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to perform Astbash cipher encryption, shifting letters in the message
string Astbash_cipher_1(const string& message) {
    string ciphered_message;
    // Iterate through each character in the message
    for (char letter : message) {
        // Check if the character is an alphabet letter
        if (isalpha(letter)) {
            // Calculate the shift required to encrypt the letter
            char shift = 'Z' - (toupper(letter) - 'A');
            // Append the shifted letter to the ciphered message
            ciphered_message += shift;
        }
    }
    return ciphered_message;
}

// Function to perform a different variation of Astbash cipher encryption
string Astbash_cipher_2(const string& message) {
    string ciphered_message;
    // Iterate through each character in the message
    for (char letter : message) {
        // Check if the character is an alphabet letter
        if (isalpha(letter)) {
            // Convert the letter to uppercase for consistency
            letter = toupper(letter);
            // Check if the letter falls in the first half of the alphabet
            if (letter >= 'A' && letter <= 'M') {
                // Calculate the shift required for encryption
                int x = (12) - (letter % 65);
                char shift = 'A' + x;
                // Append the shifted letter to the ciphered message
                ciphered_message += shift;
            }
                // Check if the letter falls in the second half of the alphabet
            else if (letter >= 'N' && letter <= 'Z') {
                // Calculate the shift required for encryption
                int x = 12 - (letter % 78);
                char shift = 'N' + x;
                // Append the shifted letter to the ciphered message
                ciphered_message += shift;
            }
        }
    }
    return ciphered_message;
}

void Astbash() {
    int choice;
    string message, ciphered_message;

    do {
        // Display menu options
        cout << "Welcome to Astbash cipher\n";
        cout << "1. Encrypt using Cipher 1\n";
        cout << "2. Decrypt using Cipher 1\n";
        cout << "3. Encrypt using Cipher 2\n";
        cout << "4. Decrypt using Cipher 2\n";
        cout << "5. Exit \n";
        cout << "Enter your choice: ";
        // Read user choice
        cin >> choice;

        // Validate user input
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            // Clear error flag and discard invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Skip the rest of the loop and start from the beginning
            continue;
        }

        // Perform operations based on user choice
        switch (choice) {
            case 1:
                // Encrypt message using Cipher 1
                cout << "Please enter the message you want to encrypt: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, message);
                ciphered_message = Astbash_cipher_1(message);
                cout << "The encrypted message is: " << ciphered_message << endl;
                break;
            case 2:
                // Decrypt message using Cipher 1
                cout << "Please enter the message you want to decrypt: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, message);
                ciphered_message = Astbash_cipher_1(message); // Ciphered message is actually the encrypted message here
                // To decrypt, we use the same function with the encrypted message, it performs the inverse operation
                cout << "The decrypted message is: " << ciphered_message << endl;
                break;
            case 3:
                // Encrypt message using Cipher 2
                cout << "Please enter the message you want to encrypt: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, message);
                ciphered_message = Astbash_cipher_2(message);
                cout << "The encrypted message is: " << ciphered_message << endl;
                break;
            case 4:
                // Decrypt message using Cipher 2
                cout << "Please enter the message you want to decrypt: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, message);
                ciphered_message = Astbash_cipher_2(message); // Ciphered message is actually the encrypted message here
                // To decrypt, we use the same function with the encrypted message, it performs the inverse operation
                cout << "The decrypted message is: " << ciphered_message << endl;
                break;
            case 5:
                // Exit the program
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

}

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void encryption_baconian() {
    map<char, string> char_order;
    char_order['A'] = "00000"; char_order['B'] = "00001";
    char_order['C'] = "00010"; char_order['D'] = "00011";
    char_order['E'] = "00100"; char_order['F'] = "00101";
    char_order['G'] = "00110"; char_order['H'] = "00111";
    char_order['I'] = "01000"; char_order['J'] = "01001";
    char_order['K'] = "01010"; char_order['L'] = "01011";
    char_order['M'] = "01100"; char_order['N'] = "01101";
    char_order['O'] = "01110"; char_order['P'] = "01111";
    char_order['Q'] = "10000"; char_order['R'] = "10001";
    char_order['S'] = "10010"; char_order['T'] = "10011";
    char_order['U'] = "10100"; char_order['V'] = "10101";
    char_order['W'] = "10110"; char_order['X'] = "10111";
    char_order['Y'] = "11000"; char_order['Z'] = "11001";

    string MSG, f_MSG;
    cout << "Enter your message: ";
    getline(cin, MSG);
    while (MSG.empty()) {
        cout << "Message cannot be empty. Please enter your message again: ";
        getline(cin, MSG);
    }

    string new_MSG;
    for (char letter : MSG) {
        if (isalpha(letter)) {
            new_MSG += toupper(letter);
        }
    }

    char one, two;
    cout << "Enter the character to represent '0': ";
    cin >> one;
    cout << "Enter the character to represent '1': ";
    cin >> two;

    for (char letter : new_MSG) {
        if (char_order.find(letter) != char_order.end()) {
            f_MSG += char_order[letter] + ' ';
        }
    }

    // Convert '0's to 'A's and '1's to 'B's
    for (char& c : f_MSG) {
        if (c == '0') {
            c = one;
        } else if (c == '1') {
            c = two;
        }
    }

    cout << "Encrypted Message: " << f_MSG << endl;
}
void decryption_baconian() {
    map<string, char> Map{
            {"00000", 'A'}, {"00001", 'B'}, {"00010", 'C'}, {"00011", 'D'},
            {"00100", 'E'}, {"00101", 'F'}, {"00110", 'G'}, {"00111", 'H'},
            {"01000", 'I'}, {"01001", 'J'}, {"01010", 'K'}, {"01011", 'L'},
            {"01100", 'M'}, {"01101", 'N'}, {"01110", 'O'}, {"01111", 'P'},
            {"10000", 'Q'}, {"10001", 'R'}, {"10010", 'S'}, {"10011", 'T'},
            {"10100", 'U'}, {"10101", 'V'}, {"10110", 'W'}, {"10111", 'X'},
            {"11000", 'Y'}, {"11001", 'Z'}
    };

    string decrypted_Msg;
    do {
        cout << "Enter your encrypted message: ";
        getline(cin, decrypted_Msg);

        if (decrypted_Msg.empty() || decrypted_Msg.length() < 5) {
            cout << "Invalid input: Please enter a non-empty encrypted message.\n";
        }
    } while (decrypted_Msg.empty() || decrypted_Msg.length() < 5);

    string new_decryptedMSG;
    for (char letter : decrypted_Msg) {
        if (isalpha(letter)) {
            new_decryptedMSG += tolower(letter);
        }
    }

    char one, two;
    cout << "Enter the character representing '0': ";
    cin >> one;
    cout << "Enter the character representing '1': ";
    cin >> two;

    // Replace the characters '0' and '1' with their original representations
    string deciphered_Msg;
    for (char letter : new_decryptedMSG) {
        if (letter == one) {
            deciphered_Msg += '0';
        } else if (letter == two) {
            deciphered_Msg += '1';
        }
    }

    // Convert the deciphered message back to the original characters
    string decryptedOutput;
    for (size_t i = 0; i < deciphered_Msg.length(); i += 5) {
        string group = deciphered_Msg.substr(i, 5);
        if (Map.find(group) != Map.end()) {
            decryptedOutput += Map[group];
        } else {
            decryptedOutput += group;
        }
    }
    cout << "Decrypted message: " << decryptedOutput << endl;
}

void Baconian() {
    int choice;
    do {
        cout << "Welcome to Baconian Cipher\n";
        cout << "Choose an option:\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the newline character from the input buffer


        if (cin.fail()) {
            // Clear error state
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Display error message
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue; // Skip to the next iteration of the loop
        }


        switch (choice) {
            case 1:
                encryption_baconian();
                break;
            case 2:
                decryption_baconian();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 3);


}

#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
using namespace std;
void encryption() {
    string encryptedMessage = "";
    string userMessage, userKey;

    // Input validation for user message
    do {
        cout << "Enter your message (up to 80 characters): ";
        getline(cin, userMessage);

        if (userMessage.length() >= 80) {
            cout << "Error: Please enter 80 characters maximum." << endl;
        }

    } while (userMessage.length() >= 80);

    // Input validation for keyword
    do {
        cout << "Enter your keyword (up to 8 characters): ";
        getline(cin, userKey);

        if (userKey.length() >= 8) {
            cout << "Error: Please enter 8 characters at most." << endl;
        }

    } while (userKey.length() >= 8);

    // Convert user message to uppercase
    for (char &c : userMessage) {
        c = toupper(c);
    }

    // Convert keyword to uppercase
    for (char &c : userKey) {
        c = toupper(c);
    }

    // Map the keyword to the user message length
    string repeatedKey = "";
    int keyIndex = 0;
    for (int i = 0; i < userMessage.length(); ++i) {
        repeatedKey += userKey[keyIndex];
        keyIndex = (keyIndex + 1) % userKey.length();
    }

    // Encryption process
    for (int i = 0; i < userMessage.length(); ++i) {
        if (isdigit(userMessage[i]) || isspace(userMessage[i]) || ispunct(userMessage[i])) {
            encryptedMessage += userMessage[i];
        } else {
            int encryptedChar = (userMessage[i] - 'A' + repeatedKey[i] - 'A') % 26 + 'A';
            encryptedMessage += static_cast<char>(encryptedChar);
        }
    }

    cout << "Encrypted message: " << encryptedMessage << endl;
}

void decryption() {
    string decryptedMessage = "";
    string encryptedMessage, userKey;

    // Input validation for encrypted message
    do {
        cout << "Enter the encrypted message (up to 80 characters): ";
        getline(cin, encryptedMessage);

        if (encryptedMessage.length() > 80) {
            cout << "Error: Please enter 80 characters at most." << endl;
        }

    } while (encryptedMessage.length() > 80);

    // Input validation for keyword
    do {
        cout << "Enter the keyword (up to 8 characters): ";
        getline(cin, userKey);

        if (userKey.length() > 8) {
            cout << "Error: Please enter 8 characters at most." << endl;
        }

    } while (userKey.length() > 8);

    // Convert encrypted message to uppercase
    for (char &c : encryptedMessage) {
        c = toupper(c);
    }

    // Convert keyword to uppercase
    for (char &c : userKey) {
        c = toupper(c);
    }

    // Map the keyword to the encrypted message length
    string repeatedKey = "";
    int keyIndex = 0;
    for (int i = 0; i < encryptedMessage.length(); ++i) {
        repeatedKey += userKey[keyIndex];
        keyIndex = (keyIndex + 1) % userKey.length();
    }

    // Decryption process
    for (int i = 0; i < encryptedMessage.length(); ++i) {
        if (isspace(encryptedMessage[i]) || isdigit(encryptedMessage[i]) || ispunct(encryptedMessage[i])) {
            decryptedMessage += encryptedMessage[i];
        } else {
            int decryptedChar = (encryptedMessage[i] - repeatedKey[i] + 26) % 26 + 'A';
            decryptedMessage += static_cast<char>(decryptedChar);
        }
    }

    cout << "Decrypted message: " << decryptedMessage << endl;
}


void vignere() {
    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. End the program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                cin.ignore(); // Clear the input buffer
                encryption();
                break;
            case '2':
                cin.ignore(); // Clear the input buffer
                decryption();
                break;
            case '3':
                cout << "Ending the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter again." << endl;
        }
    } while (choice != '3');


}
