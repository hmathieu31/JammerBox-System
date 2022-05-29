#include "results.h"

namespace jbox {
namespace results {

namespace {
  const std::map<char, std::string> messages = {
    std::make_pair('1', "COM error"), 
    std::make_pair('2', "CRK is configured"), 
    std::make_pair('3', "CAM is configured"), 
    std::make_pair('4', "CRK-synchronization ready"), 
    std::make_pair('5', "CRK-synchronization lost"), 
    std::make_pair('6', "CAM/CRK-synchronization ready"), 
    std::make_pair('7', "CAM/CRK-synchronization lost"), 
    std::make_pair('8', "Failure active"), 
    std::make_pair('9', "Failure passive"), 
    std::make_pair('a', "Failure CAM blank out active"), 
    std::make_pair('b', "Failure CAM blank out passive"), 
    std::make_pair('x', "Successful communication"), 
    std::make_pair('y', "")
  };
}

Result::Result(char identifier) : identifier(identifier) {
  try {
    message = messages.at(identifier);
  } catch(const std::out_of_range &e) {
    fprintf(stderr, "jbox::results:: Error identifier %c not found\n", identifier);
    message = "unknown result";
  }
}

}  // namespace results
}  // namespace jbox
