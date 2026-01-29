/*
数据（Data）：一切能输入到计算机中并能被计算机程序识别和处理的符号集合。
数值数据：整数、实数等
非数值数据：图形、图象、声音、文字等
数据元素(Data Element)：数据的基本单位，在程序中通常作为一个整体进行考虑和处理（Node, Record）。
数据项(Data Item)：构成数据元素的不可分割的最小单位(Field)。
数据对象(Data Object)：具有相同性质的数据元素的集合，是数据的子集。

数据结构的两个层次：
逻辑结构---数据元素间抽象化的相互关系，与数据的存储无关，独立于计算机，它是从具体问题抽象出来的数学模型。
存储结构（物理结构）----数据元素及其关系在计算机存储器中的存储方式。

划分方法一
（1）线性结构----
有且仅有一个开始和一个终端结点，并且所有结点都最多只有一个直接前趋和一个后继。
例如：线性表、栈、队列、串
（2）非线性结构----
一个结点可能有多个直接前趋和直接后继。
例如：树、图

划分方法二
集合：数据元素之间就是 “属 于同一个集合” ；
数据线性结构：数据元素之间 存在着一对一的线性关系；
树型结构：数据元素之间存在 着一对多的层次关系；
图结构：数据元素之间存在着 多对多的任意关系。


存储结构
顺序存储结构—借助元素在存储器中的相对位置来表示数据元素间的逻辑关系
链式存储结构—借助指示元素存储地址的指针表示数据元素间的逻辑关系

抽象数据类型可以用以下的三元组来表示：
           ADT = （D，S，P）

  D:D: 数据对象   S:D上的关系集    P:D上的操作集 

ADT抽象数据类型名{ 
        数据对象：<数据对象的定义>
        数据关系：<数据关系的定义> 
        基本操作 ：<基本操作的定义> 
    } ADT抽象数据类型名

数据对象：D={e1,e2|e1,e2 ∈R,R为实数集}
数据关系：S={<e1,e2>|e1为实部,e2为虚部}
基本操作：              Create(&C,x,y)
                   GetReal(C)
                   Add(C1，C2)
                   ……

表示部分：
typedef struct{
   float Realpart;
   float Imagepart;
}  Complex;
实现部分：
void Create(&Complex c,float x,float y){
    c.Realpart=x;
    c.Imagepart=y;
}
float GetReal(Complex c){
   return c.Realpart;
}
……


算法定义和特征
定义：
一个有穷的指令集，这些指令为解决某一特定任务规定了一个运算序列
特性：
 输入     有0个或多个输入
 输出     有一个或多个输出(处理结果)
 确定性  每步定义都是确切、无歧义的
 有穷性  算法应在执行有穷步后结束
 有效性  每一条运算应足够基本

 算法描述-欧几里德算法
 自然语言
①输入m 和n；
② 求m除以n的余数r；
③ 若r等于0，则n为最大公约数，算法结束；否则执行 第④步；
④ 将n的值放在m中，将r的值放在n中；
⑤ 重新执行第②步。


优点：容易理解 缺点：冗长、二义性

程序语言或伪代码
1. r = m % n;
2. while(n!=0){
m = n;
n = r;
r = m % n;} 
3. output n
表达能力强，抽象性强，容易理解 ;


*/

//循环,消耗空间与n无关，SSum(n)=1

template<class T>
T Sum(T a[],int n){
    T tsum=0;
    for(int i=0,i<n;i++)
        tsum+=a[i];
        return tsum;
}

//递归，消耗空间(递归栈空间)与n有关，SRsum(n)=(sizeof(a指针)+sizeof(int)+sizeof(函数指针))*n

template<class T>
T Rsum(T a[],int n){
    if(n>0)
        return Rsum(a,n-1)+a[n-1];
    return 0;
}

