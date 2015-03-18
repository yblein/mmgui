#include "constantgenerator.hpp"

#include <mm/heightmap.h>
#include <QInputDialog>
#include <QtGlobal>

#include "src/map.hpp"

ConstantGenerator::ConstantGenerator()
	: width_(256), height_(256), value_(0.5)
{
}


void ConstantGenerator::generate(Map *output)
{
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	mm::heightmap map(width_, height_);
	for (size_t y = 0; y < map.height(); ++y) {
		for (size_t x = 0; x < map.width(); ++x) {
			map.at(x, y) = value_;
		}
	}

	outputHeightmap->data = map;
}

bool ConstantGenerator::configure()
{
	bool ok;
	auto newValue = QInputDialog::getDouble(nullptr, "Constant generator settings", "Constant value", value_, 0, 1, 2, &ok);
	if (ok) {
		value_ = newValue;
		return true;
	}
	return false;
}
