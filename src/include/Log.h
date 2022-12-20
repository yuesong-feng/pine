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
#include <cstdio>

static FILE *log_fp = NULL;

static enum LOG_LEVEL {
  LOG_ERROR,
  LOG_WARN,
  LOG_INFO,
  LOG_DEBUG
} log_level = LOG_INFO;

#define LOG_FILE(log_file) log_fp = fopen(log_file, "a+");
#define LOG_LEVEL(level) log_level = level;

#ifdef __GNUC__
#define CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#else
#define CHECK_FMT(a, b)
#endif

void log_error(const char *fmt, ...) CHECK_FMT(1, 2);
void log_warn(const char *fmt, ...) CHECK_FMT(1, 2);
void log_info(const char *fmt, ...) CHECK_FMT(1, 2);
void log_debug(const char *fmt, ...) CHECK_FMT(1, 2);

#define LOG_ERROR(fmt, ...)                                    \
  do {                                                         \
    if (log_level >= LOG_ERROR) log_error(fmt, ##__VA_ARGS__); \
  } while (0)

#define LOG_WARN(fmt, ...)                                   \
  do {                                                       \
    if (log_level >= LOG_WARN) log_warn(fmt, ##__VA_ARGS__); \
  } while (0)

#define LOG_INFO(fmt, ...)                                   \
  do {                                                       \
    if (log_level >= LOG_INFO) log_info(fmt, ##__VA_ARGS__); \
  } while (0)

#define LOG_DEBUG(fmt, ...)                                    \
  do {                                                         \
    if (log_level >= LOG_DEBUG) log_debug(fmt, ##__VA_ARGS__); \
  } while (0)

#endif
