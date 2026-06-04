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
void worker(const vector<vector<int>> &a, const vector<vector<int>> &b, vector<vector<int>> &result, int strow, int endrow){
    int n= a.size();
    for(int i=strow; i<endrow; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

vector<vector<int>> parmultiply(const vector<vector<int>> &a, const vector<vector<int>> &b){
    int n= a.size();
    int chunk= (n+3)/4;

    //Here we dont need 4 separate vectors for each thread nor locks
    //As each thread is gonna work on a different portion of the result vector
    vector<vector<int>> result(n, vector<int>(n, 0));
    thread t1(worker, cref(a), cref(b), ref(result), 0, min(chunk, n));
    thread t2(worker, cref(a), cref(b), ref(result), min(chunk, n), min(2*chunk, n));
    thread t3(worker, cref(a), cref(b), ref(result), min(2*chunk, n), min(3*chunk, n));
    thread t4(worker, cref(a), cref(b), ref(result), min(3*chunk, n), n);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return result;
}
int main(){
    int n=128;
    vector<vector<int>> a= genmatrix(n);
    vector<vector<int>> b= genmatrix(n);
    return 0;
}