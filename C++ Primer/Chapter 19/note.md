# 第十九章 特殊工具与技术

### 19.1

+ 可以通过重载new和delete函数控制程序内存的使用。如果把new和delete定义成类的成员时，new在构造函数之前执行，delete在析构函数之后执行，所以它们是静态成员函数，编译器会为我们隐式设置为静态，所以它们不能操纵任何数据成员。
```c++
void *operator new(size_t);
void *operator new[](size_t);
void *operator delete(void *) noexcept;   // delete不允许抛出异常
void *operatro delete[](void *) noexcept;

void *operator new(size_t, nothrow_t&) noexcept;   // nothrow_t是定义在new头文件下一个struct，这个类型不包含任何成员。
void *operator new[](size_t, nothrow_t&) noexcept;  // 在new头文件下定义了一个名为nothrow的const对象，利用这个对象请求new的非抛出异常版本
void *operator delete(void *, nothrow_t&) noexcept;
void *operatro delete[](void *, nothrow_t&) noexcept;
```

 + 函数`void *operator new(size_t, void*)`不允许重载。
 
 + 一条new表达式的执行过程总是先调用operator new函数以获取内存空间，然后在得到的内存空间中构造对象，与之相反，一条delete表达式的执行过程总是先销毁对象，然后调用operator delete函数释放空间。
```c++
void *operator new(size_t size) {
    if (void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}

void operator delete(void *mem) noexcept { free(mem); }

```

### 19.2

+ **dynamic_cast运算符**，用于将基类的指针或引用安全地转换生成派生类的指针或引用
```c++
dynamic_cast<type*>(e)
dynamic_cast<type&>(e)
dynamic_cast<type&&>(e) // e 不能是左值

// e必须是目标type的类型或目标type的公有基类或type的公有派生类。
```

+ 在头文件**typeinfo**中定义typeid运算符。typeid运算符返回一个type_info或type_info的公有派生类的引用。typeid运算符可以作用与任何类型的表达式，其中顶层const会被忽略，如果表达式是一个引用，返回所引对象的类型。如果表达式是一个数组则返回数组类型。如果表达式是含有虚函数的类式，结果由动态类型决定。

### 19.3

+ c++11可以定义限定作用域的枚举类型，做法是在enum和名字间添加一个class/struct(等价)
```c++
enum class open_mode {input, output, append};
enum color {red, yellow, green};


enum stoplight {red, yellow, green} // 错误 ，重复定义
enum class peppers {red, yellow, green};

color eyes = green;

peppers p = green // 错误
color hair = color::red;
peppers p2 = peppers::red // 正确
```

+ 不限定作用域的枚举类型的对象可以或枚举类型成员自动转换成整型，而限定作用域的不行。

+ c++11中允许在enum名字后加上冒号以及我们想在该enum中使用的类型,不限定作用域的enum在前置声明的时候必须要指明类型，限定作用域的可以使用默认的int。
```c++
enum intValues:unsigned long long {
    charTyp = 225, shortTyp = 65535,
    ...
    long_longTyp = 18446744073709551615ULL
}
```

### 19.4

+ 获取一个类的数据成员的指针时，需要在\*之前添加classname::，初始化的时候使用`pdata = &className::data`的方式。同时也有连个新的运算符`.*和->*`，这两个运算符用于解引用并获得该对象的成员。
```c++
const string Screen::*pdata;
pdata = &Screen::contents;
c++11:
auto pdata = &Screen::contents;

Screen myScreen, *pScreen = &myScreen;

auto s = myScreen.*pdata;

s = pScreen->*pdata;
```

+ 常规的访问控制规则对于成员指针同样有效，通常定义一个函数令其返回值是指向该成员的指针,通过这个函数可以获取到成员的类型。
```c++
class Screen {
public:
    static const std::string Screen::*data() {return &Screen::contents;}
};
```

