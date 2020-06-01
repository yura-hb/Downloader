#include "HTMLAttribute.hpp"

const std::string HTMLAttribute::javascriptPrefix = "javascript";
const std::string HTMLAttribute::tag = "#";

bool HTMLAttribute::consume(const Input& input, const EmitFunction& func) const {
  AbstractPattern::EmitFunction function = std::function<void(const Data<>&)>([&](const Data<>& str) {
    if ((str.find(javascriptPrefix, str.begin()) != str.end()) || (str.find(tag, str.begin()) != str.end()))
      return;

    func(str);
  });

  return Attribute::consume(input, function);
}
