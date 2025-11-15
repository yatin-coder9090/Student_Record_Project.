#include <stdio.h>
#include <string.h>

#define MAX 100  // Maximum number of students

// Structure to store student information
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function prototypes
void addStudent(struct Student s[], int *n);
void displayStudents(struct Student s[], int n);
void linearSearch(struct Student s[], int n, int roll);
int binarySearch(struct Student s[], int left, int right, int roll);
void mergeSort(struct Student s[], int left, int right);
void merge(struct Student s[], int left, int mid, int right);
void quickSort(struct Student s[], int low, int high);
int partition(struct Student s[], int low, int high);

int main() {
    struct Student s[MAX];
    int n = 0;
    int choice, roll, pos;

    while (1) {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search (Linear)\n");
        printf("4. Search (Binary)\n");
        printf("5. Sort (Merge Sort)\n");
        printf("6. Sort (Quick Sort)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(s, &n);
                break;
            case 2:
                displayStudents(s, n);
                break;
            case 3:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                linearSearch(s, n, roll);
                break;
            case 4:
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                pos = binarySearch(s, 0, n - 1, roll);
                if (pos != -1)
                    printf("Student Found: Roll=%d, Name=%s, Marks=%.2f\n", s[pos].roll, s[pos].name, s[pos].marks);
                else
                    printf("Student not found! (Note: Binary search works only on sorted data)\n");
                break;
            case 5:
                mergeSort(s, 0, n - 1);
                printf("Records sorted using Merge Sort!\n");
                break;
            case 6:
                quickSort(s, 0, n - 1);
                printf("Records sorted using Quick Sort!\n");
                break;
            case 7:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Function to add a new student
void addStudent(struct Student s[], int *n) {
    if (*n >= MAX) {
        printf("Cannot add more students. Limit reached.\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s[*n].roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s[*n].name);
    printf("Enter Marks: ");
    scanf("%f", &s[*n].marks);

    (*n)++;
    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents(struct Student s[], int n) {
    if (n == 0) {
        printf("No records to display!\n");
        return;
    }

    printf("\n%-10s %-20s %-10s\n", "Roll", "Name", "Marks");
    printf("---------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-10.2f\n", s[i].roll, s[i].name, s[i].marks);
    }
}

// Linear search
void linearSearch(struct Student s[], int n, int roll) {
    for (int i = 0; i < n; i++) {
        if (s[i].roll == roll) {
            printf("Student Found: Roll=%d, Name=%s, Marks=%.2f\n", s[i].roll, s[i].name, s[i].marks);
            return;
        }
    }
    printf("Student not found!\n");
}

// Binary search (array must be sorted by roll)
int binarySearch(struct Student s[], int left, int right, int roll) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (s[mid].roll == roll)
            return mid;
        else if (s[mid].roll < roll)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Merge Sort
void mergeSort(struct Student s[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(s, left, mid);
        mergeSort(s, mid + 1, right);
        merge(s, left, mid, right);
    }
}

void merge(struct Student s[], int left, int mid, int right) {
    struct Student temp[MAX];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (s[i].roll < s[j].roll)
            temp[k++] = s[i++];
        else
            temp[k++] = s[j++];
    }

    while (i <= mid)
        temp[k++] = s[i++];
    while (j <= right)
        temp[k++] = s[j++];

    for (i = left, j = 0; i <= right; i++, j++)
        s[i] = temp[j];
}

// Quick Sort
void quickSort(struct Student s[], int low, int high) {
    if (low < high) {
        int pi = partition(s, low, high);
        quickSort(s, low, pi - 1);
        quickSort(s, pi + 1, high);
    }
}

int partition(struct Student s[], int low, int high) {
    int pivot = s[high].roll;
    int i = low - 1;
    struct Student temp;

    for (int j = low; j < high; j++) {
        if (s[j].roll < pivot) {
            i++;
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
    }

    temp = s[i + 1];
    s[i + 1] = s[high];
    s[high] = temp;

    return (i + 1);
}
