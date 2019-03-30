#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <map>

void log(std::ostream &destination,std::string const &method,int line,std::string const &message);
void log(std::ostream &destination,std::string const &method,std::string const &message);
char *trimWhiteFromTail(char *buffer);

#endif
