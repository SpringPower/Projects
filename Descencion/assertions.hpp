#ifndef ASSERTIONS_HPP
#define ASSERTIONS_HPP

#include <exception>
#include <string>
#include <sstream>

class AssertionError
{
public:
    AssertionError(unsigned long line, const char *pszFilename, const char *pszDescription = NULL)
    {
        ssError << pszFilename << "(" << line << "): Assertion Error: ";
        if (NULL != pszDescription)
        {
            ssError << pszDescription;
        }
    }
    virtual ~AssertionError(){}

    std::stringstream ssError;
};

#define EXPECT(tValue0, tValue1)                                        \
{                                                                       \
    if ((tValue0) != (tValue1))                                         \
    {                                                                   \
        AssertionError *ptErr = new AssertionError(__LINE__, __FILE__); \
        ptErr->ssError << "Expected " << tValue0 << " Got " << tValue1; \
    }                                                                   \
}

#define EXPECT_TRUE(bCond)                                      \
{                                                               \
    if (!(bCond))                                               \
    {                                                           \
        throw new AssertionError(__LINE__, __FILE__, #bCond);   \
    }                                                           \
}

#define EXPECT_NOT(tValue0, tValue1)                                    \
{                                                                       \
    if ((tValue0) == (tValue1))                                         \
    {                                                                   \
        AssertionError *ptErr = new AssertionError(__LINE__, __FILE__); \
        ptErr->ssError << "Expected " << tValue0 << " != " << tValue1;  \
    }                                                                   \
}

#define EXPECT_NOT_NULL(pvPtr)                                          \
{                                                                       \
    if ((NULL) == (pvPtr))                                              \
    {                                                                   \
        AssertionError *ptErr = new AssertionError(__LINE__, __FILE__); \
        ptErr->ssError << "Expected NULL " << " != " << pvPtr;          \
    }                                                                   \
}

#define EXPECT_MESSAGE(szMessage)                                   \
{                                                                   \
    AssertionError *ptErr = new AssertionError(__LINE__, __FILE__); \
    ptErr->ssError << szMessage;                                    \
}

#ifdef DEBUG
#define ASSERT(bCond) EXPECT_TRUE(bCond)
#define ASSERT_MESSAGE(szMessage) EXPECT_MESSAGE(szMessage)
#else
#define ASSERT(bCond)
#define ASSERT_MESSAGE(szMessage)
#endif

#endif // ASSERTIONS_HPP