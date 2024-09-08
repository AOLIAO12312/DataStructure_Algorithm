#include <iostream>  
#include <regex>  
#include <string>  
  
int main() {  
    std::string text = "Hello, this is a sample text with some numbers 12345.";  
    std::regex pattern("\\d+"); // 匹配一个或多个数字  
    std::smatch matches; // 用于存储匹配结果  
  
    if (std::regex_search(text, matches, pattern)) {  
        std::cout << "Found match: " << matches.str() << std::endl;  
    } else {  
        std::cout << "No match found." << std::endl;  
    }  
  
    return 0;  
}