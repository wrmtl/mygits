#include<stdio.h>
int main(){
	
	FILE *fp;
	int num_f,num_s;
	char enter='\n';
		
	fp=fopen("finger.bmp","rb");
	
	while(enter=='\n'){
		scanf("%ld,%ld",&num_f,&num_s);getchar();
		fseek(fp,num_f,0);
		for(int i=0;i<num_s-num_f;i++){
			printf("%d  ",fgetc(fp));
		}
		enter=getchar();
	}
	return 0;
} 
