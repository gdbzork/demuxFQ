#ifndef __INDEXPATTERN_H__
#define __INDEXPATTERN_H__

#include <exception>
#include <stdexcept>
#include <string>

class IndexException: public std::runtime_error {
  public:
    IndexException(std::string pat): std::runtime_error("Index parse error: '"+pat+"'") {}
};

class PatternException: public std::runtime_error {
  public:
    PatternException(std::string pat): std::runtime_error("Illegal pattern: '"+pat+"'") {}
};

class IndexPattern {

  public:
    IndexPattern(std::string pat);
    bool matches(const std::string &line);
    std::string const &first(void);
    std::string const &second(void);

  protected:
    const char FIRST_INDEX_CHAR = '1';
    const char SECOND_INDEX_CHAR = '2';
    const char IGNORE_CHAR = 'X';

    std::string pattern;
    std::string index1;
    std::string index2;
    size_t firstStart = std::string::npos;
    size_t firstLength = std::string::npos;
    size_t secondStart = std::string::npos;
    size_t secondLength = std::string::npos;

    bool isValid(void);
    void setEndpoints(void);

    friend class IndexPatternFriend;
};

#endif // __INDEXPATTERN_H__
