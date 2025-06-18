#include "core/list.h"

// 创建新链表
// 使用safe_malloc安全分配内存, 初始化头部、尾部为NULL、大小为0
LinkedList* list_create() {
    LinkedList* list = (LinkedList*)safe_malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// 销毁链表
void list_destroy(LinkedList** list, void (*free_data)(void*)) {
    // 检查输入有效性
    if (list == NULL || *list == NULL) return;

    // 遍历链表所有节点，使用free_data释放节点数据
    ListNode* current = (*list)->head;
    while (current != NULL) {
        ListNode* next = current->next;

        if (free_data != NULL) {
            free_data(current->data);
        }
        safe_free((void**)&current);

        current = next;
    }

    // 释放链表结构体并将指针置NULL
    safe_free((void**)list);
}

// 添加元素到末尾
ErrorCode list_append(LinkedList* list, void* data) {
    // 输入有效性检查
    if (list == NULL || data == NULL) return ERR_INVALID_INPUT;

    // 为新节点分配内存 + 指明内容
    ListNode* new_node = (ListNode*)safe_malloc(sizeof(ListNode));
    new_node->data = data;
    new_node->next = NULL;

    // 如果当前链表为空链表，则添加的节点是头结点
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++; // 更新链表大小计数器，别忘了
    return SUCCESS;
}

// 获取迭代器 - 返回链表头部指针或NULL（如果链表为空）
ListIterator list_begin(LinkedList* list) {
    return (list != NULL) ? list->head : NULL;
}

// 获取下一个元素
ListIterator list_next(ListIterator it) {
    return (it != NULL) ? it->next : NULL;
}