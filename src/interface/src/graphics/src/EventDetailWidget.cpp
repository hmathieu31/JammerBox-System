#include "EventDetailWidget.h"

#include <QString>
#include <sstream>
#include <vector>

namespace jbox {
namespace graphics {

void EventDetailWidget::show_failure_detail(std::string timestamp,
                                            const failures::Failure* failure) {
  // Display the time of the test
  std::string timestamp_str =
      "<b>Timestamp</b> : " + timestamp + "<br>";
  QString content = QString(timestamp_str.c_str());

  // Display the name of the failure
  std::string failure_name_str = "<b>Failure</b> : " + failure->name + "<br>";
  content.append(QString(failure_name_str.c_str()));

  // Display the type of the failure
  failures::FailureType failure_type(failure->type);
  std::string failure_type_str = "<b>Type</b> : " + failure_type.name + "<br>";
  content.append(failure_type_str.c_str());

  // Display the params of the failure
  std::string params_str = "<b>Parameters</b> :<br>";
  std::vector<failures::FailureParam>::const_iterator it =
      failure->params.cbegin();
  while (it != failure->params.cend()) {
    std::stringstream ss;
    ss << *it;
    params_str += "      - Name : " + it->name + "  Value : " + ss.str() + "\n";
    it++;
  }
  content.append(params_str.c_str());

  label->setText(content);
}

void EventDetailWidget::show_result_detail(std::string timestamp,
                                           const results::Result* result) {
  // Display the time of the test
  std::string timestamp_str =
      "<b>Time</b> : " + timestamp + "<br>";
  QString content = QString(timestamp_str.c_str());

  // Display the identifier of the result
  std::string identifier_str =
      "<b>Identifier</b> : " + std::string(1, result->identifier) + "<br>";
  content.append(identifier_str.c_str());
  // Display the message of the result
  std::string message_str = "<b>Message</b> : " + result->message + "<br>";
  content.append(message_str.c_str());

  label->setText(content);
}

}  // namespace graphics
}  // namespace jbox
