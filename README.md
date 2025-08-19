请将circular_list和circular_queue文件放入指定文件夹。
示例（适用于Dev-C++）：
C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++
然后将stl_circular_list.h和stl_circular_queue.h文件放入指定的子文件夹中。
示例（适用于Dev-C++）：
C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++\bits
之后，在你的 C++ 代码中，用以下方式包含它们：
cpp
#include <循环列表>
#include <循环队列>
*（需要编译器支持 #__has_include 或 C++17 标准）*
