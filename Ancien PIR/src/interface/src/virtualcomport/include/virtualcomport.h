#ifndef SRC_INTERFACE_SRC_VIRTUALCOMPORT_INCLUDE_VIRTUALCOMPORT_H_INCLUDED_
#define SRC_INTERFACE_SRC_VIRTUALCOMPORT_INCLUDE_VIRTUALCOMPORT_H_INCLUDED_

#define MAX_READ_SIZE 512

#include <functional>
#include <stdexcept>
#include <string>
#include <thread>

#ifdef _WIN64
#include <windows.h>
#endif

#ifdef __unix__
#include <errno.h>   // Error integer and strerror() function
#include <string.h>
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <termio.h>  // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#endif

namespace jbox {
namespace com {

class not_connected_error : public std::runtime_error {
 public:
  not_connected_error() : std::runtime_error("") {}
};
class send_failed_error : public std::runtime_error {
 public:
  send_failed_error() : std::runtime_error("") {}
};
class configuration_error : public std::runtime_error {
 public:
  configuration_error() : std::runtime_error("") {}
};

class VirtualComPort {
 public:
  VirtualComPort();
  ~VirtualComPort();

  /**
   * Connect to a COM port
   *
   * @param port the port to connect to
   * @return zero if succeeded
   */
  void connect(std::string port);

  /**
   * Send data through the connected port
   *
   * @param data the data to be sent
   * @return zero if succeeded
   */
  void send(const std::string& data);

  /**
   * Receive data from the connected port
   *
   * @return the received data as an r-value reference
   */
  std::string receive();

  /**
   * Starts the receive thread.
   * Calls the callback when receiving
   *
   * @param callback the callback
   */
  void start_receive_thread(std::function<void(std::string)> callback);

  /**
   * Stops the receive thread
   */
  void stop_receive_thread();

  /**
   * Chooses the CAM to use for the failures
   */
  void set_cam(int cam_id);

 private:
#ifdef _WIN64
  HANDLE hComm;
#endif

#ifdef __unix__
  int serial_port = -1;
#endif

  std::string selected_port = "";
  bool isReceiving = false;
};

}  // namespace com
}  // namespace jbox

#endif
