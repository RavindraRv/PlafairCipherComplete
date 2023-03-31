/*Implement the encryption as well as the decryption of the following cipher. The encryption works as
follows:
1. Consider a word (without any space) as a plaintext. (Input)
2. Adjust the length of the plaintext and handle the repetition of letter (if present) according to the
rule of the Playfair cipher. If there is any J in the word convert it to I. Let the final word be ∆.
3. Print the word ∆. (Output)
4. Consider a word as input and convert J (if any) to I and consider that converted word as the key
K1. (Input)
5. Generate the 5 × 5 key matrix of the Playfair cipher from K1 and print it. (Output)
6. Encrypt ∆ using the Playfair cipher where the key is K1. Let the ciphertext be C1. Print the
ciphertext C1. (Output)
7. Encrypt C1 using the Affine cipher where the key is K2 = (11, 15) ∈ Z26 × Z26. Let the ciphertext
be C2. Print the ciphertext C2. (Output)
8. Encrypt C2 using the Shift cipher where the key is K3 (0 ≤ K2 ≤ 25). Let the ciphertext be C3.
Print the ciphertext C3. (Output)
Now you have to think on the decryption to write the code for the decryption. If the code is correct then
the decrypted text after doing the Playfair cipher decryption should match with ∆. You have to print
all the middle layered decrypted texts in the code.*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void handleRepetition(char *plaintext) {
    int i, j;
    for (i = 0; i < strlen(plaintext) - 1; i++) {
        if (plaintext[i] == plaintext[i + 1]) {
            for (j = strlen(plaintext); j > i + 1; j--)
                plaintext[j] = plaintext[j - 1];
            plaintext[i + 1] = 'X';
        }
    }
    if (strlen(plaintext) % 2 != 0)
        strcat(plaintext, "X");
    for(i=0;i<strlen(plaintext);i++){
        if(plaintext[i]>='a'&&plaintext[i]<='z')
            plaintext[i]-=32;
    }
}
void createKeyMatrix(char key[]) {
    char matrix[5][5];
    int i, j, k = 0;
    int used[26] = {0};

    // Initialize matrix with 'A'
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            matrix[i][j] = 'A';
        }
    }

    // Fill in the keyword
    for (i = 0; i < strlen(key); i++) {
        key[i] = toupper(key[i]); // convert to uppercase
        if (key[i] == 'J') key[i] = 'I'; // replace 'J' with 'I'
        if (!used[key[i] - 'A']) {
            used[key[i] - 'A'] = 1;
            matrix[k / 5][k % 5] = key[i];
            k++;
        }
    }

    // Fill in the remaining alphabet
    for (i = 0; i < 26; i++) {
        char c = i + 'A';
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }

    // Print the key matrix
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void generateKeyMatrix(char *key, char matrix[5][5]) {
    int i, j, k = 0;
    char uniqueChars[25];
    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'J')
            key[i] = 'I';
        if (!strchr(uniqueChars, key[i]) && key[i]>='A' && key[i]<='Z')
            uniqueChars[k++] = key[i];
    }
    for (i = 0; i < 25; i++) {
        if (!strchr(uniqueChars, (char)(i + 'A')) && (i + 'A') != 'J')
            uniqueChars[k++] = (char)(i + 'A');
    }
    k = 0;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            matrix[i][j] = uniqueChars[k++];
}

void encryptPlayfair(char *plaintext, char matrix[5][5]) {
    int i, x1, y1, x2, y2;
    for (i = 0; i < strlen(plaintext); i += 2) {
        // Find the row and column indices of the first letter
        for(int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                if(matrix[j][k]==plaintext[i]){
                    x1 = j;
                    y1 = k;
                }
            }
        }
        // Find the row and column indices of the second letter
        for(int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                if(matrix[j][k]==plaintext[i+1]){
                    x2 = j;
                    y2 = k;
                }
            }
        }

        // Check if the letters are in the same row
        if (x1 == x2) {
            plaintext[i] = matrix[x1][(y1 + 1) % 5];
            plaintext[i + 1] = matrix[x2][(y2 + 1) % 5];
        }
        // Check if the letters are in the same column
        else if (y1 == y2) {
            plaintext[i] = matrix[(x1 + 1) % 5][y1];
            plaintext[i + 1] = matrix[(x2 + 1) % 5][y2];
        }
        // If the letters are in different rows and columns
        else {
            plaintext[i] = matrix[x1][y2];
            plaintext[i + 1] = matrix[x2][y1];
        }
    }
}


void encryptAffine(char *plaintext, int a, int b) {
int i;
for (i = 0; i < strlen(plaintext); i++) {
plaintext[i] = (a * (plaintext[i] - 'A') + b) % 26 + 'A';
}
}

void encryptShift(char *plaintext, int shift) {
int i;
for (i = 0; i < strlen(plaintext); i++) {
plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
}
}

void decryptShift(char *ciphertext, int shift) {
int i;
for (i = 0; i < strlen(ciphertext); i++) {
ciphertext[i] = (ciphertext[i] - 'A' - shift + 26) % 26 + 'A';
}
}
int getModInverse(int a, int m) 
{ 
    int m0 = m; 
    int y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        // q is quotient 
        int q = a / m; 
        int t = m; 
  
        // m is remainder now, process same as 
        // Euclid's algo 
        m = a % m, a = t; 
        t = y; 
  
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
       x += m0; 
    return x; 
}

void decryptAffine(char *ciphertext, int a, int b) {
    int i, inv_a = getModInverse(a,26);
    for (i = 0; i < strlen(ciphertext); i++) {
        if(ciphertext[i]>='A'&&ciphertext[i]<='Z'){
            ciphertext[i] = (inv_a * (ciphertext[i] - 'A' - b + 26)) % 26 + 'A';
        }
        if(ciphertext[i]>='a'&&ciphertext[i]<='z'){
            ciphertext[i] = (inv_a * (ciphertext[i] - 'a' - b + 26)) % 26 + 'a';
        }
    }
}


void decryptPlayfair(char *ciphertext, char matrix[5][5]) {
    int i, x1, y1, x2, y2;
    for (i = 0; i < strlen(ciphertext); i += 2) {
        // Find the row and column indices of the first letter
        for(int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                if(matrix[j][k]==ciphertext[i]){
                    x1 = j;
                    y1 = k;
                }
            }
        }
        // Find the row and column indices of the second letter
        for(int j=0; j<5; j++){
            for(int k=0; k<5; k++){
                if(matrix[j][k]==ciphertext[i+1]){
                    x2 = j;
                    y2 = k;
                }
            }
        }

        // Check if the letters are in the same row
        if (x1 == x2) {
            ciphertext[i] = matrix[x1][(y1 + 4) % 5];
            ciphertext[i + 1] = matrix[x2][(y2 + 4) % 5];
        }
        // Check if the letters are in the same column
        else if (y1 == y2) {
            ciphertext[i] = matrix[(x1 + 4) % 5][y1];
            ciphertext[i + 1] = matrix[(x2 + 4) % 5][y2];
        }
        // If the letters are in different rows and columns
        else {
            ciphertext[i] = matrix[x1][y2];
            ciphertext[i + 1] = matrix[x2][y1];
        }
    }
}


int main() {
char plaintext[100], key[100], matrix[5][5], ciphertext[100];
int a, b, shift;
 char skey[20];
    
printf("Enter plaintext: ");
scanf("%s", plaintext);
handleRepetition(plaintext);
printf("Adjusted plaintext: %s\n", plaintext);
printf("Enter key: ");
    scanf("%s", skey);
    createKeyMatrix(skey);
/*printf("Enter key: ");
scanf("%s", key);*/
generateKeyMatrix(skey, matrix);
/*printf("Key matrix:\n");
int i,j;
for(i=0;i<5;i++){
for(j=0;j<5;j++){
printf("%c ",matrix[i][j]);
}
printf("\n");
}*/
encryptPlayfair(plaintext, matrix);
printf("Ciphertext after Playfair encryption: %s\n", plaintext);
printf("Enter key a and b for Affine encryption: ");
scanf("%d %d", &a, &b);
handleRepetition(plaintext);
encryptAffine(plaintext, a, b);
printf("Ciphertext after Affine encryption: %s\n", plaintext);
printf("Enter key for Shift encryption: ");
scanf("%d", &shift);
encryptShift(plaintext, shift);
printf("Ciphertext after Shift encryption: %s\n", plaintext);
strcpy(ciphertext, plaintext);
decryptShift(ciphertext, shift);
printf("Decrypted text after Shift decryption: %s\n", ciphertext);
handleRepetition(plaintext);
decryptAffine(ciphertext, a, b);
printf("Decrypted text after Affine decryption: %s\n", ciphertext);
decryptPlayfair(ciphertext, matrix);
printf("Decrypted text after Playfair decryption: %s\n", ciphertext);
return 0;
}
