#pragma once
#include "Macro.h"
/*
	行列とは

	行と列からなる数字の集合体のことで、プログラミング的には２次元配列と似たようなもの
	int a[3][2] = { 
		{0, 1},
		{2, 3},
		{4, 5}
	};
	このように配列の一次元(左側)が行を指し、２次元(右側)が列を指す
	主に回転や移動などの変換作業に必要とする

*/

//	行列の配列
struct Matrix2X2{
	float index[2][2];
};
struct Matrix3X3{
	float index[3][3];
};
struct Matrix4X4{
	float index[4][4];
};
struct Matrix3X1{
	float index[3];
};
struct Matrix4X1{
	float index[4];
};



//	行列の行数を出力
template <typename T>
int MatrixLine(const T &m){
	return sizeof(m.index) / sizeof(m.index[0]);
}

//	行列の列数を出力
template <typename T>
int MatrixColumn(const T &m){
	return sizeof(m.index[0]) / sizeof(m.index[0][0]);
}

//　行列の要素を０で初期化
template <typename T>
void ClearMatrix(T &a){
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (int i = 0; i < line; i++){
		for (int j = 0; j < column; j++){
			a.index[i][j] = 0;
		}
	}
}

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

//	2つの行列が同じかどうかの判定
//	こちらは行と列の数が同じならばどの型も判定できる 2*2 4*4などの行列
template <typename T>
bool SameMatrixDecision(const T &a, const T &b){
	bool iErrorFlag = true;
	int i, j;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (i = 0; i < line; ++i){
		for (j = 0; j < column; ++j){
			if (a.index[i][j] != b.index[i][j]){
				return false;
			}
		}
	}
	return iErrorFlag;
}

//	行列の足し算
template <typename T>
T AddMatrix(const T a, const T b){
	T temp;
	int i, j;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (i = 0; i < line; ++i){
		for (j = 0; j < column; ++j){
			temp.index[i][j] = a.index[i][j] + b.index[i][j];
		}
	}
	
	return temp;
}

//	行列の引き算
template <typename T>
T MinMatrix(const T a, const T b){
	T temp;
	int i, j;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (i = 0; i < line; ++i){
		for (j = 0; j < column; ++j){
			temp.index[i][j] = a.index[i][j] - b.index[i][j];
		}
	}

	return temp;
}

//	行列のスカラー倍
template <typename T>
T ScalarMatrix(const T a, float scale){
	T temp;
	int i, j;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (i = 0; i < line; ++i){
		for (j = 0; j < column; ++j){
			temp.index[i][j] = a.index[i][j] * scale;
		}
	}

	return temp;
}

//	行と列の同じ２つの行列同士の掛け算
template <typename T>
T MultiMatrix(const T &a, const T &b){
	T temp;
	ClearMatrix(temp);
	int num = MatrixLine(a);
	for (int i = 0; i < num; i++){
		for (int j = 0; j < num; j++){
			for (int k = 0; k < num; k++){
				temp.index[i][j] += a.index[i][k] * b.index[k][j];
			}
		}
	}

	return temp;
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


//	行列の要素を表示する関数
template <typename T>
void PrintMatrix(const T &a){
	int i, j;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);
	for (i = 0; i < line; ++i){
		cout << i + 1 << "行" << endl;
		for (j = 0; j < column; ++j){
			cout << j + 1 << "列 : " << a.index[i][j] << " | " << endl;;
		}
		cout << endl;
	}
}

//	列が一つの行列の要素を表示
template <typename T>
void PrintMatrixNx1(const T &a){
	int i;
	int line = MatrixLine(a);
	for (i = 0; i < line; i++){
		cout << i + 1 << "行 : " << a.index[i] << endl;
	}
}

/*	行列の転置
	行列の転置とは行と列を入れ替えること
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
	を
	1, 4, 7
	2, 5, 8
	3, 6, 9
	のように
	変換する

	また、転置した場合は行と列の要素数が入れ替わることに注意

	DirectXとOpenGLでは行列の並びが違うので、転置させる必要があるので

	行と列の数が同じ必要がある　
	行列の計算では問題ないがプログラミングでは行列の数が変わるので
	返す構造体が定義されていないといけない
	
*/

//	行列を転地させる関数
template <typename T>
T TransposeMatrix(const T &a){
	T temp;
	int line = MatrixLine(a);
	int column = MatrixColumn(a);

	//	エラー処理　行と列が違う構造体の場合は関数を抜ける
	if (line != column) return;

	for (int i = 0; i < line; i++){
		for (int j = 0; j < column; j++){
			temp.index[j][i] = a.index[i][j];
		}
	}
	return temp;
}


/*
	行列の変換
*/

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
	ret = MultiMatrixNxM(temp, a);
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
	temp.index[0][0] = cos(DEG_TO_RAD(theta));
	temp.index[1][1] = cos(DEG_TO_RAD(theta));
	temp.index[2][2] = 1;
	temp.index[0][1] = -1 * sin(DEG_TO_RAD(theta));
	temp.index[1][0] = sin(DEG_TO_RAD(theta));

	ret = MultiMatrixNxM(temp, a);
	return ret;
}

//	3次元のz軸周りの回転(ロール)
Matrix4X1 RotateZ(const Matrix4X1 &a, float theta){
	Matrix4X4 temp;
	Matrix4X1 ret;

	ClearMatrix(temp);

	//	回転行列のための行列の作成
	temp.index[0][0] = cos(DEG_TO_RAD(theta));
	temp.index[1][1] = cos(DEG_TO_RAD(theta));
	temp.index[2][2] = 1;
	temp.index[3][3] = 1;

	temp.index[0][1] = -1 * sin(DEG_TO_RAD(theta));
	temp.index[1][0] = sin(DEG_TO_RAD(theta));

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
	temp.index[1][1] = cos(DEG_TO_RAD(theta));
	temp.index[2][2] = cos(DEG_TO_RAD(theta));
	temp.index[3][3] = 1;
	temp.index[1][2] = -1 * sin(DEG_TO_RAD(theta));
	temp.index[2][1] = sin(DEG_TO_RAD(theta));

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
	temp.index[0][2] = -1 *pointx * cos(DEG_TO_RAD(angle)) + pointy * sin(DEG_TO_RAD(angle)) + pointx;
	temp.index[1][0] = sin(DEG_TO_RAD(angle));
	temp.index[1][1] = cos(DEG_TO_RAD(angle));
	temp.index[1][2] = -1 * pointx * sin(DEG_TO_RAD(angle)) + cos(DEG_TO_RAD(angle)) * -pointy + pointy;
	temp.index[2][2] = 1;

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

