/*
例5.0 先建立一个Point(点)类，包含数据成员x,y(坐标
点)。以它为基类，派生出一个Circle(圆)类，增加数据
成员r(半径)，再以Circle类为直接基类，派生出一个
Cylinder(圆柱体)类，再增加数据成员h(高)。要求编写
程序，重载运算符“<<”和“>>”
，使之能用于输出
以上类对象。
*/
#include <iostream>
using namespace std;
//声明point类
class Point{
    public:
        Point(float x=0,float y=0);
        void setPoint(float x,float y);
        float getX() const{return x;}
        float getY() const{return y;}
        friend ostream& operator<<(ostream &out,const Point &);
    protected:
        float x,y;
};

Point::Point(float a,float b){
    x=a;
    y=b;
}

void Point::setPoint(float a,float b){
    x=a;
    y=b;
}

ostream& operator<<(ostream &output,const Point &p){
    output<<"["<<p.x<<","<<p.y<<"]"<<endl;
    return output;
}

// int main(){
//     Point p(3.5,6.4);
//     cout<<"x="<<p.getX()<<",y="<<p.getY()<<endl;
//     p.setPoint(8.5,6.8);
//     cout<<"p(new):"<<p<<endl;
// }

//声明派生Circle类
class Circle:public Point{
    public:
        Circle(float x=0,float y=0,float r=0);
        void setRadius(float r);
        float getRadius() const;
        float area() const;
        friend ostream& operator<<(ostream &output,const Circle &);
    protected:
        float radius;
};

Circle::Circle(float a,float b,float r):Point(a,b),radius(r){}
void Circle::setRadius(float r){
    radius=r;
}
float Circle::getRadius() const{
    return radius;
}
float Circle::area() const{
    return 3.14*radius*radius;
}
ostream& operator<<(ostream &output,const Circle &c){
    output<<"Center=["<<c.x<<","<<c.y<<"],r="<<c.radius<<",area="<<c.area()<<endl;
    return output;
    
}

// int main(){
//     Circle c(3.5,6.4,5.2);
//     cout<<"original circle:\nx="<<c.getX()<<",y="<<c.getY()<<",r="<<c.getRadius()<<",area="<<c.area()<<endl;
//     c.setRadius(7.5);
//     c.setPoint(5,5);
//     cout<<"new circle:\n"<<c;
//     Point &pRef=c;
//     Point&pref=c;
//     cout<<"pRef:"<<pRef<<endl;
//     return 0;

// }

//声明Circle的派生类Cylinder
class Cylinder:public Circle{
    public:
        Cylinder(float x=0,float y=0,float r=0,float h=0);
        void setHeight(float h);
        float getHeight() const;
        float area() const;
        float volume() const;
        friend ostream& operator<<(ostream&,const Cylinder&);
    protected:
        float height;
};
Cylinder::Cylinder(float a,float b,float r,float h):Circle(a,b,r),height(h){}
void Cylinder::setHeight(float h){
    height=h;
}
float Cylinder::getHeight() const{
    return height; 
}
float Cylinder::area() const{
    return 2*Circle::area()+2*3.14*radius*height;
}
float Cylinder::volume() const{
    return Circle::area()*height;
}
ostream& operator<<(ostream &output,const Cylinder &cy){
    output<<"Center=["<<cy.x<<","<<cy.y<<"],r="<<cy.radius<<",h="<<cy.height<<",area="<<cy.area()<<",volume="<<cy.volume()<<endl;
    return output;
}

int main(){
    Cylinder c(3.5,6.4,5.2,10);
    cout<<"original cylinder:\nx="<<c.getX()<<",y="<<c.getY()<<",r="<<c.getRadius()<<",h="<<c.getHeight()<<",area="<<c.area()<<",volume="<<c.volume()<<endl;
    c.setHeight(15);
    c.setPoint(5,5);
    c.setRadius(7.5);
    cout<<"new cylinder:\n"<<c;
    Point &pRef=c;
    cout<<"pRef:"<<pRef<<endl;
    Circle& cRef=c;
    cout<<"cRef:"<<cRef<<endl;
    return 0;
}

