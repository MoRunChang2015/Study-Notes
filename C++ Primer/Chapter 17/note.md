# 第十七章 标准库特殊设施

### 17.1

+ 在**c+11**中，头文件`<tuple>`新定义了**tuple**类似于pair的模板，一个tuple可以有任意数量的成员。每个确定的tuple类型的成员数目是固定的。
```c++
make_tuple(v1,v2,v3,...,vn) // 返回一个给定初始值初始化的tuple

get<i>(t) // 返回t的第i个数据成员的引用。若t是左值返回左值引用，若t是右值返回右值引用。
```

+ 创建一个tuple对象时，可以使用tuple默认构造函数，它会对每个成员进行值初始化。tuple中为每个成员赋初始值的构造函数是explicit的，所以必须使用直接初始化语法
```c++
tuple<size_t, size_t, size_t> threeD = {0, 1, 2}; // 错误

tuple<size_t, size_t, size_t> threeD({0, 1, 2}); // 正确
```

+ 使用`tuple_size<tupleType>::value`获取成员数量，`tuple_element<i, tupleType>::type`获取第i个成员的类型
```c++
typedef decltype(item) trans;
size_t sz = tuple_size<trans>::values;
tuple_element<1,trans>::type cnt = get<1>(item);
```

### 17.2

+ bitset是一个表示二进制的数组，通过指定大小n来创建对象`bitset<n> b`。
```c++
bitset<n> b(s, pos, m, zero, one) // s是一个string,字符数组或C风格的字符串，从pos位置开始m个字符，以zero字符为0，以one字符为1拷贝进入bitset，其中s的拷贝范围中不能包含zero和one以外的字符，可以省略pos，m，zero，one
```

+ 用整形值初始化bitset时，此值会被转换成unsigned long long。bitset从低位开始拷贝，若超出bitset大小就舍去，不足则补零。应该这个构造函数是constexpr,所以整形值必须是constexpr

+ string的下标编号习惯与bitset相反，string下标最大的字符用来初始化bitset中的低位。
```c++
string str("1111111000000000100100");
bitset<32> b(str,5,4); // 从str[5]开始的4个二进制位1100
```

+ 利用`any(), all(), none(), count()`判断或统计bitset中置位的数目，利用`set([pos]), reset([pos]), flip([pos])`改变bitset中一位或多位的值，其中`size()`返回一个constexpr。
```c++
b.test(pos) // 第pos为是置位返回true，否则返回false
b[pos] // 访问第pos位，若b是const，第pos为是置位返回true，否则返回false
b.to_ulong(), b.to_ullong() // 返回一个unsigned long 或者 unsigned long long

b.to_string(zero = ‘0’, one = ’1‘); // 返回一个string， zero默认是'0', one默认是'1'

os << b // 输出

is >> b // 当下一个字符不是0或者1时，或已经读入b.size()个位时，读取停止。
```

### 17.3

+ c++11中，头文件**regex**中定义了正则表达式库如`regex, regex_match, regex_search, regex_replace, sregex_iterator, smatch, ssub_match`

+ 默认情况下regex使用的正则表达式语言是ECMAScript，模式`[[:alpha:]]`匹配任意字母，在定义regex的时候可以设置规范，默认是ECMAScript。
```c++
regex r(re[, f]) // re可以是一个正则表达式，表示范围的迭代器对，string，指向空字符结尾的字符数组，花括号包围的字符列表
r1 = re    // re可以是一个正则表达式，regex对象，string，指向空字符结尾的字符数组，花括号包围的字符列表，将r1中的正则表达式替换为re
r1.assign(re, f)  // 同上
r.mark_count()  // r中子表达式数目

// 配置flag：
regex r("[[:alnum:]]+\\.(cpp|cx|cc)$)", regex::icase); // 忽略大小写。

// \\. 表示 \.
```
+ 一个正则表达式的语法是否正确是在运行时解析的。若发生错误会抛出regex_error异常，调用.what查看具体内容。

如果输入的序列类型|使用正则表达式类
-----|------
string|regex,smatch,ssub_match,sregex_iterator
const char*|regex,cmatch,csub_match,cregex_iterator
wstring|wregex,wsmatch,wssub_match,wsregex_iterator
const wchar_t*|wregex,wcmatch,wcsub_match,wcregex_iterator

+ regex_search只返回第一个匹配，利用**sregex_iterator**这个迭代器适配器获取所有匹配。
```c++
sregex_iterator it(b, e, r) // b,e表示string的范围迭代器，利用正则表达式r定位第一个匹配
sregex_iterator end // 尾后迭代器

*it
it-> 返回一个smatch对象的引用或指向smatch对象的指针。
```

+ smatch对象可以使用prefix和suffix返回表示匹配之前和匹配之后的ssub_match对象。
```c++
it->prefix().length() // 前缀大小
it->prefix().str()
```

