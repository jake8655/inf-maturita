#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PADDING                                                                                                        \
    "----------------------------------------------------------------------------------------------------------------" \
    "------------------"

typedef struct
{
    char *name;
    char *lastname;
    int grade;
} Student_Data;

typedef struct
{
    Student_Data *data;
    int size;
    int capacity;
} DA_Student_Data;

void da_append(DA_Student_Data *da, Student_Data val)
{
    if (da->size < da->capacity)
    {
        da->data[da->size] = val;
        da->size++;

        return;
    }

    if (da->capacity == 0)
    {
        Student_Data *new_data = calloc(5, sizeof(Student_Data));
        new_data[da->size++] = val;
        da->data = new_data;
        da->capacity = 5;
        return;
    }

    Student_Data *new_data = realloc(da->data, sizeof(Student_Data) * da->capacity * 2);
    new_data[da->size] = val;

    da->data = new_data;
    da->size++;
    da->capacity *= 2;
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

Student_Data get_input_student(char *buf)
{
    char *bufptr = buf;
    char *tokens[1024];
    char *token;
    int n = 0;
    while ((token = strsep(&bufptr, ",")))
    {
        tokens[n] = strdup(token);
        n++;
    }

    if (n != 3)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }

    int grade = str_to_int(tokens[2]);
    free(tokens[2]);

    Student_Data student = {.name = tokens[0], .lastname = tokens[1], .grade = grade};

    return student;
}

void print_separator(const char *left, const char *mid, const char *right, int id_w, int name_w, int lastname_w,
                     int grade_w)
{
    printf("%s", left);
    for (int i = 0; i < id_w; i++)
        printf("─");
    printf("%s", mid);
    for (int i = 0; i < name_w; i++)
        printf("─");
    printf("%s", mid);
    for (int i = 0; i < lastname_w; i++)
        printf("─");
    printf("%s", mid);
    for (int i = 0; i < grade_w; i++)
        printf("─");
    printf("%s\n", right);
}

void print_table(DA_Student_Data *students)
{
    int longest_name = 0;
    int longest_lastname = 0;

    for (int i = 0; i < students->size; i++)
    {
        int namelen = strlen(students->data[i].name);
        int lastnamelen = strlen(students->data[i].lastname);
        if (namelen > longest_name)
        {
            longest_name = namelen;
        }
        if (lastnamelen > longest_lastname)
        {
            longest_lastname = lastnamelen;
        }
    }

    int id_w = 2;
    int name_w = longest_name;
    int lastname_w = longest_lastname;
    int grade_w = 5;

    if (name_w < 4)
        name_w = 4;
    if (lastname_w < 9)
        lastname_w = 9;

    print_separator("┌", "┬", "┐", id_w + 2, name_w + 2, lastname_w + 2, grade_w + 2);
    printf("│ %-*s │ %-*s │ %-*s │ %-*s │\n", id_w, "id", name_w, "name", lastname_w, "last name", grade_w, "grade");
    print_separator("├", "┼", "┤", id_w + 2, name_w + 2, lastname_w + 2, grade_w + 2);

    for (int i = 0; i < students->size; i++)
        printf("│ %*d │ %-*s │ %-*s │ %*d │\n", id_w, i + 1, name_w, students->data[i].name, lastname_w,
               students->data[i].lastname, grade_w, students->data[i].grade);

    print_separator("└", "┴", "┘", id_w + 2, name_w + 2, lastname_w + 2, grade_w + 2);
}

void print_bad_students(DA_Student_Data *students)
{
    DA_Student_Data bad_students = {0};

    for (int i = 0; i < students->size; i++)
    {
        if (students->data[i].grade > 2)
            da_append(&bad_students, students->data[i]);
    }

    print_table(&bad_students);
    free(bad_students.data);
}

int main()
{
    DA_Student_Data students = {0};

    char buf[1024];
    for (;;)
    {
        printf("a - new student\n"
               "p - print table\n"
               "b - print bad students\n"
               "x - exit\n");

        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        if (strcmp(buf, "x") == 0)
            break;

        if (strcmp(buf, "a") == 0)
        {
            printf("Input a student's name, lastname, grade separated by commas: ");
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = 0;

            Student_Data new = get_input_student(buf);
            da_append(&students, new);
        }

        if (strcmp(buf, "p") == 0)
        {
            if (students.size == 0)
            {
                fprintf(stderr, "No students yet\n");
                continue;
            }
            print_table(&students);
        }

        if (strcmp(buf, "b") == 0)
        {
            if (students.size == 0)
            {
                fprintf(stderr, "No students yet\n");
                continue;
            }
            print_bad_students(&students);
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
