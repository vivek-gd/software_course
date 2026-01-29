/*完全二叉树的先序遍历
样例输入输出
样例1
输入:
ABDGHCEIF
输出:
GHDCBIFEA
样例2
输入:
a
输出:
a
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int getLeftSubtreeSize(int totalNodes) {
    if (totalNodes <= 1) return 0;
    int h = 0;
    while ((1 << (h + 1)) - 1 <= totalNodes) {
        h++;
    }
    int rest = totalNodes - ((1 << h) - 1);
    int leftFull = (1 << (h - 1)) - 1;
    int leftRest = min(rest, 1 << (h - 1));
    return leftFull + leftRest;
}

string buildPostOrder(const string& pre, int start, int size) {
    if (size == 0) return "";
    if (size == 1) return string(1, pre[start]);
    int leftSize = getLeftSubtreeSize(size);
    int rightSize = size - 1 - leftSize;
    string left = buildPostOrder(pre, start + 1, leftSize);
    string right = buildPostOrder(pre, start + 1 + leftSize, rightSize);
    return left + right + pre[start];
}

int main() {
    string preOrder;
    cin >> preOrder;
    cout << buildPostOrder(preOrder, 0, preOrder.size()) << endl;
    return 0;
}


/*二叉树遍历及二叉树高度

样例输入输出
样例1
输入:
9
ABDGHCEIF
GDHBAEICF
输出:
4
*/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

unordered_map<char, int> inOrderMap;

TreeNode* buildTree(const string& preorder, int preStart, int preEnd, const string& inorder, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return nullptr;
    }
    char rootVal = preorder[preStart];
    TreeNode* root = new TreeNode(rootVal);
    int inRootPos = inOrderMap[rootVal];
    int leftSubtreeSize = inRootPos - inStart;
    root->left = buildTree(preorder, preStart + 1, preStart + leftSubtreeSize, inorder, inStart, inRootPos - 1);
    root->right = buildTree(preorder, preStart + leftSubtreeSize + 1, preEnd, inorder, inRootPos + 1, inEnd);
    return root;
}

int getHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    int n;
    cin >> n;
    string preorder, inorder;
    cin >> preorder >> inorder;
    for (int i = 0; i < n; ++i) {
        inOrderMap[inorder[i]] = i;
    }
    TreeNode* root = buildTree(preorder, 0, n - 1, inorder, 0, n - 1);
    cout << getHeight(root) << endl;
    return 0;
}

