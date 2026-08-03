int main() {
    int i = 10;
    int abc = 12@45;
    while (i & 2) {
        i = i - 2;
        if(i >> 4) {
            break;
        }
        else if(i == 6) {
            continue;
        }
        else {
            printf("%d\n", i);
        }
        sizeof(i);
    }
}