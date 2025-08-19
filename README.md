Please place the circular_list and circular_queue files into the specified folder.
Example (for Dev-C++):
C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++
Then place the stl_circular_list.h and stl_circular_queue.h files into the specified subfolder.
Example (for Dev-C++):
C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++\bits
Afterwards, in your C++ code, include them with:
#include <circular_list>
#include <circular_queue>
*(Requires compiler support for #__has_include or C++17 standard)*
