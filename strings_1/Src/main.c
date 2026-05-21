#include <stdint.h>
#include <stdio.h>

int main(void)
{
	char msg1[] = "Te amo mucho";
	char *p_msg2 = "Mucho, mucho";

	printf("Message 1 %s\n", msg1);
	printf("Message 2 %s\n", p_msg2);
	printf("Adress in memory of msg 1: %p\n", &msg1); // In RAM
	printf("Adress in memory of msg 2: %p\n", &p_msg2); // In RAM
	printf("Value of p_msg2: %p ",p_msg2); // In FLASH


    /* Loop forever */
	for(;;);
}

int string_input(void){

	char name[60];

	printf("Enter your name: \n");
	scanf("%s", name); // if it has spaces, it won't work because scanf ignores \n \t spaces

	/* Method one: not ver suitable: use 2 separate strings
	 *
	 * char first_name[30];
	 * char last_name[30];
	 *
	 * scanf("%s%s", first_name, last_name);
	 * prinft("Hello %s %s", first_name, last_name);
	 *
	 */

	// USE scanset!
	scanf("%[^\n]s",name);

}
