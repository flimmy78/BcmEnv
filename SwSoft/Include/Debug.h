#ifndef _Debug_h_
#define _Debug_h_

std::ostream& DgbClearStream(char const*, uint32_t);
std::ostream& DgbOStream(char const*, uint32_t);
std::ostream& ErrOStream(char const*, uint32_t);

#define dbgcstrm DgbClearStream(__func__, __LINE__)
#define dbgstrm DgbOStream(__func__, __LINE__)
#define errstrm ErrOStream(__func__, __LINE__)

#define DbgExpandVar(v, type) #v << " = " << (type)v

class DebugFlag
{
public:
    DebugFlag();

    bool GetState(std::string const& funcName);
    void SetState(std::string const& funcName, bool isDebug);

private:
    static std::map<std::string, bool> flags;
};

#ifdef WIN32
#   define __func__ __FUNCTION__
#endif

#define Printf(...) \
{   const char* func = __func__; int line = __LINE__; \
    DebugFlag flag;                     \
    if (flag.GetState(func))            \
    {                                   \
        printf("%s, %d> ", func, line); \
        printf(__VA_ARGS__);            \
    }                                   \
}

#endif /* _Debug_h_ */
