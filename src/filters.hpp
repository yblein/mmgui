#ifndef FILTERFUNCTIONS_H
#define FILTERFUNCTIONS_H

#include <cstddef>

#include <mm/color_ramp.h>

class Map;

class Filter
{
public:
	virtual ~Filter() {}

	virtual void filter(const Map *input, Map *output) = 0;
	virtual bool configure() { return false; }
};

class IslandizeFilter : public Filter
{
public:
	IslandizeFilter();

	virtual void filter(const Map *input, Map *output);
	virtual bool configure();

private:
	double border_;
};

class FlattenFilter : public Filter
{
public:
	FlattenFilter();

	virtual void filter(const Map *input, Map *output);
	virtual bool configure();

private:
	double factor_;
};

class SmoothFilter : public Filter
{
public:
	SmoothFilter();

	virtual void filter(const Map *input, Map *output);
	virtual bool configure();

private:
	size_t iterations_;
};

class ColorizeFilter : public Filter
{
public:
	ColorizeFilter();

	virtual void filter(const Map *input, Map *output);
	virtual bool configure();

private:
	double seaLevel_;
	mm::color_ramp ramp_;
};

//! Implement shader filter with only one input for now
class ShaderFilter : public Filter
{
public:
	ShaderFilter();

	virtual void filter(const Map *input, Map *output);
	virtual bool configure();

protected:
	double seaLevel_;
	mm::color_ramp ramp_;
};


#endif // FILTERFUNCTIONS_H
