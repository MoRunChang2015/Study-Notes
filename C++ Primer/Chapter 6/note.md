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
