#include "Log.h"
#include <cstdarg>

static void log_internal(int severity, const char *fmt, va_list ap) {
  char buf[1024] = {0};
  if (fmt == NULL)
    buf[0] = '\0';
  else {
    vsnprintf(buf, sizeof(buf), fmt, ap);
    buf[sizeof(buf) - 1] = 0;
  }
  const char *severity_str = NULL;
  switch (severity) {
    case LOG_ERROR:
      severity_str = "ERROR";
      break;
    case LOG_WARN:
      severity_str = "WARN";
      break;
    case LOG_INFO:
      severity_str = "INFO";
      break;
    case LOG_DEBUG:
      severity_str = "DEBUG";
      break;
    default:
      severity_str = "UNKNOWN";
  }
  fprintf(log_fp == NULL ? stdout : log_fp, "[%s] %s\n", severity_str, buf);
  fflush(log_fp);
}

void log_error(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  log_internal(LOG_ERROR, fmt, ap);
  va_end(ap);
}
void log_warn(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  log_internal(LOG_WARN, fmt, ap);
  va_end(ap);
}
void log_info(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  log_internal(LOG_INFO, fmt, ap);
  va_end(ap);
}
void log_debug(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  log_internal(LOG_DEBUG, fmt, ap);
  va_end(ap);
}