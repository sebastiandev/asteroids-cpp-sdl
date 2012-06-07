#include "XMLValidatorFactory.h"
#include "..\..\GameModel\model\Constants.h"

using namespace persistence;

XMLValidatorFactory::XMLValidatorFactory(void)
{
}

XMLValidatorFactory::~XMLValidatorFactory(void)
{
}

ElementValidator* XMLValidatorFactory::createAsteroidsRootElementValidator(void)
{
	ElementValidator* elementValidator = new ElementValidator("asteroids");
	elementValidator->addAttributeValidator(new NumberValidator("ancho", "640"));
	elementValidator->addAttributeValidator(new NumberValidator("alto", "480"));
	elementValidator->addAttributeValidator(new FileValidator("imagen", DEFAULT_BACKGROUND));
	return elementValidator;
}

ElementValidator* XMLValidatorFactory::createAsteroidTypesElementValidator(void)
{
	return new ElementValidator("tiposAsteroide");
}

ElementValidator* XMLValidatorFactory::createAsteroidTypeElementValidator(void)
{
	ElementValidator* elementValidator = new ElementValidator("tipoAsteroide");
	elementValidator->addAttributeValidator(new NameValidator("nombre", "asteriode1"));
	elementValidator->addAttributeValidator(new FileValidator("imagen", DEFAULT_ASTEROID));
	elementValidator->addAttributeValidator(new NumberValidator("ancho", "40"));
	elementValidator->addAttributeValidator(new NumberValidator("alto", "40"));
	elementValidator->addAttributeValidator(new NumberValidator("rotacion", "45"));
	return elementValidator;
}

ElementValidator* XMLValidatorFactory::createAsteroidsElementValidator(void)
{
	return new ElementValidator("asteroides");
}

ElementValidator* XMLValidatorFactory::createAsteroidElementValidator(void)
{
	ElementValidator* elementValidator = new ElementValidator("asteroide");
	elementValidator->addAttributeValidator(new NameValidator("tipo", "asteriode1"));
	elementValidator->addAttributeValidator(new NumberValidator("x", "20"));
	elementValidator->addAttributeValidator(new NumberValidator("y", "20"));
	elementValidator->addAttributeValidator(new NumberValidator("direccion", "20"));
	elementValidator->addAttributeValidator(new NumberValidator("velocidad", "50"));
	return elementValidator;
}

ElementValidator* XMLValidatorFactory::createShipElementValidator(void)
{
	ElementValidator* elementValidator = new ElementValidator("nave");
	elementValidator->addAttributeValidator(new FileValidator("imagen", DEFAULT_SHIP));
	elementValidator->addAttributeValidator(new NumberValidator("velRotacion", "3"));
	elementValidator->addAttributeValidator(new NumberValidator("velMaxima", "300"));
	elementValidator->addAttributeValidator(new NumberValidator("propulsion", "100"));
	elementValidator->addAttributeValidator(new NumberValidator("friccion", "50"));
	elementValidator->addAttributeValidator(new NumberValidator("duracionBala", "3"));
	return elementValidator;
}
