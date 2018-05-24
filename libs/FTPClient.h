#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include "Socket.h"
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

#define FTP_OPEN_PORT 21

enum FTPResponseCode {
  LOGGED_ON = 230,
  SUCCESSFULLY_TRANSFERRED = 226,
  OPENING_DATA_CHANNEL = 150,
};

enum Mode {
  ACTIVE,
  PASSIVE,
};

enum FTPCommand {
  LS,
  PUT,
  MPUT,
  GET,
  MGET,
  CD,
  LCD,
  DELE,
  MDELE,
  MKDIR,
  RMDIR,
  PWD,
  EXIT,
  PASV,
  INVALID_COMMAND,
};

class FTPClient: public ConnectSocket {
  unsigned short send(const std::string& command, const std::string& argument = "", bool printResponse = true);
  unsigned short getResponseCode(const std::string& responseMessage);
  FTPCommand getFTPCommand(const std::string& str);
  void createDataChannel(const std::string& command, const std::string& param, std::function<void (std::shared_ptr<DataSocket>)> callback);
  std::unique_ptr<HostSocket> openPort();
  std::unique_ptr<ConnectSocket> initPassive();
  Mode _mode;

  public:
    void static printHelp();
    FTPClient(const std::string& host, int port = FTP_OPEN_PORT);
    void sendUsername(const std::string& username);
    bool sendPassword(const std::string& password);
    bool sendCommand(const std::string& command);
    void expandGlob(const std::string& file, std::vector<std::string>& files);
};

#endif

