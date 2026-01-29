
// 线性递归，数组球求和
int sum(int A[], int n)
{
    if (n < 1)
    {
        return 0;
    }
    else
        return sum(A, n - 1) + A[n - 1]; // 递归前n-1个元素之和，加上第n个元素
}

void reverse(int *, int, int); // 重载的倒置算法
void reverse(int *A, int n)    // 数组倒置
{
    reverse(A, 0, n - 1);
} // 由重载的入口启动递归或迭代算法

// 对首末元素进行倒置，然后递归地倒置除这两个元素以外的部分，时间复杂度O(n)
void reverse(int *A, int lo, int hi)
{
    if (lo < hi)
    {
        swap(A[lo], A[hi]);
        reverse(A, io + 1, hi - 1); // 递归倒置
    }
}

// 实现幂函数的多向递归版本,O(logn)
inline __int64 sqr(__int64 a) { return a * a; } //__int64代表64位有符号整数。在标准C++里，可使用 <cstdint> 头文件中的 int64_t 类型
__int64 power2(int n)
{
    if (n == 0)
        return 1;
    return (n & 1) ? sqr(power2(n >> 1)) << sqr(power2(n >> 1)); // 如果 n 是奇数（n&1 结果为 1），则返回 2 * sqr(power2(n>>1))，相当于在偶数次幂的基础上再乘 2；如果 n 是偶数（n&1 结果为 0），则直接返回 sqr(power2(n>>1))。
}

// 属于尾递归的算法均可以简洁地转换为等效的迭代版本
void reverse(int *A, int lo, int hi)
{
next: // 算法起始位置添加跳转标志
    if (lo < hi)
    {
        swap(A[lo], A[hi]);
        lo++;
        hi--;      // 收缩待倒置区间
        goto next; // 跳转至标志位置
    } // else隐含了迭代的终止
}
// 使用的goto语句有悖于结构化程序设计的原则
void reverse(int *A, int lo, int hi)
{
    while (lo < hi)             // 使用while替换跳转标志和if，完全等效
        swap(A[lo++], A[hi--];) // 交换A[lo]和A[hi]，收缩待倒置区间
}

// 数组求和，空间O(logn)
int sum(int A[], int lo, int hi)
{
    if (lo == hi)
        return A[lo];
    else
    {
        int mi = (lo + hi) >> 1;                    // 以居中单元为界，将原区间一分为二
        return sum(A, lo, mi) + sum(A, mi + 1, hi); // 递归地求和两个子区间
    }
}

// Fibonacci数列，二分递归,算法需要运行O(2^n)时间
__int64 fib(int n)
{
    return (n < 2) ? (__int64)n : fib(n - 1) + fib(n - 2); //(__int64)n类型转换，在标准 C++ 中建议使用 <cstdint> 头文件里的 int64_t 类型
}

// 通过线性递归计算Fibonacci数
#include <cstdint>
int64_t fib(int n, int64_t &prev)
{
    if (0 == n)
    {
        prev = 1;
        return 0; // 直接取值:fib(-1) = 1, fib(0) = 0
    }
    else
    {
        int64_t prevPrev;
        prev = fib(n - 1, prevPrev); // 递归计算前两项
        return prevPrev + prev;      // 其和即为正解
    }
}

// 动态规划策略,时间复杂度为O(n),仅需常数规模的附加空间
#include <cstdint>
int64_t fibI(int n)
{
    int64_t f = 0, g = 1;
    while (0 < n--)
    {
        g += f;
        f = g - f;
    }
    return f;
}

//向量对象支持如下操作接口
size() // 返回向量元素个数
get(r) // 返回向量第r个元素
put(r,e)// 用e替换向量第r个元素
insert(r,e)// 在向量第r个元素之前插入e，原后继元素依次后移
remove(r)//删除秩为r的元素，原前驱元素依次前移
disordered() // 判断向量是否已按非降序排序
sort()//调整各元素位置，使之按非降序排列
find(e)//查找等于e且秩最大的元素
search(e)//查找目标元素e，返回不大于e且秩最大的元素
deduplicate()//删除重复元素
uniquify()//删除所有重复元素
traverse()//遍历，对每个元素执行某操作

//vector模板类
typedef int Rank;
#define DEFAULT_CAPACITY 3 // 默认初始容量（实际应用中可设置为更大）

