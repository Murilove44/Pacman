#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main () {

    int m, n, soma=0;
    double media;
    cin >> m >> n;

    int** imagem = new int*[m];
    for (int i = 0; i < m; i++) {
        imagem[i] = new int[n];
    }
    for (int i=0;i<m;i++) {
        for(int j=0;j<n;j++){
            cin >> imagem[i][j];
            soma += imagem[i][j];
        }
    }
    media = soma*1.0/(m*n);
    for (int i=0;i<m;i++) {
        for(int j=0;j<n;j++){
            if (imagem[i][j] < media){
                imagem[i][j] = 0;
            } else {
                imagem[i][j] = 1;
            }
        }
    }
    for (int i=0;i<m;i++) {
        for(int j=0;j<n;j++){
            cout << imagem[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}