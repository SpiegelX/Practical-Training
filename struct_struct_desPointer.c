#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *PersonCreate(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    /*use malloc for "memory allocate" to ask the OS to
give a piece of raw memory. Pass to malloc the sizeof(struct Person) which
calculates the total size of the struct, given all the fields inside it.*/
    assert(who != NULL);
    /*Use assert to make sure that I have a valid piece of
memory back from malloc. There's a special constant
called NULL that you use to mean "unset or invalid
pointer". This assert is basically checking that malloc
didn't return a NULL invalid pointer.*/
    who -> name = strdup(name);
    /*Chức năng chính của strdup() là sao chép một chuỗi ký tự (string)
    đã cho và cấp phát bộ nhớ để lưu chuỗi sao chép.
    Nó trả về một con trỏ tới vùng nhớ mới được cấp phát 
    chứa chuỗi đã sao chép.*/
    who -> age = age;
    who -> height = height;
    who -> weight = weight;

    return who;
}

void PersonDetroy(struct Person *who)
{
    assert(who!=NULL);
    free(who -> name);
    free(who);
}

void PersonPrint(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("Age : %d\n", who->age);
    printf("Height  :   %d\n", who->height);
    printf("Weight  :   %d\n", who->weight);
}

int main(int arg, char *argv[])
{
    struct Person *HoangNG = PersonCreate("HOANG",22,165,80);
    PersonPrint(HoangNG);
    printf("I'm at ADDRESS: %p\n", HoangNG);
    return 0;
}