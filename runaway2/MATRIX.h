#pragma once
#pragma warning(disable:4244)
#include "Macro.h"
/*
	�s��Ƃ�

	�s�Ɨ񂩂�Ȃ鐔���̏W���̂̂��ƂŁA�v���O���~���O�I�ɂ͂Q�����z��Ǝ����悤�Ȃ���
	int a[3][2] = { 
		{0, 1},
		{2, 3},
		{4, 5}
	};
	���̂悤�ɔz��̈ꎟ��(����)���s���w���A�Q����(�E��)������w��
	��ɉ�]��ړ��Ȃǂ̕ϊ���ƂɕK�v�Ƃ���

*/
namespace km
{

	//	�s��̔z��
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



	//	�s��̍s�����o��
	template <typename T>
	int MatrixLine(const T &m){
		return sizeof(m.index) / sizeof(m.index[0]);
	}

	//	�s��̗񐔂��o��
	template <typename T>
	int MatrixColumn(const T &m){
		return sizeof(m.index[0]) / sizeof(m.index[0][0]);
	}

	//�@�s��̗v�f���O�ŏ�����
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

	//	2�̍s�񂪓������ǂ����̔���
	bool areMatricesWqual(Matrix3X3 a, Matrix3X3 b);

	//	2�̍s�񂪓������ǂ����̔���
	//	������͍s�Ɨ�̐��������Ȃ�΂ǂ̌^������ł��� 2*2 4*4�Ȃǂ̍s��
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

	//	�s��̑����Z
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

	//	�s��̈����Z
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

	//	�s��̃X�J���[�{
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

	//	�s�Ɨ�̓����Q�̍s�񓯎m�̊|���Z
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

	//	3X3��3X1�s��̊|���Z
	//	�񎟌��̃Q�[���ł̎d�l��ړI�Ƃ���
	Matrix3X1 MultiMatrixNxM(const Matrix3X3 &a, const Matrix3X1 &b);

	//	4X4��4X1�s��̊|���Z
	//	�O�����̃Q�[���ł̎d�l��ړI�Ƃ���
	Matrix4X1 MultiMatrixNxM(const Matrix4X4 &a, const Matrix4X1 &b);

	//	�s��̗v�f��\������֐�
	template <typename T>
	void PrintMatrix(const T &a){
		int i, j;
		int line = MatrixLine(a);
		int column = MatrixColumn(a);
		for (i = 0; i < line; ++i){
			cout << i + 1 << "�s" << endl;
			for (j = 0; j < column; ++j){
				cout << j + 1 << "�� : " << a.index[i][j] << " | " << endl;;
			}
			cout << endl;
		}
	}

	//	�񂪈�̍s��̗v�f��\��
	template <typename T>
	void PrintMatrixNx1(const T &a){
		int i;
		int line = MatrixLine(a);
		for (i = 0; i < line; i++){
			cout << i + 1 << "�s : " << a.index[i] << endl;
		}
	}

	/*	�s��̓]�u
		�s��̓]�u�Ƃ͍s�Ɨ�����ւ��邱��
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
		��
		1, 4, 7
		2, 5, 8
		3, 6, 9
		�̂悤��
		�ϊ�����

		�܂��A�]�u�����ꍇ�͍s�Ɨ�̗v�f��������ւ�邱�Ƃɒ���

		DirectX��OpenGL�ł͍s��̕��т��Ⴄ�̂ŁA�]�u������K�v������̂�

		�s�Ɨ�̐��������K�v������@
		�s��̌v�Z�ł͖��Ȃ����v���O���~���O�ł͍s��̐����ς��̂�
		�Ԃ��\���̂���`����Ă��Ȃ��Ƃ����Ȃ�

		*/

	//	�s���]�n������֐�
	template <typename T>
	T TransposeMatrix(const T &a){
		T temp;
		int line = MatrixLine(a);
		int column = MatrixColumn(a);

		//	�G���[�����@�s�Ɨ񂪈Ⴄ�\���̂̏ꍇ�͊֐��𔲂���
		if (line != column) return;

		for (int i = 0; i < line; i++){
			for (int j = 0; j < column; j++){
				temp.index[j][i] = a.index[i][j];
			}
		}
		return temp;
	}


	/*
		�s��̕ϊ�
		*/

	//	�񎟌��̍s��̊|���Z�ɂ�镽�s�ړ�
	Matrix3X1 TranslateMatrix(const Matrix3X1 &a, float dx, float dy);

	//	�O�����̍s��̊|���Z�ɂ�镽�s�ړ�
	Matrix4X1 TranslateMatrix(const Matrix4X1 &a, float dx, float dy, float dz);

	//	�񎟌��̍s��̊|���Z�ɂ��g��k��(�X�P�[�����O)
	Matrix3X1 ScaleMatrix(const Matrix3X1 &a, float dx, float dy);

	//	�O�����̍s��̊|���Z�ɂ��g��k��
	Matrix4X1 ScaleMatrix(const Matrix4X1 &a, float dx, float dy, float dz);
	//	�񎟌��̉�]�����邽�߂̍s��̊|���Z
	Matrix3X1 Rotate2D(const Matrix3X1 &a, float theta);

	//	3������z������̉�](���[��)
	Matrix4X1 RotateZ(const Matrix4X1 &a, float theta);
	// 3������x������̉�](�s�b�`)
	Matrix4X1 RotateX(const Matrix4X1 &a, float theta);

	// 3������y������̉�](���[)
	Matrix4X1 RotateY(const Matrix4X1 &a, float theta);

	//	3�����ɂ������]�̍s��̑g�ݍ��킹
	Matrix4X4 CreateRotationCombo(float thetax, float thetay, float thetaz);

	Matrix4X1 RotateCombo(Matrix4X4 combo, const Matrix4X1 &vertex);

	//	2�����̔C�ӂ̓_�𒆐S�Ƃ����g��k��
	Matrix3X1 ScaleAnyPoints(const Matrix3X1 &a, float dx, float dy, float pointx, float pointy);

	//	2�����̔C�ӂ̓_�𒆐S�Ƃ�����]
	Matrix3X1 RotateAnyPoints(const Matrix3X1 &a, float angle, float pointx, float pointy);

	Matrix4X1 RotateAnyPoints(const Matrix4X1 &a, float thetax, float thetay, float thetaz, float pointx, float pointy, float pointz);


}