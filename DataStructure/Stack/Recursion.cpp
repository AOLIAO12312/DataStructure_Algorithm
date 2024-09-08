#include<iostream>
#include<unordered_map>
using namespace std;

size_t Fibo(size_t x){
    static unordered_map<size_t,size_t> Map;
    if((x == 0 || x == 1)){
        return 1;
    }else{
        size_t num1;
        if(Map.find(x - 1) != Map.end()){
            num1 = Map[x - 1];
        }else{
            num1 = Fibo(x - 1);
            Map[x - 1] = num1;
        }        
        size_t num2;
        if(Map.find(x - 2) != Map.end()){
            num2 = Map[x - 2];
        }else{
            num2 = Fibo(x - 2);
            Map[x - 2] = num2;
        }
        return num1 + num2;
    }
}

int main(){
    cout << Fibo(70) << endl;
    return 0;
}