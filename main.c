#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct str{
    void* ptr;
    int elemSize;
    int len;
};

typedef struct str str;

str* init(int length, int size){
    str* s = (str*)malloc(sizeof(str));
    s->len = length;
    s->elemSize = size;
    s->ptr = calloc(s->len, size);
    return s;
}

str* input(){
    printf("\n");
    int length;
    int size;
    printf(">>Enter string length: ");
    scanf("%d", &length);
    printf("\n>>Enter element size: ");
    scanf("%d", &size);
    str* s = init(length, size);
    void* ch = malloc(s->elemSize);
    for(int j = 0; j < s->len; j++){
        scanf("%u", ch);
        memcpy(s->ptr + (j * s->elemSize), ch, 1);
    }
    free(ch);
    printf("\n");
    return s;
}

str* concat(str* str1, str* str2){
    size_t size = (size_t)((str1->elemSize > str2->elemSize)? str1->elemSize : str2->elemSize);
    str* s = init(str1->len + str2->len, size);
    memcpy(s->ptr, str1->ptr, str1->len);
    memcpy(s->ptr + (str1->len)*size, str2->ptr, str2->len);
    return s;
}

str* substr(str* str1, int i, int j){
    str* s = init(j - i, str1->elemSize);
    memcpy(s->ptr, str1->ptr + i * str1->elemSize, j - i);
    return s;
}

int substr_search(str* buf, str* sub){
    int i = 0;
    int count = 0;
    while(i <= buf->len - sub->len){
        if(!memcmp(buf->ptr + i * buf->elemSize, sub->ptr, sub->len)){
            count++;
            i += sub->len;
        }
        else{
            i++;
        }
    }
    return count;
}

str* recode(str* str1, void(*func)(void*)){
    str* s  = init(str1->len, str1->elemSize);
    memcpy(s->ptr, str1->ptr, s->len);
    for(int j = 0; j < s->len; j++){
        func(s->ptr + j * s->elemSize);
    }
    return s;
}

void print(str* str1){
    printf(">>Output: ");
    for(int j = 0; j < str1->len; j++){
        printf("%c", *((char*)(str1->ptr + j * str1->elemSize)));
    }
    printf("\n");
}

void example_func(void* ptr){
    *((unsigned*)ptr) += 1;
}

int getOpType(){
    int type = -1;
    printf(">>Choose an operation:\n\n");
    printf("0. Substring extraction\n");
    printf("1. Substring search\n");
    printf("2. String concatenation\n");
    printf("3. String recoding\n\n");
    while(type < 0 || type > 3){
        scanf("%d", &type);
    }
    return type;
}

int main(){
    printf("---------------------------------lab1-Strings----------------------------------\n\n");
    while(1){
        str* s = input();
        int ch = getOpType();
        if(ch == 0){
            int start;
            int end;
            printf(">>Start: ");
            scanf("%d", &start);
            printf(">>End: ");
            scanf("%d", &end);
            str* res = substr(s, start, end);
            print(res);
            free(res);
        }
        if(ch == 1){
            str* s2 = input();
            printf(">>Output: %d\n", substr_search(s, s2));
            free(s2);
        }
        if(ch == 2){
            str* s2 = input();
            str* res = concat(s, s2);
            print(res);
            free(res);
            free(s2);
        }
        if(ch == 3){
            str* res = recode(s, example_func);
            print(res);
            free(res);
        }
    }
    return 0;
}