/*
大写Ο符号 Big-Oh
定义：f(n)=O(g(n))，当且仅当存在正常数c和n0，使得对所有n≥n0 , 有f(n)≤cg(n)
注意：Big-Oh不一定是最小上界。但是通常会求最小上界

对数没有给出对数基，因为
logan=logbn/logba，仅常数不同，相差logba倍

松散界限
当n≥2时，3n+3≤3n23n+3=O(n2)，不是最小上界
当n≥2时，10n2+4n+2≤10n410n2+4n+2=O(n4) 
6n2n+20=O(n22n)，更小上界n2n
逐步用更低阶的函数替换高阶函数，直到找到最小上界
高阶函数一定是低阶函数的松散上界。

关于大O符号有如下认识
时间复杂度的“级别”比“具体量”更重要！
确定时间消耗是什么级别，而非具体多少
是问题规模的函数
根据渐进性质，考虑问题足够大的情况
本质上是最差情况，这一点符合工业界需求

Ω符号(Big-Omega)
定义：f(n)= Ω(g(n))，当且仅当存在正常数c和n0，使得对所有n≥n0 , 有f (n)≥c g(n)
f至少是g的c倍，对足够大的n，g是f的一个下界

定理2：如果f(n)=amnm+…+a1n+a0且am>0，则f(n)=Ω(nm)


Θ符号(Big-Theta)
定义：f(n)=Θ(g(n))，当且仅当存在正常数c1、c2和n0，使得对所有n≥n0 , 有c1g(n)≤f (n)≤c2g(n)
f介于g的c1倍和c2倍之间，对足够大的n，g既是f的上界也是下界
也就是当O与Ω相同时，该函数为f函数的Θ
定理3：如果f(n)=amnm+…+a1n+a0且am>0，则f(n)= Θ(nm)

小写o符号(little-Oh)
定义：f(n)=o(g(n))，当且仅当f(n)=O(g(n))，且f(n)≠Ω(g(n))
例如：
3n+2=O(n2)且3n+2≠Ω(n2)3n+2=o(n2)但3n+2≠o(n)
10n2+4n+2=o(n3)，但10n2+4n+2≠o(n2)

*/
//求最大子序列

//算法一
//时间复杂度：O(n3)
int MaxsubsequenceSum(const int A[],int N){
    int ThisSum,MaxSum,i,j,k;
    MaxSum=0;
    for(i=0;i<N;i++){
        for(i=i;j<N;j++){
            ThisSum=0;
            for(k=i;k<=j;k++){
                ThisSum=0;
                for(k=i;k<=j;k++){
                    ThisSum+=A[k];
                }
                if(ThisSum>MaxSum){
                    MaxSum=ThisSum;
                }
            }
        }
    }
    return MaxSum;
}

//算法二
//时间复杂度：O(n2)
int MaxsubsequenceSum(const int A[],int N){
    int ThisSum,MaxSum,i,j;
    MaxSum=0;
    for(i=0;i<N;i++){
        ThisSum=0;
        for(j=i;j<N;j++){
            ThisSum+=A[j];
            if(ThisSum>MaxSum){
                MaxSum=ThisSum;
            }
        }
    }
    return MaxSum;
}
//算法三
//时间复杂度：O(n)
int MaxSubsequenceSum(const int A[],int N){
    int ThisSum,MaxSum,j;
    ThisSum=MaxSum=0;
    for(j=0;j<N;j++){
        ThisSum+=A[j];
        if(ThisSum>MaxSum){
            MaxSum=ThisSum;
        }
        else if(ThisSum<0){
            ThisSum=0;
        }
    }
}

