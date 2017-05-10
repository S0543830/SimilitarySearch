#include "stdafx.h"

int Datenbank::connect2Server(std::string ip,std::string databasename,std::string userId, std::string password)
{
	SqlConnection ^cnc = gcnew SqlClient::SqlConnection("Data Source=" + gcnew String(ip.c_str()) + ";Initial Catalog=" + gcnew String(databasename.c_str()) + ";Integrated Security=SSPI;User ID=" + gcnew String(userId.c_str()) + ";Password=" + gcnew String(password.c_str()));
	DataSet ^set = gcnew DataSet("myData");
	DataAdapter ^adp = gcnew SqlDataAdapter("SELECT * FROM Personal", cnc);
	adp->Fill(set);
	return 0;
}

int Datenbank::add()
{
	return 0;
}

int Datenbank::remove()
{
	return 0;
}