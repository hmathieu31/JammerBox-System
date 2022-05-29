#ifndef SRC_INTERFACE_SRC_RESULTS_INCLUDE_RESULTS_H_INCLUDED_
#define SRC_INTERFACE_SRC_RESULTS_INCLUDE_RESULTS_H_INCLUDED_

#include <string>
#include <map>
#include <stdexcept>

namespace jbox {
namespace results {

struct Result {
  const char identifier;
  std::string message;
    
  // Default Constructor
  Result() : identifier('\0'), message("") {}

  Result(char identifier);

  ~Result() = default;
};

}  // namespace results
}  // namespace jbox

#endif
