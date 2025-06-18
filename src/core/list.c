#include "core/list.h"

// ����������
// ʹ��safe_malloc��ȫ�����ڴ�, ��ʼ��ͷ����β��ΪNULL����СΪ0
LinkedList* list_create() {
    LinkedList* list = (LinkedList*)safe_malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// ��������
void list_destroy(LinkedList** list, void (*free_data)(void*)) {
    // ���������Ч��
    if (list == NULL || *list == NULL) return;

    // �����������нڵ㣬ʹ��free_data�ͷŽڵ�����
    ListNode* current = (*list)->head;
    while (current != NULL) {
        ListNode* next = current->next;

        if (free_data != NULL) {
            free_data(current->data);
        }
        safe_free((void**)&current);

        current = next;
    }

    // �ͷ�����ṹ�岢��ָ����NULL
    safe_free((void**)list);
}

// ���Ԫ�ص�ĩβ
ErrorCode list_append(LinkedList* list, void* data) {
    // ������Ч�Լ��
    if (list == NULL || data == NULL) return ERR_INVALID_INPUT;

    // Ϊ�½ڵ�����ڴ� + ָ������
    ListNode* new_node = (ListNode*)safe_malloc(sizeof(ListNode));
    new_node->data = data;
    new_node->next = NULL;

    // �����ǰ����Ϊ����������ӵĽڵ���ͷ���
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++; // ���������С��������������
    return SUCCESS;
}

// ��ȡ������ - ��������ͷ��ָ���NULL���������Ϊ�գ�
ListIterator list_begin(LinkedList* list) {
    return (list != NULL) ? list->head : NULL;
}

// ��ȡ��һ��Ԫ��
ListIterator list_next(ListIterator it) {
    return (it != NULL) ? it->next : NULL;
}