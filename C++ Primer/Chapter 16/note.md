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
