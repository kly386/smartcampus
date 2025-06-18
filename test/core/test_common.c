#include <stdio.h>
#include <string.h>
#include "core/common.h"

// 简单断言宏
#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            printf("[失败] %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return 0; \
        } \
    } while (0)

// 测试 safe_malloc 和 safe_free
int test_safe_malloc_and_free() {
    int* p = (int*)safe_malloc(sizeof(int) * 10);
    ASSERT_TRUE(p != NULL);
    for (int i = 0; i < 10; ++i) p[i] = i;
    for (int i = 0; i < 10; ++i) ASSERT_TRUE(p[i] == i);
    safe_free((void**)&p);
    ASSERT_TRUE(p == NULL);

    // safe_free(NULL) 应无异常
    safe_free(NULL);

    // safe_free 已为 NULL 的指针
    safe_free((void**)&p);

    return 1;
}

// 测试 error_message
int test_error_message() {
    ASSERT_TRUE(strcmp(error_message(SUCCESS), "操作成功") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_MEMORY_ALLOC), "内存分配失败") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_OPEN), "文件打开失败") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_WRITE), "文件写入失败") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_FILE_READ), "文件读取失败") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_DUPLICATE), "记录已存在") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_NOT_FOUND), "记录不存在") == 0);
    ASSERT_TRUE(strcmp(error_message(ERR_INVALID_INPUT), "输入无效") == 0);
    ASSERT_TRUE(strcmp(error_message((ErrorCode)999), "未知错误") == 0);
    return 1;
}

int main() {
    int total = 0, passed = 0;
    printf("==== common.c 单元测试 ====\n");

    total++; if (test_safe_malloc_and_free()) { printf("[通过] safe_malloc/safe_free\n"); passed++; }
    total++; if (test_error_message()) { printf("[通过] error_message\n"); passed++; }

    printf("==== 通过 %d/%d ====\n", passed, total);
    return (passed == total) ? 0 : 1;
}