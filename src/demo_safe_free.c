#include<stdio.h>
#include<stdlib.h>
void safs_free_bad(void*ptr){
	// ������ͷŷ�ʽ�����ܵ����ڴ�й©��δ������Ϊ
	if(ptr != NULL) {
		free(ptr);
		ptr = NULL; // ���д��벻��ı�ԭʼָ���ֵ
	}
}
void safs_free_good(void** ptr) {
	// ������ͷŷ�ʽ�����ܵ����ڴ�й©��δ������Ϊ
	if (ptr != NULL&&*ptr!=NULL) {
		free(*ptr);	
		*ptr = NULL; // ���д����ı�ԭʼָ���ֵ	
	}
}
int main() {
	/*int i = 42;
	double b = 2.3;
	printf("int���ݵĴ�СΪ:%d\n", sizeof(i));
	printf("double���ݵĴ�СΪ:%d\n", sizeof(b));
	printf("int������ַΪ:%d\n", &i);
	printf("double������ַΪ:%d\n", &b);*/


	//int* i = malloc(sizeof(int)); 
	//*i = 42; // ʹ��ָ������ڴ沢��ֵ	
	//printf("iָ��ĵ�ַΪ��%d\n", i);	
	//printf("iָ���ֵΪ��%d\n", *i); // ���ָ����ָ���ֵ	

	//double* b = malloc(sizeof(double));
	//*b = 3.12; // ʹ��ָ������ڴ沢��ֵ	
	//printf("bָ��ĵ�ַΪ��%d\n", b);	
	//printf("bָ���ֵΪ��%lf\n", *b); // ���ָ����ָ���ֵ	

	//printf("i�����Ĵ�СΪ��%d\n", sizeof(i));
	//printf("b�����Ĵ�СΪ��%d\n", sizeof(b)); // ���ָ��Ĵ�С��ͨ����4��8�ֽڣ�ȡ����ϵͳ�ܹ�	

	int* p = malloc(sizeof(int)); // �����ڴ��ָ��p	
	*p = 100; // ��ָ��p��ָ����ڴ渳ֵ
	printf("pָ���ֵΪ��%d\n", *p); // ���ָ��p��ָ���ֵ	
	printf("pָ��ĵ�ַΪ��%d\n", p); // ���ָ��p�ĵ�ַ	
	printf("p�Լ��ĵ�ַΪ��%d\n", &p); // ���ָ��p����ĵ�ַ	


	safs_free_good(&p); // ��ȷ�ͷ��ڴ沢��ָ����ΪNULL
	printf("pָ���ֵΪ��%d\n", *p); // ���ָ��p��ָ���ֵ	
	printf("pָ��ĵ�ַΪ��%d\n", p); // ���ָ��p�ĵ�ַ	
	printf("p�Լ��ĵ�ַΪ��%d\n", &p); // ���ָ��p����ĵ�ַ	


	*p = 200;
	printf("pָ���ֵΪ��%d\n", *p); // ���ָ��p��ָ���ֵ	




	return 0;
}