template <typename T>class Vector{//向量模板类
    protected:
        Rank _size;int _capacity;T* _elem;//规模、容量和数据区
        void copyFrom(T const* A,Rank lo,Rank hi);//复制数组区间A[lo,hi)
        void expand();//空间不足时扩容
        void shrink();//装填因子过小时压缩
        bool bubble(Rank lo,Rank hi);//扫描交换
        void bubbleSort(Rank lo,Rank hi);//气泡排序算法
        Rank max(Rank lo,Rank hi);//选取最大元素
        void selectionSort(Rank lo,Rank hi);//选取排序算法
        void merge(Rank lo,Rank mi,Rank hi);//归并算法
        void mergeSort(Rank lo,Rank hi);//归并排序算法
        Rank partition(Rank lo,Rank hi);//轴点构造算法
        void quickSort(Rank lo,Rank hi);//快速排序算法
        void heapSort(Rank lo,Rank hi);//快速排序算法
        void heapSort(Rank lo,Rank hi);//堆排序
    public:
        // 构造函数
        Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)//容量为c，规模为s，所有元素初始为v
        {
            _elem=new T[_capacity=c];
            for(_size=0;_size<s;_elem[_size++]=v)；
        }//s<=c
        Vector(T const* A,Rank n){copyFrom(A,0,n);}//数组整体复制
        Vector(T const* A,Rank lo,Rank hi){copyFrom(A,lo,hi);}//区间
        Vector(Vector<T>const& V){copyFrom(V._elem,0,V._size);}//向量整体复制
        Vector(Vector<T>const& V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi);}//区间
        // 析构函数
        ~Vector(){delete[]_elem;}//释放内部空间
        // 只读访问接口
        Rank size()const{return _size;}//规模
        bool empty()const{return !_size;}//判空
        int disordered()const;//判断向量是否已排序
        Rank find(T const& e)const{return find(e,0,_size);}//无序向量整体查找
        Rank find(T const& e,Rank lo,Rank hi)const;//无序向量区间查找
        Rank search(T const& e)const//有序向量整体查找
        {return (0>=_size)?-1:search(e,0,_size);}
        Rank search(T const& e,Rank lo,Rank hi)const;//有序向量区间查找
        // 可写访问接口
        T& operator[](Rank r)const;//重载下标操作符，可以类似于数组形式引用各元素
        Vector<T>& operator=(Vector<T>const&);//重载赋值操作符，以便直接克隆向量
        T remove(Rank r);//删除秩为r的元素
        int remove(Rank lo,Rank hi);//删除秩在区间[lo,hi)之内的元素
        Rank insert(Rank r,T const& e);//插入元素
        Rank insert(T const& e){return insert(_size,e);}//默认插入到向量尾部
        void sort(Rank lo,Rank hi);//对区间[lo,hi)的元素排序
        void sort(){sort(0,_size);}//整体排序
        void unsort(Rank lo,Rank hi);//打乱区间[lo,hi)内元素的次序
        void unsort(){unsort(0,_size);}//整体打乱
        int deduplicate();//无序去重
        int uniquify();//有序去重
        // 遍历
        void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部性修改）
        template <typename VST>void traverse(VST&);//遍历（使用函数对象，可全局性修改）

}

template <typename T> T& Vector<T>::operator[](Rank r) const//重载下标操作符
{return _elem[r];}

//向量整体置乱算法,借助重载的操作符“[]”,通过秩间接地访问向量的元素。
template <typename T>void permute(Vector<T>& V){
    for(int i=V.size();i>0;i--)//自后向前
        swap(V[i-1],V[rand()%i]);//V[i-1]与V[0,i]中某一随机元素交换
}

//向量区间置乱接口,通过下标,直接访问内部数组的元素
template <typename>void Vector<T>::unsort(Rank lo,Rank hi){
    T* V=_elem+lo;//将子向量_elem[lo,hi)视作另一向量V[0,hi-lo)
    for(Rank i=hi-lo;i>0;i--)//自后向前
        swap(V[i-1],V[rand()%i]);//将V[i-1]与V[0,i-1]中某一随机元素交换

}


//无序向量元素查找接口
template <typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi)const{
    while((lo<hi--)&(e!=_elem[hi]));//逆向查找
    return hi;//若hi<lo说明失败，否则hi即命中元素的秩
}


//向量区间删除接口
template<typename T>int Vector<T>::remove(Rank lo,Rank hi){
    if(lo==hi) return 0;
    while(hi<--_size) _elem[lo++]=_elem[hi++];//[hi, _size)顺次前秱hi - lo个单元,自前向后覆盖
    _size=lo;//更新觃模,直接丢弃尾部[lo, _size = hi)匙间
    shrink();//装填因子过小时压缩向量所占空间
    return hi-lo;//返回被删除元素的个数
}

//向量元素单删除接口
template <typename T>T Vector<T>::remove(Rank r){
    T e=_elem[r];//备份被删除元素
    remove(r,r+1);
    return e;//返回被删除元素
}

//无序向量清除重复元素接口
template<typename T>int Vector<T>::deduplicate(){
    int oldSize=_size;
    Rank i=1;
    while(i<_size)
        (find(_elem[i],0,i)<0)?i++:remove(i);
    return oldSize-_size;//向量规模变化量，即被删除元素总数
}

