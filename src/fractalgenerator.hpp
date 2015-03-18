#ifndef FRACTALGENBUILDER_H
#define FRACTALGENBUILDER_H

#include "generator.hpp"

#include <QDialog>
#include <mm/random.h>
#include <mm/fractal.h>

namespace Ui {
class FractalGenerator;
}
class Map;

// TODO: get rid of the private inheritance
class FractalGenerator : private QDialog, public Generator
{
	Q_OBJECT

public:
	explicit FractalGenerator(QWidget *parent = 0);
	~FractalGenerator();

	virtual void generate(Map *output);
	virtual bool configure();

private slots:
	void on_buttonBox_accepted();
	void on_noiseTypeComboBox_currentIndexChanged(int index);

private:
	typedef std::function<double(double, double)> NoiseFunction;
	typedef std::function<double(double)> CurveFunction;

	NoiseFunction getValueNoise();
	NoiseFunction getGradientNoise();
	NoiseFunction getSimplexNoise();

	CurveFunction getCurve();

	Ui::FractalGenerator *ui;
	mm::random_engine engine_;
	mm::fractal fractal_;
	size_t width_;
	size_t height_;
};

#endif // FRACTALGENBUILDER_H
