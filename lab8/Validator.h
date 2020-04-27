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