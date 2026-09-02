#include "ResumeParser/EntityExtractor/EntityExtractor.h"
#include <regex>
#include <sstream>

namespace ResumeParser {

std::string EntityExtractor::extractEmail(const std::string &text) {
  static const std::regex emailPattern(
      R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
  std::smatch match;
  if (std::regex_search(text, match, emailPattern)) {
    return match.str();
  }
  return "";
}

std::string EntityExtractor::extractPhone(const std::string &text) {
  static const std::regex phonePattern(
      R"((\+?\d{1,3}[-\s]?)?\d{10}|(\+?\d{1,3}[-\s]?)?\d{3}[-\s]?\d{3}[-\s]?\d{4})");
  std::smatch match;
  if (std::regex_search(text, match, phonePattern)) {
    return match.str();
  }
  return "";
}

PersonalInfo
EntityExtractor::extractPersonalInfo(const std::vector<Line> &lines) {
  PersonalInfo info;
  for (const auto &line : lines) {
    if (info.email.empty()) {
      info.email = extractEmail(line.text);
    }
    if (info.phone.empty()) {
      info.phone = extractPhone(line.text);
    }
  }
  if (!lines.empty()) {
    info.name = lines[0].text;
  }
  return info;
}

std::vector<Education>
EntityExtractor::extractEducation(const std::vector<Line> &lines) {
  std::vector<Education> result;
  Education current;
  for (const auto &line : lines) {
    if (line.text.empty())
      continue;
    if (current.degree.empty()) {
      current.degree = line.text;
    } else if (current.institution.empty()) {
      current.institution = line.text;
      result.push_back(current);
      current = Education{};
    }
  }
  if (!current.degree.empty()) {
    result.push_back(current);
  }
  return result;
}

std::vector<Experience>
EntityExtractor::extractExperience(const std::vector<Line> &lines) {
  std::vector<Experience> result;
  Experience current;
  for (const auto &line : lines) {
    if (line.text.empty())
      continue;
    if (current.title.empty()) {
      current.title = line.text;
    } else {
      current.description +=
          (current.description.empty() ? "" : " ") + line.text;
    }
  }
  if (!current.title.empty()) {
    result.push_back(current);
  }
  return result;
}

std::vector<std::string>
EntityExtractor::extractSkills(const std::vector<Line> &lines) {
  std::vector<std::string> result;
  for (const auto &line : lines) {
    std::stringstream ss(line.text);
    std::string skill;
    while (std::getline(ss, skill, ',')) {
      auto start = skill.find_first_not_of(" \t");
      auto end = skill.find_last_not_of(" \t");
      if (start != std::string::npos) {
        result.push_back(skill.substr(start, end - start + 1));
      }
    }
  }
  return result;
}

std::vector<Project>
EntityExtractor::extractProjects(const std::vector<Line> &lines) {
  std::vector<Project> result;
  Project current;
  for (const auto &line : lines) {
    if (line.text.empty())
      continue;
    if (current.name.empty()) {
      current.name = line.text;
    } else {
      current.description +=
          (current.description.empty() ? "" : " ") + line.text;
    }
  }
  if (!current.name.empty()) {
    result.push_back(current);
  }
  return result;
}

Resume EntityExtractor::extract(const std::vector<ClassifiedBlock> &blocks) {
  Resume resume;

  for (const auto &block : blocks) {
    switch (block.type) {
    case SectionType::PersonalInfo: {
      PersonalInfo info = extractPersonalInfo(block.lines);
      if (!info.name.empty())
        resume.personalInfo.name = info.name;
      if (!info.email.empty())
        resume.personalInfo.email = info.email;
      if (!info.phone.empty())
        resume.personalInfo.phone = info.phone;
      break;
    }
    case SectionType::Education: {
      auto edu = extractEducation(block.lines);
      resume.education.insert(resume.education.end(), edu.begin(), edu.end());
      break;
    }
    case SectionType::Experience: {
      auto exp = extractExperience(block.lines);
      resume.experience.insert(resume.experience.end(), exp.begin(), exp.end());
      break;
    }
    case SectionType::Skills: {
      auto sk = extractSkills(block.lines);
      resume.skills.insert(resume.skills.end(), sk.begin(), sk.end());
      break;
    }
    case SectionType::Projects: {
      auto proj = extractProjects(block.lines);
      resume.projects.insert(resume.projects.end(), proj.begin(), proj.end());
      break;
    }
    default:
      break;
    }
  }

  return resume;
}

} // namespace ResumeParser
