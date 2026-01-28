//14模板
//函数模板的声明
/*
template <class Type…>
返回类型 函数名（参数表）
{
使用Type的函数体
}
或者
template<typename 类型参数>
返回类型 函数名（模板型参表）
{
函数体
}

函数模板的调用形式：
函数名（实参数表）；
*/
#include<iostream>
template<class T>//声明一个函数模板
T max(T x,T y){
    return(x>y)?x:y;
}

int main(){
    std::cout<<max(5,6)<<std::endl;//函数模板实例化
}

#include<iostream>
#include<cstring>
template<class type1,class type2>
void myfunc(type1 x,type2 y){
    cout<<x<<" "<<y<<endl; 
}

//用非模板函数重载函数模板
//声明一个非模板函数的原型
template<class T>
T max(T x,T y){
    return(x>y)?x:y;
}
int max(int,int);//声明一个非模板函数的原型
void func(int i,char c){
    max(i,i);//正确
    max(c,c);
    max(i,c);//正确，调用max(int,int),使用隐式类型转换
    max(c,i);
}
//定义一个完整的非模板函数重载模板函数
char* max(char* x,char* y){
    return(strcmp(x,y)>0)?x:y;
}

//定义一个求幂函数的函数模板
#include<iostream>
using namespace std;
template<class T>
T Power(T a,int exp){
    T ans=a;
    while(--exp>0) ans *=a;
    return ans;
}
int main(){
    cout<<"3^5="<<Power(3,5)<<endl;
    cout<<"1.1^2="<<Power(1.1,2)<<endl;
    return 0;
}

//使用函数模板实现顺序查找算法
#include<iostream>
using namespace std;
template<class T>
int sequentialsearch(T a[],const T&k,int n){
    int i=0;
    while(k!=a[i]&&i<=n-1) i++;
    if(i>n-1) i=-1;
    return i;
}
int main(){
    int i1[]={3,2,5,0,-1,7};
    double d1[]={3.3,2.1,0.3,1.5,10.6,5.2};
    char* c1="xjtu";
    cout<<sequentialsearch(i1,15,6)<<endl;
    cout<<sequentialsearch(d1,3.3,5)<<endl;
    cout<<sequentialsearch(c1,'j',4)<<endl;
    return 0;
}

//类模板
/*
template<class T>
class ClassName{
    //类定义
}

template<typename Type>
class ClassName{
//具体内容
};

调用形式：
ClassName<类型实参表> object；

类模板：
template<class T>
class Stack
{
数据成员；
成员函数；
};
直接使用： 声明对象
Stack<char> st;
*/
#include<iostream>
using namespace std;
template<class Type>
class Stack{
        Type data[100];
        int top;
    public:
        Stack();
        void push(Type e);
        Type pop();
};

template<class Type>
Stack<Type>::Stack(){
    top=0;
}
template<class Type>
void Stack<Type>::push(Type e){
    data[top++]=e;

}

template<class Type>
Type Stack<Type>::pop(){
    return data[--top];
} 

int main(){
    Stack<char>s1;//模板类Stack<char>
    Stack<int>s2;//模板类Stack<int>
    s1.push('a');
    s2.push(56);
    s2.push(89);
    cout<<s1.pop()<<endl;
    cout<<s2.pop()<<endl;
}

#include<iostream>
using namespace std;
template<class T1,class T2>
class myclass{
        T1 i;
        T2 j;
    public:
        myclass(T1 a,T2 b){
            i=a;
            j=b;
        }
        void show(){cout<<"i="<<i<<" j="<<j<<endl;}
};

int main(){
    myclass<int ,double>ob1(12,0.15);
    myclass<char,char*>ob2('x',"This is a test");
    ob1.show();
    ob2.show();
    return 0;
}

//栈类模板
#include<iostream>
using namespace std;
template<class T>
class stack{
    private:
        T stck[100];
        int tos;
    public:
        stack(){tos=0;}
        void push(T ch);
        T pop();
};

//压栈实现
template<class T>
void stack<T>::push(T ch){
    if(tos==100-1){
        cout<<"stack is full\n";
        return;
    }
    stck[tos]=ch;
    tos++;
}

//出栈实现
template<class T>
T stack<T>::pop(){
    if(tos==0){
        cout<<"stack is empty\n";
        return 0;
    }
    tos--;
    return stck[tos];
}

int main(){
    stack<char>s1,s2;
    int i;
    s1.push('a');
    s2.push('x');
    cout<<"pop s1:"<<s1.pop()<<endl;
    cout<<"pop s2:"<<s2.pop()<<endl;
    return 1;
}

//定义通用数组类
#include<iostream>
//using namespace std;
template<class X>
class array{
    public:
        X* ptr;
        array(int N){
            ptr=new X[N];
        }
};
int main(){
    array<int> a(16);
    a.ptr[0]=168;
    std::cout<<"array class: "<<a.ptr[0]<<std::endl;
    return 0;
}

#include<iostream>
#include<stdlib.h>
using namespace std;
template<class SType>
class Stack{
    public:
        Stack(int size);
        ~Stack(){
            delete[] s;
        }
        void push(SType i);
        SType pop();
    private:
        int tos,length;
        SType* s;

};
template<class SType>
Stack<SType>::Stack(int size){
    s=new SType[size];
    if(!s)//如果内存分配不成功
    {
        cout<<"can't allocate stack."<<endl;
    }
    length=size;
    tos=0;
}
template<class SType>
void Stack<SType>::push(SType i){
    if(tos==length){
        cout<<"stack is full"<<endl;
    }
    s[tos]=i;
    tos++;
}
template<class SType>
SType Stack<SType>::pop(){
    if(tos==0){
        cout<<"stack overflow."<<endl;
    }
    tos--;
    return s[tos];
}

int main(){
    Stack<int>a(10);
    Stack<double>b(10);
    Stack<char>c(10);
    a.push(45);
    b.push(100-0.7);
    b.push(10);
    a.push(8+6);
    b.push(2*1.5);
    cout<<a.pop()<<endl;
    cout<<b.pop();
}