# 第十四章 重载运算与类型转换

### 14.1

+ 通常情况下，不应该重载逗号，取地址，逻辑与和逻辑或运算符。赋值(=)，小标([])，调用(())和访问箭头(->)运算符都必须是成员。

### 14.2

+ 通常，输出运算符应该主要负责打印对象的内容而非格式，输出运算符不应该打印换行符。

+ 输入输出运算符必须是非成员函数。

+ 输入运算符必须处理输入可能失败的情况，而输出运算符不需要。

### 14.4

+ 可以定义参数是`initializer_list<T>`的赋值运算符。
```c++
StrVec &operator=(std::initializer_list<std::string>);
```

### 14.5

+ 如果一个类包含下标运算符，则它通常会定义两个版本，一个返回普通引用，另一个是类的常量成员并且返回常量的引用。


### 14.6

+ 定义前置版本的递增/递减运算符。
```c++
class StrBlobPtr {
public:
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
}
```

+　定义后置版本的递增/递减运算符。差别在于一个不被使用的int类型形参，在定义中也无需为它命名，当使用后置运算符时，编译器为这个形参提供一个值为0的实参，通常返回对象的原值，返回的形式是一个值而非引用。
```c++
class StrBlobPtr {
public:
    StrBlobPtr& operator++(int);
    StrBlobPtr& operator--(int);
}
```

### 14.8

+ 函数调用运算符必须是成员函数，一个类可以定义多个不同版本的调用运算符，相互之间应该在参数数量或类型上有所区别。

+ 标准库定义了一系列的函数对象，如`plus<Type> minus<Type>`，可以利用这些对象用于泛型算法，泛型算法的callable对象可以是标准库的函数对象，也可以是自定义的函数对象。
```c++
sort(svec.begin(), svec.end(), greater<string>());


```

+ 标准库的**function**类型，可以用函数指针，lambda或者函数对象初始化。
```c++
int add(int i, int j) { return i + j;}

auto mod = [](int i, intj) { return i % j};
// 函数对象
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
}

function<int(int, int)> f = add;
function<int(int, int)> f2 = mod;
function<int(int, int)> f3 = divide;
```

### 14.9

+　类型转换运算符是类的一种特殊成员函数，他负责将一个类类型的值转换成其他类型。(不允许转换成数组或者函数类型，但是可以转换成指针或引用类型)
```c++
operator type() const;

class SmallInt {
public:
   operator int() const {return val};
privateL
    std::size_t val;
}
```

+ 隐式的类型转换运算符可能产生意外的结果，所以c++11提供了显式的类型转换运算符，就是在声明前加**explicit**

```c++
explicit operator type() const;

class SmallInt {
public:
   explicit operator int() const {return val};
privateL
    std::size_t val;
}
```

+ 继上条，如果表达式被用作条件，编译器会将显式的类型转换自动应用于它。在下列情况下会被隐式执行。
1. if, while, do 语句的条件部分
2. for语句头的条件表达式
3. 逻辑非，逻辑或，逻辑与运算符的运算对象。
4. 条件运算符(?:)的条件表达式。

+ 避免有二义性的类型转换，比如两个类提供相同的类型转换：A提供了一个接受B类对象的转换构造函数，同时B类定义了一个转换目标是A类的类型转换运算符。又比如类定义了多个转换规则，而这些规则涉及的类型本身可以通过其他类型转换联系到一起。

+ 避免转换目标是内置算术类型转换。特别是已经定义了一个转化成算术类型的类型转换时，不要再定义接受算术类型的重载运算符，不要定义转换到多种算术类型的类型转换。

+ 总之，除了显示地向bool类型的转换外，应该尽量避免定义类型转换函数并尽量可能地限制那些"显然正确"的非显式构造函数(使用`explictit`修饰转换运算符)。
