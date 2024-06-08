#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Matrix;

void printMatrix(const Matrix &key){
    for(const auto &row : key){
        for(const auto &elem : row){
            cout << elem << " ";
        }
        cout << endl;
    }
}

void to_matrix(Matrix& A, string str){
    
    int m = A.size();
    int n = A[0].size();
    int t = str.length();

    int k = 0; //char pos
    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){
            if(k < t && str[k] >= 'a' && str[k] <= 'z')
                A[i][j] = str[k] - 'a';
            else
                A[i][j] = 26;
            k++;
        }
    }

    return;
}

string to_text(Matrix& cipher){

    int m = cipher.size();
    int n = cipher[0].size();

    string str = "";
    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){
            int offset = (((cipher[i][j]) % 27) + 27) % 27;
            if(offset < 26){
                char ch = ('a' + offset);
                str += ch;
            }
            else
                str += "_";
        }
    }

    return str;
}

Matrix multiply_matrix(const Matrix &A, const Matrix &B) {
    
    int m = B.size();
    int n = B[0].size();

    Matrix Ans(m, vector<int>(n));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            Ans[i][j] = 0;
            for(int k = 0; k < m; ++k){
                Ans[i][j] += (((A[i][k] + 27) % 27) * (B[k][j] % 27)) % 27;
                Ans[i][j] %= 27;
            }
        }
    }

    return Ans;
}

Matrix find_submatrix(const Matrix& A, int r, int c){
    
    int n = A.size();
    Matrix subA(n-1);

    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != r && j != c)
                subA[k].push_back(A[i][j]);
        }
        if(i != r) k++;
    }

    return subA;
}

int det(const Matrix& A){
    
    int n = A.size();
    if(n == 2)
        return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);

    if(n == 1)
        return A[0][0];

    int sign = 1, determinant = 0, i = 0;
    while(i < n){
        Matrix sub_matx = find_submatrix(A, 0, i);
        determinant += A[0][i] * det(sub_matx) * sign;
        sign = -sign;
        i++;
    }

    return determinant;
}

int modInverse(int a, int m){
    a = a % m;
    for(int x = -m; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // If no modular inverse exists
}

void inverse_matrix(Matrix& A){
    int n = A.size();
    int detA = det(A);

    if (detA == 0)
        throw runtime_error("Matrix is singular and cannot be inverted.");

    Matrix invA(n, vector<int>(n));
    int modInv = modInverse(detA, 27);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Matrix subA = find_submatrix(A, i, j);
            int cofactor = det(subA);
            invA[j][i] = ((cofactor * ((i + j) % 2 == 0 ? 1 : -1)) * modInv) % 27;
        }
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            A[i][j] = invA[i][j];
    cout << modInv;
    return;
}

void get_key(Matrix& key, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> key[i][j];
        }
    }

    if(det(key) == 0){
        puts("Invalid key! det(key) = 0;");
        get_key(key, n);
    }
}

    /* Notes for reference
    key matrix size: m x m
    text matrix size: m x n
    */

string encode(string text, Matrix& key){

    transform(text.begin(), text.end(), text.begin(), ::tolower);

    int m = key.size();
    int n = (text.length() + m - 1) / m;

    Matrix plain(m, vector<int>(n));
    to_matrix(plain, text);

    Matrix cipher = multiply_matrix(key, plain);
    
    return to_text(cipher);
}

string decode(string text, Matrix& key){

    int m = key.size();
    int n = (text.length() + m - 1) / m;

    Matrix cipher(m, vector<int>(n));
    to_matrix(cipher, text);

    inverse_matrix(key);
    Matrix plain = multiply_matrix(key, cipher);
    
    string decoded = to_text(plain);
    replace(decoded.begin(), decoded.end(), '_', ' ');
    decoded.erase(decoded.find_last_not_of(" ") + 1);

    return decoded;
}

int main(){
    Matrix A(2, vector<int>(6));
    to_matrix(A, "hello world");
    printMatrix(A);
    
    Matrix key = {{5, -3}, {-4, 2}};
    printMatrix(key);
    
    Matrix B = multiply_matrix(key, A);
    printMatrix(B);
    
    inverse_matrix(key);
    printMatrix(key);
    
    Matrix C = multiply_matrix(key,B);
    printMatrix(C);
    
    return 0;
}