/*
C和C++计时函数

*/
#include<windows.h>
#include<iostream>
using namespace std;
LARGE_INTEGER t1,t2,tc;
QueryPerformanceFrequency(&tc);
QueryPerformanceCounter(&t1);
fastSquareMatrixMultiply(a,b,c,5000);
QueryPerformanceCounter(&t2);
cout<<"time5000:"<<(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart<<endl;

//矩阵乘法ikj顺序更快

/*
数据元素(Data Element)：数据的基本单位，在程序中通常作为一个整体进行考虑和处理（Node, Record）。
数据项(Data Item)：构成数据元素的不可分割的最小单位(Field)。
数据对象(Data Object)：具有相同性质的数据元素的集合，是数据的子集。
*/
indexOf(x)
template<class T>
int arrayListNoSTL<T>::indexOf(const T& theElement)
const{
    for(int i=0;i<lsitSize;i++)
        if(element[i]==theElement)
            return i;
    return -1;
}

insert(k)
void arrayListNOSTL<T>::insert(int theIndex,const T&theElement){
    if(listSize==arrayLength){
        changeLength1D(element,arrayLength,2*arrayLength);
        arrayLength*2=2;
    }
    for(int i=listSize-1;i>=theIndex;i--){
        element[i+1]=element[i];    
    }
    element[theIndex]=theElement;
    listSize++;
}

delete(k)
void arrayListNoSTL<T>::delete(int theIndex){
    checkIndex(theIndex);
    for(int i=theIndex+1;i<listSize;i++){
        element[i-1]=element[i];
    }
    element[--listSize].~T();
}

//单向链表定义
class chain
template<class T>
class chain:public linearList<T>{
    chain(int initialCapacity=10);
    chain(const chain<T>&);
    ~chain();
    bool empty() const{return listSize==0;}
    int size() const{return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex,const T& theElement);
    void output(ostream& out) const;
    protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;
    int listSize;
};

//析构函数：删除链表中所有节点
template<class T>
Chain<T>::~Chain(){
    ChainNode<T>* next;
    while(first){
        next=first->link;
        delete first;
        first=next;
    }
}

template<class T>
T& chain<T>::get(int theIndex) const{
    chainNode<T>* currentNode=firstNode;
    for(int i=0;i<theIndex;i++){
        currentNode=currentNode->next;
    }
    return currentNode->element;
}

//根据结点序号删除结点实现
void chain<T>::erase(int theIndex){
    chainNode<T>* deleteNode;
    if(theIndex==0){
        deleteNode=firstNode;
        firstNode=firstNode->next;
    }
    else{
        chainNode<T>* p=firstNode;
        for(int i=0;i<theIndex-1;i++)
            p=p->next;
        deleteNode=p->next;
        p->next=p->next->next;
    }
    listSize--;
    delete deleteNode;
}

//根据结点序号插入结点实现
void chain<T>::insert(int theIndex,const T& theElement){
    if(theIndex<0||theIndex>listSize){
        ostringstream s;
        s<<"index="<<theIndex<<" size="<<listSize;
        throw illegalIndex(s.str());
    }
    if(theIndex==0){
        firstNode=new chainNode<T>(theElement,firstNode);
    }
    else{
        chainNode<T>* p=firstNode;
        for(int i=0;i<theIndex-1;i++){
            p=p->next;         
        }
        p->next=new chainNode<T>(theElement,p->next);
    }
    listSize++;
}

//Solution of Josephus problem
#include<iostream>
#include<list>
using namespace std;

void Josephus(int n,int m){
    for (int i=0;i<n-1;i++){
        for (int j=0;j<m-1;j++){
            cout<<"Delete person"<<getData()<<endl;
        }
        remove();
    }
}
int main(){
    CircList<int> clist;
    int n,m;
    cout<<"Enter the number of Contestants?";
    cin>>n>>m;
    for(int i=1;i<=n;i++)clist.insert(i);
    clist.Josephus(n,m);
}

/*

*/
#include <windows.h>
#include "linearList.h"
#include "arrayList.h"
#include <stdlib.h>
#include "chain.h"
using namespace std;

int main()
{
   // test constructor
linearList<double> *x = new chain<double>;
   LARGE_INTEGER t1, t2,t3,t4, tc;
   QueryPerformanceFrequency(&tc);
   QueryPerformanceCounter(&t1);
   for (int i = 0; i < 50000; i++)
   {
   if (i)
   int j = rand() % i;
   else
   int j = 0;
   }
   QueryPerformanceCounter(&t2);
   cout << " randtime50000:" << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;
      
   QueryPerformanceCounter(&t3);
   
   for (int i=0; i < 50000; i++)
   {
   if (i)
   x->insert(rand() % i, i);
   else
   x->insert( i, i);

   }
   QueryPerformanceCounter(&t4);
   cout << " time50000:" << (t4.QuadPart - t3.QuadPart - (t2.QuadPart - t1.QuadPart))*1.0 / tc.QuadPart << endl;
   QueryPerformanceCounter(&t3);

   for (int i = 50000-1; i >= 0; i--)
   {
   if (i)  //平均
   x->erase(rand() % (i));
   else
   x->erase(0);

  /* //最好
   x->erase(i);   
   x->erase(0);//最差*/

   }
   QueryPerformanceCounter(&t4);
   cout << " time50000:" << (t4.QuadPart - t3.QuadPart - (t2.QuadPart - t1.QuadPart))*1.0 / tc.QuadPart << endl;
   cout << x->size()<<endl;
   system("pause");
   
   return 0;
}

//间接寻址列表类定义
template<class T>
class IndirectList{
    public:
        IndirectList(int MaxListSize=10);
        ~IndirectList();
        bool IsEmpty();
        bool IsEmpty() const {return length==0;}
        int Length() const {return length;}
        bool Find(int k,T& x) const;
        int Search(const T&x) const;
        IndirectList<T>& Delete(int k,T& x);
        IndirectList<T>& Insert(int k,const T&x);
        void Output(ostream& out) const;
    private:
        T **table;
        int length,MaxSize;            
};

//构造函数和和析构函数
template<class T>
IndirectList<T>::IndirectList(int MaxListSize){
    MaxSize=MaxListSize;
    table=new T*[MaxSize];
    length=0;
}

template<class T>
IndirectList<T>::~IndirectList(){
    for(int i=0;i<length;i++)
        delete table[i];
    delete[] table;
}

//Find函数实现
template<class T>
bool IndirectList<T>::Find(int k,T& x) const{
    if(k<1||k>length) return false;
    x=*table[k-1];
    return true;
}

//删除操作
template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k,T&x){
    if(Find(k,x)){
        for (int i=k;i<length;i++){
            table[i-1]=table[i];
        }
        length--;
        return *this;
    }
    else throw OutofBounds();
    return* this;
}

