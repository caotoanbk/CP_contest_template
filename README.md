"cpp": "cd $dir && g++ -DON_PC --std=c++17 -I D:/C++/CP/99.Share -O2 -g -Wall -Wextra -Wpedantic $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt"

##2D
^(?!\s*#define)(?!.*cin\s*>>).*?(\w+)\[(\w+)\]\[(\w+)\]
MAT($1,$2,$3)

#1D
^(?!\s*#define)(?!.*cin\s*>>).*?(\w+)\[(\w+)\]
VEC($1,$2)