#include<iostream>
#include<queue>
#include<utility>
#include<cstring>
using namespace std;

#define N 105  //注意不能声明类型，末尾不能加分号

int n,m;
char maze[N][N];
bool visited[N][N];
queue<pair<int,int>> q;
int ax[]={-1,1,0,0},ay[]={0,0,-1,1};//用数组表示上下左右

int bfs(int n,int m){
    //从起始位置开始
    q.push({1,1});//起始点入队，并标记为已访问
    visited[1][1]=true;
    
    while(!q.empty()){//首先判断数组是否为空q.empty()
        int x=q.front().first;
        int y=q.front().second;
        q.pop();//取值后移出队列
        if(x==n&&y==m){
            return true;
        }
                
        for(int i=0;i<4;i++){//for条件应该用分号隔开 ,寻找附近未访问路径入队                   
            int nx=x+ax[i];//新的临时变量存储，确保在循环中时同一个坐标基准
            int ny=y+ay[i]; 
            //寻找之后判断
            if( nx>=1&&nx<=n&&ny>=1&&ny<=m&&maze[nx][ny]=='.'&&!visited[nx][ny]){//注意比较运算符用==  ，符合条件的入队，注意判断时，迷宫用的是坐标因此也从1开始
                visited[nx][ny]=true; //标记为已访问并入队
                q.push({nx,ny});
            }
        } 
    }
   
    return false;
}
int main(){
    int n,m;//先声明后使用
    cin>>n>>m;
    for(int i=1;i<=n;i++){//迷宫也从1，1开始
        for(int j=1;j<=m;j++){
            cin>>maze[i][j];//直接将输入记为二维数组值
        }
    }
    if(bfs(n,m)){
        cout<<"Yes";//字符串用双引号引起来，变量不用
    }else{
        cout<<"No";
    }
}


#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    float a=0.1,b=0.2;
    float c=0.3;
    std::cout<<fixed<<setprecision(20)<<a<<std::endl;
    std::cout<<fixed<<setprecision(20)<<b<<std::endl;
    std::cout<<fixed<<setprecision(20)<<a+b<<std::endl;
    std::cout<<fixed<<setprecision(20)<<c<<std::endl;

    if(a+b-c==0){
        std::cout<<"Yes";
    }else{
        std::cout<<"No";
    }
}

#include<iostream>
#include<iomanip>
using namespace std;
int main(){
    double a=0.1,b=0.3;
    double c=0.4;
    std::cout<<fixed<<setprecision(20)<<a<<std::endl;
    std::cout<<fixed<<setprecision(20)<<b<<std::endl;
    std::cout<<fixed<<setprecision(20)<<a+b<<std::endl;
    std::cout<<fixed<<setprecision(20)<<c<<std::endl;

    if(a+b-c==0){
        std::cout<<"Yes";
    }else{
        std::cout<<"No";
    }
}


//求多项式的幂






