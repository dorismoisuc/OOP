#include "Validator.h"

using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{

}

std::string ValidationException::getMessage() const
{
	return this->message;
}

void ChoreValidator::validate(const Chore& c)
{
	string errors;
	FileRepo repo;
	Service service{ repo };

	vector<Chore> chores = repo.getChores();

	if (c.getTitle().size() < 1)
		errors += string("The title name cannot be less than 1 character!\n");
	if (c.getVision().size() < 1)
		errors += string("The vision cannot be less than 1 character!\n");
	if (c.getLastPerformed().size() < 1)
		errors += string("The <lastPerformed> cannot be less than 1 character\n");
	if (c.getType().size() <= 0)
		errors += string("The <type> cannot be empty\n");
	if (c.getTimesPerformed() < 0)
		errors += string("The <timesPerformed> cannot be negative\n");
	if (errors.size())
		throw ValidationException(errors);
}

void ChoreValidator::validateTitleForDelete(std::string& title)
{
	string errors;
	FileRepo repo;
	Service service{ repo };
	if (service.checkExisting(title) == 0)
		errors += string("The <title> is inexistent\n");
	if (errors.size())
		throw ValidationException(errors);
}