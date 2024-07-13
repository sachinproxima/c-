#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <hpdf.h>

using namespace std;

class ResumePDF {
public:
    ResumePDF(const string &output_file) {
        pdf = HPDF_New(NULL, NULL);
        if (!pdf) {
            throw runtime_error("Error: Cannot create PDF object.");
        }
        HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
        HPDF_UseJPEncodings(pdf);
        HPDF_UseJPFonts(pdf);
        output = output_file;
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    }

    ~ResumePDF() {
        HPDF_SaveToFile(pdf, output.c_str());
        HPDF_Free(pdf);
    }

    void addText(float x, float y, const string &text, int size, bool bold = false) {
        HPDF_Page_BeginText(page);
        HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, bold ? "Helvetica-Bold" : "Helvetica", NULL), size);
        HPDF_Page_TextOut(page, x, y, text.c_str());
        HPDF_Page_EndText(page);
    }

    void addSection(float &y, const string &title, int title_size, const vector<string> &lines, int line_size) {
        addText(50, y, title, title_size, true);
        y -= 20;
        for (const string &line : lines) {
            addText(50, y, line, line_size);
            y -= 15;
        }
        y -= 10;
    }

    void generatePDF(const string &name, const string &role, const string &email, const string &linkedin,
                     const vector<string> &achievements, const vector<string> &skills, const string &my_time,
                     const vector<map<string, string>> &degrees, const vector<map<string, string>> &languages,
                     const vector<map<string, string>> &certifications, const string &summary) {

        float y = 800;

        addText(50, y, name, 24, true);
        y -= 30;
        addText(50, y, "Role: " + role, 18, true);
        y -= 30;

        addText(50, y, email, 14, true);
        y -= 20;
        addText(50, y, "LinkedIn/Portfolio: " + linkedin, 14, true);
        y -= 40;

        vector<string> achievements_lines = { "ACHIEVEMENTS:" };
        achievements_lines.insert(achievements_lines.end(), achievements.begin(), achievements.end());
        addSection(y, "ACHIEVEMENTS", 18, achievements_lines, 12);

        vector<string> skills_lines = { "SKILLS:" };
        skills_lines.insert(skills_lines.end(), skills.begin(), skills.end());
        addSection(y, "SKILLS", 18, skills_lines, 12);

        addSection(y, "MY TIME", 18, {my_time}, 12);

        vector<string> education_lines = { "EDUCATION:" };
        for (const auto &degree : degrees) {
            education_lines.push_back("Degree and Field of Study: " + degree.at("name"));
            education_lines.push_back("  School or University: " + degree.at("school"));
            education_lines.push_back("  Date Period: " + degree.at("date_period"));
            education_lines.push_back("  Location: " + degree.at("location"));
        }
        addSection(y, "EDUCATION", 18, education_lines, 12);

        vector<string> languages_lines = { "LANGUAGES:" };
        for (const auto &language : languages) {
            languages_lines.push_back("Language: " + language.at("name"));
            languages_lines.push_back("  Level: " + language.at("level"));
        }
        addSection(y, "LANGUAGES", 18, languages_lines, 12);

        vector<string> certifications_lines = { "CERTIFICATION:" };
        for (const auto &certification : certifications) {
            certifications_lines.push_back("Course Title: " + certification.at("name"));
            certifications_lines.push_back("  Institution: " + certification.at("institution"));
        }
        addSection(y, "CERTIFICATION", 18, certifications_lines, 12);

        addSection(y, "SUMMARY", 18, {summary}, 12);
    }

private:
    HPDF_Doc pdf;
    HPDF_Page page;
    string output;
};

int main() {
    string name, role, email, linkedin, my_time, summary;
    vector<string> achievements, skills;
    vector<map<string, string>> degrees, languages, certifications;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter the role you are applying for: ";
    getline(cin, role);

    cout << "Enter your email address: ";
    getline(cin, email);

    cout << "Enter your LinkedIn profile URL: ";
    getline(cin, linkedin);

    // Get user input for achievements
    string achievement;
    cout << "Enter an achievement (or type 'end' to finish): ";
    while (true) {
        getline(cin, achievement);
        if (achievement == "end") {
            break;
        }
        achievements.push_back(achievement);
    }

    // Get user input for skills
    string skill;
    cout << "Enter a skill (or type 'end' to finish): ";
    while (true) {
        getline(cin, skill);
        if (skill == "end") {
            break;
        }
        skills.push_back(skill);
    }

    cout << "Enter your My Time information: ";
    getline(cin, my_time);

    // Get user input for education
    string degree_name, school, date_period, location;
    cout << "Enter the name of a degree (or type 'end' to finish): ";
    while (true) {
        getline(cin, degree_name);
        if (degree_name == "end") {
            break;
        }
        cout << "Enter the school for this degree: ";
        getline(cin, school);
        cout << "Enter the date period for this degree: ";
        getline(cin, date_period);
        cout << "Enter the location for this degree: ";
        getline(cin, location);
        map<string, string> degree = {{"name", degree_name}, {"school", school}, {"date_period", date_period}, {"location", location}};
        degrees.push_back(degree);
    }

    // Get user input for languages
    string language_name, level;
    cout << "Enter a language (or type 'end' to finish): ";
    while (true) {
        getline(cin, language_name);
        if (language_name == "end") {
            break;
        }
        cout << "Enter the level of proficiency in this language: ";
        getline(cin, level);
        map<string, string> language = {{"name", language_name}, {"level", level}};
        languages.push_back(language);
    }

    // Get user input for certifications
    string certification_name, institution;
    cout << "Enter a certification (or type 'end' to finish): ";
    while (true) {
        getline(cin, certification_name);
        if (certification_name == "end") {
            break;
        }
        cout << "Enter the institution that provided this certification: ";
        getline(cin, institution);
        map<string, string> certification = {{"name", certification_name}, {"institution", institution}};
        certifications.push_back(certification);
    }

    cout << "Enter a brief summary of your qualifications: ";
    getline(cin, summary);

    // Generate the PDF
    try {
        string output_file = name + "_resume.pdf";
        ResumePDF pdf(output_file);
        pdf.generatePDF(name, role, email, linkedin, achievements, skills, my_time, degrees, languages, certifications, summary);
        cout << "PDF generated successfully: " << output_file << endl;
    } catch (const exception &e) {
        cout << "Error generating PDF: " << e.what() << endl;
        return 1;
    }

    return 0;
}