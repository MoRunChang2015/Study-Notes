# 第五章 函数

### 6.2

+ 因为数组的特性：**不允许拷贝数组**和**使用数组时(通常)会将其转换成指针**,所以再形参中使用数组如下，尽管表现形式不同，但是三个函数是等价的，每个函数的唯一形参是`const int*`。
```c++
    void print(const int*);
    void print(const int[]);
    void print(const int[10]);
```

+ 变长函数参数可以使用模板类型**initializer_list**，特别的**initializer_list**对象中的元素永远是常量值，我们无法改变该对象中元素的值，注意：`lst2(lst);lst2=lst`拷贝或者赋值一个initializer_list对象不会拷贝列表中的元素，拷贝后原始列表和副本共享元素。

+ 省略符形参应该仅仅用于c和c++通用的类型。特别应该注意的是，大多数类类型的对象再传递给省略符形参都无法正常拷贝。

### 6.3

+ 不要返回局部对象的应用或指针，因为函数完成后，它所占用的储存空间也随之释放掉。

+ 函数通过引用返回左值，调用一个返回引用的函数得到左值，其他返回类型得到右值，可以像其他左值一样使用返回引用的函数的调用，特别地，我们能为返回类型是非常量引用的函数的结果赋值。如下
```c++
char& get_val(string& str, string::size_type ix) {
    return str[ix];
}
int main() {
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'A';
    cout << s << endl;
    return 0；
}
```

+ 在头文件**cstdlib**中定义了两个预处理变量，`EXIT_FAILURE`和`EXIT_SUCCESS`可以在main函数中返回这两个变量表示程序运行的失败还是成功。

+ 函数返回数组的指针定义形式是`Type (*function(parameter_list))[dimension],这样可读性不好，建议使用别名的形式
```c++
    typedef in arrT[10];
    using arrT = int[10];
    arrT* func(int i);
```

+ c++11可以使用**尾置返回类型**，注意要在本该出现类型的地方放置一个**auto**
`auto func(int i) -> int （*）[10];`

+ c++11可以使用**decltype**，如`decltype(array) * arrPtr(int i);`

### 6.4

+ **main函数**不能重载

+ **顶层const**不影响传入函数的对象。一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开来。
```c++
Record lookup(Phone);
Record lookup(const Phone); // Error!!

Record lookup(Phone*);
Record lookup(Phone* const); // Error!!
```

+ 如果形参是某种类型的指针或者引用，则通过区分其指向的是常量对象还是非常量对象可以实现函数重载，此时的const是底层的，此时当我们传递一个非常量对象或者指向非常量对象的指针的时候，编译器会优先选用非常量版本的函数。
```c++
Record lookup(Account&);
Record lookup(const Account&);

Record lookup(Account*);
Record lookup(const Account*);
```
+ 如果我们在内层作用域中声明函数，它将隐藏外层作用域中声明的同名实体，在不同作用域中无法重载函数名。原因是c++中，名字查找发生在类型检查之前。

### 6.5

+ 在给定作用域中一个形参只能被赋予一次默认实参，换句话说，函数的后续声明只能为之前那些没有默认值的形参添加默认实参，已经有默认实参的形参不能再添加即使默认值跟之前的一样，而且该形参右侧的所有形参必须都有默认值。建议放在头文件中。

+ 局部变量不能作为默认实参。初次之外，只要表达式的类型能够转换成形参所需的类型，该表达式就能作为实参。

+ constexpr函数是指能用于常量表达式的函数。其中constexpr函数的返回类型以及所有形参的类型都是字面值类型，而且函数体中必须有且只有一条return语句。为了能够在编译过程中随时展开，constexpr函数被隐式地指定为内联函数。

+ constexpr函数的返回值并非一个常量。详见[constexpr.cpp](https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%206/code/6.5/constexpr.cpp)
```c++
constexpr int new_sz() {return 42;)

constexpr size_t scale(size_t cnt) {　// 如果cnt是一个常量表达式，则scale也是常量表达式
    return new_sz() * cnt;
}

int arr[scale(2)];

int i = 2;
int arr2[scale(i)]; // Error! scale(i)不是常量表达式
```

+ 通常内联函数和constexpr函数通常定义再头文件中。

+ 可以通过宏定义**`NDEBUG`**来限制assert的行为，如果NDEBUG时assert将会无效。在编译过程中使用`CC -D NDEBUG macin.cpp`相当于在main.cpp的第一行中写`#define NDEBUG`

+ c++编译器定义了几个名字用于调试
```c++
    __FILE__ 存放文件名的字符串字面值
    __LINE__ 存放当前行号的整型字面值
    __TIME__ 存放文件编译时间的字符串字面值
    __DATE__ 存放文件编译日期的字符串字面值
```
