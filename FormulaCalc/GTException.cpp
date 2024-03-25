// GTException.cpp

#include "GTException.h"
#include <sstream>


GTException::GTException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* GTException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* GTException::GetType() const noexcept
{
	return "GT Exception";
}

int GTException::GetLine() const noexcept
{
	return line;
}

const std::string& GTException::GetFile() const noexcept
{
	return file;
}

std::string GTException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
