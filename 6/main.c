#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int points;
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
    if (da->capacity >= da->size + 1)
    {
        da->data[da->size++] = val;
        return;
    }

    if (da->capacity == 0)
    {
        Student_Data *new_data = malloc(sizeof(Student_Data) * 5);
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
           "Name: %s\nPoints: %d\nGrade: %d\n"
           "---------------\n",
           student->name, student->points, student->grade);
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
    printf("Input a student's name, points, grade separated by spaces: ");
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

    if (n != 3)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }

    Student_Data student = {
        .name = tokens[0],
        .points = str_to_int(tokens[1]),
        .grade = str_to_int(tokens[2]),
    };
    free(tokens[1]);
    free(tokens[2]);

    return student;
}

typedef struct
{
    int *students_per_grade;
    float *avg_pts_per_grade;
} Table_Data;

int num_digits(int n)
{
    if (n < 0)
        return num_digits((n == INT_MIN) ? INT_MAX : -n);
    if (n < 10)
        return 1;

    return 1 + num_digits(n / 10);
}

Table_Data calculate_table_data(DA_Student_Data *students)
{
    Table_Data td;
    td.students_per_grade = calloc(5, sizeof(int));
    td.avg_pts_per_grade = calloc(5, sizeof(int));
    int sums[5] = {0};

    for (int i = 0; i < students->size; i++)
    {
        sums[students->data[i].grade - 1] += students->data[i].points;
        td.students_per_grade[students->data[i].grade - 1]++;
    }

    for (int i = 0; i < 5; i++)
    {
        td.avg_pts_per_grade[i] = td.students_per_grade[i] ? (float)sums[i] / td.students_per_grade[i] : 0;
    }

    return td;
}

void print_table(DA_Student_Data *students)
{
    Table_Data td = calculate_table_data(students);

    printf("| %-5s | %-8s | %-7s |\n", "grade", "students", "avg pts");
    for (int i = 1; i < 6; i++)
    {
        printf("| %5d | %8d | %7.2f |\n", i, td.students_per_grade[i - 1], td.avg_pts_per_grade[i - 1]);
    }
}

void print_best_student(DA_Student_Data *students)
{
    int max_pts = 0;
    int best_idx = -1;
    for (int i = 0; i < students->size; i++)
    {
        if (students->data[i].grade == 1 && students->data[i].points > max_pts)
        {
            max_pts = students->data[i].points;
            best_idx = i;
        }
    }

    if (best_idx != -1)
        printf("Best 1 student: %s\n", students->data[best_idx].name);
}

void print_menu()
{
    printf("a - add student\n"
           "p - print students\n"
           "t - print table\n"
           "b - print best student\n"
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

        if (strcmp(buf, "t") == 0)
        {
            if (students.size == 0)
            {
                printf("No students\n");
                continue;
            }
            print_table(&students);
        }

        if (strcmp(buf, "b") == 0)
        {
            if (students.size == 0)
            {
                printf("No students\n");
                continue;
            }
            print_best_student(&students);
        }
    }

    for (int i = 0; i < students.size; i++)
    {
        free(students.data[i].name);
    }
    free(students.data);

    return 0;
}
