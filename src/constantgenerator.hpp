#ifndef CONSTANTGENERATOR_HPP
#define CONSTANTGENERATOR_HPP

#include "generator.hpp"
#include <cstddef>

class Map;

class ConstantGenerator : public Generator
{
public:
	explicit ConstantGenerator();

	virtual void generate(Map *output);
	virtual bool configure();

private:
	size_t width_;
	size_t height_;
	double value_;
};

#endif // CONSTANTGENERATOR_HPP
