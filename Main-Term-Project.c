#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Structure to store student data
struct Student 
{
    char id[6];
    char name[100];
    double score;
};

// Function to find the maximum length of names
size_t findMaxNameLength(struct Student students[], int numStudents) {
    size_t maxNameLength = 0;
    for (int i = 0; i < numStudents; i++) {
        size_t currentNameLength = strlen(students[i].name);
        if (currentNameLength > maxNameLength) {
            maxNameLength = currentNameLength;
        }
    }
    return maxNameLength;
}

// Function to print table header
void printTableHeader(size_t maxNameLength) 
{
    printf("\n%-10s | %-*s | %s\n", "Student ID", (int)maxNameLength + 2, "Name", "Score");
    printf("--------------------------------------\n");
}

// Function to print a student's information in table format
void printStudentInfo(struct Student student, size_t maxNameLength)
{
    printf("%-10s | %-*s | %.2lf\n", student.id, (int)maxNameLength + 2, student.name, student.score);
}


// 1. Function to find max and min score
void findMaxMin(struct Student students[], int numStudents) 
{
    if (numStudents > 0) 
    {
        double max = students[0].score;
        double min = students[0].score;
        // Iterate through the students to find max and min scores
        for (int i = 1; i < numStudents; i++) 
        {
            if (students[i].score > max) 
            {
                max = students[i].score;
            }

            if (students[i].score < min) 
            {
                min = students[i].score;
            }
        }
        printf("\nMaximum score: %.2lf\n", max);
        printf("Minimum score: %.2lf\n\n", min);
    } 
    else 
    {
        printf("\nNo student data available\n\n");
    }
}

// 2. Function to find average and standard deviation
void findAverageSD(struct Student students[], int numStudents) 
{
    if (numStudents > 0) 
    {
        double sum = 0.0;
        // Calculate the sum of scores
        for (int i = 0; i < numStudents; i++) 
        {
            sum += students[i].score;
        }
        double average = sum / numStudents;
        
        double sd = 0.0;
        // Calculate the sum of squared differences for standard deviation
        for (int i = 0; i < numStudents; i++) 
        {
            sd += pow(students[i].score - average, 2);
        }
        sd = sqrt(sd / numStudents);
        
        printf("\nAverage: %.2lf\n", average);
        printf("Standard Deviation: %.2lf\n\n", sd);
    } 
    else 
    {
        printf("\nNo student data available\n\n");
    }
}

// 3. Function to add student score
void addStudent(struct Student students[], int *numStudents, char filename[100]) 
{
    if (*numStudents < 100) 
    {
        char id[6];
        char name[100];
        double score;

        // Get user input for new student data
        do 
        {
            printf("Student ID: ");
            scanf("%5s", id);

            // Check if the entered ID is a 5-digit number
            int isValidID = 1;
            for (int i = 0; i < 5; i++) 
            {
                if (!isdigit(id[i])) 
                {
                    isValidID = 0;
                    break;
                }
            }

            if (strlen(id) != 5 || !isValidID) 
            {
                printf("Invalid student ID format. It should be a 5-digit number.\n");

                char retryOption;
                printf("Do you want to enter a new student ID? (y/n): ");
                scanf(" %c", &retryOption);

                if (retryOption == 'n' || retryOption == 'N') 
                {
                    // Go back to the main menu
                    return;
                }
            } 
            else 
            {
                break;
            }

        } while (1);

        // Continue with the rest of the input
        printf("Name: ");
        scanf("%s", name);
        printf("Score: ");
        scanf("%lf", &score);

        // Copy data to the next available position in the array
        strcpy(students[*numStudents].id, id);
        strcpy(students[*numStudents].name, name);
        students[*numStudents].score = score;
        (*numStudents)++;

        // Open the file for writing new data
        FILE *file = fopen(filename, "w");
        for (int i = 0; i < *numStudents; i++) 
        {
            fprintf(file, "%5s %s %.2lf\n", students[i].id, students[i].name, students[i].score);
        }
        fclose(file);

        printf("\nData added successfully\n\n");
    } 
    else 
    {
        printf("Unable to add more data\n");
    }
}


