#include "fractalgenerator.hpp"

#include "map.hpp"
#include "ui_fractalgenerator.h"

#include <mm/curve.h>
#include <mm/gradient_noise.h>
#include <mm/value_noise.h>
#include <mm/simplex_noise.h>
#include <mm/normalize.h>

FractalGenerator::FractalGenerator(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FractalGenerator),
	engine_(),
	fractal_(mm::gradient_noise(engine_, mm::curve_cubic<double>), 1),
	width_(256), height_(256)
{
	ui->setupUi(this);
	ui->seedSpinBox->setValue(mm::random_engine::default_seed);
	ui->seedSpinBox->setMaximum(1.84467441e19);

	setWindowTitle(tr("Fractal generator settings"));
}

FractalGenerator::~FractalGenerator()
{
	delete ui;
}

void FractalGenerator::generate(Map *output)
{
	auto outputHeightmap = dynamic_cast<HeightMap*>(output);
	Q_ASSERT(outputHeightmap != nullptr);

	outputHeightmap->data = mm::normalize()(fractal_(engine_, width_, height_));
}

bool FractalGenerator::configure()
{
	return exec();
}

void FractalGenerator::on_buttonBox_accepted()
{
	// image size
	width_ = ui->widthSpinBox->value();
	height_ = ui->heightSpinBox->value();

	// random engine
	engine_.seed(ui->seedSpinBox->value());

	// fractal settings
	double scale = ui->scaleDoubleSpinBox->value();
	int octaves = ui->octavesSpinBox->value();
	double lacunarity = ui->lacunarityDoubleSpinBox->value();
	double persistence = ui->persistenceDoubleSpinBox->value();

	// noise type
	typedef NoiseFunction (FractalGenerator::*MemFuncPtr)();
	MemFuncPtr noises[] = {
		&FractalGenerator::getValueNoise,
		&FractalGenerator::getGradientNoise,
		&FractalGenerator::getSimplexNoise
	};
	auto noise = (this->*(noises[ui->noiseTypeComboBox->currentIndex()]))();

	fractal_ = mm::fractal(noise, scale, octaves, lacunarity, persistence);
}

FractalGenerator::NoiseFunction FractalGenerator::getValueNoise()
{
	auto curve = getCurve();
	return std::move(mm::value_noise(engine_, curve));
}

FractalGenerator::NoiseFunction FractalGenerator::getGradientNoise()
{
	auto curve = getCurve();
	return std::move(mm::gradient_noise(engine_, curve));
}

FractalGenerator::NoiseFunction FractalGenerator::getSimplexNoise()
{
	return std::move(mm::simplex_noise(engine_));
}

FractalGenerator::CurveFunction FractalGenerator::getCurve()
{
	CurveFunction curves[] = {
		mm::curve_linear<double>,
		mm::curve_cubic<double>,
		mm::curve_quintic<double>,
		mm::curve_cosine<double>,
	};
	return curves[ui->functionComboBox->currentIndex()];
}

void FractalGenerator::on_noiseTypeComboBox_currentIndexChanged(int index)
{
	ui->noiseFunctionGroupBox->setEnabled((index == 0 || index == 1));
}