//虚函数
/*
virtual<类型说明符><函数名>(<参数表>)

*/

#include <iostream>
using namespace std;
class A{
    public:
        void show(){
            cout<<"A";
        }
};

class B:public A{
    public:
        void show(){
            cout<<"B";
        }
};

int main(){
    A a,*pc;
    B b;
    pc=&a;
    pc->show();
    pc=&b;
    pc->show();
    return 0;
}

//虚函数的使用
#include<iostream>
using namespace std;
class Base{
    public:
        Base(int x,int y){
            a=x;
            b=y;
        }
        virtual void show(){
            cout<<"Base-----\n";
            cout<<a<<" "<<b<<endl;
        }       
    private:
        int a,b;
};
class Derived:public Base{
    public:
        Derived(int x,int y,int z):Base(x,y){
            c=z;
        }
        void show(){
            cout<<"Derived-----\n"<<c<<endl;
        }
    private:
        int c;
};

int main(){
    Base mb(60,60),*pc;
    Derived mc(10,20,30);
    pc=&mb;
    pc->show();
    pc=&mc;
    pc->show();
}

//虚函数定义
#include<iostream>
using namespace std;
class Grandam{
    public:
        virtual void introduce_self(){
            cout<<"I am grandam."<<endl;
        }  
};
class Mother:public Grandam{
    public:
        void introduce_self(){
            cout<<"I am mother."<<endl;
        }
};

class Daughter:public Mother{
    public:
        void introduce_self(){
            cout<<"I am daughter."<<endl;
        }
};

int main(){
    Grandam *ptr;
    Grandam g;
    Mother m;
    Daughter d;
    ptr=&g;
    ptr->introduce_self();
    ptr=&m;
    ptr->introduce_self();
    ptr=&d;
    ptr->introduce_self();
}

#include<iostream>
#include<cstring>
using namespace std;
class Student{
    public:
        Student(int,string,float);
        virtual void display();
    protected:
        int num;
        string name;
        float score;
};

Student::Student(int n,string s,float f):num(n),name(s),score(f){}
void Student::display(){
    cout<<"num:"<<num<<endl;
    cout<<"name:"<<name<<endl;
    cout<<"score:"<<score<<endl;
}
//声明公用派生类Graduate
class Graduate:public Student{
    public:
        Graduate(int,string,float,float);
        void display();
    private:
        float pay;
};
void Graduate::display(){
    cout<<"num:"<<num<<endl<<"score:"<<score<<endl<<"pay:"<<pay<<endl;
}
Graduate::Graduate(int n,string nam,float s,float p):Student(n,nam,s),pay(p){}

int main(){
    Student stud1(1001,"Li",87.5);
    Graduate grad1(2001,"Wang",92.5,680.5);
    Student* pt=&stud1;
    pt->display();
    pt=&grad1;
    pt->display();
    return 0;
}

//析构虚函数 Virtual ~类名（）；
#include<iostream>
using namespace std;
class Grandam{
    public:
        Grandam(){}
       virtual ~Grandam(){
            cout<<"This isGrandam::~Grandam()."<<endl;
        }
};

class Mother:public Grandam{
    public:
        Mother(){}
        ~Mother(){
            cout<<"This is Mother::~Mother()."<<endl;
        }
};
int main(){
    Grandam *f;
    f=new Mother;
    delete f;
}


//虚函数与重载函数比较
#include<iostream>
using namespace std;
class Base{
    public:
        virtual void func1();
        virtual void func2();
        virtual void func3();
        void func4();
};
class Derived:public Base{
    public:
        virtual void func1();
        void func2(int x);
        void func3();
        void func4();
};
void Base::func1(){
    cout<<"--Base func1--\n";
}
void Base::func2(){
    cout<<"--Base func2--\n";
}
void Base::func3(){
    cout<<"--Base func3--\n";
}
void Base::func4(){
    cout<<"--Base func4--\n";
}

