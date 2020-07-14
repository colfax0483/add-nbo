#include <stddef.h> //for size_t
#include <stdio.h> //for printf
#include <stdint.h> //for uint8_t
#include <sys/types.h>
#include <fcntl.h>
#include <arpa/inet.h>

uint32_t my_htonl(uint8_t *buf){ //host byte order to network byte order
    uint32_t n = htonl(*((uint32_t*) buf));
    return n;
}

int main(int argc, char *argv[])
{
    uint8_t buf[16] = {0};
    uint8_t buf2[16] = {0};
    uint32_t num1, num2;
    size_t bytes = 0, i, readsz = sizeof buf;

    if(argc != 3){
        printf("Usage: %s <filename1> <filename2>\n", argv[0]);
        return 0;
    }

    FILE *fd1, *fd2;

    fd1 = fopen(argv[1], "rb");
    fd2 = fopen(argv[2], "rb");

    if(!fd1||!fd2){
        fprintf(stderr, "error: file open failed '%s'.\n", argv[1]);
        return 1;
    }

    while((bytes = fread ( buf, sizeof * buf, readsz, fd1)) == readsz){
        for ( i=0; i<readsz; i++)
            printf(" 0x%02x", buf[i]);
        printf("\n");
    }
    /*
    for (i=0; i<bytes; i++){
        printf(" 0x%02x", buf[i]);
        printf(" int = %d ", buf[i]);
    }
    */

    while((bytes = fread ( buf2, sizeof * buf2, readsz, fd2)) == readsz){
        for ( i=0; i<readsz; i++)
            printf(" 0x%02x", buf2[i]);
        printf("\n");
    }
    fclose(fd1);
    fclose(fd2);

    num1 = my_htonl(buf);
    num2 = my_htonl(buf2);
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, num1+num2, num1+num2);

    return 0;
}
