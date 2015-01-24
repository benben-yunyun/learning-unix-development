#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* for file io */
#include <unistd.h>
#include <string.h>
/* int open(const char *pathname, int oflag, mode_t mode);
 * pathname 为打开文件名
 * oflag 打开表示：
 *  必须一个：O_RDONLY 只读 O_WRONLY 只写 O_RDWR 读写
 *  可选： O_APPEND 追加写 O_CREAT 文件不存在 创建文件 但是需要mode_t 制定创建文件的模式
 *         O_EXCL 测试文件是否存在 O_TRUNC 截断文件 O_NOBLOCK 当打开特殊文件时，设置为非阻塞
 *         O_DSYNC 每次等待write等待物理IO操作完成，如果不影响读取刚写入的数据，则不等待文件属性更新
 */

/* int create(const char * pathname, mode_t mode); 等同于
 * int open(path, O_WRONLY|O_CREAT|O_TRUNCT,mode);
 *
 */


/*  off_t lseek(int filedes, off_t offset, int where);
 *  where: 表示设置文件偏移的类型
 *         SEEK_SET 将偏移设为offset
 *         SEEK_CUR 将偏移设为offset+当前的偏移
 *         SEEK_END 将偏移设为末尾＋offset
 * return: 成功返回offset，失败返回-1，errno设为ESPIPE。
 *
 */
int main(int argc, char *argv[])
{
  int file_handler = open("io.c",O_WRONLY|O_DSYNC|O_APPEND);
  off_t curpos = lseek(file_handler,0,SEEK_END);
  if (curpos!=-1) {
    printf("[INFO] lseek:%lld\n",curpos);
  }
  write(file_handler,"//lseek\n",strlen("//lseek"));
  close(file_handler);
  return 0;
}
//lseek