void Derived::func1(){
    cout<<"--Derived func1--\n";
}
void Derived::func2(int x){
    cout<<"--Derived func2--\n";
}
void Derived::func3(){
    cout<<"--Derived func3--\n";
}
void Derived::func4(){
    cout<<"--Derived func4--\n";
}

int main(){
    Base d1,*bp;
    Derived d2;
    bp=&d2;
    bp->func1();
    bp->func2();
    bp->func4();
}

//多继承与虚函数
#include<iostream>
using namespace std;
class Base1{
    public:
        virtual void fun(){
            cout<<"--Base1--\n";
        }
};
class Base2{
    public:
        void fun(){
            cout<<"--Base2--\n";
        }
};
class Derived:public Base1,public Base2{
    public:
        void fun(){
            cout<<"--Derived--\n";
        }
};

int main(){
    Base1 obj1,*ptr1;
    Base2 obj2,*ptr2;
    Derived obj3;
    ptr1=&obj1;
    ptr1->fun();
    ptr2=&obj2;
    ptr2->fun();
    ptr1=&obj3;
    ptr1->fun();
    ptr2=&obj3;
    ptr2->fun();

}

//计算三角形、矩形和圆的面积
#include<iostream>
using namespace std;
class Figure{
    public:
        Figure(double a,double b){
            x=a;
            y=b;
        }
        virtual void show_area(){
            cout<<"No area computation defined ";
            cout<<"for this class.\n";
        }
    protected:
        double x,y;
};

class Triangle:public Figure{
    public:
        Triangle(double a,double b):Figure(a,b){}
        void show_area(){
            cout<<"Triangle with height:"<<x;
            cout<<"and base"<<y<<"has an area of ";
            cout<<x*y*0.5<<endl;
        }
};

class Square:public Figure{
    public:
        Square(double a,double b):Figure(a,b){}
        void show_area(){
            cout<<"Square with dimension"<<x;
            cout<<"*"<<y<<"has an area of ";
            cout<<x*y<<endl;
        }
};

class Circle:public Figure{
    public:
        Circle(double a):Figure(a,a){}
        void show_area(){
            cout<<"Circle with radius "<<x;
            cout<<"has an area of ";
            cout<<3.14*x*x<<endl;
        }
};

int main(){
    Figure *p;
    Triangle t(10.0,6.0);
    Square s(10.0,6.0);
    Circle c(10.0);
    p=&t;
    p->show_area();
    p=&s;
    p->show_area();
    p=&c;
    p->show_area();
    return 0;
}

#include<iostream>
using namespace std;
class Polygon{
    protected:
        int width,height;
    public:
        void set_values(int a,int b){
            width=a;
            height=b;
        }
        virtual int area(){return 0;}
};

class Rectangle:public Polygon{
    public:
        int area(){
            return width*height;
        }
};
class Triangle:public Polygon{
    public:
        int area(){
            return width*height/2;
        }
};

int main(){
    Rectangle rect;
    Triangle trgl;
    Polygon poly;
    Polygon *ppoly1=&rect;
    Polygon *ppoly2=&trgl;
    Polygon *ppoly3=&poly;
    ppoly1->set_values(4,5);
    ppoly2->set_values(4,5);
    ppoly3->set_values(4,5);
    cout<<ppoly1->area()<<endl;
    cout<<ppoly2->area()<<endl;
    cout<<ppoly3->area()<<endl;
    return 0;
}

//纯虚函数和抽象类 virtual <函数类型> <函数名> ( 参数表 ) = 0;

#include<iostream>
using namespace std;
class Circle{
    public:
        void setr(int x){
            r=x;
        }
        virtual void show()=0;
    protected:
        int r;
};

