#include <wchar.h>

int main(int argc, char *argv[])
{
	wchar_t s[] = L"凯特琳";
	wprintf(L"%1s", s);
	return 0;
}
