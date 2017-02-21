void func(int a, double b, char c);

void func(int a, double b, char c = '*');

void func(int a, double b = 3.14, char c);

void func(int a = 1, double b, char c);

int temp = 10;

char test() {
    return 'X';
}

void function(int a = temp, char c = test());
