#include <iostream>

using namespace std;


void task1(){
    unsigned int x,y,z,w;
    x = 35;
    y = 2;
    asm(
    "movl %[X], %%eax\n\t"
    "movl %[Y], %%ebx\n\t"
    "addl $34, %%eax\n\t"
    "XOR %%edx, %%edx\n\t" //обнуление регистра
    "divl %%ebx\t"
    :"=a"(z), "=d"(w)
    : [X] "m"(x), [Y] "m"(y)
    :"cc", "ebx");
    cout << hex << z << ' ' << hex << w << endl;
    // проверка
    z = (x+34)/y;
    w = (x+34)%y;
    cout << hex << z << ' ' << hex << w << endl;
}

void task2(){
    unsigned int x,y,z,w;
    x = 35;
    y = 2;
    asm(
    "XOR %%edx, %%edx\n\t"
    "addl $34, %%eax\n\t"
    "divl %[Y]\t"
    :"=a"(z), "=&d"(w)
    : [X] "a"(x), [Y] "r"(y)
    :"cc"
    );
    cout << z << ' ' << w << endl;
    // проверка
    z = (x+34)/y;
    w = (x+34)%y;
    cout << z << ' ' << w << endl;
}

void task3(){
    unsigned int x,y,z,w;
    x = 35;
    y = 2;
    unsigned int* p = &x;
    unsigned int* q = &y;
    asm (
    "XOR %%edx, %%edx\n\t"
    "movl (%[pX]), %%eax\n\t"
    "addl $34, %%eax\n\t"
    "divl (%[pY])"
    :"=&a"(z), "=&d"(w)
    :[pX] "r"(p), [pY]"r"(q)
    :"cc"
    );
    cout << z << ' ' << w << endl;
    // проверка
    z = (x+34)/y;
    w = (x+34)%y;
    cout << z << ' ' << w << endl;
}

void task4(){
    unsigned short x,y,z,w;
    x = 35;
    y = 2;
    asm (
    "XOR %%dx, %%dx\n\t"
    "mov %[X], %%ax\n\t"
    "mov %[Y], %%bx\n\t"
    "add $34, %%ax\n\t"
    "div %%bx\t"
    :"=a"(z), "=d"(w)
    : [X] "m"(x), [Y] "m"(y)
    :"cc", "ebx");
    cout << z << ' ' << w << endl;
    // проверка
    z = (x+34)/y;
    w = (x+34)%y;
    cout << z << ' ' << w << endl;
}

void task5(){
    int const N = 5;
    int M[N];
    for (int i = 0; i < N; i++)
        M[i] = 0x44332211;
    cout << "Data: ";
    for (int i = 0; i < N; i++)
        printf("%#10X ", M[i]);
    cout << endl;
    size_t k = 2; // позиция
    int x = 7; // число
    asm (
    "movl %0, (%1, %2, 4)\n"
    :
    :"r"(x), "r"(M) ,"r"(k)
    : "memory"
    );
    cout << "Data: ";
    for (int i = 0; i < N; i++)
        printf("%#10X ", M[i]);
}

void task6(){
    int const N = 5;
    unsigned int M[N];
    for (int i = 0; i < N; i++)
        M[i] = 0x44332211;
    size_t j = 4;
    cout << "Data: ";
    for (int i = 0; i < N; i++)
        printf("%#10X ", M[i]);
    cout << endl;
    asm(
    "movb $0xFF, 3(%0, %1, 4)\n"
    :
    : "r"(M) ,"r"(j)
    : "memory"
    );
    cout << "Data: ";
    for (int i = 0; i < N; i++)
        printf("%#10X ", M[i]);
}

int main()
{

    cout << "Task 1:\n";
    task1();

    cout << "\nTask 2:\n";
    task2();

    cout << "\nTask 3:\n";
    task3();

    cout << "\nTask 4:\n";
    task4();

    cout << "\nTask 5:\n";
    task5();

    cout << "\n\nTask 6:\n";
    task6();


    return 0;
}
