#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> seqmul(vector<vector<int>> &a, vector<vector<int>> &b){
    int n=a.size();
    //assuming both a and b are nxn matrices
    vector<vector<int>> result(n, vector<int>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}
vector<vector<int>> genmatrix(int n){
    vector<vector<int>> a(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            a[i][j] = rand() % 100;
        }
    }
    return a;
}
int main(){
    return 0;
}