

```c
C语言中结构体的对齐

一、gcc环境下
ubuntu-14.04.3，64bit
gcc version 4.8.4

1、在64位的系统上，gcc各种数据类型占的字节：

char:     1
short:    2
int:      4
int *：   8
long:     8
float:    4
double:   8
long long:8


2、
GCC中结构体对齐原则：
在gcc中，未指明对齐字节的情况下，gcc编译器的对齐原则为：
（1）结构体中每个成员的偏移量，必须是本成员大小的整数倍（0被认为是任何数的整数倍）。
（2）结构体大小，必须是所有成员大小的整数倍。
（3）如果结构体成员是数组，整数倍只需要考虑数组元素类型的长度，而不是整个数组的长度。

关于偏移量：
结构体变量中第一个成员的地址就是结构体变量的首地址。
第一个成员的偏移量为0。
第二个成员的偏移量是第一个成员的偏移量加上第一个成员的大小。
第三个成员的偏移量是第二个成员的偏移量加上第二个成员的大小。
最终的结构体的大小是：最后一个成员的偏移量+最后一个成员的大小。
编译器在优化时为了保持字节对齐的要求，会在偏移量之后加上空字节，以满足字节对齐要求。

struct stu7 {
    	char a;
	short b;
	int c;
};
sizeof(struct stu7) = 8

struct stu8 {
	char a;
	int c;
	short b;
};
sizeof(struct stu8) = 12

struct stu3 {
	char c1;//偏移量为0
	int i;//偏移量为1， 结构体变量中成员的偏移量必须是成员大小的整数倍（0被认为是任何数的整数倍），故偏移量应为4
	char c2;//偏移量为8
};
sizeof( stu3 )=1+8=9，但9不是int的整数倍故最终大小为12

struct stu4 {
	char c1; //偏移量为0
	char c2;// //偏移量为1
	int i; //偏移量为2不符合要求故偏移量为4
};
算出sizeof( stu4 )=4+4=8，8是int的整数倍故最终大小为8


指定对齐字节数时：

struct student {
	int num;
	char c;
};
sizeof(struct student) = 8 。在不指定对齐的情况下，gcc自己选择最佳对齐方式(2/4/8/16)，对齐字节数不确定，这样对齐可以提高cpu存储变量的速度。


struct stu6 {
	char a;
	short b;
	char c[2];
};
sizeof(struct stu6) = 6。

struct stu7{
        char a;
        int b;
        char c[5];
};
sizeof(strcut stu7)=16 。

struct student2 {
	int num;
	char c;
}__attribute__((packed));
sizeof(struct student2) = 5 。__attribute__((packed))这个属性表示不让编译器对该结构体进行对齐处理。


struct student3 {
	int num;
	char c;
}__attribute__((aligned));
sizeof(struct student2) = 16。__attribute__((aligned))，采取aligned默认对齐方式，对齐为16字节。


struct student5 {
	int num;
	char c;
}__attribute__((aligned(4)));
sizeof(struct student5) = 8。指定结构体的对齐字节数，在gcc中必须是2的n次幂。aligned的最小对齐数是4。


自己定义对齐字节数
#pragma pack (2)
struct student7 {
	int num;
	char c;
};
#pragma pack () 
sizeof(struct student7) = 6。


C语言联合体的对齐：
联合体取最大的字节数，大小是其他字节数的整数倍。


union e{
	char i[7];
	char k[11];
	short j;
};
sizeof(union e)=12

union e{
	char i[3];
	short j;
};
sizeof(union e)=4

union e{
	char i[5];
	int j;
};
sizeof(union e)=8

```


