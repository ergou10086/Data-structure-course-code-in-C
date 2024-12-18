#include <stdio.h>
#include <stdlib.h>

/*
    这个函数尝试交换两个整数的值。
    传递机制：按值传递（int a 和 int b）。
    结果：由于按值传递，a 和 b 是函数change的局部副本，原始变量不会受到影响。因此，交换仅在change函数内部发生，原始变量first和second的值不变。
 */
void change(int a,int b)
{
    int temp=a;
    a=b;
    b=temp;
}


/*
    这个函数通过指针交换两个整数的值。
    传递机制：按指针传递（int *a 和 int *b）。
    结果：通过指针a和b访问和修改原始变量的值。调用PointChange(&first, &second)会直接修改first和second的值，因此first和second会被交换。
 */
void PointChange(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}


/*
    这个函数通过引用交换两个整数的值。
    传递机制：按引用传递（int &a 和 int &b）在C++中，引用是对现有变量的别名。
    结果：引用a和b直接绑定到原始变量first和second，因此QuoteChange(first, second)会直接交换first和second的值。
 */
void QuoteChange(int &a,int &b)
{
    int temp=a;
    a=b;
    b=temp;
}

int main() {

    int first = 3, second = 4;
    int &QuoteFirst = first;
    int &QuoteSecond = second;

    printf("QuoteFirst=%d,QuoteSecond=%d\n", QuoteFirst, QuoteSecond);
    printf("&first=%p,&second=%p\n", &first, &second);
    // QuoteFirst和QuoteSecond的地址，实际上这些地址与first和second的地址相同，因为引用和被引用的变量共享相同的地址。
    printf("&QuoteFirst=%p,&QuoteSecond=%p\n", &QuoteFirst, &QuoteSecond);
    printf("first=%d,second=%d\n", first, second);

    //change(first, second)：由于按值传递，first和second的值不变。
    change(first, second);
    printf("first=%d,second=%d\n", first, second);

    //PointChange(&first, &second)：通过指针传递，first和second的值会被交换。
    PointChange(&first, &second);
    printf("first=%d,second=%d\n", first, second);

    //QuoteChange(first, second)：通过引用传递，first和second的值会再次被交换
    QuoteChange(first, second);
    printf("first=%d,second=%d\n", first, second);

    system("pause");
    return 1;
}
