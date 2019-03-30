#ifndef INDICES_ARGS_H
#define INDICES_ARGS_H

/* Process command line:
 *  -v -- version
 *  -fAAA -- index format
 *  -dX -- index delimiter (from head of read name)
 */
class IndexArgs {

  public:
    IndexArgs(void);
    bool process(int argc,char **argv);

    char *format(void) { return formatStr; };
    bool shouldExit(void) { return version || help; };
    char delim(void) { return delimiter; };

  private:
    static const char *opts;
    static const char *defaultFmt;

    bool version = false;
    bool help = false;
    char delimiter = ':';
    char *formatStr = NULL;

    void doHelp(void);
    void doVersion(void);
};

#endif