//有序向量uniquify()接口的高效实现
template<typename T>int Vector<T>::uniquify(){
    Rank i=0,j=0;
    while(++j<_size)
        if(_elem[i]!=_elem[j])//跳过雷同者
            _elem[++i]=_elem[j];//发现不同元素时,向前移至紧邻于前者右侧
    _size=++i;shrink();//直接截除尾部多余元素
    return j-i;//向量规模变化量，即被删除元素总数
}

//二分查找，版本A
template<typename T>static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
    while(lo<hi){
        Rank mi=(lo+hi)>>1;//以中点为轴点
        if (e<A[mi]) hi=mi;
        else if(A[mi]<e) lo=mi+1;
        else return mi;//命中
    }
    return -1;//失败
}//有多个命中元素时,丌能保证迒回秩最大者;查找失败时,简单地迒回-1,而且不能指示失败的位置


//二分查找，版本B,不能如版本A  那样,一旦命中就能及时返回,最好情况下的效率有所倒退。当然,作为补偿,最坏情况  下的效率相应地有所提高。实际上无论是成功查找或失败查找,版本B各分支的查找长度更加接  近,故整体性能更趋稳定。
template<typename T>static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
    while(hi-lo>1){//每步迭代仅需做一次比较判断,有两个分支;成功查找不能提前终止
        Rank mi=(lo+hi)>>1;
        (e<A[mi])?hi=mi:lo=mi;
    }
    return (e==A[lo])?lo:-1;//查找成功时迒回对应的秩,否则迒回-1
}

//二分查找，版本C
template<typename T>static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
    while(hi>lo){//每步迭代仅需做一次比较判断,有两个分支
        Rank mi=(lo+hi)>>1;
        (e<A[mi])?hi=mi:lo=mi;
    } 
    return --lo;/循环结束时,lo为大亍e的元素的最小秩,故lo - 1即lo不大于e的元素的最大秩

}

//起泡排序，稳定算法
template<typename T>void Vector<T>::sort(Rank lo,Rank hi){
    while(!bubble(lo,hi--));//逐趟扫描交换,直至全序
}

//单趟扫描交换
template<typename T>bool Vector<T>::bubble(Rank lo,Rank hi){
    bool sorted=true;
    while(++lo<hi){
        if(_elem[lo-1]>_elem[lo]){
            swap(_elem[lo-1],_elem[lo]);
            sorted=false;
        }
    }
    return sorted;
}


//分治策略，二路归并
template<typename T>void Vector<T>::mergeSort(Rank lo,Rank hi){
   if(hi-lo<2) return;
   Rank mi=(lo+hi)>>1;
   mergeSort(lo,hi);
   mergeSort(mi,hi);//以中点为界分别排序
   merge(lo,mi,hi);//归并
}

//二路归并接口的实现
template<typename T>void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
    T* A=_elem+lo;//前子向量A[lo,mi)
    int lb = mi - lo; 
    T* B = new T[lb];
    for(Rank i=0;i<lb;B[i]=A[i++]);//复制前子向量至B[0,lb)
    int lc = hi - mi; 
    T* C = _elem + mi;//后子向量C[mi,hi)
    for(Rank i=0,j=0,k=0;(j<lb)||(k<lc);){//B[j]和C[k]中的较小者续至A末尾
        if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++];
        if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k] < B[j] ) ) ) A[i++] = C[k++];
    }
    delete[] B;
}
/*
( ! ( k < lc ) || ( B[j] <= C[k] ) )：这是一个逻辑或 || 表达式，包含两个条件：
! ( k < lc )：检查后子数组 C 是否已经遍历完。如果 k 大于等于 lc，说明 C 中所有元素都已经处理完毕。
( B[j] <= C[k] )：当前子数组 B 和后子数组 C 都还有元素时，比较 B[j] 和 C[k] 的大小。如果 B[j] 小于等于 C[k]，则说明 B[j] 应该优先放入目标数组 A 中。
 */

 //列表类内部方法
 template<typename T>void List<T>::init(){
    header=new ListNode<T>;//创建头哨兵节点
    trailer=new ListNode<T>;//创建尾哨兵节点
    header->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    _size=0;
 }


 //重载列表类的下标操作符
template<typename T>//重载下标操作符,以通过秩直接讵问列表节点(虽斱便,效率低,需慎用)
T& List<T>::operator[](Rank r)const{
    ListNodePosi(T) p=first();//从首节点出发
    while(0<r--) p=p->succ;//顺数第r个节点即为目标
    return p->data;//目标节点处储存的元素 
}

//有序列表剔除重复节点接口
template<typename T> int List<T>::uniquify(){
    if(_size<2) return 0;
    int oldSize=_size;
    ListNodePosi(T) p=first();
    ListNodePosi(T) q;  
    while(trailer!=p->succ){//反复考察紧邻的节点对(p,q)
        q=p->succ;
        p->data==q->data?remove(p):p=q;
    }
    return oldSize-_size;//返回被删除的节点总数
}