// 4. Function to search score by student ID
void searchScoreByStudentID(struct Student students[], int numStudents) 
{
    char searchID[6];

    // Get user input for student ID to search
    printf("Enter the student ID to search: ");
    scanf("%5s", searchID);

    // Find the maximum length of names
    size_t maxNameLength = findMaxNameLength(students, numStudents);

    // Print table header
    printTableHeader(maxNameLength);

    int found = 0;

    // Iterate through students to find and display the score
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].id, searchID) == 0) 
        {
            // Print the result in the desired format
            printStudentInfo(students[i], maxNameLength);
            printf("\n\n");
            found = 1;
            break;
        }
    }

    // Print a line separator after the result
    if (!found) 
    {
        printf("\nStudent ID not found\n\n");
    }
}

// 5. Function to sort scores in ascending order
void sortAscending(struct Student students[], int numStudents)
{
    // Find the maximum length of names
    size_t maxNameLength = findMaxNameLength(students, numStudents);

    printf("\nSort scores in ascending order :\n");

    // Print table header
    printTableHeader(maxNameLength);

    for (int i = 0; i < numStudents; i++)
    {
        for (int j = 0; j < numStudents - i - 1; j++)
        {
            if (students[j].score > students[j + 1].score)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Print sorted scores in ascending order
    for (int i = 0; i < numStudents; i++)
    {
        printStudentInfo(students[i], maxNameLength);
    }

    printf("\n\n");
}


// 6. Function to sort scores in descending order
void sortDescending(struct Student students[], int numStudents)
{
    // Find the maximum length of names
    size_t maxNameLength = findMaxNameLength(students, numStudents);

    printf("\nSort scores in descending order :\n");

    // Print table header
    printTableHeader(maxNameLength);

    for (int i = 0; i < numStudents; i++)
    {
        for (int j = 0; j < numStudents - i - 1; j++)
        {
            if (students[j].score < students[j + 1].score)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Print sorted scores in descending order
    for (int i = 0; i < numStudents; i++)
    {
        printStudentInfo(students[i], maxNameLength);
    }

    printf("\n\n");
}


// 7. Function to find and display students below average
void studentsBelowAverage(struct Student students[], int numStudents) 
{
    if (numStudents > 0) 
    {
        double sum = 0.0;
        // Calculate the sum of scores
        for (int i = 0; i < numStudents; i++) 
        {
            sum += students[i].score;
        }
        double average = sum / numStudents;

        // Use the findMaxNameLength function
        size_t maxNameLength = findMaxNameLength(students, numStudents);

        // Print table header
        printTableHeader(maxNameLength);

        // Display students with scores below average in table format
        for (int i = 0; i < numStudents; i++) 
        {
            if (students[i].score < average) 
            {
                printStudentInfo(students[i], maxNameLength);
            }
        }
        printf("\n\n");
    } 
    else 
    {
        printf("No student data available\n");
    }
}

// 8. Function to generate summary and save to file
void generateSummary(struct Student students[], int numStudents) 
{
    if (numStudents > 0) 
    {
        // Sort students by ID
        for (int i = 0; i < numStudents - 1; i++) 
        {
            for (int j = 0; j < numStudents - i - 1; j++) 
            {
                if (strcmp(students[j].id, students[j + 1].id) > 0) 
                {
                    struct Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        // Use the findMaxNameLength function
        size_t maxNameLength = findMaxNameLength(students, numStudents);

        // Find max, min, and average
        double max = students[0].score;
        double min = students[0].score;
        double sum = students[0].score;

        for (int i = 1; i < numStudents; i++) 
        {
            sum += students[i].score;

            if (students[i].score > max) 
            {
                max = students[i].score;
            }

            if (students[i].score < min) 
            {
                min = students[i].score;
            }
        }

        double average = sum / numStudents;

        // Print table header
        printTableHeader(maxNameLength);

        // Print sorted scores in table format
        for (int i = 0; i < numStudents; i++) 
        {
            printStudentInfo(students[i], maxNameLength);
        }

        // Print separator line
        printf("--------------------------------------\n");

        // Print summary statistics
        printf("\nMaximum Score: %.2lf\n", max);
        printf("Minimum Score: %.2lf\n", min);
        printf("Average Score: %.2lf\n", average);

        // Save to file
        FILE *summaryFile = fopen("Summary.txt", "w");
        fprintf(summaryFile, "%-10s | %-*s | %-6s\n", "Student ID", (int)maxNameLength + 2, "Name", "Score");
        fprintf(summaryFile, "--------------------------------------\n");

        for (int i = 0; i < numStudents; i++) 
        {
            fprintf(summaryFile, "%-10s | %-*s | %.2lf\n", students[i].id, (int)maxNameLength + 2, students[i].name, students[i].score);
        }

        // Print separator line
        fprintf(summaryFile, "--------------------------------------\n");

        // Print summary statistics to file
        fprintf(summaryFile, "\nMaximum Score: %.2lf\n", max);
        fprintf(summaryFile, "Minimum Score: %.2lf\n", min);
        fprintf(summaryFile, "Average Score: %.2lf\n", average);

        fclose(summaryFile);

        printf("\nSummary has been saved to Summary.txt\n\n");
    } 
    else 
    {
        printf("No student data available\n");
    }
}



int main() 
{
    char filename[100];
    int fileOpenAttempt = 0;
    FILE *file;

    int maxAttempts = 5;  // Maximum number of attempts
    int currentAttempt = 0;

    // Loop to attempt opening the file
    do 
    {
        printf("Enter the filename to open: ");
        scanf("%s", filename);

        // Attempt to open the file
        file = fopen(filename, "r");

        if (file == NULL) 
        {
            printf("Unable to open the file %s\n", filename);

            char retryOption;
            // Prompt user to retry or exit
            printf("Do you want to enter a new filename? (y/n): ");
            scanf(" %c", &retryOption);

            if (retryOption == 'n' || retryOption == 'N') {
                printf("End of program. Goodbye.\n");
                return 1;
            } 
            else 
            {
                currentAttempt++;
                if (currentAttempt >= maxAttempts) 
                {
                    printf("Exceeded maximum number of attempts. Exiting program.\n");
                    return 1;
                }
            }
        } 
        else 
        {
            // File opened successfully
            fileOpenAttempt = 1;
        }
    } while (!fileOpenAttempt);

    // Read data from the file
    struct Student students[100];
    int numStudents = 0;
    while (fscanf(file, "%5s %s %lf", students[numStudents].id, students[numStudents].name, &students[numStudents].score) != EOF) {
        numStudents++;
    }
    fclose(file);

    int choice;
    // Menu loop
    do 
    {
        // Display menu options
        printf("-----------------------------------------\n");
        printf("Choose an option:\n");
        printf("-----------------------------------------\n");
        printf("1. Find max and min score\n");
        printf("2. Find average and S.D\n");
        printf("3. Add student score\n");
        printf("4. Search score by student ID\n");
        printf("5. Sort scores in ascending order\n");
        printf("6. Sort scores in descending order\n");
        printf("7. Students below average\n");
        printf("8. Generate summary and save to file\n");  
        printf("9. Exit the program\n");
        printf("-----------------------------------------\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        // Switch statement to execute the chosen option
        switch (choice) 
        {
            case 1:
                findMaxMin(students, numStudents);
                break;

            case 2:
                findAverageSD(students, numStudents);
                break;

            case 3:
                addStudent(students, &numStudents, filename);
                break;

            case 4:
                searchScoreByStudentID(students, numStudents);
                break;

            case 5:
                sortAscending(students, numStudents);
                break;

            case 6:
                sortDescending(students, numStudents);
                break;

            case 7:
                studentsBelowAverage(students, numStudents);
                break;

            case 8:
                generateSummary(students, numStudents);  
                break;

            case 9:
                printf("End of program. Goodbye.\n");
                printf("-----------------------------------------\n");
                break;

            default:
                printf("\nInvalid choice\n\n");
                break;
        }
    } while (choice != 9);

    return 0;
}
