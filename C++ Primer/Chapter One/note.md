# 第一章 开始

### 1.1

+ 在**UNIX**和**WINDOWS**系统中，执行完一个程序后，都可以通过**echo**命令获取其返回值。如在UNIX系统中:

   ```
   $ echo $?
   ```
   
   在WINDOWS系统中:
   
   ```
   $ echo %ERRORLEVEL%
   ```
   
   需要注意的是，再UNIX系统中系统获取到的返回值是一个**unsigned char**即取值范围是0-255，超出则上
   /下溢出处理。
