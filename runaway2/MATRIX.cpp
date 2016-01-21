
#include "MATRIX.h"
namespace km
{
	//	2�̍s�񂪓������ǂ����̔���
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

	//	3X3��3X1�s��̊|���Z
	//	�񎟌��̃Q�[���ł̎d�l��ړI�Ƃ���
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

	//	4X4��4X1�s��̊|���Z
	//	�O�����̃Q�[���ł̎d�l��ړI�Ƃ���
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

	//	�񎟌��̍s��̊|���Z�ɂ�镽�s�ړ�
	Matrix3X1 TranslateMatrix(const Matrix3X1 &a, float dx, float dy){
		Matrix3X3 temp;
		Matrix3X1 ret;

		ClearMatrix(temp);

		//	���s�ړ��̂��߂̍s��̍쐬
		for (int i = 0; i < 3; i++){
			temp.index[i][i] = 1;
		}

		//	�ړ��ʂ���
		temp.index[0][2] = dx;
		temp.index[1][2] = dy;
		ret = MultiMatrixNxM((Matrix3X3)temp, (Matrix3X1)a);
		return ret;
	}

	//	�O�����̍s��̊|���Z�ɂ�镽�s�ړ�
	Matrix4X1 TranslateMatrix(const Matrix4X1 &a, float dx, float dy, float dz){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	���s�ړ��̂��߂̍s��̍쐬
		for (int i = 0; i < 4; i++){
			temp.index[i][i] = 1;
		}

		//	�ړ��ʂ���
		temp.index[0][3] = dx;
		temp.index[1][3] = dy;
		temp.index[2][3] = dz;
		ret = MultiMatrixNxM(temp, a);
		return ret;
	}


	//	�񎟌��̍s��̊|���Z�ɂ��g��k��(�X�P�[�����O)
	Matrix3X1 ScaleMatrix(const Matrix3X1 &a, float dx, float dy){
		Matrix3X3 temp;
		Matrix3X1 ret;

		ClearMatrix(temp);
		//	�X�P�[�����O�̂��߂̍s��̍쐬
		temp.index[0][0] = dx;
		temp.index[1][1] = dy;
		temp.index[2][2] = 1;

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	�O�����̍s��̊|���Z�ɂ��g��k��
	Matrix4X1 ScaleMatrix(const Matrix4X1 &a, float dx, float dy, float dz){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	�X�P�[�����O�̂��߂̍s��̍쐬
		temp.index[0][0] = dx;
		temp.index[1][1] = dy;
		temp.index[2][2] = dz;
		temp.index[3][3] = 1;
		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	�񎟌��̉�]�����邽�߂̍s��̊|���Z
	Matrix3X1 Rotate2D(const Matrix3X1 &a, float theta){
		Matrix3X3 temp;
		Matrix3X1 ret;
		ClearMatrix(temp);

		//	��]�s��̂��߂̍s��̍쐬
		temp.index[0][0] = cosf(DEG_TO_RAD(theta));
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = 1;
		temp.index[0][1] = -1 * sinf(DEG_TO_RAD(theta));
		temp.index[1][0] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	3������z������̉�](���[��)
	Matrix4X1 RotateZ(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	��]�s��̂��߂̍s��̍쐬
		temp.index[0][0] = cosf(DEG_TO_RAD(theta));
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = 1;
		temp.index[3][3] = 1;

		temp.index[0][1] = -1 * sin(DEG_TO_RAD(theta));
		temp.index[1][0] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	// 3������x������̉�](�s�b�`)
	Matrix4X1 RotateX(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	��]�s��̂��߂̍s��̍쐬
		temp.index[0][0] = 1;
		temp.index[1][1] = cosf(DEG_TO_RAD(theta));
		temp.index[2][2] = cosf(DEG_TO_RAD(theta));
		temp.index[3][3] = 1;
		temp.index[1][2] = -1 * sinf(DEG_TO_RAD(theta));
		temp.index[2][1] = sinf(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	// 3������y������̉�](���[)
	Matrix4X1 RotateY(const Matrix4X1 &a, float theta){
		Matrix4X4 temp;
		Matrix4X1 ret;

		ClearMatrix(temp);

		//	��]�s��̂��߂̍s��̍쐬
		temp.index[0][0] = cos(DEG_TO_RAD(theta));
		temp.index[1][1] = 1;
		temp.index[2][2] = cos(DEG_TO_RAD(theta));
		temp.index[3][3] = 1;
		temp.index[2][0] = -1 * sin(DEG_TO_RAD(theta));
		temp.index[0][2] = sin(DEG_TO_RAD(theta));

		ret = MultiMatrixNxM(temp, a);
		return ret;
	}

	//	3�����ɂ������]�̍s��̑g�ݍ��킹
	Matrix4X4 CreateRotationCombo(float thetax, float thetay, float thetaz){
		Matrix4X4 X, Y, Z, temp, ret;

		//	�s���0�ŏ�����
		ClearMatrix(X);
		ClearMatrix(Y);
		ClearMatrix(Z);
		ClearMatrix(temp);
		ClearMatrix(ret);

		//	x���̉�]�s��̐ݒ�
		X.index[0][0] = 1;
		X.index[1][1] = cos(DEG_TO_RAD(thetax));
		X.index[2][2] = cos(DEG_TO_RAD(thetax));
		X.index[3][3] = 1;

		X.index[1][2] = -1 * sin(DEG_TO_RAD(thetax));
		X.index[2][1] = sin(DEG_TO_RAD(thetax));

		//	y���̉�]�s��̐ݒ�
		Y.index[0][0] = cos(DEG_TO_RAD(thetay));
		Y.index[1][1] = 1;
		Y.index[2][2] = cos(DEG_TO_RAD(thetay));
		Y.index[3][3] = 1;

		Y.index[2][0] = -1 * sin(DEG_TO_RAD(thetay));
		Y.index[0][2] = sin(DEG_TO_RAD(thetay));

		//	z���̉�]�s��̐ݒ�
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

	//	2�����̔C�ӂ̓_�𒆐S�Ƃ����g��k��
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

	//	2�����̔C�ӂ̓_�𒆐S�Ƃ�����]
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

		//	�s���0�ŏ�����
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


		//	x���̉�]�s��̐ݒ�
		X.index[0][0] = 1;
		X.index[1][1] = cos(DEG_TO_RAD(thetax));
		X.index[2][2] = cos(DEG_TO_RAD(thetax));
		X.index[3][3] = 1;

		X.index[1][2] = -1 * sin(DEG_TO_RAD(thetax));
		X.index[2][1] = sin(DEG_TO_RAD(thetax));

		//	y���̉�]�s��̐ݒ�
		Y.index[0][0] = cos(DEG_TO_RAD(thetay));
		Y.index[1][1] = 1;
		Y.index[2][2] = cos(DEG_TO_RAD(thetay));
		Y.index[3][3] = 1;

		Y.index[2][0] = -1 * sin(DEG_TO_RAD(thetay));
		Y.index[0][2] = sin(DEG_TO_RAD(thetay));

		//	z���̉�]�s��̐ݒ�
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