//有序列表查找
template<typename T>ListNodePosi(T) List<T>::search(T const& e,int n,int m)const{
    ListNodePosi(T) p=last();
    while(m--<0) p=p->pred;
    while(n--<0&&p!=header&&e<p->data) p=p->pred;
    return p;
 
}
//有序列表查找
template<typename T>ListNodePosi(T) List<T>::search(T const& e)const{
    while (0<=n--) 
        if(((p=p->pred)->data)<=e) break;
    return p;
}

//有序列表基于排序的构造方法
template<typename T>void List<T>::sort(ListNodePosition<T> p,int n){
    switch (rand()%3) {
        case 1:insertionSort(p,n);break;
        case 2:selectionSort(p,n);break;
        default:mergeSort(p,n);break; 
    }
}

//有序列表的插入排序
template<typename T>void List<T>::insertionSort(ListNodePosi(T) p,int n){
    while(0<(n--)){//逐一为各节点
        insertAfter(search(p->data,n,p),p->data);//查找适当的位置并插入
        p=p->succ;
        remove(p->pred);//转向下一节点
    }
}

//列表的选择排序
template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p,int n){
    ListNodePosi(T) head=p->pred;
    ListNodePosi(T) tail=p;
    for(int i=0;i<n;i++) tail=tail->succ; 
    while(1<n){//在至少还剩下两个节点之前,在待排序区间内
        insertBefore(tail,remove(selectMax(head->succ,n)));
        tail=tail->pred;
        n--;
    }
}

//列表最大节点的定位
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p,int n){
    ListNodePosi(T) max=p;
    for(ListNodePosi(T) cur=p;1<n;n--){
        if(!lt((cur=cur->succ)->data,max->data)) max=cur;
    }
    return max;
}
//列表的二路排序
template<typename T>
void List<T>::merge(ListNodePosi(T)& p,int nlist<T>& L,ListNodePosition(T) q,int m){
 ListNodePosition(T) pp=p->pred;
 while(0<m){
    if(0<n&&lt(p->data,q->data)){
        if(q==(p=p->succ)) break;
        n--;
    }else{
        insertBefore(p,L.remove((q=q->succ)->pred));
        m--;
    }
 }
 p=pp->succ;
}

//列表的归并排序
template<typename T>void List<T>::mergeSort(ListNodePosi(T)& p,int n){
    if(n<2) return;
    int m=n>>1;
    ListNodePosi(T) q=p;
    for(int i=0;i<m;i++) q=q->succ;
    mergeSort(p,m);mergeSort(q,n-m);
    merge(p,n,L,q,m);
}//注意:排序后,p依然指向归并后区间的(新)起点


//栈模板类
template <typename T>
class Stack:public Vector<T>{
    public:
        void push(T const& e){this->insert(this->size(),e);}//入栈
        T pop(){return this->remove(this->size()-1);}//出栈
        T& top(){return (*this)[this->size()-1];}//取顶
};



