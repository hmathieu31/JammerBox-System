#include "sim.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <thread>

namespace jbox {
namespace sim {

Sim::Sim(std::string com_port, const std::string& path) {
  if (!path.empty()) {
    config = read_rules(path);
  }
  virtualcomport.connect(com_port);
  // display_default_rule();
}

Sim::~Sim() {}

std::map<char, Rule> Sim::read_rules(const std::string& path) {
  std::map<char, Rule> config;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "jbox::sim File not Found" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string rules;
  // Reading each line in the file
  while (std::getline(file, rules, '\n')) {
    std::istringstream ss = std::istringstream(rules);
    std::string current_word;
    char value;
    char key;
    int period = 0;
    // Parsing each line
    while (std::getline(ss, current_word, ' ')) {
      if (current_word == "when") {
        std::getline(ss, current_word, ' ');
        key = current_word.at(1);
      } else if (current_word == "send") {
        std::getline(ss, current_word, ' ');
        value = current_word.at(1);
        Rule rule = Rule(value, 0);
        config.insert(std::pair<char, Rule>(key, rule));
      } else if (current_word == "period") {
        std::getline(ss, current_word, ' ');
        period = std::stoi(current_word);
        config.at(key).period_in_ms = period;
      } else if (current_word == "default") {
        std::getline(ss, current_word, ' ');
        default_char = current_word.at(1);
      }
    }
  }

  // display_map can be used to check the result
  // display_map(config);
  return config;
}

void Sim::start() {
  std::map<char, std::promise<void>> pool;
  virtualcomport.start_receive_thread([&](std::string message) {
    char identifier = message.at(1);
    auto it = config.find(identifier);
    if (it != config.end()) {
      const int period_in_ms = it->second.period_in_ms;
      const std::string char_to_send(1, it->second.char_to_send);
      if (period_in_ms != 0) {
        if (message.at(3) == 'B') {
          // create a promise object and a future object associated to it
          std::promise<void> stop_send;
          std::future<void> future_stop = stop_send.get_future();
          // Create a thread which send a message periodically
          std::thread th(&threadSendPeriodic, this, std::move(it->second),
                         std::move(future_stop));
          th.detach();
          pool.insert(std::pair<char, std::promise<void>>(
              char_to_send.at(0), std::move(stop_send)));
        } else {
          // Set the value in promise, stop the while loop in the thread
          auto it_pool = pool.find(char_to_send.at(1));
          it_pool->second.set_value();
        }
      } else {
        std::stringstream ss;
        ss << char_to_send;
        virtualcomport.send(ss.str());
      }
    } else {
      // Using the default
      std::stringstream ss;
      ss << '!' << default_char << '%';
      virtualcomport.send(ss.str());
    }
  });
}

void Sim::threadSendPeriodic(Rule rule, std::future<void> future_stop) {
  // The thread will stop when the value is set in stop_send
  while (future_stop.wait_for(std::chrono::milliseconds(1)) ==
         std::future_status::timeout) {
    std::stringstream ss;
    ss << rule.char_to_send;
    virtualcomport.send(ss.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(rule.period_in_ms));
  }
}

void Sim::display_map(std::map<char, Rule> config) {
  auto it = config.cbegin();
  while (it != config.cend()) {
    printf("when %c send %c period %d\n", it->first, it->second.char_to_send,
           it->second.period_in_ms);
    it++;
  }
}

void Sim::display_default_rule() {
  printf("default %c\n", default_char);
}

}  // namespace sim
}  // namespace jbox

int main(int argc, char* argv[]) {
  int opt;
  std::string path = "";
  std::string port = "";
  int p_found = 0;

  while ((opt = getopt(argc, argv, "c:p:")) != -1) {
    switch (opt) {
      case 'c':
        path = std::string(optarg);
        break;
      case 'p':
        port = std::string(optarg);
        p_found = 1;
        break;
      default: /*?*/
        fprintf(stderr,
                "Usage: %s\n  "
                "Options : \n [-c]    arg : The file of configuration\n -p    "
                "arg : The port for connection\n",
                argv[0]);

        exit(EXIT_FAILURE);
    }
  }

  if (p_found == 0) {
    fprintf(stderr, "Option -p is required in all cases !\n");
    exit(EXIT_FAILURE);
  }

  jbox::sim::Sim Sim(port, path);
  Sim.start();

  while (1) {
  }

  return 0;
}
