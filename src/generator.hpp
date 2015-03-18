#ifndef GENERATOR_HPP
#define GENERATOR_HPP

class Map;

class Generator
{
public:
	virtual ~Generator() {}

	virtual void generate(Map *output) = 0;
	virtual bool configure() = 0;
};

#endif // GENERATOR_HPP
