#include<bits/stdc++.h>
using namespace std;

class LRUCache {
    private:
        class BiListNode{
        public:
            int key = 0;
            int val = 0;
            BiListNode *prior = nullptr;
            BiListNode *next = nullptr;
            BiListNode(int key = 0, int val = 0, BiListNode *prior = nullptr, BiListNode *next = nullptr){
                this->key = key;
                this->val = val;
                this->prior = prior;
                this->next = next;
            }
        };
    public:
        BiListNode *head = nullptr;
        BiListNode *tail = nullptr;
        unordered_map<int, BiListNode*> map;
        int capacity = 0;
        int size = 0;
        LRUCache(int capacity) {this->capacity = capacity;}
    
        int get(int key) {
            if(map.find(key) != map.end()){
                if(map[key] == head){
                    return map[key]->val;
                }
                map[key]->prior->next = map[key]->next;
                if(map[key] != tail){
                    map[key]->next->prior = map[key]->prior;
                }else{
                    tail = map[key]->prior;
                }
                head->prior = map[key];
                map[key]->next = head, map[key]->prior = nullptr;
                head = map[key];
                return map[key]->val;
            }
            return -1;
        }
        
        void put(int key, int value) {
            // 如果存在于缓存，则更新缓存
            if(map.find(key) != map.end()){
                map[key]->val = value;
                // 将该结点调整到头部
                if(map[key] != head){
                    // 调整前驱节点指向
                    map[key]->prior->next = map[key]->next;
                    // 调整后继节点指向
                    if(map[key] != tail){
                        map[key]->next->prior = map[key]->prior;
                    } else {
                        tail = map[key]->prior;
                    }
                    // 调整当前节点指向
                    head->prior = map[key];
                    map[key]->next = head, map[key]->prior = nullptr;
                    head = map[key];
                }
                return;
            }
            // 如果不存在于缓存
            if(size < capacity){
                // 如果没有超过缓存大小，创建新的节点，并设定为头部
                BiListNode *p = new BiListNode(key, value, nullptr, head);
                map[key] = p;
                if (head != nullptr) {
                    head->prior = p;
                }
                head = p;
                if(size == 0){tail = p;}
                ++size;
                return;
            }
            // 如果已达到最大容量
            map.erase(tail->key);
            map[key] = tail;
            tail->val = value;
            tail->key = key;
            if (tail != head) {
                tail->prior->next = nullptr;
                tail = tail->prior;
                head->prior = map[key];
                head = map[key];
            }
        }
    };

int main(){
    LRUCache *obj = new LRUCache(2);
    obj->put(2, 1);
    obj->put(1, 2);
    obj->put(2, 3);
    obj->put(4, 1);
    
    cout << obj->get(1) << endl;
    cout << obj->get(2) << endl;
}