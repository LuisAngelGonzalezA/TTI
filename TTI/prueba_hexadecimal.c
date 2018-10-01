#include <stdio.h>
int main()
{
	unsigned char a;
	unsigned int b;
	
	printf("Enter value of a: ");
	scanf("%X",&a);
	printf("Enter value of b: ");
	scanf("%X",&b);
	
	printf("Value of a: Hex: %X, Decimal: %d\n",a,a);
	printf("Value of b: Hex: %X, Decimal: %d\n",b,b);
	
	return 0;
}