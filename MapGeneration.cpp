#include "MapGeneration.h"
#include <vector>
#include <math.h>

inline double MapGeneration::fade(double t) {
	return t*t*t*(t*(t*6 - 15) + 10);
}

inline double MapGeneration::lerp(double t, double a, double b) {
	return a + t*(b - a);
}

inline double MapGeneration::grad(int hash, double x, double y, double z) {
	int h = hash & 15;
	double u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

inline double MapGeneration::Noise2D(double x, double y) {
	return ((0x6C078965*(Seed ^ (((int) x*2971902361) ^ ((int) y*3572953751)))) & 0x7FFFFFFF)/(double) 0x7FFFFFFF;
}

double MapGeneration::Noise2D_2(double x, double y) {
	int n = (int) (x + y*57);
	n = (n << 13) ^ n;
	double value = (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff)/1073741824.0f);
	return abs(value);
}

double MapGeneration::SmoothedNoise2D(double x, double y) {
	double corners = (Noise2D(x - 1, y - 1) + Noise2D(x + 1, y - 1) + Noise2D(x - 1, y + 1) +
		Noise2D(x + 1, y + 1))/16;
	double sides = (Noise2D(x - 1, y) + Noise2D(x + 1, y) + Noise2D(x, y - 1) + Noise2D(x, y + 1))/8;
	double center = Noise2D(x, y)/4;
	return corners + sides + center;
}

////////////////////////////////////////////////////////////////////////////


double MapGeneration::Cosine_Interpolate(double a, double b, double x) {
	double ft = x*3.141596;
	double f = (1 - cos(ft))*.5;

	return a*(1 - f) + b*f;
}

double MapGeneration::CompileSmoothedNoise(double x, double y) {
	double int_X = (int) x;
	double fractional_X = x - int_X;

	double int_Y = (int) y;
	double fractional_Y = y - int_Y;

	double v1 = SmoothedNoise2D(int_X, int_Y);
	double v2 = SmoothedNoise2D(int_X + 1, int_Y);
	double v3 = SmoothedNoise2D(int_X, int_Y + 1);
	double v4 = SmoothedNoise2D(int_X + 1, int_Y + 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);


	return Cosine_Interpolate(i1, i2, fractional_Y);
}

double MapGeneration::CompileSmoothedNoiseDiamond(double x, double y) {
	double int_X = (int) x;
	double fractional_X = x - int_X;

	double int_Y = (int) y;
	double fractional_Y = y - int_Y;

	double v2 = SmoothedNoise2D(int_X + 1, int_Y);
	double v3 = SmoothedNoise2D(int_X - 1, int_Y);
	double v4 = SmoothedNoise2D(int_X, int_Y + 1);
	double v1 = SmoothedNoise2D(int_X, int_Y - 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);


	return Cosine_Interpolate(i1, i2, fractional_Y);
}

double MapGeneration::CompileNoise(double x, double y) {
	double int_X = (int) x;
	double fractional_X = x - int_X;

	double int_Y = (int) y;
	double fractional_Y = y - int_Y;

	double v1 = Noise2D(int_X, int_Y);
	double v2 = Noise2D(int_X + 1, int_Y);
	double v3 = Noise2D(int_X, int_Y + 1);
	double v4 = Noise2D(int_X + 1, int_Y + 1);

	double i1 = Cosine_Interpolate(v1, v2, fractional_X);
	double i2 = Cosine_Interpolate(v3, v4, fractional_X);


	return Cosine_Interpolate(i1, i2, fractional_Y);
}

std::vector<double> MapGeneration::NoiseMap(double x, double y, int sx, int sy, double zoom) {
	std::vector<double> a(sx*sy);
	int oct = 5;

	for (int i = 0; i < sx; i++) {
		for (int j = 0; j < sy; j++) {
			double tt = 0;
			double diver = 1;
			for (int w = 1; w <= oct; w++) {
				tt += CompileNoise((i + x*sx)*zoom/diver, (j + y*sy)*zoom/diver);
				diver *= 2;
			}
			a[i*sy + j] = tt/oct;
		}
	}
	return a;
}

std::vector<double> MapGeneration::CompiledNoiseMap(double x, double y, int sx, int sy, double zoom ) {
	std::vector<double> a(sx*sy);
	int oct = 5;

	for (int i = 0; i < sx; i++) {
		for (int j = 0; j < sy; j++) {
			double tt = 0;
			double diver = 1;
			for (int w = 1; w <= oct; w++) {
				tt += CompileSmoothedNoiseDiamond((i + x*sx)*zoom/diver, (j + y*sy)*zoom/diver);
				diver *= 2;
			}
			a[i*sy + j] = tt/oct;
		}
	}
	return a;
}


std::vector<double> MapGeneration::SmoothNoiseMap(std::vector<double> a) {
	int sx, sy = sx = (int) sqrt((float)a.size());
	for (int i = 0; i < sx - 1; i++) {
		for (int j = 0; j < sy - 1; j++) {
			double round = ((a[(i)*sy + j] + a[(i + 1)*sy + j] + a[(i + 1)*sy + j + 1] + a[(i)*sy + j + 1])/4.0);
			a[(i)*sy + j] = ((a[(i)*sy + j] + round)/2.0);
			a[(i + 1)*sy + j] = ((a[(i + 1)*sy + j] + round)/2.0);
			a[(i)*sy + j + 1] = ((a[(i)*sy + j + 1] + round)/2.0);
			a[(i + 1)*sy + j + 1] = ((a[(i + 1)*sy + j + 1] + round)/2.0);
		}
	}
	return a;
}

std::vector<double> MapGeneration::PostEffect(std::vector<double> img, int iterations, double smooth) {
	for (int i = 0; i < img.size(); i++) {
		double s = (float) img[i];
		double ds = s*iterations - ((int) (s*iterations));
		ds = smooth*(ds - 0.5f) + 0.5f;
		if (ds > 1) {
			ds = 1;
		}
		if (ds < 0) {
			ds = 0;
		}
		s = (((int) (s*iterations)) + ds)/iterations;
		img[i] = s;
	}
	return img;
}

//************************************
// Method:    FloorPerlin
// FullName:  MapGeneration::FloorPerlin
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: MapSector mapSector
//************************************
void MapGeneration::FloorPerlin(MapSector mapSector) {
	//double[] a = NoiseMap(mapSector.SectorOffsetX, mapSector.SectorOffsetY, MapSector.Rx, MapSector.Ry, 0.4);
	std::vector<double> a = PostEffect(SmoothNoiseMap(SmoothNoiseMap(NoiseMap(mapSector.SectorOffsetX, mapSector.SectorOffsetY, MapSector::Rx, MapSector::Ry, 0.05))), 5, 2.5);
	for (int i = 0; i < MapSector::Rx; i++) {
		for (int j = 0; j < MapSector::Ry; j++) {
			double t = a[i*MapSector::Ry + j];
			if (t > 0.7) {
				mapSector.SetFloor(i, j, 1);
			}
			else {
				if (t > 0.5) {
					mapSector.SetFloor(i, j, 1);
				}
				else {
					mapSector.SetFloor(i, j, 2);
				}
			}
		}
	}
}