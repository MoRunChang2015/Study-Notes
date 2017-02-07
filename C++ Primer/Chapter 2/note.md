# 第二章 变量和基本类型

### 2.1

+ 类型**char**和类型**signed char**并不一样。尽管字符型有三种，但是字符的表现形式却只有两种：带符号和不带符号的的。类型**char**实际上会表现为上述两种形式的一种，具体是那种由编译器决定。所以在算术表达式中尽量不要使用char，在不同的编译器中可能会出现不同的结果，可以明确表面使用**signed char**或者**unsigned char**。

+ 执行浮点运算的时候尽量使用**double**，float可能因为精度不够而且双精度的运算代价与单精度的相差无几，事实上，某些机器上双精度运算比单精度的要快。注意一般没必要使用**long double**，它的运算消耗不容忽视。

+ **谨慎使用无符号变量**,在算术运算过程中带符号变量会转换成无符号数再进行运算，可能会出现预想不到的结果。

+ 十进制字面值的类型是**int,long和long long**中尺寸最小的那个，当然前提是这种类型能够容纳当前值。

+ 如果两个字符串字面值位置紧邻且仅由**空格,缩进或换行符**分割,则它们实际上是一个整体。如下

  ```c++
      std::cout << "Hello "
                   "world" << std::endl;
  ```
  
### 2.2

+ **C++中初始化与赋值是两个完全不同的操作**，初始化的含义是创建变量时赋予一个初始值，而赋值的含义是把对象的当前值擦除，而以一个新值来替代。


+ 如果我们使用列表初始化且初始值存在**丢失信息**风险，则编译器将报警告。如下:

  ```c++
      long double temp = 3.1415926535;
      int a{temp}, b = {temp};  // 警告：存在信息丢失风险。
      int c(temp), d = temp;    // 正确
  ```
  

+ **声明**使得名字为程序所知，一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。
 
+ **定义**负责创建与名字关联的实体。
 
+ 变量能且只能被**定义一次**，但是可以被**多次声明**。
 
+ 用域作用符显示调用全局变量，见[scope.cpp](https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%20Two/code/2.2/scope.cpp)

### 2.3

+ 引用创建后必须进行初始化，因为无法令引用重新绑定到另外一个对象。引用本身并非一个对象。

+ 指针的相等操作符(==)或者不相等操作符(!=)，只关心指针变量存储的地址是否相等，跟指针的类型无关。详见[pointerEqual.cpp](https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%20Two/code/2.3/pointerEqual.cpp)

+ `int* p1, p2 // p1是指向int的指针, p2是int`

### 2.4

+ 如果想在多个文件之间共享const对象，必须在变量的定义之前添加**extern**关键字。

+ 常量引用仅对引用可参与的操作做出限定，对引用的对象本身是不是一个常量未作限定。详见[constReference.cpp](https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%20Two/code/2.4/constReference.cpp)

+ **顶层const(top-level const)**表示指针本身是一个常量，**底层const(low-level)**表示指针所指的对象是一个常量。

+ **常量表达式**是指值不会发生改变并且再编译过程中就能得到计算结果的表达式。

+ 
```c++
  const int *p = nullptr; // p 是一个指向整型常量的指针
  constexpr int *q = nullptr // q 是一个指向整型的常量指针
  ```
  
### 2.5

+ **C++11**新增**别名声明**
  `using SI = Sales_item;`
  
+ auto类型再初始化过程中，引用被用作初始值时，真正参与初始化的其实是引用对象的值。此时编译器以引用对象的类型作为auto的类型。
```c++
   int i = 0, &r = i;
   auto a = r; // a 是整数
```

+ auto类型一般会忽略掉顶层const,同时底层const则会保留下来。
```c++
   const int ci = i, &cr = ci;
   auto b = ci;  // b 是一个整数
   auto c = cr;  // c 是一个整数
   auto d = &i;  // d 是一个整型指针
   auto e = &ci; // e 是一个指向整型常量的指针
```

+ decltype使用的表达式是一个变量，则decltype返回该变量的类型(包括顶层const和引用在内),否则行会表达式结果对象的类型(可能是引用类型)。
```c++
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;
    decltype(*p) c; Error! c is int&
```
