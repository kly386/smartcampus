#pragma once
#ifndef LIST_H
#define LIST_H

#include "../core/common.h"

// ����ڵ�
typedef struct ListNode {
    void* data;  // ����ָ�루������ƣ���ָ��������������ͣ�
    struct ListNode* next;
} ListNode;

// ����ṹ
typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t size; // ����Ľڵ�����
} LinkedList;

// ��ʼ������ - ��������ʼ��һ�������� ����ָ��������ָ��
LinkedList* list_create();

// ��������˫��ָ��ȷ�����ԭָ�룬�Ұ�ȫ�ͷŽڵ�����
void list_destroy(LinkedList** list, void (*free_data)(void*));

// ���Ԫ�ص�ĩβ
ErrorCode list_append(LinkedList* list, void* data);

// ������ - ����������������ͣ��������ʹ��
typedef ListNode* ListIterator;

// ��ȡ������ - ��ȡ����ĵ�һ���ڵ�
ListIterator list_begin(LinkedList* list);

// ��ȡ��һ��Ԫ��
ListIterator list_next(ListIterator it);

#endif