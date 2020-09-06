#include <stdio.h>

struct fish {
    char name[80];
    int age;
    int teeth;
};

void showFish(struct fish *f) {
    printf("%s is at %p. I'm changing %s's age to 23.\n", f->name,f,f->name);
    f->age = 23;
}

int main() {
    struct fish nemo = {"Nemo", 22, 30};
    showFish(&nemo);
    printf("Fish's age is %i\n", nemo.age);
    return 0;
}