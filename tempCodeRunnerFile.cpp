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