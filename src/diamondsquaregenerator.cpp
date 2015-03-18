#include "diamondsquaregenerator.hpp"

#include "map.hpp"
#include "ui_diamondsquaregenerator.h"

#include <QtGlobal>
#include <mm/normalize.h>

DiamondSquareGenerator::DiamondSquareGenerator(QWidget *parent)
	: QDialog(parent),
	  ui(new Ui::DiamondSquareGenerator),
	  engine_(), diamondSquare_(50), width_(256), height_(256)
{
	ui->setupUi(this);
	ui->seedSpinBox->setValue(mm::random_engine::default_seed);
}

DiamondSquareGenerator::~DiamondSquareGenerator()
{
	delete ui;
}

void DiamondSquareGenerator::generate(Map *output)
{
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	outputHeightmap->data = mm::normalize()(diamondSquare_(engine_, width_, height_));
}

bool DiamondSquareGenerator::configure()
{
	return exec();
}

void DiamondSquareGenerator::on_buttonBox_accepted()
{
	// image size
	width_ = ui->widthSpinBox->value();
	height_ = ui->heightSpinBox->value();

	// random engine
	engine_.seed(ui->seedSpinBox->value());

	// diamond square settings
	double nw = ui->nwDoubleSpinBox->value();
	double ne = ui->neDoubleSpinBox->value();
	double se = ui->seDoubleSpinBox->value();
	double sw = ui->swDoubleSpinBox->value();

	diamondSquare_ = mm::diamond_square(nw, ne, se, sw);
}
