# 第十六章 模板与泛型编程

### 16.1

+ 在模板中定义类型参数，使用关键字typename或者class(两者是一样的)，也可以定义非类型参数，表示一个值而非一个类型。非类型参数被一个用户提供的或编译器推断出的值代替，这些值必须是常量表达式。
```c++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1,p2);
}

compare("hi","mom"); // 编译器推断N和M
```

+ 函数模板和类模板成员函数的定义通常放在头文件中。因为C++中每一个对象所占用的空间大小，是在编译的时候就确定的，在模板类没有真正的被使用之前，编译器是无法知道，模板类中使用模板类型的对象的所占用的空间的大小的。只有模板被真正使用的时候，编译器才知道，模板套用的是什么类型，应该分配多少空间。

+ 编译器不能为类模板推断模板参数类，但是函数模板可以。

+ 类模板的成员函数具有和模板相同的模板参数，因此，定义在类模板外的成员函数就必须以关键字template开始，后接类模板参数列表。
```c++
template <template T>
void Blob<T>::check() {
 .....
}
```

+ 如果一个成员函数没有被使用，它将不会被实例化。成员函数只有在被用到的时候才进行实例化。

+ 在类模板自己的作用域中，可以直接使用模板名而不提供实参。当在类模板外定义成员时，只有遇到类名后才表示进入类的作用域。

+ 一个类模板包含一个非模板友元，则友元被授权可以访问所有模板实例。如果友元自身是模板，类可以授权给所有友元模板实例，也可以只授权给特定实例。友元声明中使用类模板不同的模板参数，就让所有实例成为友元。

+ 新标准中(c++11)，可以用模板类型参数声明为友元。
```c++
template <typename Type>
class Bar {
    friend Type;
};
```

+ c++11允许为类模板定义一个类型别名
```c++
template<typename T>
using twin = pair<T, T>;

twin<string> authors;
```

+ 类模板的static成员需要在类外定义，如下。对于任意给定的类型X都有一个`Foo<X>::ctr`，类似于任何成员函数，一个static成员函数只有在使用时才会实例化。
```c++
template<typename T>
size_t Foo<T>::ctr = 0;
```

+ 当希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class,因为c++语言假定通过作用域运算符访问的名字不是类型。
```c++
template <typename T>
typename T::value_type top(const T& c) {
    return typename T::value_type();
}

```

+ **c++11**，允许为函数模板和类模板提供默认参数，但是无论何时使用一个模板，都必须再模板名之后接上尖括号，即使全部使用默认参数。

+ 一个类(无论是普通类还是模板类)可以包含本身是模板的成员函数，这种成员称为成员模板。成员模板不能是虚函数。
```c++
class DebugDelete {
public:
    DebugDelete(std::ostream &s=std::cerr) : os(s) {}
    
    template <typename T> void operator()(T *p) const
      { os << "deleting" << std::endl; delete p;}
private:
    std::ostream os;
};

// 使用

int * ip = new int;
DebugDelete()(ip);

unique_ptr<string, DebugDelete> sp(new string, DebugDelete());
// 自动推断模板参数类型。
```

+ 对于类模板，也可以为其定义成员模板。
```c++
template <typename T> class Blob {
    template<typename It> Blob(It b, It e);
};

template <Typename T>
template <Typename It>
Blob<T>::Blob(It b, It e):data(std::make_shared<std::vector<T>>(b, e)) {}

// 使用

int ia[] = {0,1,2,3,4,5,6,7,8,9};

Blob<int> al(begin(ia), end(ia));
```

+ 当模板被使用的时候才会进行实例化，这会导致多个文件中有同一个实例。**c++11**可以通过**显式实例化**来避免。
```c++
extern template declaration; // 实例化声明， 不会生成实例代码在其他位置查找定义
template declaration;        // 实例化定义
// declaration是一个类或函数声明

extern template class Blob<string>;
extern tempalte class int compare(const int&, const int&) 
// 实例化出现再其他位置。


// 在其他文件中
template int compare(const int&, const int&);
template class Blob<string>;
```

+ 实例化定义会实例化所有成员，包括内联的成员函数。


### 16.2

+ 将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有const转换以及数组或函数到指针转换。正常类型转换应用于普通函数实参，也适用于显式指定的实参。

+ 当使用一个函数模板初始化一个函数指针或者为一个函数指针赋值时，编译器使用指针的类型来推断实参。
```c++
int (*pf)(const int&, const int&) = compare;
```

+ 当参数是一个函数模板实例的地址时，程序上下文必须满足：对每个模板参数，能唯一确定其类型或值。
```c++
void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));

func(compare) // Error

func(compare<int>) // 正确
```

+ 当将一个左值传递给函数的右值引用参数，且此引用指向模板类型参数(T&&)，编译器推断模板类型参数为实参的左值引用类型。
```c++
template<typename T> void f3(T&&);
int i;
f3(i); // 此时推断T的类型是int&,也就是类型int&的右值引用
```

+ 如果间接参加一个引用的引用，这些引用形成了折叠。在所有情况(除了一种情况)下，引用会折叠成一个普通的左值引用类型。
```c++
x& &,X& &&, X&& & 都折叠成X&
X&& &&折叠成X&&
```

+ 引用的折叠只能应用与间接创建的引用的引用，如类型别名或模板参数。

+ 如果一个函数参数是指向模板参数类型的右值引用(T&&),则可以传递给它任意类型的实参。如果将一个左值传递给这样的参数，则参数被实例化为一个普通的右值引用。

+ 标准库是这样定义move的
```c++
template<typename T>
typename remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```

+ 如果一个函数参数是指向模板类型参数的右值引用(T&&)，它对应的实参的const属性和左值/右值属性将得到保持。
```c++
template<typename F, typename T1, typename T2>
void filp2(F f, T1&& t1, T2&& t2) {
    f(t2,t1);
}

// 但是这种做法没法解决接收右值引用的函数。
void g(int &&i, int& j) {
    cout << i << " " << j << endl;
}
```

+ 跟move一样定义再utility中的std::forward返回显式实参类的右值引用。若`forward<T>`中T类型是普通(非引用)类型，则返回的是T&&, 若T是一个左值引用类型，返回类型经过折叠后是一个左值引用类型。所以继上条：
```c++
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
```

### 16.3
