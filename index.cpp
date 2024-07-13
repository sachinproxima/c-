#include<iostream>
#include<cstring>
#include<vector>
#include<fstream>

using namespace std;

class Resume 
{
 private:
    string name, email, phone, github, linkedin;
    vector<string> skills;
    vector<string> workExperience;
    string education;
    string projectWork;

public:
    void setPersonalInfo() {
        cout << "Enter your name: " << endl;
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your phone number (optional): ";
        getline(cin, phone);
        cout << "Enter your GitHub profile URL: ";
        getline(cin, github);
        cout << "Enter your LinkedIn profile URL: ";
        getline(cin, linkedin);
    }

    void setSkills() {
        string skill;
        cout << "Enter your skills (type 'end' to finish): " << endl;
        while (getline(cin, skill) && skill != "end") {
            skills.push_back(skill);
        }
    }

    void setWorkExperience() {
        string tempExp;
        int expCount;
        cout << "How many work experiences do you want to enter? ";
        cin >> expCount;
        cin.ignore(); // Consume newline character
        for (int i = 0; i < expCount; ++i) {
            cout << "Enter work experience #" << (i + 1) << ": (Company, Location - Dates, Title)" << endl;
            getline(cin, tempExp);
            workExperience.push_back(tempExp);
        }
    }

    void setEducation() {
        cout << "Enter your education: (Institute - Dates, Degree, CGPA/GPA)" << endl;
        getline(cin, education);
    }

    void setProjectWork() {
        cout << "Enter your project work: " << endl;
        getline(cin, projectWork);
    }

    void displayResume(ofstream& outFile) {
        // Combine all sections into a single string
        string resume;

        // Personal Information Section
        resume.append(name + "\n");
        resume.append(email + " | " + phone + "\n"); // Add phone number if desired
        resume.append(github + " | " + linkedin + "\n\n");

        // Skills Section with separator line
        resume.append("Skills\n");
        resume.append(string(60, '_') + "\n"); // Separator line
        for (const string& skill : skills) {
            resume.append(skill + "\n");
        }
        resume.append("\n");

        // Work Experience Section with separator line
        resume.append("Work Experience\n");
        resume.append(string(60, '_') + "\n"); // Separator line
        for (const string& exp : workExperience) {
            resume.append(exp + "\n");
        }
        resume.append("\n");

        // Education Section with separator line
        resume.append("Education\n");
        resume.append(string(60, '_') + "\n"); // Separator line
        resume.append(education + "\n\n");

        // Project Work Section with separator line
        resume.append("Project Work\n");
        resume.append(string(60, '_') + "\n"); // Separator line
        resume.append(projectWork + "\n");

        // Output the resume to the file
        outFile << resume;
    }
};

int main() {
    ofstream resumeFile("resume.txt");
    if (!resumeFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return 1;
    }

    Resume myResume;

    myResume.setPersonalInfo();
    myResume.setSkills();
    myResume.setWorkExperience();
    myResume.setEducation();
    myResume.setProjectWork();

    myResume.displayResume(resumeFile);

    resumeFile.close();

    return 0;
}
