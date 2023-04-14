#pragma once

#include <chrono>
#include <sstream>
#include <iomanip>
#include <mutex>

namespace std
{
#include <cstdlib>
};

class CBanaLog
{
public:
	~CBanaLog();

	inline void Print(const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		ReallyPrint(format, ap);
		va_end(ap);
	}

	inline void PrintWithFunction(char* function_name, const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		ReallyPrint(function_name, format, ap);
		va_end(ap);
	}

	void ReallyPrint(char* function_name, const char* format, va_list ap);
	void ReallyPrint(const char* format, va_list ap);
	void SetPureLog(bool bPure) { is_pure_log_ = bPure; }
	void SetMode(int log_type, bool single_line = true);
	void SetShareLog(CBanaLog& mkLog) { share_log_ = &mkLog; }
	void SetFile(const char* path_name, bool append = true);
	void SetFileFullName(const char* full_name, bool append = true);
	void SetTitle(std::string strTitle);
	int FlushBuffer(char* pszBuffer, int nSize);

	static std::string GetCurrentDateTime(char* date_format);

	enum BanaLogType {
		TO_DEBUG = 1,
		TO_FILE = 2,
		TO_CONSOLE = 4,
		TO_BUFFER = 8,
		TO_PRINT_F = 16
	};

    static bool is_print_nano_second;
    static bool is_print_nano_second_accumulate;

private:
	void ReallyPrintLine(const char* line);
	void OpenFile();

	bool			is_pure_log_ = false;
	HANDLE			log_file_handle_ = nullptr;
	std::string			file_name_;
	bool			file_write_append_ = false;
    std::string		console_title_;
	FILE*			m_fp1 = nullptr;
	FILE*			m_fp2 = nullptr;
    mutex*		mutex_lock_ = nullptr;
    vector<std::string>	log_string_vector_;
	CBanaLog*		share_log_ = nullptr;
	bool			single_line_ = false;
	int				osf_handle_ = 0;
	int				log_type_ = 0;


    std::chrono::steady_clock::time_point last_log_time_;
};


inline void CBanaLog::ReallyPrint(const char* format, va_list ap)
{
	ReallyPrint("", format, ap);
}


extern CBanaLog* g_bana_log;

#define BANA_LOG(text, ...)				g_bana_log->PrintWithFunction(__FUNCTION__, text, __VA_ARGS__)
#define BANA_LOG_NO_FUNCTION(text, ...)	g_bana_log->Print(text, __VA_ARGS__)