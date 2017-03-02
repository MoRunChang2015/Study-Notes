# 第十八章 用于大型程序的工具

### 18.1

+ 在栈展开的过程中，运行类类型的局部对象的析构函数。因为这些析构函数是自动执行的，所以它们不应该抛出异常。一旦在栈展开过程中析构函数抛出了异常，并且析构函数自身没能捕获到该异常，则程序被终止。

+ 抛出一条表达式时，该表达式的静态编译时的类型决定了异常对象的类型，在执行throw语句的时候会执行拷贝构造函数在编译器管理的内存空间中创建一个表达式的值的类型的对象，并将表达式的值拷贝构造/移动构造。

+ 在catch处理的代码块中可以将异常重新抛出，`throw;`即可，该异常会沿着调用链向上抛出(向调用链的上一层，当前层的不能catch)。

+ `catch(...)`可以**捕获所有异常**。

+ 要想处理构造函数初始值抛出的异常，需要将构造函数写成函数try语句块
```c++
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) try: data(std::make_shared<std::vector<T>> (il)) {
} catch (const std::bad_alloc &e) { ... };
```

+ 如果编译器确认函数不会抛出异常，他就能执行某些特殊的优化操作，而这些优化操作并不适用于可能出错的代码。**c++11**，可以通过提供noexcept说明指定某个函数不会抛出异常。可以在函数指针的声明和定义中指定noexcept，但是在typedef或者类型别名中不能出现，在成员函数中，noexcept说明符需要跟在const以及引用限定符之后，而在final，override或虚函数=0之前。

+ 若函数中声明了noexcept而抛出了异常，程序将直接终止。

+ 同时noexcept也是一个一元运算符，类似于sizeof，它不会去指向括号内的内容，返回货号内的内容是否抛出异常。
```c++
noexcept(recoup(i)) // 若recoup抛出异常则结果为true，否则为false
```

+ 函数指针以及该函数指针所指的函数必须有一直的异常说明，虚函数承诺不会抛出异常，后续派生处的虚函数也必须做出相应的承诺。当编译器合成拷贝构造函数控制成员的时候，同时也会生成一个异常说明。如果对所有成员和基类的所有操作都不抛出异常，则合成的是noexcept，否则noexcept(false)。如果我们定义了一个析构函数但是没有为他提供异常说明，则编译器将合成一个，合成异常说明将与假设编译器为类合成析构函数时所得的异常说明一致。


### 18.2

+ 命名空间作用域后面无需分号。模板特例化必须定义在原始模板所属的命名空间中。

+ **c++11**中引入了一种新的嵌套命名空间，称为**内联命名空间**。内联命名空间中的名字可以被外层命名空间直接使用。定义的方式是在关键字namespace前添加inline
```c++
inline namespace FifthEd {
   // ..
}

namespace FifthEd {   // 隐式内联
   class Query_base {/*..*/}
};
```

+ 未命名的命名空间是指关键字namespace后紧跟花括号括起来的一系列声明语句。未命名的命名空间中定义的变量有静态生命周期。未命名的命名空间运行在某个文件中不连续，但是不能跨文件。未命名的命名空间中定义的名字的作用域与该命名空间所在的作用域相同。

+ 在文件中进行静态声明的做法已经被c++标准取消了，现在的做法是使用未命名的命名空间。

+ 可以给命名空间起别名
```c++
namespace primer = cplusplus_primer;
```

+ 标准库move和forward函数都接受一个右值引用的函数形参，所以他们可以匹配任何类型。如果我们的程序也定义了一个接受单一形参的move函数，则不管该形参是什么类型，应用程序的move函数都将与标准库函数的版本冲突。

+ using指示将命名空间的成员被提升到外层外层作用域中，如果命名空间中的某个函数与该命名空间所所属作用域的函数同名，则命名空间的函数将被添加到重载集合中。