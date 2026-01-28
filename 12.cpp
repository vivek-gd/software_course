//运算符重载

//函数实现
#include <iostream>
using namespace std;
class Complex{
    public:
        Complex(){
            real=0;imag=0;
        }
        Complex(double r,double i){//构造函数重载
            real=r;imag=i;
        }
        Complex complex_add(Complex &c0);
        void display();
    private:
        double real;
        double imag;
};

Complex Complex::complex_add(Complex &c0){
    Complex c;
    c.real=real+c0.real;
    c.imag=imag+c0.imag;
    return c;
}

void Complex::display(){
    cout<<"("<<real<<","<<imag<<"i)"<<endl;
}

int main(){
    Complex c1(3,4),c2(5,-10),c3;
    c3=c1.complex_add(c2);
    cout<<"c1=";
    c1.display();
    cout<<"c2=";
    c2.display();
    cout<<"c1+c2=";
    c3.display();
}

//运算符重载
/*
函数类型 operator 运算符名称 (形参表列)
{ 对运算符的重载处理 }

运算符重载为类的成员函数的一般格式为：
<类型> <类名>:: operator <要重载的运算符>（
形参表）
{
函数体
}

运算符重载为类的友元函数的一般语法：
friend <函数类型> operator <运算符>(形参表)
{
函数体；
}
 */

 //复数加减运算符重载
 #include <iostream>
 using namespace std;
 class Complex{
    private:
        float real,imag;
    public:
        Complex(float r=0,float i=0);
        Complex Add(const Complex &c);
        Complex operator+(const Complex &c);
        Complex operator-(const Complex &c);
        Complex& operator+=(const Complex&c);//复合赋值操作符必须返回左操作数的引用
        Complex& operator=(const Complex&other);
        void Show(int i);
 };
 Complex::Complex(float r,float i){
    real=r;imag=i;
 }
 void Complex::Show(int i){
    cout<<"复数：c"<<i<<"="<<real;
    if (imag>0)
    {
       cout<<"+"<<imag<<"i"<<endl;
    }
    if(imag<0){
        cout<<imag<<"i"<<endl;
    }
 }

 Complex Complex::Add(const Complex&c){
    Complex temp;
    temp.real=real+c.real;
    temp.imag=imag+c.imag;
    return temp;
 }

 Complex Complex::operator+(const Complex&c){
    Complex temp;
    temp.real=real+c.real;
    temp.imag=imag+c.imag;
    return temp;
 }

 Complex Complex::operator-(const Complex&c){
    Complex temp;
    temp.real=real-c.real;
    temp.imag=imag-c.imag;
    return temp;
 }

 Complex& Complex::operator+=(const Complex&c){
    real+=c.real;
    imag+=c.imag;
    return *this;
 }

 Complex& Complex::operator=(const Complex&other){
     if(this==&other)
         return *this;
     real=other.real;
     imag=other.imag;
     return *this;
 }

 int main(){
    Complex c1(12,35),c2(20,46),c3,c4,c5,c6;
    c1.Show(1);
    c2.Show(2);
    c3=c1.Add(c2);
    c3.Show(3);
    c4=c1+c2;
    c4.Show(4);
    c2+=c1;
    c2.Show(2);
    c5=c1-c2;
    c5.Show(5);
    return 0;
 }

 #include<iostream>
 using namespace std;
 class String{
    public:
        String(){
            p=NULL;
        }
        String( char *str);
        void display();
    private:
        char *p;
 };
 String::String(char *str){
    p=str;
 }
 void String::display(){
     cout<<p;
 }

 int main(){
    String string1("Hello"),string2("Book");
    string1.display();
    cout<<endl;
    string2.display();
    return 0;
 }

 #include<iostream>
 #include<cstring>
 using namespace std;
 class String{
    public:
        String(){           
        }
        String(string str);
        friend bool operator>(String &string1,String &string2);
        friend bool operator<(String &string1,String &string2);
        friend bool operator==(String &string1,String &string2);
        void display();
    private:
        string p;
 };
 String::String(string str){
    p=str;
 }
 void String::display(){
    cout<<p;
 }
 bool operator>(String&string1,String&string2){
    if(string1.p>string2.p)
        return true;
    else return false;
 }

 bool operator<(String&string1,String&string2){
    if(string1.p<string2.p)
        return true;
    else return false;
 }
 bool operator==(String&string1,String&string2){
    if(string1.p==string2.p)
        return true;
    else return false;
 }

 int main(){
    String string1("Hello"),string2("Book"),string3("Computer");
    cout<<(string1>string2)<<endl;
    cout<<(string1<string3)<<endl;
    cout<<(string1==string2)<<endl;
    return 0;
 }

 #include<iostream>
 #include<cstring>
 using namespace std;
 class String{
    public:
        String(){
        }
        String(string str);
        friend bool operator>(String&string1,String&string2);
        friend bool operator<(String&string1,String&string2);
        friend bool operator==(String&string1,String&string2);

        void display();
    private:
        string p;
 };
 String::String(string str){
    p=str;
 }
 void String::display(){
     cout<<p;
 }
 bool operator>(String&string1,String&string2){
    if(string1.p>string2.p)
        return true;
    else return false;
 }

 bool operator<(String&string1,String&string2){
    if(string1.p<string2.p)
        return true;
    else return false;
 }

 bool operator==(String&string1,String&string2){
    if(string1.p==string2.p)
        return true;
    else return false;
 }

 void compare(String&string1,String&string2){
    if(operator>(string1,string2)==1){
        string1.display();
        cout<<">";
        string2.display();
        cout<<endl;
    }
    else if(operator<(string1,string2)==1){
        string1.display();
        cout<<"<";
        string2.display();
        cout<<endl;
    }
    else if(operator==(string1,string2)==1){
        string1.display();
        cout<<"==";
        string2.display();
        cout<<endl;
    }
 }

 int main(){
    String string1("Hello"),string2("Book"),string3("Computer"),string4("Hello");
    compare(string1,string2);
    compare(string2,string3);
    compare(string1,string4);
    return 0;
 }
 
 //比较运算符和赋值运算符重载
 #include<iostream>
 using namespace std;
 class point{
    private:
        float x,y;
    public:
        point(float a=0,float b=0){x=a;y=b;}
        point(point&);//拷贝构造函数
        ~point(){}
        bool operator==(point);
        bool operator!=(point);
        point operator+=(point);
        point operator-=(point);
        float get_x(){return x;}
        float get_y(){return y;}
 };
 point::point(point&p){
    x=p.x;
    y=p.y;
 }
 bool point::operator==(point p){
    if(x==p.get_x()&&y==p.get_y()) return 1;
    else return 0;
 }
 bool point::operator!=(point p){
    if(x!=p.get_x()&&y!=p.get_y()) return 1;
    else return 0;
 }
 point point::operator+=(point p){
    x+=p.get_x();
    y+=p.get_y();
    return *this;
 }
 point point::operator-=(point p){
    x-=p.get_x();
    y-=p.get_y();
    return *this;
 }
 int main(){
    point p1(1,2),p2(3,4),p3(5,6);
    cout<<"p1==p2?"<<(p1==p2)<<endl;
    cout<<"p1!=p2?"<<(p1!=p2)<<endl;
    p3+=p1;
    cout<<"p3+=p1,p3:"<<p3.get_x()<<","<<p3.get_y()<<endl;
    p3-=p1;
    cout<<"p-=p1,p3:"<<p3.get_x()<<","<<p3.get_y()<<endl;
 }

