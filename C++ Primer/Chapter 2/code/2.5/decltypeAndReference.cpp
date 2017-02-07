int main() {
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;
    // decltype(*p) c; Error! c is int&
    return 0;
}
