#include<stdio.h>
#include<stdlib.h>
void safs_free_bad(void*ptr){
	// 错误的释放方式，可能导致内存泄漏或未定义行为
	if(ptr != NULL) {
		free(ptr);
		ptr = NULL; // 这行代码不会改变原始指针的值
	}
}
void safs_free_good(void** ptr) {
	// 错误的释放方式，可能导致内存泄漏或未定义行为
	if (ptr != NULL&&*ptr!=NULL) {
		free(*ptr);	
		*ptr = NULL; // 这行代码会改变原始指针的值	
	}
}
int main() {
	/*int i = 42;
	double b = 2.3;
	printf("int数据的大小为:%d\n", sizeof(i));
	printf("double数据的大小为:%d\n", sizeof(b));
	printf("int变量地址为:%d\n", &i);
	printf("double变量地址为:%d\n", &b);*/


	//int* i = malloc(sizeof(int)); 
	//*i = 42; // 使用指针分配内存并赋值	
	//printf("i指向的地址为：%d\n", i);	
	//printf("i指向的值为：%d\n", *i); // 输出指针所指向的值	

	//double* b = malloc(sizeof(double));
	//*b = 3.12; // 使用指针分配内存并赋值	
	//printf("b指向的地址为：%d\n", b);	
	//printf("b指向的值为：%lf\n", *b); // 输出指针所指向的值	

	//printf("i变量的大小为：%d\n", sizeof(i));
	//printf("b变量的大小为：%d\n", sizeof(b)); // 输出指针的大小，通常是4或8字节，取决于系统架构	

	int* p = malloc(sizeof(int)); // 分配内存给指针p	
	*p = 100; // 给指针p所指向的内存赋值
	printf("p指向的值为：%d\n", *p); // 输出指针p所指向的值	
	printf("p指向的地址为：%d\n", p); // 输出指针p的地址	
	printf("p自己的地址为：%d\n", &p); // 输出指针p本身的地址	


	safs_free_good(&p); // 正确释放内存并将指针置为NULL
	printf("p指向的值为：%d\n", *p); // 输出指针p所指向的值	
	printf("p指向的地址为：%d\n", p); // 输出指针p的地址	
	printf("p自己的地址为：%d\n", &p); // 输出指针p本身的地址	


	*p = 200;
	printf("p指向的值为：%d\n", *p); // 输出指针p所指向的值	




	return 0;
}