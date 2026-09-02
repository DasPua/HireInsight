#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace ResumeParser {

struct PersonalInfo {
  std::string name;
  std::string email;
  std::string phone;
};

struct Education {
  std::string degree;
  std::string institution;
  std::string year;
};

struct Experience {
  std::string title;
  std::string company;
  std::string duration;
  std::string description;
};

struct Project {
  std::string name;
  std::string description;
};

struct Resume {
  PersonalInfo personalInfo;
  std::vector<Education> education;
  std::vector<Experience> experience;
  std::vector<Project> projects;
  std::vector<std::string> skills;
};
inline void to_json(nlohmann::json &j, const PersonalInfo &p) {
  j = nlohmann::json{{"name", p.name}, {"email", p.email}, {"phone", p.phone}};
}
inline void to_json(nlohmann::json &j, const Education &p) {
  j = nlohmann::json{
      {"degree", p.degree}, {"institution", p.institution}, {"year", p.year}};
}
inline void to_json(nlohmann::json &j, const Experience &p) {
  j = nlohmann::json{{"company", p.company},
                     {"description", p.description},
                     {"duration", p.duration},
                     {"title", p.title}};
}
inline void to_json(nlohmann::json &j, const Project &p) {
  j = nlohmann::json{
      {"name", p.name},
      {"description", p.description},
  };
}
inline void to_json(nlohmann::json &j, const Resume &r) {
  j = nlohmann::json{
      {"personalInfo", r.personalInfo},
      {"education", r.education},
      {"experience", r.experience},
      {"projects", r.projects},
      {"skills", r.skills},
  };
}

} // namespace ResumeParser
