#ifndef _XMLVALIDATORFACTORY_H_
#define _XMLVALIDATORFACTORY_H_

#include "ElementValidator.h"
#include "NumberValidator.h"
#include "FileValidator.h"
#include "NameValidator.h"

namespace persistence
{
class XMLValidatorFactory
{
public:
	XMLValidatorFactory(void);
	virtual ~XMLValidatorFactory(void);
	ElementValidator* createAsteroidsRootElementValidator(void);
	ElementValidator* createAsteroidTypesElementValidator(void);
	ElementValidator* createAsteroidTypeElementValidator(void);
	ElementValidator* createAsteroidsElementValidator(void);
	ElementValidator* createAsteroidElementValidator(void);
	ElementValidator* createShipElementValidator(void);
};
};

#endif
