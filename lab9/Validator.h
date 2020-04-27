#pragma once
#include <string>
#include "Chores.h"
#include "FileRepository.h"
#include "Service.h"
#include "UI.h"

class ValidationException
{
private:
	std::string message;
public:
	ValidationException(std::string _message);
	std::string getMessage() const;
};

class ChoreValidator
{
public:
	static void validate(const Chore& c);
	static void validateTitleForDelete(std::string& title);
};

class Exceptions
{
public:
	virtual std::string get_message() const = 0;
};

class RepoException : public Exceptions
{
	private:
		std::string message;
	public:
		RepoException(std::string _message) { this->message = _message; }
		std::string get_message() const;
};

class ServiceException : public Exceptions
{
	private:
		std::string message;
	public:
		ServiceException(std::string _message) { this->message = _message; }
		std::string get_message() const;
};

class UIException : public Exceptions
{
	private:
		std::string message;
	public:
		UIException(std::string _message) { this->message = _message; }
		std::string get_message() const;

};