/*判断是否为堆-堆整理

样例输入输出
样例1
输入:
10
-9 -9 -6 -8 -2 1 10 7 8 2
输出:
min 10 8 1 7 2 -9 -6 -9 -8 -2
样例2
输入:
3
1 1 1
输出:
max min 
样例3
输入:
10
10 8 1 7 2 -9 -6 -9 -8 -2
输出:
max -9 -9 -6 -8 -2 1 10 7 8 2
样例4
输入:
10
-8 8 -9 10 -2 1 -6 -9 7 2 
输出:
10 8 1 7 2 -9 -6 -9 -8 -2
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 判断是否为最大堆
bool isMaxHeap(const vector<int>& arr, int n) {
    for(int i = 0; i <= (n - 2)/2; ++i){
        int left = 2*i +1;
        int right = 2*i +2;
        if(left < n && arr[i] < arr[left]) return false;
        if(right < n && arr[i] < arr[right]) return false;
    }
    return true;
}

// 判断是否为最小堆
bool isMinHeap(const vector<int>& arr, int n) {
    for(int i = 0; i <= (n - 2)/2; ++i){
        int left = 2*i +1;
        int right = 2*i +2;
        if(left < n && arr[i] > arr[left]) return false;
        if(right < n && arr[i] > arr[right]) return false;
    }
    return true;
}

// 调整堆为最大堆，父节点有相等子节点时选择右子节点下沉
void heapifyMax(vector<int>& arr, int n, int i){
    int largest = i;
    int left = 2*i +1;
    int right = 2*i +2;

    // 先检查右子节点是否大于左子节点
    if(right < n && arr[right] >= arr[left]){
        if(arr[right] > arr[largest]){
            largest = right;
        }
    }
    else if(left < n && arr[left] > arr[largest]){
        largest = left;
    }

    if(largest != i){
        swap(arr[i], arr[largest]);
        heapifyMax(arr, n, largest);
    }
}

// 调整堆为最小堆，父节点有相等子节点时选择右子节点下沉
void heapifyMin(vector<int>& arr, int n, int i){
    int smallest = i;
    int left = 2*i +1;
    int right = 2*i +2;

    // 先检查右子节点是否小于左子节点
    if(right < n && arr[right] <= arr[left]){
        if(arr[right] < arr[smallest]){
            smallest = right;
        }
    }
    else if(left < n && arr[left] < arr[smallest]){
        smallest = left;
    }

    if(smallest != i){
        swap(arr[i], arr[smallest]);
        heapifyMin(arr, n, smallest);
    }
}

// 构建最大堆
void buildMaxHeap(vector<int>& arr){
    int n = arr.size();
    for(int i = n/2 -1; i >=0; --i){
        heapifyMax(arr, n, i);
    }
}

// 构建最小堆
void buildMinHeap(vector<int>& arr){
    int n = arr.size();
    for(int i = n/2 -1; i >=0; --i){
        heapifyMin(arr, n, i);
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &x : arr) cin >> x;

    bool maxHeap = isMaxHeap(arr, n);
    bool minHeap = isMinHeap(arr, n);

    if(maxHeap && minHeap){
        // 所有元素相同
        cout << "max min ";
    }
    else if(maxHeap){
        buildMinHeap(arr);
        cout << "max ";
        for(int i=0;i<n;++i){
            if(i) cout << " ";
            cout << arr[i];
        }
    }
    else if(minHeap){
        buildMaxHeap(arr);
        cout << "min ";
        for(int i=0;i<n;++i){
            if(i) cout << " ";
            cout << arr[i];
        }
    }
    else{
        buildMaxHeap(arr);
        for(int i=0;i<n;++i){
            if(i) cout << " ";
            cout << arr[i];
        }
    }

    return 0;
}

//机器猫迷宫
#include<iostream>
#include<queue>
#include<utility>
#include<string>

using namespace std;

const int MAXN=105;
char maze[MAXN][MAXN];//迷宫判断
bool visited[MAXN][MAXN];//访问标记
int n,m;

//方向数组，分别代表上下左右
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

int bfs(){
    queue<pair<int,int>> q;
    q.push({1,1});
    visited[1][1]=true;

    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();

        if (x==n&&y==m){
            return true;
        }
        for(int i=0;i<4;++i){//以当前坐标为基，判断上下左右
            int newX=x+dx[i];
            int newY=y+dy[i];
            if(newX>=1&&newX<=n&&newY>=1&&newY<=m&&maze[newX][newY]=='.'&&!visited[newX][newY]){//'.'表示空地，迷宫最左边从1开始，最下面从1开始,因为1<=n,m<=100
                q.push({newX,newY});
                visited[newX][newY]=true;
            }
        }
    }
    return false;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>maze[i][j];
        }
    }
    if(bfs()){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    return 0;
}

//求多项式的幂
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;

//去掉负号，将非符号部分存入字符串
string getNum(const string&s){
    int t=s.size();
    string str="";
    if (s[0]=='-'){
        for(int i=1;i<t;i++)
            str+=s[i];
    }
    else{
        for(int i=0;i<t;i++){
            str+=s[i];
        }
    }
    return str;
}

string multi(const string& a,const string& b){
    int len1,len2;
    int isNeg=0;
    if(((a[0]=='-'&&b[0]!='-')||(a[0]!='-'&&b[0]=='-'))&&(a!="0"&&b!="0"))
        isNeg=1;//设置负号标记位
    string num1=getNum(a);
    string num2=getNum(b);
    len1=num1.size();
    len2=num2.size();

    int* res=new int[len1+len2];//分配空间，可用int* res = new int[len1 + len2](); 末尾加 () 会值初始化为 0代替两行，变量不能直接定义数组
    memset(res,0,sizeof(int)*(len1+len2));//c语言写法，将数组初始化为0

    for(int i=len1-1;i>=0;--i){// 遍历 num1 的每一位（从最低位到最高位）
        for(int j=len2-1;j>=0;--j){// 遍历 num2 的每一位（从最低位到最高位）
            res[i+j+1]+=(num1[i]-'0')*(num2[j]-'0');// 相乘并累加
        }
    }

    for(int i=len1+len2-1;i>=0;--i){
        if(res[i]>=10){
            res[i-1]+=res[i]/10;
            res[i]%=10;
        }
    }

    string ans="";
    for(int i=0;i<len1+len2;++i) ans +=res[i]+'0';//将每个数字转换成字符并拼接成字符串ans，0为ASCII码基值

    if(isNeg) ans='-'+ans;
    return ans;
}

//加法
string plusNum(const string& num1,const string& num2){
    int len1=num1.size(),len2=num2.size();
    int len=max(len1,len2)+1;//加一为可能产生的最高位进位预留空间
    int length=len;//length用于for循环
    string ans="";

    int* res=new int[length]();
    while(len1>0&&len2>0){//到1结束，len-1到0
        res[len-1]=(num1[len1-1]-'0')+(num2[len2-1]-'0');//用ASCII码相减将字符转换成数字，并从最低位开始相加
        len1--;
        len2--;
        len--;
    }

    while(len1>0){//如果num2比较完全，上面到0结束，因此下面len-1
        res[len-1]=(num1[len1-1]-'0');
        len1--;
        len--;
    }

    while(len2>0){
        res[len-1]=(num2[len2-1]-'0');
        len2--;
        len--;
    }

    for(int i=length-1;i>=0;--i){
        if(res[i]>=10){
            res[i-1]+=res[i]/10;
            res[i]%=10;
        }
    }

    int k;
    for (k=0;k<length;k++){//跳过前导符0
        if(res[k]!=0) break;
    }

    if(k==length) ans="0";
    else{
        for(int i=k;i<length;i++) ans+=res[i]+'0';//转换成字符
    }
    return ans;
}

//减法
string minusNum(string& num1,string& num2){
    int len1=num1.size();
    int len2=num2.size();
    int len;

    if(len1>=len2){
        for(int i=1;i<=len1-len2;i++){
            num2='0'+num2;//在num2前面补前导0，直到长度为len1
        }
        len=len1;
    }

    if(len2>len1){
        for(int i=1;i<=len2-len1;i++){
            num1='0'+num1;
        }
        len=len2;
    }

    int* num_a=new int[len]();
    int* num_b=new int[len]();
    for(int i=0;i<len;++i){
        num_a[i]=num1[i]-'0';//将字符转换成对应数字
        num_b[i]=num2[i]-'0';
    }

    int q=0;//记录退位
    for(int i=len-1;i>=0;--i){//数组最后一位为最低位
        num_a[i]-=q;
        if(num_a[i]<num_b[i]){
            num_a[i]+=10;//进位＋10
            q=1;
        }
        num_b[i]=num_a[i]-num_b[i];
    }

    int k;
    string ans="";
    for(k=0;k<len;k++) if(num_b[k]!=0) break;//消去前导0,不等于0时直接跳出，不加1
    if(k==len) ans="0";//判断是否位全0
    else{
        for(int i=k;i<len;i++) ans+=num_b[i]+'0';
    }
    return ans;
}

//判断两数组相减是否为负数
bool isPos(const string&str1,const string str2){
    if (str1.size()>str2.size()) return true;
    if (str1.size()==str2.size()) return str1>str2;//比较两个字符串，大于返回真，小于返回假
    return false;
}

void powerFun(queue<string>& q,int n,const string& a,const string& b){
    string t="0";
    string s;
    string num1,num2;
    string ans;
    for(int i=2;i<=n;i++){
        q.push(to_string(0));
        for(int j=1;j<=i+1;j++){
            s=q.front();
            q.pop();
            num1=multi(t,b);
            num2=multi(s,a);
            if(num1[0]!='-'&&num2[0]!='-'){
                ans=plusNum(num1,num2);
            }else if(num1[0]=='-'&&num2[0]=='-'){
                ans=plusNum(getNum(num1),getNum(num2));
                ans='-'+ans;
            }

            if(num1[0]=='-'&&num2[0]!='-'){
                num1=getNum(num1);
                if(isPos(num2,num1)){
                    ans=minusNum(num2,num1);
                }
                else{
                    ans='-'+minusNum(num1,num2);
                }
            }

            if(num1[0]!='-'&&num2[0]=='-'){
                num2=getNum(num2);
                if(isPos(num1,num2)){
                    ans=minusNum(num1,num2);
                }else{
                    ans='-'+minusNum(num2,num1);
                }
            }
            q.push(ans);
            t=s;
        }
    }
}

void showRes(queue<string>& q,int n){
    int k=n;
    int flag=1;
    while(!q.empty()){
        if(q.front()=="0"){
            q.pop();
            k--;
            flag=0;
            continue;
        }
        else if(q.front()=="1"){
            if (flag!=0&&k<n) cout<<'+';
            flag=1;
        }
        else if(q.front()[0]!='-'){
            if(k<n) cout<<'+';
            cout<<q.front();
        }
        else if(q.front()=="-1") cout<<'-';
        else if(q.front()[0]=='-') cout<<q.front();

        if(k==1) cout<<'x';
        else if(k!=0) cout<<"x^"<<k;
        if (k==n-1) cout<<'y';
        else if(k!=n) cout<<"y^"<<n-k;
        q.pop();
        k--;
    }
    cout<<endl;
}

int main(){
    int a,b,n;
    cin>>a>>b>>n;
    queue<string> q;
    string str1=to_string(a);
    string str2=to_string(b);
    q.push(str1);
    q.push(str2);
    powerFun(q,n,str1,str2);
    showRes(q,n);
    return 0;
}

//旋转的矩阵，顺逆时针交替旋转打印
#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    int num=n*m;
    int *matrix=new int [num];
    for(int i=0;i<num;i++){
        cin>>matrix[i];
    }
    int count=0;
    int i,j;
    int left=0,right=m-1,top=0,bottom=n-1;
    while(count<num){
        //顺时针输出
        if(left<right&&top<bottom){
            for(i=top,j=left;j<right;j++){//从左到右输出,j循环,不包括最后一位，最后一位由列输出
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            for(j=right;i<bottom;i++){//从上到下输出，i循环
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            for(i=bottom;j>left;j--){//从右到左
                cout<<matrix[i*m+j]<<" ";
                count++;//每输出一个加一次count
            }
            for(j=left;i>top;i--){//从下到上
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            left++;right--;top++;bottom--;//转到下一圈

        }
        //逆时针输出
        if(left<right&&top<bottom){
            for(i=top,j=left;i<bottom;i++){//从上到下
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            for(i=bottom;j<right;j++){//从左到右
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            for(j=right;i>top;i--){//从下到上
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            for(i=top;j>left;j--){
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
            left++;right--;top++;bottom--;//转到下一圈
        }

        if(left==right){
            for(i=top,j=left;i<=bottom;++i){//只有一列的话从上到下
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
        }

        if(top==bottom){
            for(i=top,j=left;j<=right;j++){//只有一行的话从左到右
                cout<<matrix[i*m+j]<<" ";
                count++;
            }
        }
    }
    delete[] matrix;
    return 0;
}

#include<iostream>
using namespace std;
//顺时针打印函数
void clockwise(int* data,int beginrow,int r,int c){
    int left=beginrow,right=c-beginrow-1;
    int top=beginrow,bottom=r-beginrow-1;
    if(left>right||top>bottom) return;
    //从左到右
    for(int i=left;i<=right;i++){
        cout<<data[top*c+i]<<" ";  
    }
    //从上到下
    for(int i=top+1;i<=bottom;i++){
        cout<<data[i*c+right]<<" ";
    }
    //从右到左
    if(top<bottom){
        for(int i=right-1;i>=left;i--){
            cout<<data[i*c+left]<<" ";
        }
    }
    //从下到上
    if(left<right){
        for(int i=bottom-1;i>top;i--){
            cout<<data[i*c+left]<<" ";
        }
    }
}

//逆时针打印函数
void anticlockwise(int *data,int beginrow,int r,int c){
    int left=beginrow,right=c-beginrow-1;
    int top=beginrow,bottom=r-beginrow-1;
    if(left>right||top>bottom) return;//终止条件

    //从上到下

    for(int i=top;i<=bottom;i++){
        cout<<data[i*c+left]<<" ";
    }

    //从左到右
    for(int i=left+1;i<=right;i++){
        cout<<data[bottom*c+i]<<" ";
    }
    //从下到上
    if(left<right){
        for(int i=bottom-1;i>=top;i--){
            cout<<data[i*c+right]<<" ";
        }
    }
    //从右到左
    if(top<bottom){
        for(int i=right-1;i>left;i--){
            cout<<data[top*c+i]<<" ";
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    int* data=new int[n*m];
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>data[i*m+j];
        }
    }
    int beginrow=0;
    bool isClockwise=true;//开始是顺时针
    while(beginrow*2<n&&beginrow*2<m){
        if(isClockwise){
            clockwise(data,beginrow,n,m);
        }else{
            anticlockwise(data,beginrow,n,m);
        }
        beginrow++;
        isClockwise=!isClockwise;
    }
    delete[] data;
    return 0;
}

//布尔矩阵奇偶性
#include<iostream>
using namespace std;
const int N=105;
int a[N][N];//全局定义
bool checkRow(int n){
    for (int i=0;i<n;i++){
        int sum =0;
        for (int j=0;j<n;j++){
            sum+=a[i][j];
        }
        if (sum%2!=0){
            return false;
        }
    }
    return true;
}

bool checkCol(int n){
    for(int j=0;j<n;j++){
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=a[i][j];
        }
        if(sum%2!=0){
            return false;
        }
    }
    return true;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    if(checkRow(n)&&checkCol(n)){
        cout<<"OK"<<endl;
    }
    else{
        for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=1-a[i][j];
            if(checkRow(n)&&checkCol(n)){
                cout<<"Change bit("<<i+1<<","<<")"<<endl;
                return 0;
            }
            a[i][j]=1-a[i][j];//更改后复原，进行下一轮尝试
            }
        }
        cout<<"Corrupt"<<endl;//不能更改则输出错误
    }

    return 0;
}


//三元组稀疏矩阵乘法运算
#include<iostream>
#include<vector>
#include<map>
using namespace std;

struct Triple{
    int row,col,val;
};

vector<Triple> multiplySparseMatrices(int r1,int c1,vector<Triple>& mat1,int r2,int c2,vector<Triple>& mat2){
    if(c1!=r2){
        cout<<"ERROR"<<endl;
        exit(0);
    }
    map<pair<int,int>,int> result;
    map<int,vector<Triple>> mat2ByCol;

    for(const auto& t:mat2){
        mat2ByCol[t.row].push_back(t);
    }
    for(const auto t1:mat1){
        if(mat2ByCol.find(t1.col)!=mat2ByCol.end()){
            for(const auto& t2:mat2ByCol[t1.col]){
                result[{t1.row,t2.col}]+=t1.val*t2.val;
            }
        }
    }

    vector<Triple> res;
    for(const auto& kv:result){
        if(kv.second!=0){
            res.push_back({kv.first.first,kv.first.second,kv.second});
        }
    }
    return res;
}

int main(){
    int r1,c1,count1,r2,c2,count2;
    cin>>r1>>c1>>count1;
    vector<Triple> mat1(count1);
    for(int i=0;i<count1;i++){
        cin>>mat1[i].row>>mat1[i].col>>mat1[i].val;
    }

    cin >> r2 >> c2 >> count2;
    vector<Triple> mat2(count2);
    for (int i = 0; i < count2; i++) {
        cin >> mat2[i].row >> mat2[i].col >> mat2[i].val;
    }
    vector<Triple> result = multiplySparseMatrices(r1, c1, mat1, r2, c2, mat2);
    if(result.empty()){
        cout << "The answer is a Zero Matrix" << endl;
    }else {
        for (const auto& t : result) {
            cout << t.row << " " << t.col << " " << t.val << endl;
        }
    }
    return 0;
}

//求整数最大间隔
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;
int seed;
int rand(){
    return (((seed=seed*214013L+2531011L)>>16)&0x7fff);
}
int rand32(){
    return ((rand()<<16)+(rand()<<1)+rand()%2);
}

//桶排序思想求最大间隔
int maximumGap(int n){
    if(n<2) return 0;
    int minVal=INT_MAX,maxVal=INT_MIN;
    vector<int> nums(n);
    for(int i=0;i<n;++i){
        nums[i]=rand32();
        minVal=min(minVal,nums[i]);
        maxVal=max(maxVal,nums[i]);
    }
    if(minVal==maxVal) return 0;

    int bucketSize=max(1,(maxVal-minVal))/(n-1);//n个元素需要n-1个间隔
    int bucketNum=(maxVal-minVal)/bucketSize+1;//加一为了向上取整

    vector<int> bucketMin(bucketNum,INT_MAX);// 初始化每个桶的最小值为INT_MAX
    vector<int> bucketMax(bucketNum,INT_MIN); // 初始化每个桶的最大值为INT_MIN

    for(int num:nums){
        int idx=(num-minVal)/bucketSize;
        bucketMin[idx]=min(bucketMin[idx],num);
        bucketMax[idx]=max(bucketMax[idx],num);
    }

    int prevMax=minVal;
    int maxGap=0;

    for(int i=0;i<bucketNum;++i){
        if (bucketMin[i]==INT_MAX) continue;// 跳过空桶
        maxGap=max(maxGap,bucketMin[i]-prevMax);
        prevMax=bucketMax[i];// 更新为当前桶的最大值
    }
    return maxGap;
}
int main(){
    int n;
    cin>>n>>seed;
    cout<<maximumGap(n)<<endl;
    return 0;
}

//完全二叉树的先序遍历，特殊二叉树只需一个遍历顺序推出其他
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int getLeftSubtreeSize(int totalNodes){
    if (totalNodes<=1) return 0;
    int h=0;
    while((1<<(h+1))-1<=totalNodes){
        h++;
    }
    int rest=totalNodes-((1<<h)-1);
    int leftFull=(1<<(h-1))-1;
    int leftRest=min(rest,1<<(h-1));
    return leftFull+leftRest;
}

string buildPostOrder(const string& pre,int start,int size){
    if (size==0) return "";
    if (size==1) return string(1,pre[start]);
    int leftSize=getLeftSubtreeSize(size);
    int rightSize=size-1-leftSize;
    string left=buildPostOrder(pre,start+1,leftSize); // 左子树后序
    string right=buildPostOrder(pre,start+1+leftSize,rightSize);// 右子树后序
    return left+right+pre[start];//左+右+根，后序遍历的核心操作：最后拼接根节点
}

int main(){
    string preOrder;
    cin>>preOrder;
    cout<<buildPostOrder(preOrder,0,preOrder.size())<<endl;
    return 0;
}


//二叉树前序，中序，后续，层序遍历
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//二叉树节点结构
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}//（TreeNode）的构造函数,构造函数强制初始化所有成员，避免悬空指针。
};

//前序遍历(根左右)
vector<int> preorderTraversal(TreeNode* root){
    vector<int> result;
    if(root==nullptr) return result;
    result.push_back(root->val);//根节点存入数组

    vector<int> left=preorderTraversal(root->left);
    result.insert(result.end(),left.begin(),left.end());//将 `left` 容器的所有元素追加到 `result` 容器的末尾
    
    vector<int> right=preorderTraversal(root->right);
    result.insert(result.end(),right.begin(),right.end());

    return result;
}

//中序遍历
vector<int> inorderTraversal(TreeNode* root){
    vector<int> result;//C++ 中声明并创建一个整型动态数组（vector）
    if(root==nullptr) return result;

    vector<int> left=inorderTraversal(root->left);//左子树中序遍历
    result.insert(result.end(),left.begin(),left.end());//将左子树中序遍历结果存入result

    result.push_back(root->val);//左子树中序遍历结果入栈后，根节点存入后面

    vector<int> right=inorderTraversal(root->right);
    result.insert(result.end(),right.begin(),right.end());

    return result;//返回结果
}

//后序遍历
vector<int> postorderTraversal(TreeNode* root){
    vector<int> result;
    if (root==nullptr) return result;//递归终止条件

    vector<int> left=postorderTraversal(root->left);//声明并初始化
    result.insert(result.end(),left.begin(),left.end());

    vector<int> right=postorderTraversal(root->right);
    result.insert(result.end(),right.begin(),right.end());

    result.push_back(root->val);

    return result;
}

//层序遍历(广度优先搜索)
vector<int> levelOrderTraversal(TreeNode* root){
    vector<int> result;
    if(root==nullptr) return result;//根节点为空结束

    queue<TreeNode*> q;
    q.push(root);//入队

    while(!q.empty()){
        TreeNode* current=q.front();//当前节点指向队头
        q.pop();//队头节点出栈
        result.push_back(current->val);//将当前节点压入数组

        if(current->left!=nullptr) q.push(current->left);//左子节点不为空则入队
        if(current->right!=nullptr) q.push(current->right);//右子节点不为空，右子节点入队

    }
    return result;

}

//创建测试二叉树
TreeNode* createTestTree(){
    TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(5);
    return root;
}

//释放二叉树内存
void destoryTree(TreeNode* root){
    if(root==nullptr) return;
    destoryTree(root->left);
    destoryTree(root->right);
    delete root;
}

int main(){
    TreeNode* root=createTestTree();
    cout<<"前序遍历";
    vector<int> preorder=preorderTraversal(root);
    for(int val:preorder) cout<<val<<" ";
    cout<<endl;

    cout<<"中序遍历";
    vector<int> inorder=inorderTraversal(root);
    for(int val:inorder) cout<<val<<" ";
    cout<<endl;

    cout<<"后序遍历";
    vector<int> postorder=postorderTraversal(root);
    for(int val:postorder) cout<<val<<" ";
    cout<<endl;//末尾换行

    cout<<"层序遍历";
    vector<int> levelOrder=levelOrderTraversal(root);
    for(int val:levelOrder) cout<<val<<" ";
    cout<<endl;

    destoryTree(root);//释放节点
    return 0;

}

//二叉树遍历及高度

#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

struct TreeNode{
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x):val(x),left(nullptr),right(nullptr){}
};

unordered_map<char,int> inOrderMap;

TreeNode* buildTree(const string& preorder,int preStart,int preEnd,const string& inorder,int inStart,int inEnd){
    if(preStart>preEnd||inStart>inEnd){
        return nullptr;
    }
    char rootVal=preorder[preStart];
    TreeNode* root=new TreeNode(rootVal);

    int inRootPos=inOrderMap[rootVal];
    int leftSubtreeSize=inRootPos-inStart;

    root->left=buildTree(preorder,preStart+1,preStart+leftSubtreeSize,inorder,inStart,inRootPos-1);
    root->right=buildTree(preorder,preStart+leftSubtreeSize+1,preEnd,inorder,inRootPos+1,inEnd);

    return root;
}

int getHeight(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    int leftHeight=getHeight(root->left);
    int rightHeight=getHeight(root->right);

    return max(leftHeight,rightHeight)+1;

}

int main(){
    int n;
    cin>>n;
    string preorder,inorder;
    cin>>preorder>>inorder;
    for(int i=0;i<n;++i){
        inOrderMap[inorder[i]]=i;
    }
    TreeNode* root=buildTree(preorder,0,n-1,inorder,0,n-1);
    cout<<getHeight(root)<<endl;
    return 0;
}

//二叉树遍历及其高度
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

struct TreeNode{
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x):val(x),left(nullptr),right(nullptr){}
};

unordered_map<char,int> inOrderMap;

TreeNode* buildTree(const string& preorder,int preStart,int preEnd,const string& inorder,int inStart,int inEnd){
    if(preStart>preEnd||inStart>inEnd){
        return nullptr;
    }
    char rootVal=preorder[preStart];//从前序遍历中提取出当前子树的根节点
    TreeNode* root=new TreeNode(rootVal);

    int inRootPos=inOrderMap[rootVal];
    int leftSubtreeSize=inRootPos-inStart;

    //root->left=buildTree(preorder,preStart+1,preStart+leftSubtreeSize,inorder,inStrat,inRootPos-1);
    //root->right=buildTree(preorder,preStart+leftSubtreeSize+1,preEnd,inorder,inRootPos+1,inEnd);
    root->left = buildTree(preorder, preStart + 1, preStart + leftSubtreeSize, inorder, inStart, inRootPos - 1);
    root->right = buildTree(preorder, preStart + leftSubtreeSize + 1, preEnd, inorder, inRootPos + 1, inEnd);
    return root;
}

int getHeight(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    int leftHeight=getHeight(root->left);
    int rightHeight=getHeight(root->right);
    return max(leftHeight,rightHeight)+1;
}

int main(){
    int n;
    cin>>n;
    string preorder,inorder;
    cin>>preorder>>inorder;
    for(int i=0;i<n;++i){
        inOrderMap[inorder[i]]=i;
    }
    TreeNode* root=buildTree(preorder,0,n-1,inorder,0,n-1);
    cout<<getHeight(root)<<endl;
}


//判断是否为堆整理
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

//判断是否为最大堆
bool isMaxHeap(const vector<int>& arr,int n){
    for(int i=0;i<=(n-2)/2;++i){
        int left=2*i+1;
        int right=2*i+2;
        if(left<n&&arr[i]<arr[left]) return false;//不符合条件返回错误
        if(right<n&&arr[i]<arr[right]) return false;
    }
    return true;
}

//判断是否为最小堆
bool isMinHeap(const vector<int>& arr,int n){
    for(int i=0;i<=(n-2)/2;++i){
        int left=2*i+1;
        int right=2*i+2;
        if(left<n&&arr[i]>arr[left]) return false;
        if(right<n&&arr[i]>arr[right]) return false;
    }
    return true;
}

//调整堆为最大堆，父节点有相等子节点时选择右子节点下沉
void heapifyMax(vector<int>& arr,int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(right<n&&arr[right]>=arr[left]){//右子节点大于左节点
        if(arr[right]>arr[largest]){
            largest=right;
        }
    }
    else if(left<n&&arr[left]>arr[largest]){
        largest=left;
    }
    if(largest!=i){
        swap(arr[i],arr[largest]);
        heapifyMax(arr,n,largest);
    }
}

//调整堆为最小堆，父节点有相等子节点时选择右子节点下沉
void heapifyMin(vector<int>& arr,int n,int i){
    int smallest=i;
    int left=2*i+1;
    int right=2*i+2;
    //检查右子节点是否小于左子节点  
    if(right<n&&arr[right]<=arr[left]){
        if(arr[right]<arr[smallest]){
            smallest=right;//指向最小节点
        }
    }
    else if(left<n&&arr[left]<arr[smallest]){
        smallest=left;
    }
    if (smallest!=i){
        swap(arr[i],arr[smallest]);
        heapifyMin(arr,n,smallest);
    }
}

//构建最大堆
void buildMaxHeap(vector<int>& arr){
    int n=arr.size();
    for(int i=n/2-1;i>=0;--i){//下标从1开始要减一
        heapifyMax(arr,n,i);
    }
}

//构建最小堆
void buildMinHeap(vector<int>& arr){
    int n=arr.size();
    for(int i=n/2-1;i>=0;--i){
        heapifyMin(arr,n,i);
    }
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    for(auto &x:arr)cin>>x;
    bool maxHeap=isMaxHeap(arr,n);
    bool minHeap=isMinHeap(arr,n);

    if(maxHeap&&minHeap){//所有元素相同
        cout<<"max min";
    }
    else if(maxHeap){
        buildMinHeap(arr);
        cout<<"max";
        for(int i=0;i<n;i++){
            if(i) cout<<" ";
            cout<<arr[i];
        }
    }
    else  if(minHeap){//将小根堆转换为大根堆
        buildMaxHeap(arr);
        cout<<"min";
        for(int i=0;i<n;++i){
            if(i) cout<<" ";
            cout<<arr[i];
        }
    }
    else{
        buildMaxHeap(arr);
        for(int i=0;i<n;++i){
            if(i) cout<<" ";
            cout<<arr[i];
        }
    }
    return 0;
}

//哈夫曼树，合并水晶块
#include<iostream>
#include<queue>
using namespace std;

int main(){
    int n;
    cin>>n;
    
    priority_queue<long long,vector<long long>,greater<long long>> pq;//`priority_queue`：指定了greater是小根堆
    long long num;

    for(int i=0;i<n;++i){
        cin>>num;
        pq.push(num);
    }

    long long sum=0;
    while(pq.size()>1){
        long long a=pq.top();
        pq.pop();
        long long b=pq.top();
        pq.pop();
        long long temp=a+b;
        sum+=temp;
        pq.push(temp);
    }
    cout<<sum<<endl;
    return 0;
}

//创建avl树并判断是否为完全二叉树
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int x):val(x),left(NULL),right(NULL),height(1){}
};//结构体后面用分号

//获取节点高度
int getHeight(TreeNode* node){
    if(node==NULL){
        return 0;
    }
    return node->height;
}

//更新节点高度
void updateHeight(TreeNode* node){
    if(node!=NULL){
        node->height=max(getHeight(node->left),getHeight(node->right))+1;
    }
}

//获取平衡因子
int getBalanceFactor(TreeNode* node){
    if(node==NULL){
        return 0;
    }
    return getHeight(node->left)-getHeight(node->right);//左减右得平衡因子
}

//右旋操作
TreeNode* rightRotate(TreeNode* y){
    TreeNode* x=y->left;
    TreeNode* T2=x->right;
    x->right=y;
    y->left=T2;

    updateHeight(y);//更新高度
    updateHeight(x);

    return x;
}

//左旋操作
TreeNode* leftRotate(TreeNode* x){
    TreeNode* y=x->right;
    TreeNode* T2=y->left;
    y->left=x;
    x->right=T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

//插入节点
TreeNode* insert(TreeNode* root,int val){
    if(root==NULL){
        return new TreeNode(val);
    }
    if(val<root->val){
        root->left=insert(root->left,val);
    }else{
        root->right=insert(root->right,val);
    }

    updateHeight(root);
    int balanceFactor=getBalanceFactor(root);

    //左左情况
    if(balanceFactor>1&&val<root->left->val){
        return rightRotate(root);
    }
    //右右情况
    if (balanceFactor>1&&val>root->left->val){
        return leftRotate(root);
    }
    //左右情况
    if(balanceFactor>1&&val>root->left->val){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
    //右左情况
    if(balanceFactor<-1&&val<root->right->val){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

//层次遍历
void levelOrderTraversal(TreeNode* root,vector<int>& result){
    if(root==NULL){
        return;
    }
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        TreeNode* node=q.front();
        q.pop();
        result.push_back(node->val);
        if(node->left!=NULL){
            q.push(node->left);
        }
        if(node->right!=NULL){
            q.push(node->right);
        }
    }
}

//判断是否为完全二叉树
bool isCompleteBinaryTree(TreeNode* root){
    if(root==NULL){
        return true;
    }
    queue<TreeNode*> q;
    q.push(root);
    bool hasNull=false;

    while(!q.empty()){
        TreeNode* node=q.front();
        q.pop();
        if(node==NULL){
            hasNull=true;
        }else{
            if(hasNull){
                return false;
            }
            q.push(node->left);
            q.push(node->right);
        }
    }
    return true;
}

int main(){
    int n;
    cin>>n;
    TreeNode* root=NULL;
    int val;
    for(int i=0;i<n;++i){
        cin>>val;
        root=insert(root,val);
    }
    vector<int> levelOrder;
    levelOrderTraversal(root,levelOrder);

    for(size_t i=0;i<levelOrder.size();++i){
        cout<<levelOrder[i];
        if(i!=levelOrder.size()-1){
            cout<<" ";
        }
    }
    cout<<endl;
    if(isCompleteBinaryTree(root)){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    return 0;
}

//红黑树
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

enum Color{RED,BLACK};

struct Node{
    int data;
    Color color;
    Node* left,*right,*parent;
    Node(int data):data(data),color(RED),left(nullptr),right(nullptr),parent(nullptr){}
};

class RBTree{
    private:
        Node* root;
        Node* nil;

        void  leftRotate(Node* x){
            Node* y=x->right;
            x->right=y->left;
            if(y->left!=nil) y->left->parent=x;
            y->parent=x->parent;
            if(x->parent==nil) root=y;
            else if(x==x->parent->left) x->parent->left=y;
            else x->parent->right=y;
            y->left=x;
            x->parent=y;
        }

        void rightRotate(Node*x){
            Node* y=x->left;
            x->left=y->right;
            if(y->right!=nil) y->right->parent=x;
            y->parent=x->parent;
            if(x->parent==nil) root=y;
            else if(x==x->parent->right) x->parent->right=y;
            else x->parent->left=y;
            y->right=x;
            x->parent=y;
        }

        void insertFixup(Node* z){
            while(z->parent->color==RED){
                if(z->parent==z->parent->parent->left){
                    Node* y=z->parent->parent->right;
                    if(y->color==RED){
                        z->parent->color=BLACK;
                        y->color=BLACK;
                        z->parent->parent->color=RED;
                        z=z->parent->parent;
                    }else{
                        if(z==z->parent->right){
                            z=z->parent;
                            leftRotate(z);
                        }
                        z->parent->color=BLACK;
                        z->parent->parent->color=RED;
                        rightRotate(z->parent->parent);
                    }
                }else{
                    Node* y=z->parent->parent->left;
                    if(y->color==RED){
                        z->parent->color=BLACK;
                        y->color=BLACK;
                        z->parent->parent->color=RED;
                        z=z->parent->parent;
                    }
                    else{ 
                        if(z==z->parent->left){
                            z=z->parent;
                            rightRotate(z);
                        }
                        z->parent->color=BLACK;
                        z->parent->parent->color=RED;
                        leftRotate(z->parent->parent);  
                    }
                }
            }
            root->color=BLACK;
        }

        void transplant(Node* u,Node* v){
            if(u->parent==nil) root=v;
            else if(u==u->parent->left) u->parent->left=v;
            else u->parent->right=v;
            v->parent=u->parent;
        }

        Node* minimum(Node* x){
            while(x->left!=nil) x=x->left;
            return x;
        }

        void deleteFixup(Node* x){
            while(x!=root&&x->color==BLACK){
                if(x==x->parent->left){
                    Node* w=x->parent->right;
                    if(w->color==RED){
                        w->color=BLACK;
                        x->parent->color=RED;
                        leftRotate(x->parent);
                        w=x->parent;
                    }
                    if(w->left->color==BLACK&&w->right->color==BLACK){
                        w->color=RED;
                        x=x->parent;
                    }else{
                        if(w->right->color==BLACK){
                            w->left->color=BLACK;
                            w->color=RED;
                            rightRotate(w);
                            w=x->parent->right;
                        }
                        w->color=x->parent->color;
                        x->right->color=BLACK;
                        w->right->color=BLACK;
                        leftRotate(x->parent);
                        x=root;
                    }
                }
                else{
                    Node* w=x->parent->left;
                    if(w->color==RED){
                        w->color=BLACK;
                        x->parent->color=RED;
                        rightRotate(x->parent);
                        w=x->parent->left;
                    }
                    if(w->right->color==BLACK&&w->left->color==BLACK){
                        w->color=RED;
                        x=x->parent;
                    }else{
                        if(w->left->color==BLACK){
                            w->right->color=BLACK;
                            w->color=RED;
                            leftRotate(w);
                            w=x->parent->left;
                        }
                        w->color=x->parent->color;
                        x->parent->color=BLACK;
                        w->left->color=BLACK;
                        rightRotate(x->parent);
                        x=root;
                    } 
                }
            }
            x->color=BLACK;
        }
    
        void preOrderHelper(Node* node,vector<string>& res){
            if(node!=nil){
                res.push_back(to_string(node->data)+(node->color==BLACK?"(B)":"(R)"));
                preOrderHelper(node->left,res);
                preOrderHelper(node->right,res);
            }
        }

        Node* searchHelper(Node* node,int key){
            if(node==nil||key==node->data) return node;
            if(key<node->data) return searchHelper(node->left,key);
            else return searchHelper(node->right,key);
        }
    
    public:
        RBTree(){
            nil=new Node(0);
            nil->color=BLACK;
            root=nil;
        }

        void insert(int key){
            Node* z=new Node(key);
            Node* y=nil;
            Node* x=root;
            while(x!=nil){
                y=x;
                if(z->data<x->data) x=x->left;
                else x=x->right;
            }

            z->parent=y;
            if(y==nil) root=z;
            else if(z->data<y->data) y->left=z;
            else y->right=z;

            z->left=nil;
            z->right=nil;
            z->color=RED;
            insertFixup(z);

        }

        void deleteNode(int key){
            Node* z=searchHelper(root,key);
            if(z==nil) return;
            Node* y=z;
            Node* x;
            Color y_original_color=y->color;

            if(z->left==nil){
                x=z->right;
                transplant;
            }else if(z->right==nil){
                x=z->left;
                transplant(z,z->left);
            }else{
                y=minimum(z->right);
                y_original_color=y->color;
                x=y->right;
                if(y->parent==z) x->parent=y;
                else{
                    transplant(y,y->right);
                    y->right=z->right;
                    y->right->parent=y; 
                }
                transplant(z,y);
                y->left=z->left;
                y->left->parent=y;
                y->color=z->color;
            }
            if(y_original_color==BLACK) deleteFixup(x);
            delete z;
        }

        vector<string> preOrder(){
            vector<string> res;
            preOrderHelper(root,res);
            return res;
        }

        int getMin(){
            Node* x=root;
            while(x->left!=nil) x=x->left;
            return x->data;
        }

        int getMax(){
            Node* x=root;
            while(x->right!=nil) x=x->right;
            return x->data;
        }

};

int main(){
    RBTree tree;
    int N,M;
    cin>>N;
    for(int i=0;i<N;++i){
        int val;
        cin>>val;
        tree.insert(val);
    }

    //输出前序遍历
    vector<string> pre=tree.preOrder();
    for(const auto&s:pre) cout<<s<<" ";
    cout<<endl;

    //输出最大值和最小值
    cout<<tree.getMin()<<" "<<tree.getMax()<<endl;

    //删除节点
    cin>>M;
    for(int i=0;i<M;++I){
        int val;
        cin>>val;
        tree.deleteNode(val);
    }

    //输出删除后的前序遍历
    pre=tree.preOrder();
    if(pre.empty()) cout<<"Null"<<endl;
    else{
        for(const auto&s:pre) cout<<s<<" ";
        cout<<"Null"<<endl;
    } 
    return 0;
}
