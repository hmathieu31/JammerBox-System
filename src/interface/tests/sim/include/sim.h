#ifndef SRC_INTERFACE_TESTS_SIM_INCLUDE_SIM_H_INCLUDED_
#define SRC_INTERFACE_TESTS_SIM_INCLUDE_SIM_H_INCLUDED_

#include <future>
#include <iostream>
#include <map>
#include <string>

#include "virtualcomport.h"

#define DEFAULT_CHAR 'a'

namespace jbox {
namespace sim {

struct Rule {
  char char_to_send;
  int period_in_ms;

  Rule(char char_send, int period)
      : char_to_send(char_send), period_in_ms(period) {}
};

struct MsgThread {
  Rule rule;
  std::future<void> future_stop;

  MsgThread(Rule rule, std::future<void> future_stop)
      : rule(rule), future_stop(std::move(future_stop)) {}
};

class Sim {
 public:
  Sim(std::string com_port, const std::string& path);

  ~Sim();

  /**
   * @brief Returns an HashMap containing all the rules of the config file
   *
   * @param path string giving the path of the config file
   * @return map containing each rules
   */
  std::map<char, Rule> read_rules(const std::string& path);

  /**
   * @brief decodes a message and sends the appropriate response
   */
  void start();

 



  
private:
  std::map<char, Rule> config;

  /**
   * @brief Displays the given map
   *
   * @param config map containing all the rules
   */
  void display_map(std::map<char, Rule> config);

  /**
   * @brief Displays the default char
   */
  void display_default_rule();

  jbox::com::VirtualComPort virtualcomport;
  void threadSendPeriodic(Rule rule, std::future<void> future_stop) ;

  char default_char = DEFAULT_CHAR;
};

}  // namespace sim
}  // namespace jbox

#endif

