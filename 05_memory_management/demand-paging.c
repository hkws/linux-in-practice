#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define BUFFER_SIZE    (100 * 1024 * 1024)
#define NCYCLE        10
#define PAGE_SIZE    4096

int main(void)
{
    char *p;
    time_t t;
    char *s;

    t = time(NULL);
    s = ctime(&t);
    // メモリ獲得前だよメッセージ
    printf("%.*s: before allocation, please press Enter key\n",
           (int)(strlen(s) - 1), s);
    getchar();

    // 100Mメモリ確保
    p = malloc(BUFFER_SIZE);
    if (p == NULL)
        err(EXIT_FAILURE, "malloc() failed");

    t = time(NULL);
    s = ctime(&t);
    // メモリ確保完了メッセージ
    printf("%.*s: allocated %dMB, please press Enter key\n",
           (int)(strlen(s) - 1), s, BUFFER_SIZE / (1024 * 1024));
    getchar();

    // メモリの最初から最後までアクセス
    int i;
    for (i = 0; i < BUFFER_SIZE; i += PAGE_SIZE) {
        p[i] = 0;
        int cycle = i / (BUFFER_SIZE / NCYCLE);
        if (cycle != 0 && i % (BUFFER_SIZE / NCYCLE) == 0) {
            t = time(NULL);
            s = ctime(&t);
            printf("%.*s: touched %dMB\n",
                   (int) (strlen(s) - 1), s, i / (1024*1024));
            sleep(1);
        }
    }

    // 全メモリアクセス完了メッセージ
    t = time(NULL);
    s = ctime(&t);
    printf("%.*s: touched %dMB, please press Enter key\n",
           (int) (strlen(s) - 1), s, BUFFER_SIZE / (1024 * 1024));
    getchar();

    exit(EXIT_SUCCESS);
}

