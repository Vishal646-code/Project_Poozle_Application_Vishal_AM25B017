#include <bits/stdc++.h>
using namespace std;
int minDistance(string word1, string word2) {
    int m= word1.size(), n= word2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int j=0; j<n; j++) dp[m][j] = n-j;
    for(int i=0; i<m; i++) dp[i][n] = m-i;
    for(int i = m-1; i>=0; i--){
        for(int j= n-1; j>=0; j--){
            if(word1[i] == word2[j]) dp[i][j] = dp[i+1][j+1];
            else{
                //insert
                int insert = 1 + dp[i][j+1];
                //replace
                int replace = 1 + dp[i+1][j+1];
                //delete
                int del = 1 + dp[i+1][j];
                dp[i][j]= min({insert, replace, del});
            }
        }
    }
    return dp[0][0];
}
int main(int argc, char* argv[]){
    //I expect the input to be in the form "command query dictionaryfilename.txt".
    //Since there are 3 parts to it, argc should be 3.
    if(argc != 3){
        cout<<"Usage: "<<argv[0]<<"<query> <dictionary_filename>"<<endl;
        return 1;
    }
    string query= argv[1];
    string filename= argv[2];
    ifstream fin(filename); //This is for opening the file for reading
    if(!fin){
        cout<<"Error opening file: "<<filename<<'\n';
        return 1;
    }
    return 0;
}