+ 正则表达式中的模式通常包含一个或者多个**子表达式**，正则表达式语法通常用括号表示子表达式。如`"([[:alnum:]]+)\\.(cpp|cx|cc)$)"`第一个子表达式是([[:alnum:]]+)，第二个是(cpp|cx|cc)$)。

+ 通过regex_search得到的smatch也包含了子表达式匹配的信息。
```c++
m.ready() // 是否经过regex_search获取结果

m.size() // 返回匹配的正则表达式中子表达式的结果，若匹配失败返回0

m.empty() // size()为0返回true

m.length(n) // 第n个匹配的子表达式的大小

m.position(n) // 第n个子表达式距序列开始的距离

m.str(0) // 第n个表达式匹配的string,第0个是整个模式对应的匹配

m[n] // 第n个子表达式的sub_match对象

m.begin(), m.end()
m.cbegin(), m.cend() // 迭代器。

ssub_match成员有：
matched // 是否有匹配
first, second // 返回指向匹配序列的首元素的和尾后位置的迭代器。
length()  // 长度
str() // 返回string
```

+ 使用match的format和regex_replace将正则表达式匹配的内容格式化。`fmt="$2.$5.$7"`表示使用第二个第五个第七个子表达式匹配的结果中间用'.'连接。
```c++
string new_s = smatch.format(fmt);
string new_s2 = regex_replace(s, r, fmt);
```

+ 可以使用在std::regex_constants命名空间中的标识控制regex_search,regex_match或是smatch的format成员的行为。
```c++
regex_replace(s, r, fmt, std::regex_constants::format_no_copy); // 只返回格式化部分
```

### 17.4

+ **c++11**中**random**头文件定义了一系列的随机数引擎类和随机数分布类，用于产生随机数。
```c++
default_random_engine e;
for (size_t i = 0; i < 10; ++i)
    cout << e() << " ";   // 生成下一个随机数
    
// Engine e(s);
// e.seed(s)   // 设置种子
// e.min(),e.max() // 最小值最大值
// Engine::result_type // unsigned整型类型
// e.discard(u) 将引擎推进n步，u的类型为unsigned long long
```
+ 利用随机数分布类可以产生一个得到指定范围内的数的随机数。
```c++
uniform_int_distribution<unsigned> u(0, 9);  // 0-9均匀分布
default_random_engine e;
u(e);
```

+ **随机数发生器**一般指分布对象和引擎对象的组合。一个给定的随机数发生器一直会生成相同的随机数序列。一个函数如果定义了局部的随机数发生器，应该将其(包括引擎和分布对象)定义为static的。否则，每次调用函数都会产生相同的序列，当然也可以通过提供不同的种子解决。
```c++
default_random_engine e(time(0)) // time返回的是以秒计算的，因此这种方式只适用于生成种子的间隔为秒级或更长的应用。
```
+ 可以定义分布对象生成0-1之间的实数`uniform_real_distribution<double> u(0,1)`,也可以生成正太分布`normal_distribution<> n(4, 1.5) // 默认double`，也可以生成二项分布`bernoulli_distribution b`, 它有50%概率返回true;
```c++
default_random_engine e;
bernoulli_distribution b;
b(e);

bernoulli_distribution b(0.55); // 为true的概率是0.55
```

### 17.5

+ `boolalpha`可以让布尔类型输出"true"或者“false”。利用控制符号hex，oct，dec让输出改为十六进制，八进制，十进制，使用控制符"showbase"显示当前进制，“noshowbase”停止。

+ 通过配饰os的precision属性，或者使用setprecision控制符控制浮点数精度,setprecision和其他接受参数的控制符都定义在iomanip头文件中。
```c++
cout.precision(12) // 设置12位进度
// 等价
cout << setprecision(12)
```

+ 标准库提供了三种做法退回从输入流中读取的字符，peek返回输入流中下一个字符的副本，但不会将它从流中删除，unget使得输入流向后移动，从而最后读取的值又回到流中，putback退回从流中读取的最后一个值，但它接受一个参数，此参数必须与最后读取的值相同。peek和无参数版本的get都以int类型从输入流返回一个字符。

+ 标准库定义了一些列的函数如`is.get(sink,size, delim), is.getline(sink, size, delim), is.read(sink, size), is.gcount(), os.write(source,size), is.ignore(size,delim)`,其中is.get(sink, size, delim)表示从is中读取size个字节或遇到delim字符为止到sink中，调用gcount确定最后一个未格式化输入后操作读取里多少个字符。

+ 通过seek和tell函数实现对fstream和sstream的随机读取，一个通过将标记seek到一个给定的位置来重定位，另一个函数tell我们标记的当前位置。在输入和输出流中有不同的版本，通过后缀是g(输入)和p(输出)判断。详细操作见[seek_tell.cpp]((https://github.com/MoRunChang2015/Study-Notes/blob/master/C%2B%2B%20Primer/Chapter%2017/code/17.5/seek_tell.cpp))
