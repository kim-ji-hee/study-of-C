#include <stdio.h>
#include <stdarg.h>	//매크로가 정의된 헤더 파일

void printValues(char *types, ...)
{
	va_list ap;
	int i = 0;

	va_start(ap, types);
	while(types[i] != '\0')
	{
		switch (types[i])
		{
		case 'i':
			printf("%d ", va_arg(ap, int));
			break;
		case 'd':
			printf("%f ", va_arg(ap, double));
			break;
		case 'c':
			printf("%c ", va_arg(ap, char));
			break;
		case 's':
			printf("%s ", va_arg(ap, char*));
			break;
		default :
			break;
		}
		i++;
	}
	va_end(ap);
	
	printf("\n");
}

int main()
{
	printValues("i", 10);
	printValues("ci", 'a', 10);
	printValues("dci", 1.234567, 'a', 10);
	printValues("sicd", "Hello, world!", 10, 'a', 1.234567);

	return 0;
}