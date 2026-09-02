#include <ResumeParser/DocumentParser/DocumentParser.h>
#include <ResumeParser/ResumeParserPipeline/ResumeParserPipeline.h>
#include <iostream>
#include <nlohmann/json.hpp>
int main(int argc, char *argv[]) {

  if (argc < 2) {
    throw ResumeParser::ParseException("Not enough arguments");
  } else {

    auto resume = ResumeParser::ResumeParserPipeline::parseFile(argv[1]);

    auto json = nlohmann::json(resume);
    std::cout << json.dump(4) << std::endl;

    std::cout << "Name: " << resume.personalInfo.name << "\n";
    std::cout << "Email: " << resume.personalInfo.email << "\n";
    std::cout << "Phone: " << resume.personalInfo.phone << "\n";

    std::cout << "\nSkills:\n";
    for (const auto &s : resume.skills) {
      std::cout << "  - " << s << "\n";
    }

    std::cout << "\nEducation:\n";
    for (const auto &e : resume.education) {
      std::cout << "  " << e.degree << " | " << e.institution << " | " << e.year
                << "\n";
    }

    std::cout << "\nExperience:\n";
    for (const auto &e : resume.experience) {
      std::cout << "  " << e.title << " | " << e.company << " | "
                << e.description << "\n";
    }

    std::cout << "\nProjects:\n";
    for (const auto &p : resume.projects) {
      std::cout << "  " << p.name << " | " << p.description << "\n";
    }
  }
}
