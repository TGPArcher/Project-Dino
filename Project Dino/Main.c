extern int menu();
extern void console_initializations();

int main() {

	console_initializations();

	while (menu());

	return 0;
}