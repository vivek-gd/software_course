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