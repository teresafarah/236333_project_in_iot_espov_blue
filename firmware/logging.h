/// ********************************************************************************************************************
/// multiple include protection
/// ********************************************************************************************************************

//#pragma once

/// ********************************************************************************************************************
/// includes
/// ********************************************************************************************************************

//#include <iostream>
//#include <string>

/// ********************************************************************************************************************
/// using
/// ********************************************************************************************************************

//using namespace std;

/// ********************************************************************************************************************
/// smart MACROS
/// ********************************************************************************************************************

//#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))
//#define NAME_AT_LINE_2(Name, Line) Name##_##Line
//#define NAME_AT_LINE_1(Name, Line) NAME_AT_LINE_2(Name, Line)
//#define NAME_AT_LINE(Name) NAME_AT_LINE_1(Name, __LINE__)

//#define LOG_SCOPE
//    ::LogScope NAME_AT_LINE(log_scope)(__PRETTY_FUNCTION__, __FILENAME__, __LINE__)

/// ********************************************************************************************************************
/// class for logging flow
/// ********************************************************************************************************************

//class LogScope {
//
//  const string m_scope;
//  const string m_file;
//  int m_line;
//
//public:
//  LogScope(const string& scope, const string& file, int line = 0) : m_scope(scope), m_file(file), m_line(line){
//    std::clog << "[" << m_file << "] - starting    '" << m_scope << "' " << std::endl;
//  }
//
//  ~LogScope() {
//    std::clog << "[" << m_file << "] - finishing   '" << m_scope << "' " << std::endl;
//  }
//};