//进制转换算法
void convert(Stack<char>& S,__int64 n,int base){
    static char digit[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    while(n>0){
        S.push(digit[n%base]);
        n/=base;
    }
}

//括号匹配算法，递归版
void trim(const char exp[],int& lo,int& hi){
    while((lo<=hi)&&(exp[lo]!='(')&&(exp[lo]!=')')) lo++;
    while((lo<=hi)&&(exp[hi]!='(')&&(exp[hi]!=')')) hi--;
}

int divide(const char exp[],int lo,int hi){
    int mi=lo;
    int crc=1;
    while((0<crc)&&(++mi<hi)){
        if(exp[mi]==')') crc--;
        else if(exp[mi]=='(') crc++;
    }
    return mi;
}

bool paren(const char exp[],int lo,int hi){
    trim(exp,lo,hi);
    if(lo>hi) return true;
    if(exp[lo]!='(') return false;
    if(exp[hi]!=')') return false;
    int mi=divide(exp,lo,hi);
    if(mi>hi) return false;
    return paren(exp,lo+1,mi-1)&&paren(exp,mi+1,hi);
}

//括号匹配算法迭代实现
bool paren(const char exp[],int lo,int hi){
    Stack<char> S;//使用栈记录已发现但尚未匹配的左括号
    for(int i=lo;i<=hi;i++)//左括号直接进栈;右括号若与栈顶失配,则表达式必不匹配
        switch(exp[i]){
            case 'c':case '[':case '{':S.push(exp[i]);break;
            case ')':if(S.empty()||S.pop()!='(') return false;break;
            case ']':if(S.empty()||S.pop()!='[') return false;break;
            case '}':if(S.empty()||S.pop()!='{') return false;break;
            default:break;
        }
    return S.empty();
}

//表达式求值算法
float evaluate(const char* S,char*& RPN){
    Stack<float> opnd;Stack<char> optr;
    optr.push('\0');//尾哨兵'\0'也作为头哨兵首先入栈
    while (!optr.empty()){
        if(isdigit(*S)){
            readNumber(S,opnd);append(RPN,opnd.top());
        }
        else switch(orderBetween(optr.top(),*S)){
            case '<':
                optr.push(*S++);break;
            case '=':
                optr.pop();S++;break;
            case '>':{
                char op=optr.pop();append(RPN,op);
                if('!'==op){
                    float pOpnd=opnd.pop();
                    opnd.push(calcu(op,pOpnd));
                }else{
                    float pOpnd2=opnd.pop(),poPnd1=opnd.pop();
                    opnd.push(calcu(pOpnd1,op,pOpnd2));
                }
                break;
            }
            default:break;
            
        }
    }
    return opnd.pop();
};


//皇后类
struct Queen{
    int x,y;
    Queen (int xx=0,int yy=0):x(xx),y(yy){};
    bool operator==(Queen const& q) const{
        return (x==q.x)||(y==q.y)||(x+y==q.x+q.y)||(x-y==q.x-q.y);
    }
    bool operator!=(Queen const& q) const{
        return !(*this==q);
    }
};

//N皇后算法
void placeQueens(int N){
    Stack<Queen> solu;
    Queen q(0,0);
    do{
        if(N<=solu.size()||N<=q.y){
            q=solu.pop();
            q.y++;
        }
        else{
            while((q.y<N)&&(0<=solu.find(q))){
                q.y++;
                nCheck++;
            }
            if(N>q.y){
                solu.push(q);
                if (N<=solu.size()) nSolu++;
                q.x++;
                q.y=0;
            }
        }
    }
    while ((0<q.x)||(q.y<N));
}

//迷宫迅径
typedef enum{AVAILABLE,UNAVAILABLE,IN_PATH} Status;
typedef enum{UNKNOW,EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN;

inline ESWN nextESWN(ESWN eswn){ return ESWN(eswn+1);}

struct Cell{
    int x,y;
    Status status;
    ESWN incoming,outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX]; //迷宫

//邻格查询
inline Cell* neighbor(Cell* cell){
    switch(cell->outgoing){
        case EAST:return cell+LABY_MAX;
        case SOUTH:return cell+1;
        case WEST:return cell-LABY_MAX;
        case NORTH:return cell-1;
        default:exit(-1);
    }
}

//邻格转入
inline Cell* advance(Cell* cell){
    Cell* next;
    switch(cell->outgoing){
        case EAST:next=cell+LABY_MAX;next->incoming=WEST;break;
        case SOUTH:next=cell+1;next->incoming=NORTH;break;
        case WEST:next=cell-LABY_MAX;next->incoming=EAST;break;
        case NORTH:next=cell-1;next->incoming=SOUTH;break;
        default:exit(-1);
    }
    return next;
}

//迷宫迅径算法
bool labyrinth(Cell laby[LABY_MAX][LABY_MAX],Cell* s,Cell* t){
    if((AVAILABLE !=s->status)||(AVAILABLE !=t->status))
        return false;
    Stack<Cell*> path;
    s->incoming=UNKNOWN;s->status=ROUTE;path.push(s);
    do{
        Cell* c=path.top();
        if (c==t) return true;
        while(NO_WAY>(c->outgoing=nextESWN(c->outgoing)))
            if (AVAILABLE==neighbor(c)->status) break;
        if (NO_WAY<=c->outgoing) {
            c->status=BACKTRACKED;c=path.pop(); 
        }  
        else{
            path.push(c=advance(c));
            c->outgoing=UNKNOWN;
            c->status=ROUTE;
        }
        } 
    while(!path.empty());
    return false;
        
    }
 
//循环分配器
RoundRobin{
    Queue Q(clients);//参不资源分配的所有客户组成队列Q
    while (!ServiceClosed()) { //在服务关闭之前,反复地
        e = Q.dequeue(); //队首的客户出队,并
        serve(e); //接受服务,然后
        Q.enqueue(e); //重新入队
}
}

//银行服务模拟
struct Customer{
    int window;unsigned int time;
};

void simulate(int nWin,int servTime){
    Queue<Customer>* windows=new Queue<Customer>[nWin];
    for(int now=0;now<servTime;now++){
        if(rand()%(1+nWin)){
            Customer c;c.time=1+rand()%98;
            c.window=bestWindow(windows,nWin);
            windows[c.windows].enqueue(c);
        }
        for(int i=0;i<nWin;i++){
            if(!windows[i].empty()){
                
                if(--windows[i].front().time<=0){
                    windows[i].dequeue();
                }
            }

        }
    }
    delete[] windows;
}

//查找最短路径
int bestWindow(Queue<Customer> windows[],int nWin){
    int minSize=windows[0].size(),optiWin=0;
    for (int i=1;i<nWin;i++)
        if(minSize>windows[i].size()){
            minSize=windows[i].size();
            optiWin=i;
        }
    return optiWin;
}

//二叉树中序遍历算法的统一入口
template<typename T>template <typename VST>
void BinNode<T>::travIn(VST& visit){
    switch(rand()%5){
        case 1:tranIn_I1(this,visit);break;
        case 2:tranIn_I2(this,visit);break;
        case 3:travIn_I3(this,visit);break;
        case 4:tranIn_I4(this,visit);break;
        default:tranIn_R(this,visit);break;
    }
}

//先序遍历递归版
template<typename T,typename VST>
void travPre_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lc,visit);
    travPre_R(x->rc,visit);
}

