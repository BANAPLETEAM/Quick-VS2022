#include "stdafx.h"
#include "BanaLog.h"
#include <io.h>
#include <direct.h>


CBanaLog *g_bana_log = nullptr;
bool CBanaLog::is_print_nano_second = true;
bool CBanaLog::is_print_nano_second_accumulate = true;

using namespace std;


CBanaLog::~CBanaLog()
{
	if (log_file_handle_ != NULL) {
		CloseHandle(log_file_handle_);
	}
}


void CBanaLog::SetMode(int log_type, bool single_line)
{
	single_line_ = single_line;
	log_type_ = log_type;

	if (log_type & BanaLogType::TO_FILE) {
		OpenFile();
	}

	if (log_type & BanaLogType::TO_CONSOLE) {
		AllocConsole();
		if (!osf_handle_) {
			osf_handle_ = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 0);
		}
	}

	last_log_time_ = chrono::high_resolution_clock::now();
	Print("-------- START  ------(%dY)\n", COleDateTime::GetCurrentTime().GetYear());
}

void CBanaLog::SetFile(const char* path_name, bool append)
{
	int return_unused = mkdir(path_name);
	file_write_append_ = append;

    file_name_ = "";
	file_name_ += path_name;
	file_name_ += "\\" + GetCurrentDateTime("%Y_%m_%d") + ".TXT";
	if (log_type_ & BanaLogType::TO_FILE) {
		OpenFile();
	}
}

string CBanaLog::GetCurrentDateTime(char* date_format)
{
	auto current_time = std::chrono::system_clock::to_time_t(chrono::system_clock::now());
	std::ostringstream oss;
	oss << put_time(std::localtime(&current_time), date_format);
	return oss.str();
}

void CBanaLog::SetFileFullName(const char* full_name, bool append)
{
	file_write_append_ = append;
    file_name_ = "";
	file_name_ = full_name;
	if (log_type_ & BanaLogType::TO_FILE) {
		OpenFile();
	}
}

void CBanaLog::OpenFile()
{
	if (!file_write_append_) {
		//파일 뒷부분 붙여쓰기가 아니면, 기존 파일을 백업한다.
		string bakcup_file_name = file_name_ + ".bak";
		MoveFileEx(file_name_.c_str(), bakcup_file_name.c_str(), MOVEFILE_REPLACE_EXISTING);
	}

	log_file_handle_ = CreateFile(file_name_.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (log_file_handle_ == INVALID_HANDLE_VALUE) {
		log_type_ &= ~BanaLogType::TO_FILE;
		BANA_LOG("Error opening BanaLog file %s\n", file_name_);
	}

	if (file_write_append_) {
		SetFilePointer(log_file_handle_, 0, NULL, FILE_END);
	}
	else {
		SetEndOfFile(log_file_handle_);
	}
}

inline void CBanaLog::ReallyPrintLine(const char* line)
{
	HANDLE handle;
	DWORD byteswritten;

	if (log_type_ & BanaLogType::TO_DEBUG) {
		OutputDebugString(line);
	}

	if (log_type_ & BanaLogType::TO_CONSOLE) {
		if ((handle = GetStdHandle(STD_OUTPUT_HANDLE)) != NULL) {
			WriteConsole(handle, line, strlen(line), &byteswritten, NULL);
		}
	}

	if (log_type_ & BanaLogType::TO_FILE) {
		WriteFile(log_file_handle_, line, strlen(line), &byteswritten, NULL);
	}

	if (log_type_ & BanaLogType::TO_BUFFER) {
		if (mutex_lock_ == nullptr) {
			mutex_lock_ = new mutex;
		}
		unique_lock<mutex> lock(*mutex_lock_);
		log_string_vector_.push_back(line);
	}

	if (log_type_ & BanaLogType::TO_PRINT_F) {
		printf(line);
	}
}

void CBanaLog::ReallyPrint(char* function_name, const char* format, va_list arg)
{
#ifdef _MKSERVER
	if (g_server_info->bNoLogFile)	return;
#endif
	if (!this) return;

	string line_text;

	if (!is_pure_log_) {
		if (is_print_nano_second_accumulate || is_print_nano_second) {
			chrono::duration<double> elapsed_time = chrono::high_resolution_clock::now() - last_log_time_;
			line_text += to_string(elapsed_time.count());
		}
		else {
			line_text += GetCurrentDateTime("%m-%d %H:%M:%S]");
		}

		if (is_print_nano_second && !is_print_nano_second_accumulate) {
			last_log_time_ = chrono::high_resolution_clock::now();
		}

		line_text += single_line_ ? " " : "\r\n";
	}

	if (function_name[0] != NULL) {
		line_text += function_name;
		line_text += " | ";
	}

	vector<char> buf(std::vsnprintf(nullptr, 0, format, arg) + 5);
	std::vsnprintf(buf.data(), buf.size(), format, arg);

	line_text += buf.data();
	if (line_text.length() > 0 && line_text.back() == '\n') {
		line_text.pop_back();
	}
	line_text += "\r\n";

	ReallyPrintLine(line_text.c_str());

	if (share_log_) {
		share_log_->ReallyPrint(format, arg);
	}
}

int CBanaLog::FlushBuffer(char* buffer_ptr, int buffer_size)
{
	int cur_pos = 0;
	if (log_type_ & BanaLogType::TO_BUFFER) {
		unique_lock<mutex> lock(*mutex_lock_);

		while (log_string_vector_.size() > 0) {
			string& line_text = log_string_vector_.front();
			int min_buffer_size = min((buffer_size - cur_pos - 1), line_text.length());

			if (cur_pos > 0 && min_buffer_size != line_text.length()) {
				break;
			}

			memcpy(&buffer_ptr[cur_pos], line_text.c_str(), min_buffer_size);
			cur_pos += min_buffer_size;
			log_string_vector_.erase(log_string_vector_.begin());

			if (cur_pos == min_buffer_size - 1) {
				break;
			}
		}
	}

	buffer_ptr[cur_pos] = 0;
	return cur_pos;
}

void CBanaLog::SetTitle(string console_title)
{
	console_title_ = console_title;
	SetConsoleTitle(console_title_.c_str());
}
