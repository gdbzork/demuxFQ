#include <string.h>
#include <ctype.h>
#include <time.h>
#include <iostream>

void log(std::ostream &destination,std::string const &method,int line,std::string const &message) {
  char stamp[1024];
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(stamp,1024,"[%Y-%m-%d %H:%M:%S] ",timeinfo);
  destination << stamp << method << ": Line " << line << ": " << message << std::endl;
}

void log(std::ostream &destination,std::string const &method,std::string const &message) {
  char stamp[1024];
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(stamp,1024,"[%Y-%m-%d %H:%M:%S] ",timeinfo);
  destination << stamp << method << ": " << message << std::endl;
}

char *trimWhiteFromTail(char *buffer) {
  int end;

  end = strlen(buffer) -1;
  while (end >= 0 && isspace(buffer[end])) {
    end--;
  }
  buffer[end+1] = '\0';
  return buffer;
}
