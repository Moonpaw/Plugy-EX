/*==============================================
	File created by Yohann NICOLAS.

    @file error.hpp
    @brief Error logger definition.

    This file defiens various functions related to
    error handling in D2External functions.

==============================================*/
#pragma once

#include <Windows.h>
namespace PlugY {
    extern int active_logFile;

    void log_initfile();

    void log_close();

    void log_box(const char *pFormat, ...);

    void log_msg(const char *pFormat, ...);

    void d2_assert(bool pCondition, const char *pLocation, const char *pMessage, int pLineNbr);

}