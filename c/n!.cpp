#include <stdio.h>
int main(){
	int a,sum=1;
	scanf("%d",&a);
	sum=1;
	for(int i=1;i<=a;i++){
		sum=sum*i;
	}
	printf("%d",sum);
	return 0;
} 