//插入操作
template<class T>
IndirectList<T>& IndirectList<T>::Insert(int k,const T&x){
    if(k<0||k>length) throw NoMem();
    for (int i=length-1;i>=k;i--)
        table[i+1]=table[i];
    table[k]=new T;
    *table[k]=x;
    length++;
    return *this;
}

//链表数据域
class Node{
    friend ostream& operator<<(ostream&,const Node&);
    friend void BinSort(Chain<node>&,int);
    public:
        int operator !=(Node x) const{
            return (score!=x.score);
        }
    private:
        int score;
        char *name;
};
ostream& operator<<(ostream& out,const Node& x){
    out<<x.name<<' '<<return out;
}

//箱子排序实现
void BinSort(Chain<Node>& X,int range){
    int len=X.Length();
    Node x;
    Chain<Node>* bin;
    bin=new Chain<Node>[range+1];
    for(int i=1;i<=len;i++){
        X.Delete(1,x);
        bin[x.score].Insert(0,x);
    }
    for(int j=range;j>0;j--){
        while (!bin[j].IsEmpty()){
            bin[j].Delete(1,x);
            X.Insert(0,x);
        }
        delete[] bin;
    }
}

//优化：作为Chain类的成员函数
template<class T>
void Chain<T>::BinSort(int range){
    int b;
    ChainNode<T>**bottom,**top;
    bottom=new ChainNode<T>*[range+1];
    top=new ChainNode<T>*[range+1];
    for (b=0;b<=range;b++){
        bottom[b]=0;
    }
    for (;first;first=first->link){
        b=first->data;
        if (bottom[b]){
            top[b]->link=first;
            top[b]=first;
        }
        else{
            bottom[b]=top[b]=first;
        }
    }
    ChainNode<T>*y=0;
    for (b=0;b<=range;b++){
        if (bottom[b]){
            if (y){
                y->link=bottom[b];
            }
            else first=bottom[b];
            y=top[b];
        }    
    }
    if (y){
        y->link=0;
    }
    delete[] bottom;
    delete[] top;
}

/*
ADT 栈(stack)
Data
同线性表，元素具有相同的类型，相邻元素具有前驱和后继关系
Operation
InitStack(*S);
DestoryStack(*S);
ClearStack(*S);
StackEmpty(S);
GetTop(s,*e);
Push(*S,e);
Pop(*S,*e);

endADT
*/
template<class T>
class stack
{
    public:
        virtual ~stack(){
        virtual bool empty() const=0;
        virtual int size() const=0;
        virtual T&top()=0;
        virtual void pop()=0;
        virtual void push(const T&theElement)=0;
        }
};

//使用数组实现1
class arrayStack:public stack<T>{
    private:
         int stackTop;
         int arrayLength;
         T*stack;
    public:
         arrayStack(int initialCapacity=10);
         ~arrayStack(){
            delete[] stack;
         }
         bool empty() const{
            return stackTop==-1;
         }
         int size() const{
            return stackTop+1;
         }
         T&top()；
         void pop();
         void push(const T&theElement);
};

template<class T>
T&arrayStack<T>::top(){
    if (stackTop==-1){
        throw stackEmpty();
        return stack[stacTop];
    }
}

void arrayStack<T>::pop(){
    if (stackTop==-1){
        throw stackEmpty();
        stack[stackTop--].~T();
    }
}

