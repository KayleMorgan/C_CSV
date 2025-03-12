#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024  

typedef struct {
    int id;
    char name[20];
    float salary;
} Employees;

int main() {
    FILE* csv;
    char line[MAX_LINE];

    errno_t err = fopen_s(&csv, "employees.csv", "r");
    if (err != 0 || !csv) {
        perror("Error \n");
        return 1;
    }

    while (fgets(line, sizeof(line), csv)) {
        char* context;
        char* token = strtok_s(line, ";", &context);
        Employees emp;

        while (token) {
            if (token) emp.id = atoi(token);

            token = strtok_s(NULL, ";", &context);
            if (token) strcpy_s(emp.name, sizeof(emp.name), token);

            token = strtok_s(NULL, ";", &context);
            if (token) emp.salary = atof(token);
        }
        printf("ID: %d, Name:%s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(csv);
}
