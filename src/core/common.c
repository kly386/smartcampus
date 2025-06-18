#include "core/common.h"

// 安全内存分配
// 尝试分配指定大小的内存;如果分配失败，打印错误信息并退出程序;返回分配的内存指针
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "[ERROR] 内存分配失败\n");
        exit(ERR_MEMORY_ALLOC);
    }
    return ptr;
}

// 安全释放内存
// 检查指针是否有效（非NULL）;释放内存;将指针置为NULL，避免悬空指针
void safe_free(void** ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

// 错误消息描述:通过switch语句将错误码映射为可读字符串
const char* error_message(ErrorCode err) {
    switch (err) {
    case SUCCESS:          return "操作成功";
    case ERR_MEMORY_ALLOC: return "内存分配失败";
    case ERR_FILE_OPEN:    return "文件打开失败";
    case ERR_FILE_WRITE:   return "文件写入失败";
    case ERR_FILE_READ:    return "文件读取失败";
    case ERR_DUPLICATE:    return "记录已存在";
    case ERR_NOT_FOUND:    return "记录不存在";
    case ERR_INVALID_INPUT:return "输入无效";
    default:               return "未知错误";
    }
}