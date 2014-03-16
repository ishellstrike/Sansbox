#ifndef MapGeneration_h__
#define MapGeneration_h__

#include "MapSector.h"
#include <vector>

class MapGeneration{
public:
	inline static double fade(double t);
	inline static double lerp(double t, double a, double b);
	inline static double grad(int hash, double x, double y, double z);
	static void FloorPerlin(MapSector mapSector);
	static std::vector<double> PostEffect(std::vector<double> img, int iterations, double smooth);
	static std::vector<double> SmoothNoiseMap(std::vector<double> a);
	static std::vector<double> CompiledNoiseMap(double x, double y, int sx, int sy, double zoom);
	static std::vector<double> NoiseMap(double x, double y, int sx, int sy, double zoom);
	static double CompileNoise(double x, double y);
	static double CompileSmoothedNoiseDiamond(double x, double y);
	static double CompileSmoothedNoise(double x, double y);
	static double Cosine_Interpolate(double a, double b, double x);
	static double SmoothedNoise2D(double x, double y);
	static double Noise2D_2(double x, double y);
	inline static double Noise2D(double x, double y);
	static const int Seed = 123456;
};
#endif // MapGeneration_h__