//使用数组实现2
template<class T>
arrayStack<T>::arrayStack(int initialCapacity){
    if(initialCapacity<1){
        ostringstream s;
        s<<"Initial capacity="<<initialCapacity<<"Muat be>0";
        throw illegalParameterValue(s,str());
    }
    arrayLength=initialCapacity;
    stack=new T[arrayLength];
    atckTop=-1;
}
template<calss T>
void arrayStack<T>::push(const T&theElement){
    if (stackTop==arrayLength-1){
        changeLength1D(stack,arrayLength,2*arraylength);
        arrayLength*=2
    }
    stack[++stackTop]=theElement;
}

template<class T>
void changeLength1D(T*&a,int oldLength,int newLength){
    if(newLength<0){
        throw illegalParameter Value("new length must be>=0");
    }
    T*temp=new T[newLength];
    int number=oldLength>newLength?oldLength:newLength;
    copy(a,a+number,temp);
    delete[] a;
    a=temp;
}

//使用继承顺序表实现
template<class T>
class derivedArrayStack:private arrayList<T>,public stack<T>{
    public:
        derivesArrayStack(int initialCapacity=10):arrayLiat<T>(initialCapacity){}
        bool empty() const{
            return arrayList<T>::empty();
        }
        int size() const{
            return arrayList<T>::empty();
        }
        T&top(){
            if (arrayList<T>::empty()){
                throw stackEmpty();
                return get(arrayList<T>::size()-1);
            }
        }

        void pop(){
            if (arrayList<T>::empty()){
                throw stackEmpty();
                erase(arrayList<T>::size()-1);
            }
        }

        void push(const T&theElement){
            insert(arrayList<T>::size(),theElement);
        }
};

//使用链表实现1
class linkedStack:public stcak<T>
{
    private:
        chainNode<T>*stackTop;
        int stackSize;
        linkedStack(int initialCapacity=10){
            stackTop=NULL;
            stackSize=0;
        }
        ~linkedStack();
        bool empty() const{
            return stackSize==0;
        }
        int size() const{
            return stackSize;
        }
        T& top();
        void pop();
        void push(const T&theElement);
};

template<class T>
T&linkedStack<T>::top(){
    if (stackSize==0){
        throw stackEmpty();
        return stackTop->element;
    }
    void linkedStack<T>::push(){
        stackTop=new chainNode<T>(theElement,stackTop);
        stackSzie++;
    }
}

//检测病毒
#include <iostream>
#include <string>
using namespace std;
//检测是否为环状匹配
bool isCircularMatch(const string& virusDNA,const string& patientDNA){
    int viruslen=virusDNA.length();
    int patientlen=patientDNA.length();
    for (int i=0;i<viruslen;++i){
        // 该代码段实现了对字符串 `virusDNA` 进行旋转操作，生成新的字符串 `rotatedVirus`
        // substr(i) 从原病毒 DNA 字符串的第 i 个位置开始截取到末尾，
        // substr(0, i) 从位置 0 开始截取 virusDNA 的子字符串，长度为 i，从位置 0 到 i（不包括 i）
        // 将两个子字符串拼接起来，形成新的字符串 rotatedVirus，实现了将病毒 DNA 循环左移 i 个位置
        string rotatedVirus=virusDNA.substr(i)+virusDNA.substr(0,i);
        for (int j=0;j<=patientlen-viruslen;++j){
            if (patientDNA.substr(j,viruslen)==rotatedVirus){
                return true;
            }
        }
    }
    return false;
}

int main(){
    string virusDNA="baa";
    string patientDNA1="aaabbbba";
    string patientDNA2="babbbba";
    if (isCircularMatch(virusDNA,patientDNA1)){
        cout<<"patient1 infected"<<endl;
    }
    else{
        cout<<"patient1 uninfected"<<endl;
    }

    if(isCircularMatch(virusDNA,patientDNA2)){
        cout<<"patient2 infected"<<endl;
    }
    else cout<<"patient2 uninfected"<<endl;
    return 0;

}

//串的操作运用
string MakeNull();//创建并返回一个空字符串
string result=MakeNull();//初始化一个字符串用于后续操作

bool IsNull(S);//检查给定的字符串是否为空，为空返回true,否则返回false
string input;
if (IsNull(input)){
    cout<<"输入为空，请重新输入。"<<endl;
}

void In(S,a);//将字符串a插入到字符串S中,具体插入位置可能根据函数实现而顶，通常插入到字符串末尾
string str;
char ch='A';
In(str,ch);

int Len(S);//返回字符串S的长度
string str="Hello";
int length=Len(str);
for (int i=0;i<length;i++){
    cout<<str[i]<<endl;
}

