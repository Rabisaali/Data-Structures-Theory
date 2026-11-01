#include<iostream>
using namespace std;
const int N=5;
void solve(int i,int j,int maze[N][N],int n,string ans[],string move,int vis[N][N],int di[],int dj[],int &an){
    if(i==n-1 && j==n-1){
        ans[an++]=move;
        return;
    }
    string dir="DLRU";
    vis[i][j]=1;
    for(int ind=0;ind<4;ind++){
        int nexti=i+di[ind];
        int nextj=j+dj[ind];
        if(nexti>=0 && nextj>=0 && nexti<n &&nextj<n && !vis[nexti][nextj] &&maze[nexti][nextj]==1){
            //vis[i][j]=1;
            solve(nexti,nextj,maze,n,ans,move+dir[ind],vis,di,dj,an);
        }
        }
        vis[i][j]=0;
}

string *findPath(int m[N][N],int n,int&count){
    int capacity=500;
    string*ans=new string[capacity];
    int v[N][N]={};
    //these positions are set in order with dir matching order of required char
    int di[]={+1,0,0,-1};
    int dj[]={0,-1,1,0};
    count=0;
    if(m[0][0]==1 && m[n-1][n-1]==1){
        solve(0,0,m,n,ans,"",v,di,dj,count);
    }
    return ans;
}
int main(){
    int maze[N][N]={
        {1,0,0,0,0},
        {1,1,0,1,1},
        {1,1,1,0,1},
        {0,0,1,1,1},
        {1,1,1,0,1}
    };
    int count=0;
    string *paths=findPath(maze,N,count);
    if(count==0){
        cout<<"No path exist. "<<endl;
    }
    else{
        cout<<"Possible paths: "<<endl;
                for (int i = 0; i < count; i++) {
            cout << paths[i] << endl;
        }
    }

    delete[] paths;
    return 0;
}