//先序遍历迭代版
template<typename T,typename VST>
void travPre_I(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)> s;
    while(x||!s.empty()){
        while(x){
            visit(x->data);
            s.push(x);
            x=x->lc;
        }
        x=s.pop();x=x->rc;
    }
}

//二叉树后续遍历算法
template<typename T,typename VST>
void travPost_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travPost_R(x->lc,visit);
    travPost_R(x->rc,visit);
    visit(x->data);
}

//二叉树中序遍历算法
template<typename T,typename VST>
void travIn_R(BinNodePosi(T) x,VST& visit){
    if(!x) return;
    travIn_R(x->lc,visit);
    visit(x->data);
    travIn_R(x->rc,visit);
}

//事叉树先序遍历算法(迭代版)
template<typename T,typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x,VST& visit,Stack<BinNodePosi(T)& S){
    while(X){
        visit(x->data);
        S.push(x->rc);
        x=x->lc;
    }
}

template<typename T,typename VST>
void travPre_I2(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)>S;
    while(x||!S.empty()){
        visitAlongLeftBranch(x,visit,S);
        x=S.pop();
    }
}

//二叉树中序遍历算法(迭代版)
template <typename T>
static void visitAlongLeftBranch(BinNodePosi(T) x,Stack<BinNodePosi(T)>& s){
    while(x){S.push(x);x=x->lc;}
}
template<typename T,typename VST>
void travIn_I2(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)> S;
    while(x||!S.empty()){
        visitAlongLeftBranch(x,visit,S);
        x=S.pop();
    }
}

//二叉树后序遍历算法(迭代版)
template<typename T,typename VST>
void travPost_I(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)>S;
    while(x||!S.empty()){
        while(x){
            S.push(x);
            x=x->lc;
        }
        x=S.pop();visit(x->data);
        if(!S.empty()&&S.top()->rc==x){
            x=S.pop();
            visit(x->data);
            x=S.top()->rc;
        }
        else x=NULL;
    }
}

//二叉树节点直接后继的定位
template<typename T> BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s=this;
    if (rc)
    {
        s=rc;
        while(HasLChild(*s)) s=s->lc;
    }
    else{
        while(IsRChild(*s)) s=s->parent;
        s=->parent;
    }
    return s;
}
//二叉树中序遍历算法(迭代版)进一步改进
template<typename T,typename VST>
void travIn_I2(BinNodePosi(T),VST& visit){
    Stack<BinNodePosi(T)> S;//辅助栈
    while (true)
    {
        if(x){
            S.push(x);
            x=x->lc;
        }
        else if(!S.empty()){
                x=S.pop();
                visit(x->data);
                x=x->rc;
            }
            
        else break;    
}

//二叉树中序遍历算法(迭代版3)
template<typename T,typename VST>
void tranIn_I3(BinNodePosi(T),VST& visit){
    bool backtrack=false;
    while(true){
        if(!backtrack&&HasLChild(*x)) x=x->lc;
        else{
            visit(x->data);
            if(HasRChild(*x)){x=x->rc;backtrack=false;} 
            else{
                if(!(x=x->succ())) break;
                backtrack=true;
            }
        } 
    }
}

//迭代版后序遍历(迭代版)
template<typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S){
    while(BinNodePosi(T) x=S.top()){
        if(HasLChild(*x)){
            if(HasRChild(*x)) S.push(x->rc);
            S.push(x->lc);
        }
        else S.push(x->rc);
    } 
    S.pop();
}
template<typename T,typename VST>
void travPost_I(BinNodePosi(T) x,VST& visit){
    Stack<BinNodePosi(T)> S;
    if(x) S.push(x);
    while(!S.empty()){
        if(S.top()!=x->parent) gotoHLVFL(S);
        x=S.pop();visit(x->data);
    }
}

//二叉树层次遍历算法
template<typename T,typename VST>
void travLevel(BinNodePosi(T) x,VST& visit){
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(x);
    while(!Q.empty()){
        x=Q.dequeue();
        visit(x->data);
        if(HasLChild(*x)) Q.enqueue(x->lc);
        if(HasRChild(*x)) Q.enqueue(x->rc);
    }
}

