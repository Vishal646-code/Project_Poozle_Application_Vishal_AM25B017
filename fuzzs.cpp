#include <bits/stdc++.h>
using namespace std;
int mindistance(string word1, string word2) {
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

//Each thread will be processing a chunk of the dictionary.

void processchunk(const vector<string> &words, const string &query, int start, int end, vector<pair<int, string>> &localresults){
    for(int i=start; i<end; i++){
        int dist = mindistance(query, words[i]);
        localresults.emplace_back(dist, words[i]);
    }
}
int main(int argc, char* argv[]){
    //I expect the input to be in the form "<command> <query> <dictionary_filename>".
    //Since there are 3 parts to it, argc should be 3.
    if(argc != 3){
        cout<<"Usage: "<<argv[0]<<" <query> <dictionary_filename>"<<endl;
        return 1;
    }
    string query= argv[1];
    string filename= argv[2];
    ifstream fin(filename); //This is for opening the file for reading
    if(!fin){
        cout<<"Error opening file: "<<filename<<'\n';
        return 1;
    }
    vector<string> words;
    string word;
    while(fin >> word){
        words.push_back(word);
    }
    if(words.empty()){
        cout<<"The dictionary file is empty"<<'\n';
        return 1;
    }
    //Lets fix number of threads as 4.
    int n= words.size();
    int chunksize = (n+3)/4;
    vector<pair<int, string>> results1;
    vector<pair<int, string>> results2;
    vector<pair<int, string>> results3;
    vector<pair<int, string>> results4;
    thread t1(processchunk, cref(words), cref(query), 0, chunksize, ref(results1));
    thread t2(processchunk, cref(words), cref(query), chunksize, 2*chunksize, ref(results2));
    thread t3(processchunk, cref(words), cref(query), 2*chunksize, 3*chunksize, ref(results3));
    thread t4(processchunk, cref(words), cref(query), 3*chunksize, n, ref(results4));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}