+ 对于一个类的成员函数也类似，需要在\*前加上classname::，类似于任何类型的函数指针，指向成员的指针也需要指定目标函数的返回类型和形参列表，如果成员是const成员的话或引用成员，则必须将const限定符或引用限定符包含进来。
```c++
char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
pmf2 =&Screen::get; (&必不可少)

(pScreen->*pmf)(0, 0);
(myScreen.*pmf)(0, 0); // 函数调用运算符的优先级较高，所以()必不可少。
```

+ 可以使用成员指针的类型别名使成员指针更容易理解。
```c++
using Action = char(Screen::*)(Screen::pos, Screen::pos) const;

Action get = &Screen::get;
```

+ 利用function将成员函数指针打包成一个可调用对象，就可以传入泛型算法。也可以使用定义在functional头文件中的mem_fn让编译器负责推断成员的类型,当然也可以使用bind从成员函数生成一个可调用对象。
```c++
vector<string> v;
function<bool(const string&)> fp = &string::empty;
find_if(v.begin(), v.end(), fp);

find_if(v.begin(), v.end(), mem_fn(&string::empty));

auto f = mem_fn(&string::empty);
f(*v.begin());
f(&svec[0]);

auto f = bind(&string::empyt, placeholder::_1);
f(*svec.begin());
f(*svec[0]);
```

### 19.5

+ 一个类可以定义在另一个类的内部，前者称为嵌套类或嵌套类型。嵌套类的名字在外层作用域是可见的，在外层类作用域之外是不可见的。外层类对嵌套类的成员没有特殊的访问权限，同样，嵌套类对外层类的成员也没有特殊的访问权限。

+ 嵌套类必须声明在类的外部，但是可以定义在类的内部或外部，需要加上域作用符，在外层类外定义嵌套类的成员函数的时候要多加一层域作用符。

### 19.6

+ **联合**是一种特殊的类，一个union可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。分配给一个union对象的储存空间至少要容纳它的最大数据成员。类的某些特性对union同样适用，但并非所有特性都如此。union不能含有引用类的成员。c++11中含有构造函数或析构函数的类类型也可以作为union的成员类型。默认情况下，union的成员是public的，union不能继承自其他类，也不能作为基类适用，所以union中不能含有虚函数。

+ 匿名union不能包含受保护的成员或私有成员，也不能定义成员函数。


### 19.7

+ 类定义在某个函数内部，我们称这样的类是局部类。局部类的所有成员(包含成员函数)都必须完整定义在类的内部。因此，局部类的作用与嵌套类相比相差很远。局部类中无法定义静态数据成员。

+ 局部类只能访问外层作用域定义的类型名，静态变量以及枚举成员。


### 19.8

+ c++定义的一些固有的**不可移植**的特性是指因机器而异的特性。

+ 类可以将其(非静态)数据成员定义成**位域**，在一个位域中含有一定数量的二进制位。当一个程序需要向其他程序或设备传递二进制数据时，通常用到位域。位域的类型必须是整型或枚举类型。这些位域会储存在同一个unsigned int中。取地址运算符(&)不能作用于位域。
```c++
typedef unsigned int bit;
class File {
    Bit mode: 2;  // mode占2位
    Bit modified: 1;
    Bit prot_owner: 3;
...
};

void File::write() {
    modified = 1;
    ..
};

void File:open() {
    mod |= READ;
};
```

+ 一些变量由程序以外的过程控制，这些变量应该声明为**volatile**，通知编译器不应对这样的对象进行优化。
```c++
volatile int display_register;
volatile const int bitmapBuf;
```

+ 合成的拷贝对volatile无效。

+ c++的链接提示`extern"C"`指出任意非c++程序说用的语言。类似的也有`extern "Ada", extren "FORTRAN"`
```c++
extren "C" size_t strlen(const char*);

extern "C" {
    int strcmp(const char*, cosnt char*);
    char *strcat(char*, const char*);
}

```
