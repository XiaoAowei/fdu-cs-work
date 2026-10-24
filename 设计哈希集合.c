#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct {
     Node* buckets[10000]; 
} MyHashSet;


MyHashSet* myHashSetCreate() {
      MyHashSet* obj = (MyHashSet*)calloc(1, sizeof(MyHashSet));
    return obj;
  
}

void myHashSetAdd(MyHashSet* obj, int key) {
      int index = key % 10000; // 算哈希值（去哪个桶）
    Node* curr = obj->buckets[index];
    
    // 先检查是不是已经有了，有了就不加
    while (curr != NULL) {
        if (curr->key == key) return;
        curr = curr->next;
    }
    
    // 没有的话，头插法加进去
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = obj->buckets[index];
    obj->buckets[index] = newNode;
}

void myHashSetRemove(MyHashSet* obj, int key) {
      int index = key % 10000;
    Node* curr = obj->buckets[index];
    Node* prev = NULL;
    
    // 找这个节点
    while (curr != NULL) {
        if (curr->key == key) {
            // 找到了，把它从链表里抠出来
            if (prev == NULL) {
                obj->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr); // 释放内存
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int index = key % 10000;
    Node* curr = obj->buckets[index];
    
    // 遍历链表找
    while (curr != NULL) {
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) {
    // 把每个桶里的链表节点全释放掉
    for (int i = 0; i < 10000; i++) {
        Node* curr = obj->buckets[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(obj); // 最后释放集合本身
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/
