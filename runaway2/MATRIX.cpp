
#include "MATRIX.h"
namespace km
{
	//	2つの行列が同じかどうかの判定
	bool areMatricesWqual(Matrix3X3 a, Matrix3X3 b){
		bool iErrorFlag = true;
		int i, j;
		for (i = 0; i < 3; ++i){
			for (j = 0; j < 3; ++j){
				if (a.index[i][j] != b.index[i][j]){
					return false;
				}
			}
		}
		return iErrorFlag;
	}

	//	3X3と3X1行列の掛け算
	//	二次元のゲームでの仕様を目的とする
	Matrix3X1 MultiMatrixNxM(const Matrix3X3 &a, const Matrix3X1 &b){
		Matrix3X1 temp;
		temp.index[0] = temp.index[1] = temp.index[2] = 0;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				temp.index[i] += a.index[i][j] * b.index[j];
			}
		}
		return temp;
	}

	//	4X4と4X1行列の掛け算
	//	三次元のゲームでの仕様を目的とする
	Matrix4X1 MultiMatrixNxM(const Matrix4X4 &a, const Matrix4X1 &b){
		Matrix4X1 temp;
		temp.index[0] = temp.index[1] = temp.index[2] = temp.index[3] = 0;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				temp.index[i] += a.index[i][j] * b.index[j];
			}
		}
		return temp;
	}

	//	二次元の行列の掛け算による平行移動
	Matrix3X1 TranslateMatrix(const Matrix3X1 &a, float dx, float dy){
		Matrix3X3 temp;
		Matrix3X1 ret;

		ClearMatrix(temp);

		//	平行移動のための行列の作成
		for (int i = 0; i < 3; i++){
			temp.index[i][i] = 1;
		}

		//	移動量を代入
		temp.index[0][2] = dx;
		temp.index[1][2] = dy;
		ret = MultiMatrixNxM((Matrix3X3)temp, (Matrix3X1)a);
		return ret;
	}

	//	三次元の行列の掛け算による平行移動
	Matrix4X1 TranslateMatrix(const Matrix4X1 &a, float dx, float dy, float dz){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	平行移動のための行列の作成
		for (int i = 0; i < 4; i++){
			temp.index[i][i] = 1;
		}

		//	移動量を代入
		temp.index[0][3] = dx;
		temp.index[1][3] = dy;
		temp.index[2][3] = dz;
		ret = MultiMatrixNxM(temp, a);
		return ret;
	}


	//	二次元の行列の掛け算による拡大縮小(スケーリング)
	Matrix3X1 ScaleMatrix(const Matrix3X1 &a, float dx, float dy){
		Matrix3X3 temp;
		Matrix3X1 ret;

		ClearMatrix(temp);
		//	スケーリングのための行列の作成
		temp.index[0][0] = dx;
		temp.index[1][1] = dy;
		temp.index[2][2] = 1;

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	三次元の行列の掛け算による拡大縮小
	Matrix4X1 ScaleMatrix(const Matrix4X1 &a, float dx, float dy, float dz){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	スケーリングのための行列の作成
		temp.index[0][0] = dx;
		temp.index[1][1] = dy;
		temp.index[2][2] = dz;
		temp.index[3][3] = 1;
		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	二次元の回転させるための行列の掛け算
	Matrix3X1 Rotate2D(const Matrix3X1 &a, float theta){
		Matrix3X3 temp;
		Matrix3X1 ret;
		ClearMatrix(temp);

		//	回転行列のための行列の作成
		temp.index[0][0] = cosf(DEG_TO_RAD(theta));
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = 1;
		temp.index[0][1] = -1 * sinf(DEG_TO_RAD(theta));
		temp.index[1][0] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	3次元のz軸周りの回転(ロール)
	Matrix4X1 RotateZ(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	回転行列のための行列の作成
		temp.index[0][0] = cosf(DEG_TO_RAD(theta));
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = 1;
		temp.index[3][3] = 1;

		temp.index[0][1] = -1 * sin(DEG_TO_RAD(theta));
		temp.index[1][0] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	// 3次元のx軸周りの回転(ピッチ)
	Matrix4X1 RotateX(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	回転行列のための行列の作成
		temp.index[0][0] = 1;
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = cosf(DEG_TO_RAD(theta));
		temp.index[3][3] = 1;
		temp.index[1][2] = -1 * sinf(DEG_TO_RAD(theta));
		temp.index[2][1] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	// 3次元のy軸周りの回転(ヨー)
	Matrix4X1 RotateY(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	回転行列のための行列の作成
		temp.index[0][0] = cos(DEG_TO_RAD(theta));
		temp.index[1][1] = 1;
		temp.index[2][2] = cos(DEG_TO_RAD(theta));
		temp.index[3][3] = 1;
		temp.index[2][0] = -1 * sin(DEG_TO_RAD(theta));
		temp.index[0][2] = sin(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	3次元における回転の行列の組み合わせ
	Matrix4X4 CreateRotationCombo(float thetax, float thetay, float thetaz){
		Matrix4X4 X, Y, Z, temp, ret;

		//	行列を0で初期化
		ClearMatrix(X);
		ClearMatrix(Y);
		ClearMatrix(Z);
		ClearMatrix(temp);
		ClearMatrix(ret);

		//	x軸の回転行列の設定
		X.index[0][0] = 1;
		X.index[1][1] = cos(DEG_TO_RAD(thetax));
		X.index[2][2] = cos(DEG_TO_RAD(thetax));
		X.index[3][3] = 1;

		X.index[1][2] = -1 * sin(DEG_TO_RAD(thetax));
		X.index[2][1] = sin(DEG_TO_RAD(thetax));

		//	y軸の回転行列の設定
		Y.index[0][0] = cos(DEG_TO_RAD(thetay));
		Y.index[1][1] = 1;
		Y.index[2][2] = cos(DEG_TO_RAD(thetay));
		Y.index[3][3] = 1;

		Y.index[2][0] = -1 * sin(DEG_TO_RAD(thetay));
		Y.index[0][2] = sin(DEG_TO_RAD(thetay));

		//	z軸の回転行列の設定
		Z.index[0][0] = cos(DEG_TO_RAD(thetaz));
		Z.index[1][1] = cos(DEG_TO_RAD(thetaz));
		Z.index[2][2] = 1;
		Z.index[3][3] = 1;

		Z.index[0][1] = -1 * sin(DEG_TO_RAD(thetaz));
		Z.index[1][0] = sin(DEG_TO_RAD(thetaz));

		temp = MultiMatrix(Y, X);
		ret = MultiMatrix(temp, Z);

		return ret;
	}

	Matrix4X1 RotateCombo(Matrix4X4 combo, const Matrix4X1 &vertex){
		Matrix4X1 temp;
		temp = MultiMatrixNxM(combo, vertex);
		return temp;
	}

	//	2次元の任意の点を中心とした拡大縮小
	Matrix3X1 ScaleAnyPoints(const Matrix3X1 &a, float dx, float dy, float pointx, float pointy){
		Matrix3X3 temp;
		Matrix3X1 ret;

		ClearMatrix(temp);

		temp.index[0][0] = dx;
		temp.index[0][2] = dx * (-pointx) + pointx;
		temp.index[1][1] = dy;
		temp.index[1][2] = dy * (-pointy) + pointy;
		temp.index[2][2] = 1;

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	2次元の任意の点を中心とした回転
	Matrix3X1 RotateAnyPoints(const Matrix3X1 &a, float angle, float pointx, float pointy){
		Matrix3X3 temp;
		Matrix3X1 ret;
		ClearMatrix(temp);
		temp.index[0][0] = cos(DEG_TO_RAD(angle));
		temp.index[0][1] = -1 * sin(DEG_TO_RAD(angle));
		temp.index[0][2] = -1 * pointx * cos(DEG_TO_RAD(angle)) + pointy * sin(DEG_TO_RAD(angle)) + pointx;
		temp.index[1][0] = sin(DEG_TO_RAD(angle));
		temp.index[1][1] = cos(DEG_TO_RAD(angle));
		temp.index[1][2] = -1 * pointx * sin(DEG_TO_RAD(angle)) + cos(DEG_TO_RAD(angle)) * -pointy + pointy;
		temp.index[2][2] = 1;
		//km::TransposeMatrix(temp);
		ret = MultiMatrixNxM(temp, a);
		return ret;
	}



	Matrix4X1 RotateAnyPoints(const Matrix4X1 &a, float thetax, float thetay, float thetaz, float pointx, float pointy, float pointz){
		Matrix4X4 X, Y, Z, temp, ret, trans1, trans2;

		//	行列を0で初期化
		ClearMatrix(X);
		ClearMatrix(Y);
		ClearMatrix(Z);
		ClearMatrix(temp);
		ClearMatrix(ret);
		ClearMatrix(trans1);
		ClearMatrix(trans2);

		for (int i = 0; i < 4; i++){
			trans1.index[i][i] = 1;
			trans2.index[i][i] = 1;
		}
		trans1.index[0][3] = pointx;
		trans1.index[1][3] = pointy;
		trans1.index[2][3] = pointz;
		trans2.index[0][3] = -pointx;
		trans2.index[1][3] = -pointy;
		trans2.index[2][3] = -pointz;


		//	x軸の回転行列の設定
		X.index[0][0] = 1;
		X.index[1][1] = cos(DEG_TO_RAD(thetax));
		X.index[2][2] = cos(DEG_TO_RAD(thetax));
		X.index[3][3] = 1;

		X.index[1][2] = -1 * sin(DEG_TO_RAD(thetax));
		X.index[2][1] = sin(DEG_TO_RAD(thetax));

		//	y軸の回転行列の設定
		Y.index[0][0] = cos(DEG_TO_RAD(thetay));
		Y.index[1][1] = 1;
		Y.index[2][2] = cos(DEG_TO_RAD(thetay));
		Y.index[3][3] = 1;

		Y.index[2][0] = -1 * sin(DEG_TO_RAD(thetay));
		Y.index[0][2] = sin(DEG_TO_RAD(thetay));

		//	z軸の回転行列の設定
		Z.index[0][0] = cos(DEG_TO_RAD(thetaz));
		Z.index[1][1] = cos(DEG_TO_RAD(thetaz));
		Z.index[2][2] = 1;
		Z.index[3][3] = 1;

		Z.index[0][1] = -1 * sin(DEG_TO_RAD(thetaz));
		Z.index[1][0] = sin(DEG_TO_RAD(thetaz));

		temp = MultiMatrix(trans1, Y);
		ret = MultiMatrix(temp, X);
		ret = MultiMatrix(ret, Z);
		ret = MultiMatrix(ret, trans2);
		return RotateCombo(ret, a);

	}
}