void Concat(S1,S2);//将字符串S2连接到字符串S1的末尾，返回连接后的字符串
string path="d:\\desktop\\";
Concat(path,"file.txt");

string Substr(S,m,n);//返回字符串S中从m到n的子串，m和n都是从0开始的索引，m和n都是可选的，如果省略m，则从0开始，如果省略n，则到字符串末尾,如果m>n，则返回空串,
string Substr(S,m);//返回字符串S中从m到末尾的子串，如果m大于字符串长度，则返回空串
string Substr(S);//返回整个字符串S
string date="2025-04-14";
string year=Substr(date,0,4);//提取年份

bool Index(S,S1);//检测S1是否是S的字串，如果是则返回true，则返回false;
string text="测试";
if(Index(text,keyword)){
    cout<<"keyword is in text"<<endl;
}

//串匹配暴力算法
//最坏时间平均复杂度O(mn)，最好情况下的平均时间复杂性为O(m+n)
#include <iostream>
#include <string>
using namespace std;
int bruteForceSearch(const string& text,const string& pattern){
    int n=text.length();
    int m=pattern.length();
    //遍历主串
    for(int i=0;i<=n-m;++i){
        int j;
        for(j=0;j<m;++j){
            if(text[i+j]!=pattern[j]){
                break;//跳出内层的for循环
            }
        }
        //如果模式串全部匹配成功
        if (j==m){
            return i;//返回匹配的起始位置
        }
    }
    //未找到匹配的子串
    return -1;
}

int main(){
    string text="ABABDABACDABABCABAB";
    string pattern="ABABCABAB";

    int index=bruteForceSearch(text,pattern);
    if (index!=-1){
        cout<<"Pattern found at index "<<index<<endl;
    }
    else{
        cout<<"Pattern not found"<<endl;
    }
    return 0;
}


//KMP算法
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//计算部分匹配表(next数组)，lps 是 “Longest Prefix Suffix” 的缩写，意思是 “最长公共前后缀”。
/**
 * @brief 计算模式串的最长前缀后缀数组（LPS数组）
 * 
 * LPS数组用于KMP（Knuth-Morris-Pratt）字符串匹配算法中，
 * 它记录了模式串中每个位置之前的子串的最长相同前缀和后缀的长度。
 * 
 * @param pattern 输入的模式串，即要在主串中查找的子串
 * @param lps 用于存储最长前缀后缀数组的向量，数组长度应与模式串长度相同
 */
void computeLPSArray(const string& pattern, vector<int> lps) {
    // len 用于记录当前已经匹配的最长前缀后缀的长度
    int len = 0;
    // 模式串第一个字符的最长前缀后缀长度为 0
    lps[0] = 0;
    // 从模式串的第二个字符开始遍历
    int i = 1;
    // 遍历模式串，直到处理完所有字符
    while (i < pattern.length()) {
        // 如果当前字符与最长前缀后缀的下一个字符匹配
        if (pattern[i] == pattern[len]) {
            // 最长前缀后缀长度加 1
            len++;
            // 记录当前位置的最长前缀后缀长度
            lps[i] = len;
            // 移动到下一个字符
            i++;
        }
        else {
            // 如果最长前缀后缀长度不为 0
            if (len != 0) {
                // 回溯到前一个位置的最长前缀后缀长度对应的位置
                len = lps[len - 1];
            }
            else {
                // 如果最长前缀后缀长度为 0，当前位置的最长前缀后缀长度为 0
                lps[i] = 0;
                // 移动到下一个字符
                i++;
            }
        }
    }
}

//KMP字符串匹配函数
int KMPSearch(const string& text,const string& pattern){
    int n=text.length();
    int m=pattern.length();
    vector<int> lps(m);

    //计算部分匹配表
    computeLPSArray(pattern,lps);

    int i=0;
    int j=0;
    while(i<n){
        if (pattern[j]==text[i]){
            j++;
            i++;
        }

        if (j==m){
            return i-j;
        }

        else if(i<n && pattern[j]!=text[i]){
            if(j!=0){
                j=lps[j-1];
            }
            else{
                i++;
            }
        }
    }
    return -1;

}

int main(){
    string text="ABABDABACDABABCABAB";
    string pattern="ABABCABAB";

    int index=KMPSearch(text,pattern);
    if (index!=-1){
        cout<<"Pattern found at index "<<index<<endl;
    }
    else{
        cout<<"Pattern not found"<<endl;
    }
    return 0;
}











