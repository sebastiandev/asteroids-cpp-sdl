#ifndef _FILEVALIDATOR_H_
#define _FILEVALIDATOR_H_

#include "AttributeValidator.h"
#include "Utils.h"

using namespace util;

namespace persistence
{
class FileValidator : public AttributeValidator
{
public:
	FileValidator(string);
	FileValidator(string, string);
	virtual ~FileValidator(void);
	virtual void validate(Attribute*);
private:
	bool isFileExists(string);
};
};

#endif
