#include<iostream>
#define MaxSize 10
using namespace std;
template <class T>
class Linear_List{
private:
    int size;
    int Max_size;
    T* list;
public:
    Linear_List(){
        this->list = new T[MaxSize];
        this->Max_size = MaxSize;
        this->size = 0;
    }
    ~Linear_List(){
        delete list;
    }
    int getSize(){
        return this->size;
    }
    bool add(T t){
        if(size < MaxSize){
            this->list[this->size] = t;
            ++this->size;
            return true;
        }else{
            cout << "list is full" << endl;
            return false;
        }
    }
    T getElem(int index){//按位查找
        if(index < this->size){
            return list[index];
        }else{
            cout << "index is excessive" << endl;
            return -1;;
        }
    }
    int LocateElem(T t){//按值查找
        for(int i = 0;i<this->size;++i){
            if(this->list[i] == t){
                return i+1;
            }
        }
        return 0;
    }
};

int main(){
    Linear_List<int> ll;
    for(int i = 0;i<9;++i){
        ll.add(i*7);
    }
    for(int i = 0;i<ll.getSize();++i){
        cout << ll.getElem(i) << endl;
    }
    cout << "The position of 49 is:" << ll.LocateElem(49) << endl;
    return 0;
}
