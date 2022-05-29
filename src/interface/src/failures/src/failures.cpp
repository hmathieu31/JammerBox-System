#include "failures.h"

#include <sstream>
#include <stdexcept>

#define START_CHAR '!'
#define SEPARATION_CHAR '/'
#define END_CHAR '%'
#define FAILURE_START_REQUEST 'B'
#define FAILURE_STOP_REQUEST 'S'

namespace jbox {
namespace failures {

FailureType::FailureType(FailureTypeEnum type) : type(type) {
  switch (type) {
  case CRK:
    name = "CRK";
    break;
  case CAM:
    name = "CAM";
    break;
  case OTHER:
    name = "OTHER";
    break;
  }
}

ParamData::ParamData(int i) {
  data.i = i;
  type = INT;
}

ParamData::ParamData(float f) {
  data.f = f;
  type = FLOAT;
}

ParamData::ParamData(char c) {
  data.c = c;
  type = CHAR;
}

/**
 *  The start and stop messages could be generated
 *  at instantiation in a const std::string, but as
 *  we are going to create a new Failure object every
 *  time, it wouldn't change much from this.
 */

std::string Failure::toStartMessage() {
  std::stringstream ss;
  // The start message has the following format
  // START_CHAR MESSAGE_IDENTIFIER SEPARATION_CHAR FAILURE_START_REQUEST
  // <failure-data> END_CHAR
  ss << START_CHAR << identifier << SEPARATION_CHAR << FAILURE_START_REQUEST
     << paramsToString() << END_CHAR;
  return ss.str();
}

std::string Failure::paramsToString() {
  std::stringstream ss;
  // It should have the following format
  // SEPARATION_CHAR <data separated by SEPARATION_CHAR>
  //
  // Data should be converted to ascii
  std::vector<FailureParam>::const_iterator it = params.cbegin();
  while (it != params.cend()) {
    ss << SEPARATION_CHAR << *it;
    it += 1;
  }
  return ss.str();
}

std::string Failure::toStopMessage() {
  std::stringstream ss;
  // The stop message has the following format
  // FAILURE_STOP_REQUEST END_CHAR
  ss << START_CHAR << identifier << SEPARATION_CHAR << FAILURE_STOP_REQUEST
     << END_CHAR;
  return ss.str();
}

Failure Failure::create_instance(std::vector<ParamData> p) const {
  Failure failure(identifier, type.type, name, params);
  if (p.size() != params.size()) {
    fprintf(stderr,
            "jbox::failures:: Error parameter list size doesn't match %s's "
            "parameters\n",
            name.c_str());
    throw std::runtime_error("jbox::failures:: parameter list size error");
  }

  for (int i = 0; i < p.size(); i++) {
    if (p[i].type != failure.params[i].value.type) {
      fprintf(stderr,
              "jbox::failures:: Error parameter list types doesn't match %s's "
              "parameters\n",
              name.c_str());
      throw std::runtime_error(
          "jbox::failures:: Error parameter list types error");
    }

    failure.params[i].value = p[i];
  }

  return failure;
}

} // namespace failures
} // namespace jbox
