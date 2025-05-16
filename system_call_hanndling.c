#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

struct Student {
    int roll;
    char name[50];
    int marks;
};

void createFile(const char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        printf("Could not create file.\n");
        return;
    }
    close(fd);
    printf("Database file created successfully.\n");
}

void insertStudent(const char *filename) {
    struct Student s;
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter marks: ");
    scanf("%d", &s.marks);

    int fd = open(filename, O_WRONLY | O_APPEND);
    if (fd < 0) {
        printf("Could not open file.\n");
        return;
    }

    write(fd, &s, sizeof(s));
    close(fd);
    printf("Student record inserted.\n");
}

void viewStudents(const char *filename) {
    struct Student s;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Could not open file.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (read(fd, &s, sizeof(s)) > 0) {
        printf("Roll: %d, Name: %s, Marks: %d\n", s.roll, s.name, s.marks);
    }
    close(fd);
}

void searchStudent(const char *filename) {
    struct Student s;
    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Could not open file.\n");
        return;
    }

    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll == roll) {
            printf("Record Found -> Roll: %d, Name: %s, Marks: %d\n", s.roll, s.name, s.marks);
            close(fd);
            return;
        }
    }
    printf("Record not found.\n");
    close(fd);
}

void deleteStudent(const char *filename) {
    struct Student s;
    int roll;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Could not open file.\n");
        return;
    }

    int tempFd = open("temp.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (tempFd < 0) {
        printf("Could not create temp file.\n");
        close(fd);
        return;
    }

    int found = 0;
    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll != roll) {
            write(tempFd, &s, sizeof(s));
        } else {
            found = 1;
        }
    }

    close(fd);
    close(tempFd);
    remove(filename);
    rename("temp.dat", filename);

    if (found)
        printf("Record deleted.\n");
    else
        printf("Record not found.\n");
}

void updateStudent(const char *filename) {
    struct Student s;
    int roll;
    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        printf("Could not open file.\n");
        return;
    }

    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll == roll) {
            printf("Current -> Roll: %d, Name: %s, Marks: %d\n", s.roll, s.name, s.marks);
            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new marks: ");
            scanf("%d", &s.marks);

            lseek(fd, -sizeof(s), SEEK_CUR);
            write(fd, &s, sizeof(s));
            printf("Record updated.\n");
            close(fd);
            return;
        }
    }

    printf("Record not found.\n");
    close(fd);
}

int main() {
    const char *filename = "student.dat";
    int choice;

    do {
        printf("\n--- Student Database Menu ---\n");
        printf("1. Create\n2. View\n3. Insert\n4. Delete\n5. Update\n6. Search\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(filename); break;
            case 2: viewStudents(filename); break;
            case 3: insertStudent(filename); break;
            case 4: deleteStudent(filename); break;
            case 5: updateStudent(filename); break;
            case 6: searchStudent(filename); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}