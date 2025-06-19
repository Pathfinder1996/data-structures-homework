/*
Data Structures Homework 1
M11212913 Sheng-Yen Dai, 2025/03/07
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*
Definition of the student structure
Includes all fields from the PDF assignment,
and an additional 'final_score' field to store the average score.
Each student sizeof(student) = 124 bytes.
*/
typedef struct {
    char name[80];
    char personal_id[9];
    char student_id[10];
    int age;
    char dept[3];
    int mid_1;
    int mid_2;
    int term_exam;
    int final_score;
} student;

/*
Function Prototypes
*/
void demo_input();
// void check_info(student *arr, int num);
void selection_sort(student* arr, const int n);

int main() {

    /*
    Check the structure size (for internal verification).
    Not required for assignment output, so it's commented out.
    sizeof(student) = 124 bytes.
    */
    // cout << sizeof(student) << endl;

    demo_input();

    return 0;
}

/*
This function:
1. Reads "list2.txt".
2. Loads the data into a dynamically allocated student array.
3. Calculates final_score (average).
4. Sorts the array in ascending order of final_score.
5. Prints sorted results and the student with the highest score.
*/
void demo_input() {
    /*
    Read the file. If it does not exist, terminate.
    */
    ifstream fin("input.txt");

    if (!fin) {
        cout << "File not found" << endl;
        exit(1);
    }

    int num;

    /*
    Read the first line of the file to get the number of students.
    */
    fin >> num;

    /*
    Allocate the student array dynamically and read file data.
    */
    student* student_info = new student[num];
    int i;
    for (i = 0; i < num; i++) {
        fin >> student_info[i].name
            >> student_info[i].personal_id
            >> student_info[i].student_id
            >> student_info[i].age
            >> student_info[i].dept
            >> student_info[i].mid_1
            >> student_info[i].mid_2
            >> student_info[i].term_exam;

        student_info[i].final_score = (student_info[i].mid_1 + student_info[i].mid_2 + student_info[i].term_exam) / 3;
    }

    /*
    Check contents for internal verification.
    Not required for assignment output, so it's commented out.
    */
    // check_info(student_info, num);

    /*
    Perform selection sort based on final_score (ascending).
    */
    selection_sort(student_info, num);

    /*
    Check sorted contents for internal verification.
    Not required for assignment output, so it's commented out.
    */
    // check_info(student_info, num);

    /*
    Output sorted student records and the student with the highest final_score.
    */
    cout << "Student Record List Sorted Ascendingly according to Final Score" << endl;
    cout << " Index F_NAME   StudentID   AGE Mid1 Mid2 Term Final" << endl;

    for (i = 0; i < num; i++) {
        cout << right << setw(4) << i
            << "   " << left << setw(9) << student_info[i].name
            << left << setw(12) << student_info[i].student_id
            << left << setw(5) << student_info[i].age
            << left << setw(5) << student_info[i].mid_1
            << left << setw(5) << student_info[i].mid_2
            << left << setw(6) << student_info[i].term_exam
            << left << setw(3) << student_info[i].final_score << endl;
    }
    cout << "The student with the highest score:" << endl;
    cout << "F_NAME    : " << student_info[num - 1].name << endl;
    cout << "ID        : " << student_info[num - 1].personal_id << endl;
    cout << "StudentID : " << student_info[num - 1].student_id << endl;
    cout << "AGE       : " << student_info[num - 1].age << endl;
    cout << "Scores    : " << student_info[num - 1].mid_1
        << "," << student_info[num - 1].mid_2
        << "," << student_info[num - 1].term_exam << endl;
    cout << "Final     : " << student_info[num - 1].final_score << endl;

    /*
    Close the file and free the allocated array.
    */
    fin.close();
    delete[] student_info;

}

/*
Check student array contents (internal use).
Not required for assignment output, so it's commented out.
*/
// void check_info(student *arr, int num) {
//     int i;
//     for (i = 0; i < num; i++) {
//         cout << left << setw(10) << arr[i].name
//             << setw(10) << arr[i].personal_id 
//             << setw(10) << arr[i].student_id
//             << setw(5) << arr[i].age
//             << setw(5) << arr[i].dept
//             << setw(5) << arr[i].mid_1
//             << setw(5) << arr[i].mid_2
//             << setw(5) << arr[i].term_exam
//             << setw(5) << arr[i].final_score << endl;
//     }
// }

/*
Selection sort: sorts the student array
in ascending order of final_score.
*/
void selection_sort(student* arr, const int n) {
    int i, k, s;
    student temp;
    for (i = 0; i < n; i++) {
        s = i;

        for (k = i + 1; k < n; k++) {
            if (arr[k].final_score < arr[s].final_score) {
                s = k;
            }
        }

        temp = arr[i];
        arr[i] = arr[s];
        arr[s] = temp;
    }
}
