#pragma once
#include <math.h>

//	円周率
#define PI 3.14159265

//	度数法からラジアンへの変換
#define DEG_TO_RAD(degree) ((degree) * (PI / 180))

//　ラジアンから度数法への変換
#define RAD_TO_DEG(rad) ((rad) * (180 / PI))