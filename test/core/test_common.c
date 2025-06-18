#include <stdio.h>
#include <string.h>
#include "core/common.h"

// �򵥶��Ժ�
#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            printf("[ʧ��] %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return 0; \
        } \
    } while (0)

// ���� safe_malloc �� safe_free
int test_safe_malloc_and_free() {
    int* p = (int*)safe_malloc(sizeof(int) * 10);
    ASSERT_TRUE(p != NULL);
    for (int i = 0; i < 10; ++i) p[i] = i;
    for (int i = 0; i < 10; ++i) ASSERT_TRUE(p[i] == i);
    safe_free((void**)&p);
    ASSERT_TRUE(p == NULL);

    // safe_free(NULL) Ӧ���쳣
    safe_free(NULL);

    // safe_free ��Ϊ NULL ��ָ��
    safe_free((void**)&p);

    return 1;
}

// ���� error_message
int test_error_message() {
    ASSERT_TRUE(strcmp(error_message(SUCCESS), "�����ɹ�") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_MEMORY_ALLOC), "�ڴ����ʧ��") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_OPEN), "�ļ���ʧ��") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_WRITE), "�ļ�д��ʧ��") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_READ), "�ļ���ȡʧ��") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_DUPLICATE), "��¼�Ѵ���") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_NOT_FOUND), "��¼������") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_INVALID_INPUT), "������Ч") == 0);
    ASSERT_TRUE(strcmp(error_message((ErrorCode)999), "δ֪����") == 0);
    return 1;
}

int main() {
    int total = 0, passed = 0;
    printf("==== common.c ��Ԫ���� ====\n");

    total++; if (test_safe_malloc_and_free()) { printf("[ͨ��] safe_malloc/safe_free\n"); passed++; }
    total++; if (test_error_message()) { printf("[ͨ��] error_message\n"); passed++; }

    printf("==== ͨ�� %d/%d ====\n", passed, total);
    return (passed == total) ? 0 : 1;
}