class Area:public Circle{
    public:
        void show(){
            cout<<"Area is "<<3.14*r*r<<endl;
        }
};
class Perimeter:public Circle{
    public:
        void show(){
            cout<<"Perimeter is "<<2*3.14*r<<endl;
        }
};
int main(){
    Circle* ptr;
    Area ob1;
    Perimeter ob2;
    ob1.setr(10);
    ob2.setr(10);
    ptr=&ob1;
    ptr->show();
    ptr=&ob2;
    ptr->show();
}

/*
如果一个类至少有一个纯虚函数，那么就称该
类为抽象类。
*/
#include<iostream>
using namespace std;
const double PI=3.14159;
class Shapes{
    protected:
        int x,y;
    public:
        void setvalue(int a,int b=0){
            x=a;
            y=b;
        }
        virtual void display()=0;
};

class Rectangle:public Shapes{
    public:
        void display(){
            cout<<"The area of rectangle is: "<<x*y<<endl;
        }
};

class Circle:public Shapes{
    public:
        void display(){
            cout<<"The area of circle is: "<<PI*x*x<<endl;
        }
};

int main(){
    Shapes *ptr[2];
    Rectangle rect;
    Circle cir;
    ptr[0]=&rect;
    ptr[1]=&cir;
    ptr[0]->setvalue(5,8);
    ptr[1]->setvalue(10);
    ptr[0]->display();
    ptr[1]->display();
}

#include<iostream>
using namespace std;
class A{
    public:
        virtual void f(){
            cout<<"A f"<<endl;
        }
};
class B:public A{
    public:
        void f(){
            cout<<"B f"<<endl;
        }
};
class C:public B{
    public:
        void f(){
            cout<<"C f"<<endl;
        }
};

int main(){
    A a;
    B b;
    C c;
    A *p;
    a.f();
    b.f();
    c.f();
    p=&a;
    p->f();
    p=&b;
    p->f();
    p=&c;
    p->f();
}

#include<iostream>
#include<cstring>
using namespace std;
class Person{
    public:
        Person(){
            setinfo(1,"jetty",'M',"china");
        }
        void setinfo(int n,string strname,char s,string strfrom){
            id=n;
            name=strname;
            sex=s;
            from=strfrom;
        }
        
        virtual void showinfo(){
            cout<<endl<<"ID: "<<id<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Sex: "<<sex<<endl;
            cout<<"From: "<<from<<endl;
        }
    protected:
        int id;
        string name;
        char sex;
        string from;
};

class UnderGraduate:virtual public Person{
    public:
        UnderGraduate(){
            setinfo(1,"jetty",'M',"china",90);
        }
        void setinfo(int n,string strname,char s,string strfrom,float sc){
            Person::setinfo(n,strname,s,strfrom);
            score=sc;
        }
        void showinfo(){
            Person::showinfo();
            cout<<"\nScore: "<<score<<endl;
        }
    protected:
        float score;
};

class Graduate:public UnderGraduate{
    public:
        Graduate(){
            setinfo(1,"jetty",'M',"china",90,1000);
        }
        void setinfo(int n,string strname,char s,string strfrom,float sc,float sa){
            id=n;
            name=strname;
            sex=s;
            from=strfrom;
            score=sc;
            salary=sa;
        }
       void showinfo(){
            cout<<endl<<"ID: "<<id<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Sex: "<<sex<<endl;
            cout<<"From: "<<from<<endl;
            cout<<"Score: "<<score<<endl;
            cout<<"Salary: "<<salary<<endl;
        }
    protected:
        float salary;
};

int main(){
    Person *pp;
    Person p;
    pp=&p;
    UnderGraduate u;
    pp=&u;
    pp->showinfo();
    Person t;
    pp=&t;
    pp->showinfo();
    Graduate g;
    pp=&g;
    pp->showinfo();
}        

#include<iostream>
using namespace std;
class base{
    public:
        virtual ~base(){
            cout<<endl<<"base deatructor";
        }
};
class derived:public base{
    public:
        ~derived(){
            cout<<endl<<"derived deatructor";
        }
};
int main(){
    base *p=new derived;
    delete p;
}


