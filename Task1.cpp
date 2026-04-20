#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// Convert letter grade to grade points (10-point scale)
double gradeToPoints(const string& grade) {
    if (grade == "O")  return 10.0;
    if (grade == "A+") return 9.0;
    if (grade == "A")  return 8.0;
    if (grade == "B+") return 7.0;
    if (grade == "B")  return 6.0;
    if (grade == "C+") return 5.0;
    if (grade == "C")  return 4.0;
    if (grade == "P")  return 4.0;
    if (grade == "F")  return 0.0;
    return -1.0; // invalid
}

int main() {
    int numCourses;

    cout << "----------------------------------------\n";
    cout << "         CGPA CALCULATOR (C++)\n";
    cout << "----------------------------------------\n";
    cout << "Grade scale: O(10) A+(9) A(8) B+(7) B(6)\n";
    cout << "             C+(5) C(4) P(4) F(0)\n";
    cout << "----------------------------------------\n";

    cout << "Enter number of courses: ";
    cin >> numCourses;

    if (numCourses <= 0) {
        cout << "Invalid number of courses.\n";
        return 1;
    }

    // Vectors to store course data
    vector<string> courseNames(numCourses);
    vector<string> grades(numCourses);
    vector<int>    credits(numCourses);
    vector<double> gradePoints(numCourses);

    double totalCredits    = 0;
    double totalGradePoints = 0;

    // Input loop
    for (int i = 0; i < numCourses; i++) {
        cout << "\n--- Course " << (i + 1) << " ---\n";

        cin.ignore();   
        cout << "Course name   : ";
        getline(cin, courseNames[i]);

        // Grade input with validation
        double gp = -1.0;
        while (gp < 0) {
            cout << "Grade         : ";
            cin >> grades[i];
            gp = gradeToPoints(grades[i]);
            if (gp < 0)
                cout << "Invalid grade. Use: O A+ A B+ B C+ C P F\n";
        }

        // Credit hours input with validation
        while (true) {
            cout << "Credit hours  : ";
            cin >> credits[i];
            if (credits[i] > 0) break;
            cout << "Credit hours must be greater than 0.\n";
        }

        gradePoints[i]    = gp;
        totalCredits      += credits[i];
        totalGradePoints  += gp * credits[i];
    }

    // Calculate GPA / CGPA
    double cgpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;

    // Display results
    cout << "\n\n========================================\n";
    cout << "           COURSE SUMMARY\n";
    cout << "========================================\n";
    cout << left
         << setw(20) << "Course"
         << setw(8)  << "Grade"
         << setw(10) << "Credits"
         << setw(12) << "Grade Pts"
         << "Status\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < numCourses; i++) {
        double pts = gradePoints[i] * credits[i];
        string status = (gradePoints[i] >= 4.0) ? "Pass" : "FAIL";
        cout << left
             << setw(20) << courseNames[i]
             << setw(8)  << grades[i]
             << setw(10) << credits[i]
             << setw(12) << fixed << setprecision(2) << pts
             << status   << "\n";
    }

    cout << "========================================\n";
    cout << "Total Credits     : " << totalCredits    << "\n";
    cout << "Total Grade Points: " << fixed << setprecision(2) << totalGradePoints << "\n";
    cout << "----------------------------------------\n";
    cout << "Semester GPA      : " << fixed << setprecision(2) << cgpa << "\n";
    cout << "Overall CGPA      : " << fixed << setprecision(2) << cgpa << "\n";
    cout << "========================================\n";

    return 0;
}