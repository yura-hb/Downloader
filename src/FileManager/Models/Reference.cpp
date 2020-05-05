#include "Reference.hpp"

bool Reference::isDirectory() const{
  return type == Type::HYPER_LINK && path.at(path.size() - 1) == '/';
}

bool Reference::isRelative() const {
  return *path.begin() == '/';
}

Reference Reference::addAbsoleteReference(const std::string& str) const {
  if (type == Type::EXTERNAL_LINK)
    throw Exception("Only can apply on the local references");
  return Reference(str + '/' + path);
}

Reference Reference::addPath(const std::string& str) const {
  if (type == Type::EXTERNAL_LINK)
    throw Exception("Only can apply on the local references");

  return Reference(path + '/' + str);
}

std::list<std::string> Reference::loadComponents() const {
  if (type == Type::EXTERNAL_LINK)
    return {};

  std::list<std::string> list;

  auto begin = path.begin();
  auto next = path.begin();

  while ((next = std::find(begin, path.end(), '/')) != path.end()) {
    list.push_back(std::string(begin, next));
    begin = next + 1;
  }

  list.push_back(std::string(begin, path.end()));
  return list;
}

void Reference::simplify() {
  std::list<std::string> components = loadComponents();

  auto accumulator = [this, components](std::string result, std::string& component) {
    if (component == "" || component == ".")
      return result;

    // In this case, remove previous reference
    if (component == "..") {
      auto iter = result.rbegin();
      if ((iter = std::find(result.rbegin(), result.rend(), '/')) != result.rend()) {
        int offset = result.rend() - iter;
        return std::string(result.begin(), result.begin() + offset);
      }
      return std::string();
    }
    if (result == "/" && isRelative())
      return std::move(result) + component;

    return std::move(result) + component + "/";
  };

  bool isDirectoryPath = isDirectory();
  std::string prefix = isRelative() ? "/" : "";
  path = prefix + std::accumulate(components.begin(), components.end(), std::string(), accumulator);

  if (path.at(path.size() - 1) == '/')
    path.at(path.size() - 1) = isDirectoryPath ? '/' : ' ';
}

std::ostream& operator<< (std::ostream& out, const Reference& ref) {
  out << ref.path << std::endl;
  return out;
}