//下标运算符重载
#include<iostream>
#include<cstring>
using namespace std;
class word{
   private:
      string str;
   public:
       word(string s){
         str=s;
       }
       char& operator[](int i) {
         //if (i < 0 || i >= str.size()) throw std::out_of_range("Invalid index");
         return str[i];
     }
       void display(){
         cout<<str<<endl;
      }
};

int main(){
   string s="china";
   word w(s);
   w.display();
   int n=s.length();
   while(n>0){
      w[n-1]=w[n-1]-32;
      n--;
   }
   w.display();
}

#include<iostream>
#include<malloc.h>
using namespace std;
class rect{
   private:
       int length,width;
   public:
       rect(int l,int w){
         length=l;
         width=w;
       }
       void *operator new(size_t size){
         return malloc(size);
       }
       void operator delete(void*p){
         free(p);
       }
       void display(){
          cout<<"area: "<<length*width<<endl;
       }

};
int main(){
   rect *p;
   p=new rect(5,9);
   p->display();
   delete p;
}

//重载转换运算符
#include<iostream>
using namespace std;
class RMB{
   public:
       RMB(double value=0.0){
         yuan=value;
         fen=(value-yuan)*100+0.5;//实现四舍五入
       }
       void ShowRMB(){
         cout<<yuan<<"元"<<fen<<"分"<<endl;
       }
       operator double(){
         return yuan+fen/100.0;
       }
   private:
       int yuan,fen;
};
int main(){
   RMB r1(1.01),r2(2.20),r3;
   r3=RMB((double)r1+(double)r2);
   r3=r1+2.40;
   r3.ShowRMB();
   r3=2.0-r1;
   r3.ShowRMB();
}

