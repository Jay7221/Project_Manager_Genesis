#include<iostream>
int main(){
    freopen("Error.txt", "w", stderr);
    std::string s = "ls Projectsd";
    std::cout << system(s.c_str()) << std::endl ;
    return 0;
}