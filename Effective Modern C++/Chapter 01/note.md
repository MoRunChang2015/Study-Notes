# 第一章 类型推导

### Item 1:理解模板类型的推导

+ 考虑函数模板:
```c++
template<typename T>
void f(ParamType param);
```

+ 可能出现的情况有三种：
> 1. `ParamType`是指针或引用(不包含universal reference);
> 2. `ParamType`是**universal reference**;
> 3. `ParamType`既不是指针也不是引用。
> 注：universal reference表示类似于`T&&`

+ 第一种情况下，通过`f(expr)`调用函数，类型推导规则如下：
> 1. 若expr的类型是引用，则忽略引用部分
> 2. 通过ParamType的结构推导出T的类型
> 如`ParamType`是`const T&`，当expr是`cont int&`的时候，T为`int`

+ 第二种情况下，通过`f(expr)`调用函数，类型推导规则如下：
> 1. 如果`expr`是左值，那么`T和ParmType`都被推导为左值引用。
> 2. 如果`expr`是右值，那么按照第一种情况的规则推导。
> Item 24会有更详细的解答。

+ 第三种情况，通过`f(expr)`调用函数，类型推导规则如下：
> 1. 若expr的类型是引用，则忽略引用部分
> 2. 忽视expr的const，volatile修饰(Item 40)。