//基于二叉树的PFC编码
int main(int argc,char* argv[]){
    PFCForest* forest=initForest();//初始化
    PFCTree* tree=generateTree(forest);
    release(forest);
    PFCTable* table=generateTable(tree);
    for(int i=1;i<argc;i++){
        Bitmap codeString;
        int n=encode(table,argv[i],codeString);
        decode(tree,codeString,n);
    }
    release(tree);release(table);
    return 0;
}

//初始化PFC森林
PFCForest* initForest(){
    PFCForest* forest=new PFCForest;
    for (int i=0;i<N_CHAR;i++){
        forest->insert(i,new PFCTree());
        (*forest)[i]->insertAsRoot(i);
    }
    return forest;
}

//构造PFC编码树
PFCTree* generateTree(PFCForest* forest){
    srand((unsigned int)time(NULL));
    while(forest->size()>1){
        PFCTree* s=new PFCTree;
        s->insertAsRoot('^');
        Rank r1=rand()%forest->size();
        s->attachAsLC(s->root(),(*forest)[r1]);
        forest->remove(r1);
        Rank r2=rand()%forest->size();
        s->attachAsRC(s->root(),(*forest)[r2]);
        forest->remove(r2);
        forest->insert(forest->size(),s);
    }
    return (*forest)[0];
}

//生成PFC编码表
void generateCT(Bitmap* code,int length,BinNodePosi(char) v){
    if(IsLeaf(*v)){
        table->put(v->data,code->bits2string(length));
        return;
    }
    if(HasLChild(*v)){
        code->clear(length);
        generateCT(code,length+1,v->lc);
    }
    if(HasRChild(*v)){
        code->set(length);
        generateCT(code,length+1,v->rc); 
    }
}

PFCTable* generateTable(PFCTree* tree){
    PFCTable* table=new PFCTable;
    Bitmap* code=new Bitmap;
    generateCT(code,0,tree->root());
    release(code);
    return table; 
}

//编码
int encode(PFCTable* table,Bitmap& codeString,char* s){
    int n=0;
    for(size_t m=strlen(s),i=0;i<m;i++){
        char** pCharCode=table->get(s[i]);
        if(!pCharCode) pCharCode=table->get(s[i]+'A'-'a');
        if(!pCharCode) pCharCode=table->get(' ');
        printf("%s",*pCharCode);
        for(size_t m=strlen(*pCharCode),j=0;j<m;j++){
            '1'==*(*pCharCode+j)?codeString.set(n++):codeString.clear(n++);
        }

    }
    return n;
}

//解码
void decode(PFCTree* tree,Bitmap& code,int n){
    BinNodePosi(char) x=tree->root();
    for(int i=0;i<n;i++){
        x=code.test(i)?x->rc:x->lc;
        if(IsLeaf(*v)){
            printf("%c",x->data);
            x=tree->root();
        }
    }
}

//基于二叉树的Huffman编码
int main(int argc,char* argv[]){
    int* freq=statistics(argv[1]);//统计
    HuffmanTree* forest=initForest(freq);release(freq);//构造
    HuffmanCode* tree=generateTree(forest);release(forest);//生成
    HuffTable* table=generateTable(tree);//将Huffman编码树转换为编码表
    for(int i=1;i<argc;i++){//编码
        Bitmap codeString;
        int n=encode(table,argv[i],codeString);
        decode(tree,codeString,n);
        release(codeString);
    }
    release(tree);release(table);
    return 0;
}

//统计
int* statistics(char* s){
    int* freq=new int[N_CHAR];
    memset(freq,0,sizeof(int)*N_CHAR);
    FILE* fp=fopen(sample_text_file,"r");
    for(char ch;0<fscanf(fp,"%c",&ch);)
        if(isalpha(ch)) freq[ch-'a']++; 
    fclose(fp);
    return freq; 
}

//初始化Huffman森林
HuffForest* initForest(int* freq){
    HuffForest* forest=new HuffForest;
    for(int i=0;i<N_CHAR;i++){
        if(freq[i]){
            forest->insertAsLast(new HuffTree);
            forest->last()->data->insertAsRoot(HuffChar(i,freq[i]));//存入其中
        }
    }
    return forest;
}

