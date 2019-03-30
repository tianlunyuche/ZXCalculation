//
//  CMyString.cpp
//  ZXCalculation
//
//  Created by xinying on 2019/3/30.
//  Copyright © 2019年 habav. All rights reserved.
//


class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);
    
    CMyString& operator=(const CMyString& str) noexcept
    {
        if (this != &str) {
            CMyString strTemp(str);
            char* pTemp = strTemp.m_pData;
            m_pData = pTemp;
        }
        return *this;
    }
    
private:
    char* m_pData;
};



