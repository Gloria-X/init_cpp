#pragma once
#include <string>
#include <libssh2.h>

void showSCPUsage();
int ssh_connect(const std::string &remoteHost, int port, const std::string &username, const std::string &password, const std::string &privateKeyFile, const std::string &publicKeyFile);
void SCP(const std::string &remoteHost, int port, const std::string &username, const std::string &password, const std::string &privateKeyFile, const std::string &publicKeyFile, const std::string &remoteFile, const std::string &localFile);
