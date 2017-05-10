#ifndef __DATENBANK_H__
#define __DATENBANK_H__
#include "stdafx.h"

class Datenbank
{
public:
	int connect2Server(std::string ip,std::string databasename,  std::string userId, std::string password);
	int add();
	int remove();
private:
	
};

#endif __DATENBANK_H__