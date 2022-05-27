#ifndef SRC_INTERFACE_SRC_FAILURES_INCLUDE_FAILURES_H_INCLUDED_
#define SRC_INTERFACE_SRC_FAILURES_INCLUDE_FAILURES_H_INCLUDED_

/**
 * The first intent for the Failures' implementation was to have a compile-time
 * resolution of types. This was achieved through having a parent Failure class
 * and extending it for every failures. This was a great approach in terms of
 * error tracking, but didn't fit our needs. We wanted to be able to loop
 * through them programaticaly and get a list of parameters with their types,
 * while having a friendly way of defining new failures. These requirements led
 * to a runtime implementation of the failures
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace jbox {
namespace failures {

enum FailureTypeEnum {
  CRK,
  CAM,
  OTHER
};
struct FailureType {
  FailureTypeEnum type;
  std::string name;

  FailureType(FailureTypeEnum type);
};

union ParamDataType {
  int i;
  float f;
  char c;
};
enum ParamType { INT, FLOAT, CHAR };
struct ParamData {
  ParamDataType data;
  ParamType type;

  ParamData() {}
  ParamData(int i);
  ParamData(float f);
  ParamData(char c);
};

/**
 * A Failure parameter has a name and a value
 */
struct FailureParam {
  std::string name;
  ParamData value;

  /**
   * This constructor is used to define a parameter name and type but doesn't
   * give it any value
   */
  FailureParam(ParamType type, std::string name) : name(name) {
    value.type = type;
  }

  /**
   * Overrides the stream operator to be used with std::stringstream
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const FailureParam &param) {
    switch (param.value.type) {
      case INT:
        out << param.value.data.i;
        break;
      case FLOAT:
        out << param.value.data.f;
        break;
      case CHAR:
        out << param.value.data.c;
        break;
    }
    return out;
  }
};

struct Failure {
  const char identifier;
  const std::string name;
  const FailureType type;
  std::vector<FailureParam> params;

  //Default constructor
  Failure() : identifier('\0'),name(""), type(OTHER), params() {}

  Failure(char identifier, FailureTypeEnum type, std::string name, std::vector<FailureParam> params)
      : identifier(identifier), type(type), name(name), params(params) {}

  // Default destructor
  ~Failure() = default;
  

  /**
   *  Computes the start message of a Failure
   */
  std::string toStartMessage();

  /**
   * Computes the parameter string of a Failure
   */
  std::string paramsToString();
  /**
   *  Computes the stop message of a Failure
   */
  std::string toStopMessage();

  /**
   * Creates an instance of a failure given the parameter values
   *
   * @param data parameter values
   * @return the created instance
   */
  Failure create_instance(std::vector<ParamData> data) const;
};

/**
 * Add new failures here
 */

// clang-format off
const std::vector<Failure> failures = {
  Failure('l', CRK, "POSN_ENG_STST", {
       FailureParam(INT, "crk_teeth_off")
    }
  ),
  Failure('k', CRK, "CRK_PLS_ORNG", {
      FailureParam(FLOAT, "crk_pulse_duration")
    }
  ),
  Failure('j', CRK, "SEG_ADP_ER_LIM", {
      FailureParam(FLOAT, "crk_delay")
    }
  ),
  Failure('i', CRK, "CRK_GAP_NOT_DET",
    {}
  ),
  Failure('h', CRK, "CRK_TOOTH_OFF", {
      FailureParam(INT, "number_tooth_off")
    }
  ),
  Failure('c', CAM, "CAM_DELAY", {
      FailureParam(INT, "shift")
    }
  ),
  Failure('b', CAM, "CAM_PAT_ERR", 
    {}
  ),
  Failure('9', CRK, "CRK_TOOTH_PER", {
      FailureParam(INT, "start_tooth"),
      FailureParam(INT, "number_pulses"),
      FailureParam(INT, "number_revolutions")
    }
  ),
  Failure('8', CAM, "CAM_PER", {
      FailureParam(INT, "active_edges"),
      FailureParam(INT, "number_edges")
    }
  ),
  Failure('7', CRK, "CRK_RUN_OUT", {
      FailureParam(INT, "start_position"),
      FailureParam(CHAR, "sc_type"),
      FailureParam(INT, "failure_period")
    }
  )
};
// clang-format on

}  // namespace failures
}  // namespace jbox

#endif
