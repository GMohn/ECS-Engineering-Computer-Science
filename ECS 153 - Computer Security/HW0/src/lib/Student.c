#include "Student.h"
#include "Human.h"
#include "stdint.h"
#include "string.h"


void *new_Student(char *input) {
    // Allocate memory for the Student object
    Student *student = malloc(sizeof(Student));

    // Extract name and grade from the input string
    char name[MAX_LEN];
    int grade;
    sscanf(input, "%s %d", name, &grade);

    // Create a new Human object
    student->human.impl = malloc(sizeof(GenericTraits));
    student->human.impl->new = new_Human;
    student->human.impl->dump = dump_Human;
    student->human.impl->cmp = cmp_Human;
    student->human.impl->drop = drop_Human;
    strncpy(student->human.name, name, MAX_LEN);

    // Assign grade
    student->grade = grade;

    return student;
}

void dump_Student(void *self, FILE *fp) {
    Student *student = (Student *)self;
    fprintf(fp, "%s %d\n", student->human.name, student->grade);
}

int cmp_Student(void *self, void *other) {
    Student *student1 = (Student *)self;
    Student *student2 = (Student *)other;

    // Compare grades first
    if (student1->grade < student2->grade)
        return -1;
    else if (student1->grade > student2->grade)
        return 1;

    // If grades are equal, compare names using the inherited Human comparison
    return cmp_Human(&(student1->human), &(student2->human));
}

void drop_Student(void *self) {
    Student *student = (Student *)self;
    free(student->human.impl);
    free(student);
}

void __attribute__((constructor)) register_Student() {
    // Register Student implementation with the system
    add_ctor_dtor("Student", new_Student, drop_Student);
}