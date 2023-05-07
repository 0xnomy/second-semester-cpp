#include <iostream>

class CMyString
{
private:
    char *dynarr;
    int m_nLength;
    int m_nAllocated;

public:
    // Default constructor
    CMyString()
    {
        dynarr = new char[50]; // points to the first char in the array
        dynarr[0] = '\0';      //  denotes the end for the string[50]
        m_nLength = 0;
        m_nAllocated = 50;
    }

    // Constructor with character array argument
    CMyString(const char *pszData)
    {
        int nLength = 0;
        while (pszData[nLength] != '\0')
        {
            nLength++;
        }

        dynarr = new char[nLength + 1];
        for (int i = 0; i < nLength; i++)
        {
            dynarr[i] = pszData[i];
        }
        dynarr[nLength] = '\0';
        m_nLength = nLength;
        m_nAllocated = nLength;
    }

    // Constructor with size argument
    CMyString(int nSize)
    {
        dynarr = new char[nSize + 1];
        dynarr[0] = '\0';
        m_nLength = 0;
        m_nAllocated = nSize;
    }

    // Copy constructor
    CMyString(const CMyString &other)
    {
        dynarr = new char[other.m_nLength + 1];
        for (int i = 0; i < other.m_nLength; i++)
        {
            dynarr[i] = other.dynarr[i];
        }
        dynarr[other.m_nLength] = '\0';
        m_nLength = other.m_nLength;
        m_nAllocated = other.m_nLength;
    }

    // Destructor
    ~CMyString()
    {
        delete[] dynarr;
    }

    // Function to get the length of the string
    int GetLength() const
    {
        return m_nLength;
    }

    // Function to get the size of the character array
    int GetAllocatedSize() const
    {
        return m_nAllocated;
    }

    // Function to concatenate two strings using '+'
    CMyString operator+(const CMyString &other) const
    {
        int nNewLength = m_nLength + other.m_nLength;
        CMyString newString(nNewLength);
        for (int i = 0; i < m_nLength; i++)
        {
            newString.dynarr[i] = dynarr[i];
        }
    }
};