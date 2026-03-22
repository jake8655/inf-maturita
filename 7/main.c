#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int *points_per_discipline;
    int total;
} Student_Data;

typedef struct
{
    Student_Data *data;
    int size;
    int capacity;
} DA_Student_Data;

int da_get_idx(DA_Student_Data *da, Student_Data *val)
{
    int i;
    for (i = 0; i < da->size; i++)
    {
        if (val->total >= da->data[i].total)
        {
            return i;
        }
    }

    return i;
}

void da_append(DA_Student_Data *da, Student_Data val)
{
    if (da->capacity >= da->size + 1)
    {
        int new_idx = da_get_idx(da, &val);

        for (int i = da->size; i > new_idx; i--)
        {
            da->data[i] = da->data[i - 1];
        }
        da->data[new_idx] = val;
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
    int new_idx = da_get_idx(da, &val);

    for (int i = da->size; i > new_idx; i--)
    {
        new_data[i] = new_data[i - 1];
    }
    new_data[new_idx] = val;

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

    if (n != 5)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }

    int *points_per_discipline = calloc(4, sizeof(int));
    int total = 0;
    for (int i = 0; i < 4; i++)
    {
        points_per_discipline[i] = str_to_int(tokens[i + 1]);
        total += points_per_discipline[i];
        free(tokens[i + 1]);
    }

    Student_Data student = {.name = tokens[0], .points_per_discipline = points_per_discipline, .total = total};

    return student;
}

void save_data(DA_Student_Data *sd)
{
    FILE *f = fopen("./vysledkova listina.txt", "w");

    int longest_name_len = 0;
    for (int i = 0; i < sd->size; i++)
    {
        int len = strlen(sd->data[i].name);
        if (len > longest_name_len)
        {
            longest_name_len = len;
        }
    }

    for (int i = 0; i < sd->size; i++)
    {
        fprintf(f, "%d. %-*s %db\n", i + 1, longest_name_len + 9, sd->data[i].name, sd->data[i].total);
    }

    fclose(f);
}

int main()
{
    DA_Student_Data students = {0};

    char buf[1024];
    for (;;)
    {
        printf("Input a student's name, points per each discipline separated by commas (x to stop): ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        if (strcmp(buf, "x") == 0)
            break;

        Student_Data new = get_input_student(buf);
        printf("Name: %s, Total: %d\n", new.name, new.total);
        da_append(&students, new);

        save_data(&students);
    }

    for (int i = 0; i < students.size; i++)
    {
        free(students.data[i].name);
        free(students.data[i].points_per_discipline);
    }
    free(students.data);

    return 0;
}
