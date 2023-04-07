1. include 文件夹中的 client.h 和 message.h 里面有写函数的功能

2. demo.cpp 是代码的演示，使用 g++ demo.cpp src/client.cpp -o demo 编译它

3. 运行服务器 server 和 demo 就可以收到服务器回传的信息，1表示成功 0表示失败