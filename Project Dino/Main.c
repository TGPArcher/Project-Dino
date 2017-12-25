extern int menu();
extern void console_initializations();
extern void redirect();

int main() {

	redirect();

	console_initializations();

	while (menu());

	return 0;
}