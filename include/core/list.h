#pragma once
#ifndef LIST_H
#define LIST_H

#include "../core/common.h"

// 链表节点
typedef struct ListNode {
    void* data;  // 数据指针（泛型设计，可指向任意的数据类型）
    struct ListNode* next;
} ListNode;

// 链表结构
typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t size; // 链表的节点数量
} LinkedList;

// 初始化链表 - 创建并初始化一个空链表， 返回指向该链表的指针
LinkedList* list_create();

// 销毁链表：双重指针确保清空原指针，且安全释放节点数据
void list_destroy(LinkedList** list, void (*free_data)(void*));

// 添加元素到末尾
ErrorCode list_append(LinkedList* list, void* data);

// 迭代器 - 定义链表迭代器类型，方便后续使用
typedef ListNode* ListIterator;

// 获取迭代器 - 获取链表的第一个节点
ListIterator list_begin(LinkedList* list);

// 获取下一个元素
ListIterator list_next(ListIterator it);

#endif