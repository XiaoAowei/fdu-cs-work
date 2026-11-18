typedef struct Node {
    int key;
    int value;
    struct Node *prev;
    //prev 是一个指针，它指向另一个 struct Node 类型的结构体。
    struct Node *next;
    //next 是一个指针，指向下一个 struct Node
} Node;
//把 struct Node 这个类型，起个别名叫 Node。

typedef struct HashNode {
    int key;
    Node *node;
    struct HashNode *next;
} HashNode;


typedef struct {
   //匿名结构体
     int capacity;
    int size;
    Node *head;          /* 虚拟头，head->next 为最近使用 */
    Node *tail;          /* 虚拟尾，tail->prev 为最久未使用 */
    HashNode **buckets;  /* 哈希桶（链地址法） */
    int bucketCount;//桶的数量
} LRUCache;

/* ---------------- 双向链表操作 ---------------- */

static void addToHead(LRUCache *obj, Node *node) {
    //addToHead —— 函数名
    //把 node 插到链表头部
    //：传入一个指向 LRUCache 结构体的指针。
    //传入一个指向 Node 的指针，即要插入的那个链表节点。
    node->prev = obj->head;
    node->next = obj->head->next;
    obj->head->next->prev = node;
    obj->head->next = node;
}
//把节点node插到 head 后面

