#pragma once
// service/course_schedule/schedule_service.h
#pragma once
#ifndef SCHEDULE_SERVICE_H
#define SCHEDULE_SERVICE_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

typedef struct {
    /**
     * @brief 获取所有排课信息
     * @return 排课链表指针
     */
    LinkedList* (*get_all_schedules)();

    // 其他服务方法声明...
    // ...原有声明
    
    /**
     * @brief 添加排课
     * @param schedule 排课信息
     * @return 错误码
     */
    ErrorCode (*add_schedule)(Schedule* schedule);
    
    /**
     * @brief 更新排课
     * @param id 排课ID
     * @param 其他参数...
     * @return 错误码
     */
    ErrorCode (*update_schedule)(int id, int course_id, int classroom_id,
                               int week, int day, int slot);
    
    /**
     * @brief 删除排课
     * @param id 排课ID
     * @return 错误码
     */
    ErrorCode (*delete_schedule)(int id);
    
    // ...其他声明
} ScheduleService;

/**
 * @brief 获取排课服务实例
 */
ScheduleService* get_schedule_service();

#endif // SCHEDULE_SERVICE_H