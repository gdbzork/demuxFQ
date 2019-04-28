#ifndef LINETYPE_H
#define LINETYPE_H

#include <exception>
#include <istream>
#include <string>

enum LineType {UNIX,DOS,MAC,UNKNOWN};

class LineTypeException: public std::exception {
  public:
    LineTypeException(std::string txt):msg(txt) {};
    const char* what() const throw() { return msg.c_str(); } ;
  private:
    std::string msg;
};

class LineTypeChecker {
  public:
    static LineType sget(std::string &fn,unsigned limit=10000);
    static LineType fget(std::istream &fd,unsigned limit=10000);
    static std::string text(LineType tt);
  private:
    static LineType get(char *buffer,unsigned limit=10000);
  friend class LineTypeFriend;
};

#endif
