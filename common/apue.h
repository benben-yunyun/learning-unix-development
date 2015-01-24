#ifndef _APUE_H
#define _APUE_H

#include <sys/types.h>          /* 定义各种类型 */
#include <sys/stat.h>           /* 定义目录操作 */
#include <sys/termios.h>        /* 定义终端结构 */
#include <sys/ioctl.h>          /* 定义IO的参数 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#define MAXLINE 4096

/* 
 * S_IRUSR: 允许创建者读
 * S_IWUSR: 允许创建者写
 * S_IRGRP: 允许组读
 * S_IWGRP: 允许组写
 */
#define FILE_MODE (S_IRUSR|S_IXUSR|S_IRGRP|S_IROTH)

/* 
 * S_IXUSR: 允许创建者执行
 * S_IXGRP: 允许组执行
 * S_IXOTH: 允许其他执行
 */
#define DIR_MODE (FILE_MODE|S_IXUSR|S_IXGRP|S_IXOTH)

typedef void SigFunc(int);      /* 信号处理句柄 */

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((SigFunc *)-1);
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

void err_doit(const char * fmt, va_list ap) {
  char buf[MAXLINE]; 
  sprintf(buf,"[ERROR] ");
  vsnprintf(buf+strlen(buf),MAXLINE,fmt,ap);
  strcat(buf,"\n");
  fflush(stdout);
  fputs(buf,stderr);
  fflush(NULL);
}

void err_dump(const char * fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  err_doit(fmt,ap);
  va_end(ap);
  abort();
}

void err_msg(const char * fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  err_doit(fmt,ap);
  va_end(ap);
}


void info_doit(const char * fmt, va_list ap) {
  char buf[MAXLINE]; 
  sprintf(buf,"[INFO] ");
  vsnprintf(buf+strlen(buf),MAXLINE,fmt,ap);
  strcat(buf,"\n");
  fflush(stdout);
  fputs(buf,stdout);
  fflush(NULL);
}

void info_msg(const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  info_doit(fmt,ap);
  va_end(ap);
}

#endif  /* _APUE_H */
