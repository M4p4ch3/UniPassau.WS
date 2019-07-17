
# include <iostream>

using namespace std;

class STRUtils
{
    public :

    static bool contains(string base, string pattern)
    {
        bool contains = false;

        int iBase = 0;
        int iPattern = 0;

        iBase = 0;
        contains = false;

        while (iBase < base.length() && contains == false)
        {
            iPattern = 0;
            contains = true;
            
            while (iBase + iPattern < base.length() && iPattern < pattern.length() && contains == true)
            {
                if (base[iBase + iPattern] != pattern[iPattern])
                {
                    contains = false;
                }
                
                iPattern = iPattern + 1;
            }

            iBase = iBase + 1;
        }

        if (iBase == base.length() || iPattern != pattern.length())
        {
            contains = false;
        }

        return contains;
    }

    static bool isStart(string str)
    {
        bool result = false;

        int iStr = 0;

        iStr = skipVoidChars(str);

        if (str[iStr] == '/' && str[iStr + 1] == '/' && str[str.length() - 3] == '-' && str[str.length() - 2] == '-' )
        {
            result = true;
        }

        return result;
    }

    static bool isEnd(string str)
    {
        bool result = false;

        int iStr = 0;

        iStr = skipVoidChars(str);

        if (str[iStr] == '-' && str[iStr + 1] == '-' && str[str.length() - 3] == '/' && str[str.length() - 2] == '/' )
        {
            result = true;
        }

        return result;
    }

    static int skipVoidChars(string str)
    {
        bool voidChar = false;
        
        int iStr = 0;
        int iVoidChars = 0;

        int voidCharsSize = 4;
        char voidChars[voidCharsSize] = {'\t', ' ', '0', 'x'};

        iStr = 0;
        voidChar = true;
        while (iStr < str.length() && voidChar == true)
        {
            voidChar = false;

            iVoidChars = 0;
            while (iVoidChars < voidCharsSize && voidChar == false)
            {
                if (str[iStr] == voidChars[iVoidChars])
                {
                    voidChar = true;
                    iStr = iStr + 1;
                }

                iVoidChars = iVoidChars + 1;
            }
        }

        if (iStr == str.length())
        {
            iStr = -1;
        }

        return iStr;
    }

    static bool isHexDigit(char c)
    {
        bool result = false;

        if (c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F')
        {
            result = true;
        }
        else
        {
            result = false;
        }

        return result;
    }

    static int skipUntilChar(string str, char breakChar)
    {
        int iStr = 0;

        iStr = 0;
        while (iStr < str.length() && str[iStr] != breakChar)
        {
            iStr = iStr + 1;
        }

        if (iStr == str.length())
        {
            iStr = -1;
        }
        else
        {
            iStr = iStr + 1;
        }

        return iStr;
    }

    static string getValue(string str)
    {
        int iStr = 0;
        
        string value = "";

        // Skip until ':'
        iStr = skipUntilChar(str, ':');

        // Skip ' '
        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != ' ')
        {
            value = value + str[iStr];

            iStr = iStr + 1;
        }

        return value;
    }

    static string getAddress(string str)
    {
        int iStr = 0;
        
        string address = "";

        iStr = skipVoidChars(str);

        while (iStr < str.length() && isHexDigit(str[iStr]))
        {
            address = address + str[iStr];

            iStr = iStr + 1;
        }

        return address;
    }

    static string removeExt(string str)
    {
        int iStr = 0;
        
        string newStr = "";

        while (iStr < str.length() && str[iStr] != '.')
        {
            newStr = newStr + str[iStr];

            iStr = iStr + 1;
        }

        return newStr;
    }

    static double getLat(string str)
    {
        int iStr = 0;
        
        string strLat = "";
        double lat = 0;

        while (iStr < str.length() && str[iStr] != '"')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != '"')
        {
            strLat = strLat + str[iStr];
            iStr = iStr + 1;
        }

        lat = std::stod(strLat);

        return lat;
    }

    static double getLng(string str)
    {
        int iStr = 0;
        
        string strLng = "";
        double lng = 0;

        while (iStr < str.length() && str[iStr] != '"')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != '"')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != '"')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != '"')
        {
            strLng = strLng + str[iStr];
            iStr = iStr + 1;
        }

        lng = std::stod(strLng);

        return lng;
    }

    static double getXMLVal(string str)
    {
        int iStr = 0;
        
        string strVal = "";
        double val = 0.0;

        while (iStr < str.length() && str[iStr] != '>')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != '<')
        {
            strVal = strVal + str[iStr];
            iStr = iStr + 1;
        }

        val = stod(strVal);

        return val;
    }

    static int getXMLTime(string str)
    {
        int iStr = 0;
        
        string strVal = "";
        int time = 0;

        while (iStr < str.length() && str[iStr] != 'T')
        {
            iStr = iStr + 1;
        }

        iStr = iStr + 1;

        while (iStr < str.length() && str[iStr] != ':')
        {
            strVal = strVal + str[iStr];
            iStr = iStr + 1;
        }

        time = stoi(strVal) * 60 * 60;
        iStr = iStr + 1;
        strVal = "";

        while (iStr < str.length() && str[iStr] != ':')
        {
            strVal = strVal + str[iStr];
            iStr = iStr + 1;
        }

        time = time + stoi(strVal) * 60;
        iStr = iStr + 1;
        strVal = "";

        while (iStr < str.length() && str[iStr] != 'Z')
        {
            strVal = strVal + str[iStr];
            iStr = iStr + 1;
        }

        time = time + stoi(strVal);

        return time;
    }
};