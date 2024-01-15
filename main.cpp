#include <stdio.h>
#include <stdlib.h>

/**
 * Description:
 * 输入3 4 5 6 7 9999一串整数，9999代表结束，通过头插法新建链表，并输出，通过尾插法新建链表并输出。
 * @return
 */

//单链表（linked list）的声明与定义
typedef int ElemType;//数据类型别名使用驼峰命名法
//节点结构类型
typedef struct LinkedNode{
    ElemType data;//具体变量名使用下划线命名法
    struct LinkedNode *next;//指向下一个节点的指针
}LinkedNode,*LinkedList;

//注意输出要采用如下代码（因为OJ判题对空格敏感，因此需要用下面的打印代码来做）：
//打印链表中每个结点的值
void print_list(LinkedList L) {
    L = L->next;
    while (L != NULL) {
        printf("%d", L->data);//打印当前结点数据
        L = L->next;//指向下一个结点
        if (L != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

//头插法新建链表,需要改变链表的值
LinkedList insert_from_head();
//尾插法新建链表
LinkedList insert_from_tail();
//按位置查找
LinkedNode* get_element(LinkedList list,int position);
LinkedNode* get_element_worse(LinkedList list,int position);
//按值查找
LinkedNode* locate_element(LinkedList list,ElemType e);
//从中间插入元素
bool insert_from_position(LinkedList list,int position,ElemType e);


int main() {
    //头插法新建链表
    printf("build list from head:");
    LinkedList linked_list;
    linked_list=insert_from_head();
    print_list(linked_list);
    //尾插法新建链表
    printf("build list from tail:");
    linked_list=insert_from_tail();
    print_list(linked_list);
    //按位置查找
    printf("get element by position:");
    int position;
    scanf("%d",&position);
    LinkedNode *node;
    node=get_element(linked_list,position);
    if (NULL!=node){
        printf("%d\n",node->data);
    }
    //按值查找
    printf("locate element by value:");
    ElemType e;
    scanf("%d",&e);
    node=locate_element(linked_list,e);
    if (NULL!=node){
        printf("%d\n",node->data);
    }
    //从中间插入元素
    printf("insert element from position:");
    scanf("%d %d",&position,&e);
    bool ret=insert_from_position(linked_list,position,e);
    if (ret){
        print_list(linked_list);
    }
    return 0;
}

//头插法新建链表
LinkedList insert_from_head(){
    //初始化头节点，data不赋值，指向下一个节点的指针变量next，赋值NULL（尾节点没有下一个指向的节点）
    LinkedNode *head_node=(LinkedList)malloc(sizeof(LinkedNode));
    head_node->next=NULL;
    //声明需要读取输入的元素变量
    int element;
    scanf("%d",&element);
    while (9999!=element){
        //头节点不存放数据，每次插入数据都需要申请新的节点空间存储新输入的值
        LinkedNode *new_node=(LinkedNode*)malloc(sizeof(LinkedNode));
        //放入元素
        new_node->data=element;
        //头节点的next保存的旧地址赋给新节点的next保存
        new_node->next=head_node->next;
        //将新节点的地址赋给头节点的next保存
        head_node->next=new_node;
        scanf("%d",&element);
    }
    return head_node;
}
//尾插法新建链表
LinkedList insert_from_tail(){
    //初始化头节点和尾节点，data不赋值
    LinkedNode *head_node=(LinkedList)malloc(sizeof(LinkedNode));
    //第一次插入时，临时尾节点地址等于头节点地址，即头节点既是头节点也是尾节点
    LinkedNode *temp_tail_node=head_node;
    //声明需要读取输入的元素变量
    int element;
    scanf("%d",&element);
    while (9999!=element){
        //头节点不存放数据，每次插入数据都需要申请新的节点空间存储新输入的值
        LinkedNode *new_node=(LinkedNode*)malloc(sizeof(LinkedNode));
        //放入元素
        new_node->data=element;
        //用临时尾节点的next指针变量存储新节点地址
        //在第一次插入时，临时尾节点就是头节点，因此第一个插入的元素是头节点的下一个元素
        temp_tail_node->next=new_node;
        //将新节点的地址作为下一次的临时尾节点
        //在后续循环中，每次插入的新节点都应该是上一次插入的节点的后继节点
        //即临时尾节点的地址永远都是链表最后一次插入的"新节点"的地址
        temp_tail_node=new_node;
        scanf("%d",&element);
    }
    temp_tail_node->next=NULL;
    return head_node;
}
//按位置查找（推荐）
LinkedNode* get_element(LinkedNode *node,int position){
    if (position<0){
        return NULL;
    }
    int j=0;
    while (node && j<position){
        node=node->next;
        j++;
    }
    return node;
}
//按位置查找（不推荐）
LinkedNode* get_element_worse(LinkedList list,int position){
    if (position==0){
        return list;
    }
    if (position<1){
        return NULL;
    }
    //已经找了第一个节点
    LinkedNode *node=list->next;
    //所以循环起始位置前移一位
    int j=1;
    while (node && j<position){
        node=node->next;
        j++;
    }
    return node;
}
//按值查找
LinkedNode* locate_element(LinkedList list,ElemType e){
    LinkedNode *node=list->next;
    while (NULL!=node && node->data!=e){
        node=node->next;
    }
    return node;
}
//从中间插入元素
bool insert_from_position(LinkedList list,int position,ElemType e){
    LinkedNode *prev_node=get_element(list, position - 1);
    if (NULL == prev_node){
        return false;
    }
    //申请新节点空间
    LinkedNode *new_node=(LinkedNode*)malloc(sizeof(LinkedNode));
    //给新节点赋值
    new_node->data=e;
    //将前节点原本指向的下一个节点交给新节点去指向
    new_node->next=prev_node->next;
    //让前节点指向新节点
    prev_node->next=new_node;
    return true;
}
