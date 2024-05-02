#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to calculate the hash value for a given string
int hashValue(string str, int prime) {
    int hash = 0;
    for (char c : str) {
        hash = (hash * 256 + c) % prime;
    }
    return hash;
}

// Rabin-Karp algorithm for pattern searching
void rabinKarpSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int prime = 101; // A prime number for modular arithmetic

    // Calculate the hash value of the pattern
    int patternHash = hashValue(pattern, prime);

    // Calculate the hash value of the first window of text
    int textHash = hashValue(text.substr(0, m), prime);

    // Initialize the highest power of 256 modulo prime
    int highestPower = 1;
    for (int i = 1; i < m; i++) {
        highestPower = (highestPower * 256) % prime;
    }

    // Iterate through the text string
    for (int i = 0; i <= n - m; i++) {
        // If the hash values match, check for character-by-character equality
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate the hash value for the next window
        if (i < n - m) {
            textHash = (256 * (textHash - text[i] * highestPower) + text[i + m]) % prime;
            if (textHash < 0) {
                textHash += prime;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    rabinKarpSearch(text, pattern);

    return 0;
}