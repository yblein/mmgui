#include "filterfunctions.hpp"

#include "map.hpp"

#include <mm/islandize.h>
#include <mm/flatten.h>
#include <mm/smooth.h>
#include <mm/colorize.h>
#include <QtGlobal>

void islandizeFilter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	double border = 0.25 * inputHeightmap->data.width();
	outputHeightmap->data = mm::islandize(border)(inputHeightmap->data);
}

void flattenFilter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	double border = 2.5;
	outputHeightmap->data = mm::flatten(border)(inputHeightmap->data);
}

void smoothFilter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	double border = 2.5;
	outputHeightmap->data = mm::smooth(border)(inputHeightmap->data);
}

void colorizeFilter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputColormap = dynamic_cast<ColorMap*>(output);
	Q_ASSERT(outputColormap != nullptr);

	double sea_level = 0.5;

	outputColormap->data = mm::colorize(mm::color_ramp::basic(), sea_level)(inputHeightmap->data);
}
