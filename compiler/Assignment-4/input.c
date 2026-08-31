int global_var;

void my_function(int param) {
    int local_var;
    local_var = param * 2;
}

int main() {
    int x, y;
    x = 10;
    y = 20;

    if (x < y) {
        int z;
        z = x + y;
    } else {
        x = x - 1;
    }

    while (x > 0) {
        x = x - 1;
    }
    
    return 0;
}