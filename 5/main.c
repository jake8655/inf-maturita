#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    char *lastname;
    int height;
    int weight;
} Student_Data;

typedef struct
{
    Student_Data *data;
    int size;
    int capacity;
} DA_Student_Data;

void da_append(DA_Student_Data *da, Student_Data val)
{
    if (da->capacity >= da->size + 1)
    {
        da->data[da->size++] = val;
        return;
    }

    if (da->capacity == 0)
    {
        Student_Data *new_data = malloc(sizeof(Student_Data)*5);
        new_data[da->size++] = val;
        da->data = new_data;
        da->capacity = 5;
        return;
    }

    Student_Data *new_data = realloc(da->data, sizeof(Student_Data) * da->capacity * 2);
    new_data[da->size++] = val;
    da->data = new_data;
    da->capacity *= 2;
}

void print_student(Student_Data *student)
{
    printf("---------------\n"
           "Name: %s\nLast Name: %s\nHeight: %d\nWeight: %d\n"
           "---------------\n",
           student->name, student->lastname, student->height, student->weight);
}

long str_to_long(char *str)
{
    char *endptr;
    errno = 0;
    long num = strtol(str, &endptr, 10);
    int len = strlen(str);

    if (errno == ERANGE || endptr == str || (*endptr && *endptr != str[len - 1]))
    {
        fprintf(stderr, "ERROR: Not a number: %s\n", str);
        exit(1);
    }

    return num;
}

int str_to_int(char *str)
{
    long num = str_to_long(str);
    if (num > INT_MAX)
    {
        fprintf(stderr, "ERROR: Number too large: %ld", num);
        exit(1);
    }

    return (int)num;
}

Student_Data get_input_student()
{
    char buf[1024];
    printf("Input a student's name, lastname, height (cm), weight(kg) separated by spaces: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;

    char *bufptr = buf;
    char *tokens[1024];
    char *token;
    int n = 0;
    while ((token = strsep(&bufptr, " ")))
    {
        tokens[n] = strdup(token);
        n++;
    }

    if (n != 4)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }

    Student_Data student = {
        .name = tokens[0],
        .lastname = tokens[1],
        .height = str_to_int(tokens[2]),
        .weight = str_to_int(tokens[3]),
    };
    free(tokens[2]);
    free(tokens[3]);

    return student;
}

float perform_b(DA_Student_Data *students)
{
    float height_sum = 0;
    int n = 0;

    for (int i = 0; i < students->size; i++)
    {
        if (students->data[i].weight <= 70)
            continue;

        height_sum += students->data[i].height;
        n++;
    }

    if (n == 0)
        return 0;
    return height_sum / n;
}

int perform_c(DA_Student_Data *students)
{
    int min = students->data[0].height;
    int idx = 0;

    for (int i = 0; i < students->size; i++)
    {
        if (students->data[i].height < min)
        {
            min = students->data[i].height;
            idx = i;
        }
    }

    return idx;
}

void print_menu()
{
    printf("a - add student\n"
           "p - print students\n"
           "b - perform b\n"
           "c - perform c\n"
           "x - quit\n");
}

int main()
{
    DA_Student_Data students = {0};

    char buf[1024];
    for (;;)
    {
        print_menu();
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        if (strcmp(buf, "x") == 0)
            break;

        if (strcmp(buf, "a") == 0)
        {
            Student_Data new = get_input_student();
            da_append(&students, new);
        }

        if (strcmp(buf, "p") == 0)
        {
            if (students.size == 0)
            {
                printf("No students\n");
                continue;
            }
            for (int i = 0; i < students.size; i++)
                print_student(&students.data[i]);
        }

        if (strcmp(buf, "b") == 0)
        {
            if (students.size == 0)
            {
                printf("No students\n");
                continue;
            }
            printf("Average height of >70kg: %f\n", perform_b(&students));
        }

        if (strcmp(buf, "c") == 0)
        {
            if (students.size == 0)
            {
                printf("No students\n");
                continue;
            }
            printf("Shortest: %s\n", students.data[perform_c(&students)].name);
        }
    }

    for (int i = 0; i < students.size; i++)
    {
        free(students.data[i].name);
        free(students.data[i].lastname);
    }
    free(students.data);

    return 0;
}