//基于邻接矩阵实现图的结构
template<typename Tv> struct Vertex{
    Tv data;
    int inDegree,outDegree;
    Vstatus status;
    int dTime,fTime;
    int parent;
    int priority;
    Vertex(Tv const& d=(Tv)0):data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template<typename Te> struct Edge{
    Te data;
    Edge(Te const& d,int w):data(d),weight(w),type(UNDISCOVERED){}
};

template<typename Tv,typename Te>
class Graphmatrix:public Graph<Tv,Te>{
    private:
         Vector<Vertex<Tv>> V;
         Vextor<vector<Edge<Te>*>>E;
    public:
        Graphmatrix():{n=e=0;}
        ~Graphmatrix(){for(int j=0;j<n;j++) st(NULL);
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    delete E[j][k];
        }
}

virtual Tv& vertex(int i){return V[i].data;}
virtual int inDegree(int i){return V[i].inDegree;} 
virtual int outDegree(int i){return V[i].outDegree;}
virtual int firstNbr(int i){return nextNbr(i,-1);}
virtual int nextNbr(int i,int j){
   while((-1<j)&&(!exists(i,--j)));return j;
}
virtual VStatus& status(int i){return V[i].status;}
virtual int dTime(int i){return V[i].dTime;}
virtual int fTime(int i){return V[i].fTime;}
virtual int parent(int i){return V[i].parent;}
virtual int priority(int i){return V[i].priority;}
virtual int& insert(Tv const& vertex){
    for(int j=0;j<n;j++) E[j].insert(NULL);n++;
    E.insert(Vector<Edge<Te>*>(n,n,(Edge<Te>*)NULL));
    return V.insert(Vertex<Tv>(vertex));
}

virtual Tv remove(int i){
    for(int j=0;j<n;j++){
        if(exists(i,j)){
            delete E[i][j];
            V[j].inDegree--;
        }
    }
    E.remove(i);n--;
    Tv vBak=vertex(i);V.remove(i);
    for (int j=0;j<n;j++){
        if(Edge<Te>* e=E[j].remove(i)){delete e;V[j].outDegree--;
        }
    }
    return vBak;
}

virtual bool exists(int i,int j){
    return(0<=i)&&(i<n)&&(0<=j)&&(j<n)&&E[i][j]!=NULL;
}

virtual EType& type(int i,int j){return E[i][j]->type;}
virtual Te& edge(int i,int j){return E[i][j]->data;}
virtual int& weight(int i,int j){return E[i][j]->weight;}
virtual Te* insert(int i,int j,Te const& edge,int weight){
    if(exists(i,j)) return;
    E[i][j]=new Edge<Te>(edge,weight);
    e++;
    V[i].outDegree++;
    V[j].inDegree++;
    return E[i][j];
}
virtual Te remove(int i,int j){
    Te eBak=edge(i,j);
    delete E[i][j];E[i][j]=NULL;
    e--;V[i].outDegree--;V[j].inDegree--;
    return eBak;
}

//BFS算法
template<typename Tv,typename Te>
void Graph<Tv,Te>::bfs(int s){
    reset();int clock=0;int v=s;
    do
        if(UNDISCOVERED==status(v)){
            BFS(v,clock);
        }
    while(s!=(v=(++v%n)));
}
template<typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v,int& clock){
    Queue<int> Q;
    status(V)=DISCOVERED;Q.enqueue(v);
    while(!Q.empty()){
        int v=Q.dequeue();dTime(v)=++clock;
        for(int u=firstNbr(v);-1<u;u=nextNbr(v,u)){
            if(UNDISCOVERED==status(u)){
                status(u)=DISCOVERED;Q.enqueue(u);
                type(v,u)=TREE;parent(u)=v;
            }
            else{
                type(v,u)=CROSS;
            }
        }
        status(v)=VISITED;
    }
}

//DFS算法
template<typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s){
    reset();int clock=0;int v=s;
    do
        if(UNDISCOVERED==status(v)){
            DFS(v,clock);
        }
    while(s!=(v=(++v%n)));
}
template<typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int& clock){
    dTime(v)=++clock;status(v)=DISCOVERED;
    for(int u=firstNbr(v);-1<u;u=nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                type(v,u)=TREE;parent(u)=v;DFS(u,clock);
                break;
            case DISCOVERED:
                type(v,u)=BACKWARD;break;
            default:
                type(v,u)=status(u)==VISITED?CROSS:FORWARD;
        }
    }
    status(v)=VISITED;fTime(v)=++clock;
}

//基于DFS的拓扑排序算法
template<typename Tv,typename Te>
Stack<Tv>* Graph<Tv,Te>::tSort(int s){
    reset();int clock=0;int v=s;
    Stack<Tv>* S=new Stack<Tv>;
    do{
        if(UNDISCOVERED==status(v)){
            if(!TSort(v,clock,S)){
                while(!S.empty()) S.pop();break;
            }
        }
    }
    while(s!=(v=(++v%n)));
    return S;
}
template<typename Tv,typename Te>
bool Graph<Tv,Te>::TSort(int v,int& clock,Stack<Tv>* S){
    dTime(v)=++clock;status(v)=DISCOVERED;
    for(int u=firstNbr(v);-1<u;u=nextNbr(v,u)){
        switch(status(u)){
            case UNDISCOVERED:
                type(v,u)=TREE;parent(u)=v;if(!TSort(u,clock,S)) return false;
                break;
            case DISCOVERED:
                type(v,u)=BACKWARD;
                return false;
            default:
                type(v,u)=(dTime(v)<dTime(u))?FORWARD:CROSS;
                break;
        }
    }
    status(v)=VISITED;fTime(v)=++clock;S.push(vertex(v));return true;
    }

















