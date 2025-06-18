#pragma once
// dao/course_schedule/schedule_dao.h
#pragma once
#ifndef SCHEDULE_DAO_H
#define SCHEDULE_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    /**
     * @brief 从文件加载所有排课数据
     * @return 包含所有排课的链表指针
     */
    LinkedList* (*load_all)();

    /**
     * @brief 保存所有排课数据到文件
     * @param list 排课数据链表
     * @return 操作结果错误码
     */
    ErrorCode(*save_all)(LinkedList* list);

    /**
     * @brief 释放排课内存
     * @param schedule 要释放的排课指针
     */
    void (*free_schedule)(Schedule* schedule);

    /**
     * @brief 根据ID查找排课
     * @param id 排课ID
     * @return 找到的排课指针，未找到返回NULL
     */
    Schedule* (*get_by_id)(int id);

    /**
     * @brief 检查时间冲突
     * @param classroom_id 教室ID
     * @param week 周次
     * @param day 星期
     * @param slot 节次
     * @return 存在冲突返回1，否则返回0
     */
    int (*check_conflict)(int classroom_id, int week, int day, int slot);
} ScheduleDAO;

/**
 * @brief 获取排课DAO单例
 * @return ScheduleDAO实例指针
 */
ScheduleDAO* get_schedule_dao();

#endif // SCHEDULE_DAO_H