static void removeNode(Node *node) {
     //removeNode：函数名，"移除节点"

//Node *node：要删除的那个节点指针
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
//删除code

static void moveToHead(LRUCache *obj, Node *node) {
   //先把 node 从原位置摘掉，再把它插到头部。
    removeNode(node);
    //把 node 从它现在的位置摘出来。
    addToHead(obj, node);
    //把 node 插到 head 后面
}

/* ---------------- 哈希表操作 ---------------- */
static unsigned int hashKey(int key, int bucketCount) {
    //函数名："计算 key 的哈希"
    //int bucketCount	输入：桶的数量（结果要落在这个范围内）
    unsigned int h = (unsigned int)key;
    //含义：把 key 转成无符号整数，存进 h。
    //key是查找用的名字，value是实际存的数据
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    return h % (unsigned int)bucketCount;
}
/*hashKey 把任意整数 key 变成 [0, bucketCount) 的桶下标：先转无符号（处理负数），再两次"移位异或"把高位混到低位，中间乘一个魔数进一步打散，最后取模落到桶范围内。
目的是让不同 key 尽量均匀分布到不同桶，减少冲突，保证哈希表平均 O(1)。

你不需要背这个函数，知道"它负责把 key 变成桶下标、做扰动让分布均匀"就够了。*/

static HashNode *hashLookup(LRUCache *obj, int key) {
    //函数名："哈希查找"
    //给定一个 key，算出它在哪个桶，然后顺着那个桶的链表找，找到就返回节点，找不到返回 NULL。
    unsigned int idx = hashKey(key, obj->bucketCount);
    //idx 是一个变量名，是 index（索引/下标）的缩写，存的是"这个 key 应该放在第几号桶
    //obj->bucketCount 是什么：顺着 obj 找到缓存结构体，取出 bucketCount 成员——就是桶的数量
    //用 hashKey 算出 key 应该落在哪个桶，存进 idx。
    HashNode *p = obj->buckets[idx];
    //obj->buckets 是桶数组（HashNode **）
    //obj->buckets[idx] 是第 idx 个桶的链表头指针
    //取出 idx 号桶的链表头，赋给 p
    while (p) {
        /*while (p) 什么意思
只要 p 不是 NULL，就继续循环。 等价于 while (p != NULL)。

p 从桶头开始，沿着 next 往后走，直到 p == NULL（链表结束）*/
        if (p->key == key) return p;
        p = p->next;
    }
    //从桶头开始，挨个比对 key，一样就返回，不一样就看下一个。"
    return NULL;
}

static void hashInsert(LRUCache *obj, int key, Node *node) {
    //函数名：哈希插入
    //LRUCache *obj	缓存指针（要访问 buckets）
    unsigned int idx = hashKey(key, obj->bucketCount);
    //pp 指向"一个存着节点地址的格子"。*pp 就是那个格子里的节点地址。


    HashNode *hn = (HashNode *)malloc(sizeof(HashNode));
    //malloc(sizeof(HashNode))	分配一块 HashNode 大小的内存，返回 void *
    //(HashNode *)	强制转换成 HashNode *
    //"新建一个 HashNode，hn 指向它。"
    hn->key = key;
    hn->node = node;
    hn->next = obj->buckets[idx];
    //把参数 key 存进 hn->key。
    //把参数 node（链表节点指针）存进 hn->node。
    //这就是哈希表和链表的连接点：HashNode 通过 node 指针指向链表节点。
    ///新节点 hn 的 next 指向原来桶里的第一个节点。
      //obj->buckets[idx]：第 idx 号桶原来的链表头
    obj->buckets[idx] = hn;
 //把桶头指针改成指向 hn。 
}

/*想象一排挂钩，每个钩子上挂着一个牌子，牌子上写着下一个钩子在哪。
你手里拿着一个"指向钩子的指针"
一级指针：指向牌子（节点）
二级指针：指向"挂绳"（存着牌子地址的那个地方）
删除节点时，你要改的是"挂绳"，不是牌子本身。所以需要指向挂绳的指针 = 二级指针。
*/
static void hashDelete(LRUCache *obj, int key) {
    unsigned int idx = hashKey(key, obj->bucketCount);
    //算桶下标
    HashNode **pp = &obj->buckets[idx];
    //obj->buckets[idx]：桶头格子（存着第一个节点地址）
    //&obj->buckets[idx]：这个格子的地址
    //pp 指向"一个存着节点地址的格子"。*pp 就是那个格子里的节点地址。
    //pp ──→ [buckets[idx]] ──→ [A] → [B] → [C] → NULL
        //*pp = A
//pp 现在指着"桶头这个格子"，*pp 就是 A的地址。

    while (*pp) {
  //*pp 是当前格子里的节点地址。只要不是 NULL，就继续。
//*pp = A，非 NULL，进入
//如果桶空：*pp = NULL，直接跳过循环，函数结束（没找到）
        if ((*pp)->key == key) {
            //顺着 A 的地址，取 A 的 key 成员
            //key 是函数参数，要删除的那个 key。
            HashNode *tmp = *pp;
            //记住当前节点
            *pp = tmp->next;
            //把格子里的值改成下一个节点（跳过当前节点）
            free(tmp);
            //释放当前节点
            return;
        }
        pp = &(*pp)->next;
        //：当前节点的 next 格子（存着下一个节点地址）
        //pp 从"指向当前节点的格子"挪到"指向下一个节点的格子"
    }
}

/* ---------------- 公共接口 ---------------- */
LRUCache* lRUCacheCreate(int capacity) {
    //函数名：创建 LRU 缓存
  LRUCache *obj = (LRUCache *)malloc(sizeof(LRUCache));
  //分配一块 LRUCache 大小的内存，返回 void *
//(LRUCache *)	强转成 LRUCache *
//向系统要一块能装下 LRUCache 的内存，obj 指向它。"
    obj->capacity = capacity;
    obj->size = 0;
    //这个缓存最多装 capacity 个，现在装了 0 个

    /* 虚拟头尾节点，简化边界处理 */
    obj->head = (Node *)malloc(sizeof(Node));
    obj->tail = (Node *)malloc(sizeof(Node));
    //申请两个 Node，一个当虚拟头，一个当虚拟尾。
    obj->head->prev = NULL;
    obj->head->next = obj->tail;
    obj->tail->prev = obj->head;
    obj->tail->next = NULL;
    //head 前面没人（它是链表最前）
//	head 的右手拉 tail
//	tail 的左手拉 head
	//tail 后面没人（它是链表最后）
    //NULL ← head ? tail → NULL

    /* 桶数量取 2*capacity+1，降低冲突概率 */
    obj->bucketCount = capacity * 2 + 1;
    obj->buckets = (HashNode **)calloc(obj->bucketCount, sizeof(HashNode *));
//calloc 是 C 标准库函数，分配内存并清零。它接收两个参数：
//分配一个"桶数组"，每个格子存一个 HashNode *，全部初始化为 NULL。
    return obj;   
    //把缓存指针返回给调用者。
}

int lRUCacheGet(LRUCache* obj, int key) {
    //函数名：LRU 缓存查询
    HashNode *hn = hashLookup(obj, key);
    //调用 hashLookup，在哈希表里找 key
    //找到 → 返回对应 HashNode 的指针
//没找到 → 返回 NULL
//去哈希表里查这个 key，hn 接住结果
    if (!hn) return -1;
    //!hn 等价于 hn == NULL。
    moveToHead(obj, hn->node);      
     /* 访问后变为最近使用 */
     //hn->node：HashNode 里存着的链表节点指针
//moveToHead：把该节点移到链表头部（最近使用）
//"查到了，说明刚用过，把它标记为最近使用（移到头部）。
    return hn->node->value;
    //返回这个 key 对应的 value
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    //函数名：存入缓存
    HashNode *hn = hashLookup(obj, key);
    //先看看这个 key 是不是已经存在
    //hn != NULL：key 已存在,hn == NULL：key 不存在

    if (hn) {
        /* 已存在：更新值并移到头部 */
        hn->node->value = value;
        //key 已经存在，直接把它的 value 改成新的。
        moveToHead(obj, hn->node);
        //"虽然只是更新，但也算'使用'了一次，标记为最近使用
        return;
    }
    /* 不存在：新建节点并插入头部 */
    Node *node = (Node *)malloc(sizeof(Node));
    //向系统要一块能装下 Node 的内存
    node->key = key;
    node->value = value;
    //把参数 key 和 value 存进节点。
    addToHead(obj, node);
    //把 node 插到虚拟头 head 后面，成为第一个真实节点（最近使用）。
    hashInsert(obj, key, node);
    //在哈希表里加一条 key → node 的映射，以后按 key 能 O(1) 找到这个节点
    //hn->node = node，哈希表通过 node 指针和链表连起来。以后 hashLookup 找到 HashNode，就能通过 hn->node 拿到链表节点。
    obj->size++;
    //缓存里多了一个元素，size 加 1

    /* 超容量则淘汰尾部（最久未使用） */
    if (obj->size > obj->capacity) {
        //如果超容量
        Node *tail = obj->tail->prev;
        //站在 tail 前面那个，就是最久没用的，要踢它
        removeNode(tail);
        //从双向链表里把 tail 摘出来
        hashDelete(obj, tail->key);
        //从哈希表里把这个 key 的映射也删掉，不然哈希表里还留着一个指向已释放节点的悬空指针
        free(tail);
        //节点从链表和哈希表都删了，现在释放它的内存
        obj->size--;
        //踢掉一个，元素个数减一。"
    }
}void lRUCacheFree(LRUCache* obj) {
    /* 释放链表节点（跳过虚拟头尾） */
    //函数名：释放 LRU 缓存
    //作用：程序结束时，把 lRUCacheCreate 里 malloc/calloc 出来的所有内存全部归还，避免内存泄漏。
    Node *p = obj->head->next;
    //从链表第一个真实节点开始遍历。
    while (p != obj->tail) {
        //只要 p 不是虚拟尾，就继续。
        Node *next = p->next;
        //"记住下一个节点在哪，免得 free 当前节点后找不到路。
        free(p);
        //释放当前节点
        p = next;//p 挪到下一个节点
    }
    free(obj->head); // ① 释放虚拟头
    free(obj->tail);  // ② 释放虚拟尾

    /* 释放哈希表 */
    for (int i = 0; i < obj->bucketCount; i++) {// ③ 遍历每个桶
        HashNode *hn = obj->buckets[i];
        /*取出第 i 个桶的链表头。
空桶：hn = NULL，while 不执行
非空桶：hn 指向第一个 HashNode
人话："站到第 i 个桶的链表开头。"*/
        while (hn) {
            HashNode *next = hn->next;
            free(hn);
            hn = next;
            //先存 next：HashNode *next = hn->next;
//再 free 当前：free(hn);
//最后挪到下一个：hn = next;
        }
    }
    free(obj->buckets); 
    //buckets 是 calloc 分配的一整块连续内存（存 bucketCount 个指针）。所有 HashNode 都 free 完后，这块数组本身也要 free。
    free(obj);  
    //obj 是 lRUCacheCreate 里 malloc 出来的 LRUCache 结构体。所有成员都处理完了，最后 free 它自己。

//人话："整个缓存结构体也不要了，归还内存。"
}
/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
