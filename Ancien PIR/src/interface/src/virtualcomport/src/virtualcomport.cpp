#include "virtualcomport.h"

#include <iostream>
#include <sstream>

namespace jbox {
namespace com {

void VirtualComPort::start_receive_thread(
    std::function<void(std::string)> callback) {
  isReceiving = true;
  std::thread([&] {
    while (isReceiving) {
      std::string data = receive();
      if (!data.empty()) {
        callback(data);
      }
    }
  }).detach();
}

void VirtualComPort::stop_receive_thread() {
  isReceiving = false;
}

void VirtualComPort::set_cam(int cam_id) {
  std::string data = "!5/" + std::to_string(cam_id) + "%" ;
 send(data);
} 

/********************************************/
/* Define platform specific implementations */
/********************************************/

#ifdef _WIN64

#define BAUDRATE CBR_9600
#define BYTE_SIZE 8
#define STOP_BITS ONESTOPBIT
#define PARITY EVENPARITY

#define READ_INTERVAL_TIMEOUT MAXDWORD
#define READ_TOTAL_TIMEOUT_CONSTANT 0
#define READ_TOTAL_TIMEOUT_MULTIPLIER 0
#define WRITE_TOTAL_TIMEOUT_CONSTANT 50
#define WRITE_TOTAL_TIMEOUT_MULTIPLIER 10

VirtualComPort::VirtualComPort() {}

void VirtualComPort::connect(std::string port) {
  BOOL status;

  // Open the COM port
  std::string com_port_file;
  std::stringstream ss;
  ss << "\\\\.\\" << port << "\0";
  ss >> com_port_file;
  hComm = CreateFileA(com_port_file.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
                      NULL, OPEN_EXISTING, 0, NULL);

  // Recover the COM port parameters
  DCB dcbConfiguration;
  status = GetCommState(hComm, &dcbConfiguration);
  if (status == FALSE) {
    std::cerr << "jbox::com:: Could not get the current COM parameters"
              << std::endl;
    CloseHandle(hComm);
    throw configuration_error();
  }

  // Define specific COM port parameters
  dcbConfiguration.BaudRate = BAUDRATE;
  dcbConfiguration.ByteSize = BYTE_SIZE;
  dcbConfiguration.StopBits = STOP_BITS;
  dcbConfiguration.Parity = PARITY;

  // Set specific COM port parameters
  status = SetCommState(hComm, &dcbConfiguration);
  if (status == FALSE) {
    std::cerr << "jbox::com:: Could not set the COM parameters" << std::endl;
    CloseHandle(hComm);
    throw configuration_error();
  }

  // Define COM timeouts
  COMMTIMEOUTS commTimeouts;
  commTimeouts.ReadIntervalTimeout = READ_INTERVAL_TIMEOUT;
  commTimeouts.ReadTotalTimeoutConstant = READ_TOTAL_TIMEOUT_CONSTANT;
  commTimeouts.ReadTotalTimeoutMultiplier = READ_TOTAL_TIMEOUT_MULTIPLIER;
  commTimeouts.WriteTotalTimeoutConstant = WRITE_TOTAL_TIMEOUT_CONSTANT;
  commTimeouts.WriteTotalTimeoutMultiplier = WRITE_TOTAL_TIMEOUT_MULTIPLIER;

  // Set COM timeouts
  status = SetCommTimeouts(hComm, &commTimeouts);
  if (status == FALSE) {
    std::cerr << "jbox::com:: Could not set the COM timeouts" << std::endl;
    CloseHandle(hComm);
    throw configuration_error();
  }

  selected_port = port;
}

void VirtualComPort::send(const std::string& data) {
  if (selected_port.empty()) {
    std::cerr << "jbox::com:: Couldn't send because no COM port connected"
              << std::endl;
    throw not_connected_error();
  }

  DWORD bytes_written;
  WriteFile(hComm, static_cast<LPCVOID>(data.c_str()), data.size(),
            &bytes_written, NULL);
  if (bytes_written != data.size()) {
    std::cerr << "jbox::com:: Sent " << bytes_written
              << "bytes when should have sent " << data.size() << std::endl;
    throw send_failed_error();
  }
}

std::string VirtualComPort::receive() {
  if (selected_port.empty()) {
    std::cerr << "jbox::com:: Couldn't send because no COM port connected"
              << std::endl;
    throw not_connected_error();
  }

  char data[MAX_READ_SIZE];
  DWORD bytes_read = 0;
  ReadFile(hComm, data, MAX_READ_SIZE, &bytes_read, NULL);

  if (bytes_read == 0) {
    return "";
  } else {
    return std::string(data);
  }
}

VirtualComPort::~VirtualComPort() {
  CloseHandle(hComm);
}

#elif defined(__unix__)

#define EVEN_PARITY 1
#define TWO_STOP_BITS 0
#define BYTE_SIZE CS8
#define BAUD_RATE B9600

// Timeouts to be defined on linux
#define _VMIN 0
#define _VTIME 1

VirtualComPort::VirtualComPort() {

}

VirtualComPort::~VirtualComPort() {

}

void VirtualComPort::connect(std::string port) {
  serial_port = open(port.c_str(), O_RDWR);
  if(serial_port < 0) {
    std::cerr << "jbox::com:: Could not open the virtual com port" << std::endl;
    printf("Error %i from open: %s\n", errno, strerror(errno));
    throw configuration_error();
  }

  // Ce struct permet de configurer le com port
  struct termios tty;
  // On récupère la configuration actuelle
  if(tcgetattr(serial_port, &tty) != 0) {
    std::cerr << "jbox::com:: Could not get the current configuration" << std::endl;
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    throw configuration_error();
  }

  // Active le checking de parité
  tty.c_cflag |= PARENB;
  if(!EVEN_PARITY) {
    tty.c_cflag |= PARODD;
  }

  if(TWO_STOP_BITS) {
  // Active deux bits de stop au lieu de un
    tty.c_cflag |= CSTOPB;
  }

  // Set the byte size
  tty.c_cflag &= -CSIZE;
  tty.c_cflag |= BYTE_SIZE;

  // Enable read and ignore ctrl lines
  tty.c_cflag |= CREAD | CLOCAL;

  // Disable unwanted features
  tty.c_cflag &= -CRTSCTS;
  tty.c_lflag &= -ICANON;
  tty.c_lflag &= -ECHO;
  tty.c_lflag &= -ECHOE;
  tty.c_lflag &= -ECHONL;
  tty.c_lflag &= -ISIG;
  tty.c_iflag &= -(IXON | IXOFF | IXANY);
  tty.c_iflag &= -(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
  tty.c_oflag &= -OPOST;
  tty.c_oflag &= -ONLCR;

  // Set timeouts
  tty.c_cc[VTIME] = _VTIME;
  tty.c_cc[VMIN] = _VMIN;

  // Set the baudrate
  cfsetispeed(&tty, BAUD_RATE);
  cfsetospeed(&tty, BAUD_RATE);

  // set serial settings
  if(tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    std::cerr << "jbox::com:: Could not apply custom configuration" << std::endl;
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    throw configuration_error();
  }

  selected_port = port;
}

void VirtualComPort::send(const std::string& data) {
  if (selected_port.empty()) {
    std::cerr << "jbox::com:: Couldn't send because no COM port connected"
              << std::endl;
    throw not_connected_error();
  }

  int bytes_written = write(serial_port, data.c_str(), data.size());
  if(bytes_written != data.size()) {
    std::cerr << "jbox::com:: Couldn't send the right number of bytes" << std::endl;
    throw send_failed_error();
  }
}

std::string VirtualComPort::receive() {
  if (selected_port.empty()) {
    std::cerr << "jbox::com:: Couldn't receive because no COM port connected"
              << std::endl;
    throw not_connected_error();
  }

  char data[MAX_READ_SIZE];
  int bytes_read = read(serial_port, &data, MAX_READ_SIZE);
  if(bytes_read != 0) {
    return std::string(data);
  } else {
    return "";
  }
}
#else
// Default implementation for any other OS
VirtualComPort::VirtualComPort() {}
VirtualComPort::~VirtualComPort() {}
void VirtualComPort::connect(std::string port) {}
void VirtualComPort::send(const std::string& data) {}
std::string VirtualComPort::receive() {
  return "";
}
#endif

}  // namespace com
}  // namespace jbox
