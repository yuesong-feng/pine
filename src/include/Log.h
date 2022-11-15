/**
 * @file Log.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-07
 * 
 * @copyright Copyright (冯岳松) 2022
 * 
 */
#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <string.h>
#include <time.h>

static FILE *log_fp = NULL;

enum { LOG_ERROR, LOG_WARN, LOG_INFO, LOG_DEBUG } log_level = LOG_INFO;

#define LOG_FILE(log_file) log_fp = fopen(log_file, "a+");
#define LOG_LEVEL(level) log_level = level;

#define LOG_ERROR(fmt, ...)              \
  if (log_level >= LOG_ERROR) {          \
    LOG("LOG_ERROR", fmt, ##__VA_ARGS__) \
  }
#define LOG_WARN(fmt, ...)              \
  if (log_level >= LOG_WARN) {          \
    LOG("LOG_WARN", fmt, ##__VA_ARGS__) \
  }
#define LOG_INFO(fmt, ...)              \
  if (log_level >= LOG_INFO) {          \
    LOG("LOG_INFO", fmt, ##__VA_ARGS__) \
  }
#define LOG_DEBUG(fmt, ...)              \
  if (log_level >= LOG_DEBUG) {          \
    LOG("LOG_DEBUG", fmt, ##__VA_ARGS__) \
  }

#define LOG(log_level, fmt, ...)                                             \
  char log_buf[1024] = {'\0'};                                               \
  time_t curtime = time(NULL);                                               \
  sprintf(log_buf, "[%s] %s at %s:%d %s", log_level, __FUNCTION__, __FILE__, \
          __LINE__, ctime(&curtime));                                        \
  sprintf(log_buf + strlen(log_buf), fmt, ##__VA_ARGS__);                    \
  sprintf(log_buf + strlen(log_buf), "\n");                                  \
  fprintf(log_fp == NULL ? stderr : log_fp, "%s", log_buf);

#endif
