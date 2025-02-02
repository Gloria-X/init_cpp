#pragma once
#include <string>
#include <libssh2.h>

void showSCPUsage();
int ssh_connect(const std::string &remoteHost, int port, const std::string &username, const std::string &password, const std::string &keyFile, LIBSSH2_SESSION **session, int *sock);
void SCP(const std::string &remoteHost, const std::string &remoteFile, const std::string &localFile, const std::string &username, const std::string &password);
