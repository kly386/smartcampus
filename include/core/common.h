#pragma once
#ifndef COMMON_H
#define COMMON_H
// 防止头文件被重复包含，使用宏定义保护，确保头文件内容只被编译一次

#include <stdlib.h> // 提供内存管理函数
#include <stdio.h>  // 提供输入输出函数
#include <stdbool.h> // 提供布尔类型支持

// 内存安全函数
void* safe_malloc(size_t size); // 封装标准malloc，增加内存分配失败的检查和处理,size_t为自适应系统大小
void safe_free(void** ptr);    // 封装标准free，防止悬空指针，释放后自动置NULL

// 错误码定义
typedef enum {
    SUCCESS = 0,   // 操作成功
    ERR_MEMORY_ALLOC,  // 内存分配失败
    ERR_FILE_OPEN,     // 文件打开失败
    ERR_FILE_WRITE,    // 文件写入失败
    ERR_FILE_READ,    // 文件读取是被
    ERR_DUPLICATE,    // 重复项错误
    ERR_NOT_FOUND,    // 未找到错误
    ERR_INVALID_INPUT // 无效输入错误
} ErrorCode;



// 错误处理-错误码到错误消息的转换函数声明，将错误码转换为人可读的错误描述
const char* error_message(ErrorCode err);

#endif  // 结束头文件保护宏
