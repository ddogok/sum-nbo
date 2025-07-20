#include <stddef.h> // for size_t
#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include <stdlib.h>
#include <netinet/in.h> // for htons, htonl


uint32_t ntohl(uint32_t n) {
    uint32_t n1 = (n & 0xFF000000) >> 24;
    uint32_t n2 = (n & 0x00FF0000) >> 8;
    uint32_t n3 = (n & 0x0000FF00) << 8;
    uint32_t n4 = (n & 0x000000FF) << 24;
    return n1 | n2 | n3 | n4;
}

int main(int argc, char* argv[]) {
    FILE** fp;
    fp = (FILE**)malloc(sizeof(FILE*) * argc);
    
    for (int i = 1; i < argc; i++) {
        fp[i] = fopen(argv[i], "rb");
        if (fp[i] == NULL){
            printf("파일 열기 실패");
            continue;
        }
    }
    
    char temp[100];
    uint32_t sum = 0;
    int first = 1;

    for (int i = 1; i < argc; i++){
        size_t bytes = fread(temp, sizeof(char), 100, fp[i]);
        
        if(bytes >= 4){
            uint32_t value;
            value = *((uint32_t*)temp);
            uint32_t value2 = ntohl(value);
            if (!first) printf(" + ");
        printf("%u (0x%08x)", value2, value2);
            first = 0;
        sum += value2;
    } else {
        printf("읽기 실패: %s\n", argv[i]);
    }
}
    printf(" = %u(0x%08x)\n", sum, sum);     

    for (int i = 1; i < argc; i++) {
        if (fp[i] != NULL)
            fclose(fp[i]);
    }

    free(fp);
    return 0;
    
}




