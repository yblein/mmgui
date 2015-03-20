#include "filters.hpp"

#include "map.hpp"

#include <mm/islandize.h>
#include <mm/flatten.h>
#include <mm/smooth.h>
#include <mm/colorize.h>
#include <mm/shader.h>
#include <QInputDialog>
#include <QtGlobal>

IslandizeFilter::IslandizeFilter()
	: border_(0.15)
{
}

void IslandizeFilter::filter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	double border = border_ * inputHeightmap->data.width();
	outputHeightmap->data = mm::islandize(border)(inputHeightmap->data);
}

bool IslandizeFilter::configure()
{
	bool ok;
	auto newBorder = QInputDialog::getDouble(nullptr, "Islandize filter settings", "Border size (relative)", border_, 0, 0.5, 3, &ok);
	if (ok) {
		border_ = newBorder;
		return true;
	}
	return false;
}


FlattenFilter::FlattenFilter()
	: factor_(2.0)
{
}

void FlattenFilter::filter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	outputHeightmap->data = mm::flatten(factor_)(inputHeightmap->data);
}

bool FlattenFilter::configure()
{
	bool ok;
	auto newFactor = QInputDialog::getDouble(nullptr, "Flatten filter settings", "Factor", factor_, 0, 100, 2, &ok);
	if (ok) {
		factor_ = newFactor;
		return true;
	}
	return false;
}


SmoothFilter::SmoothFilter()
	: iterations_(10)
{
}

void SmoothFilter::filter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	outputHeightmap->data = mm::smooth(iterations_)(inputHeightmap->data);
}

bool SmoothFilter::configure()
{
	bool ok;
	auto newIterations = QInputDialog::getDouble(nullptr, "Flatten filter settings", "Factor", iterations_, 0, 100, 2, &ok);
	if (ok) {
		iterations_ = newIterations;
		return true;
	}
	return false;
}


ColorizeFilter::ColorizeFilter()
	: seaLevel_(0.5), ramp_(mm::color_ramp::basic())
{
}

void ColorizeFilter::filter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputColormap = dynamic_cast<ColorMap*>(output);
	Q_ASSERT(outputColormap != nullptr);

	outputColormap->data = mm::colorize(ramp_, seaLevel_)(inputHeightmap->data);
}

bool ColorizeFilter::configure()
{
	bool ok;
	auto newSeaLevel = QInputDialog::getDouble(nullptr, "Colorize filter settings", "Sea level", seaLevel_, 0, 100, 2, &ok);
	if (ok) {
		seaLevel_ = newSeaLevel;
		return true;
	}
	return false;
}

ShaderFilter::ShaderFilter()
	: seaLevel_(0.5), ramp_(mm::color_ramp::basic())
{
}

void ShaderFilter::filter(const Map *input, Map *output)
{
	auto inputHeightmap = dynamic_cast<const HeightMap*>(input);
	Q_ASSERT(inputHeightmap != nullptr);
	auto outputColormap = dynamic_cast<ColorMap*>(output);
	Q_ASSERT(outputColormap != nullptr);

	outputColormap->data = mm::colorize(ramp_, seaLevel_)(inputHeightmap->data);
	outputColormap->data = mm::shader(seaLevel_)(outputColormap->data, inputHeightmap->data);
}

bool ShaderFilter::configure()
{
	bool ok;
	auto newSeaLevel = QInputDialog::getDouble(nullptr, "Shader filter settings", "Sea level", seaLevel_, 0, 100, 2, &ok);
	if (ok) {
		seaLevel_ = newSeaLevel;
		return true;
	}
	return false;
}
