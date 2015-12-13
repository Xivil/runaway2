#pragma once
#pragma warning(disable:4244)
#include <math.h>
#include <iostream>
#include "DxLib.h"
#include "Macro.h"
using namespace std;

/*
	�x�N�g��
	�x�N�g���Ƃ͌������������͂⑬���̂���
	�Ⴆ�Ύ���100�L�����[�g���Ƃ����ΒP�Ȃ�傫�������A
	���Ɏ���100�L�����[�g���Ƃ����΂���͌����Ƒ傫�����������x�N�g���ƂȂ�
	�Q�[���ɂ����Ă͌��_����Ƃ������W�ŕ\����������

	�x�N�g���͑��������������|�����芄������o����B
	���ςƊO�ςƂ����x�N�g���Ɠ��̗v�f������B
	�����Z�ƈ����Z�̓x�N�g���̍��W�̉��Z������Ηǂ�
	(1,2,3)��(4,5,6)�Ƃ���2�̃x�N�g���̑����Z
	(5,7,9)�ƂȂ�B�����Z�������悤�Ɍv�Z����
	�|���Z�Ɗ���Z�̏ꍇ�̓x�N�g�����m�ł͂Ȃ��x�N�g���Ƒ傫���Ōv�Z����
	(1,2,3,)�~2��(2,4,6)�Ƃ����悤�Ɍv�Z

	���ςƊO�ςɂ��ĉ��
	���ς�2�̃x�N�g���̗v�f�����ꂼ��|���A���ꂼ��𑫂����킹�����B�l�͐����ƂȂ�
	���ς̋L���́E�ƂȂ�
	��@A(1,2,3)�EB(4,5,6)��1*4+2*5+3*6��32�ƂȂ�
	���ς̒l������������2�̃x�N�g���̊p�x��90�ȏオ�ǂ������킩��
	A�EB < 0�@�Ȃ�Ίp�x��90�x�ȏ�
	A�EB > 0�@�Ȃ�Ίp�x��90�x�ȉ�
	A�EB = 0�@�Ȃ�ΐ���
	�ƂȂ�B

	�O�ς�3�����x�N�g���݂̂ɑ��݂���T�O�ŁA
*/

/*
	���O��ԁ@namespace name�Ƃ��邱�ƂŖ��O��Ԃ��w�肷�邱�Ƃ��o����
	�Ⴆ�΁A
	namespace A{
		void draw();
	}
	�Ƃ����draw()�֐��͖��O���A�ɑ�����
	����draw()���g�p����ɂ�
	A::draw()�ƋL�q����B
	���O��Ԃ͕ʂ̃N���X��֐��Ȃǂ̍�����Փ˂�����邽�߂ɂ���B
*/
namespace km{
	//	3�����x�N�g���̃N���X
	typedef class Vector3{
	public:
		float x, y, z;		//	���W

		/*
			�R���X�g���N�^
			�N���X�̃I�u�W�F�N�g�𐶐��������ɕK�����s�����֐��̂���
		*/
		Vector3(float ex = 0, float why = 0, float zee = 0);

		/*
			�R�s�[�R���X�g���N�^
			�R���X�g���N�^������������Ƃ��ɂ̂ݑ��̃I�u�W�F�N�g�̒l���R�s�[����R���X�g���N�^
			��
			Vector3 a(1, 2, 3);
			Vector3 b = a;

			�܂��A�N���X�̒l�n��������Ƃ��i�N���X�̃|�C���^�ϐ���Q�ƕϐ�(*,&)���g�p���Ȃ�����)��
			���̊֐����I������Ƃ��Ƀf�X�g���N�^���Ă΂�Ă��܂��B
			���̎����I�m�ۂ����ϐ�������A������f�X�g���N�^�ŊJ������Ƃ��͂����������ɊJ������̂�
			�R�s�[�R���X�g���N�^�ŕ������Ă����K�v������B
			�R�s�[�R���X�g���N�^�͉������Ƃ����ꍇ�ɂ���p������
		*/
		/*
			���I�m�ۂ���|�C���^�^�ϐ������N���X�̃R�s�[�R���X�g���N�^�̗�
			�P�ɔz��̗v�f�����m�ۂ��Ă��邾���̃N���XNum
			�|�C���^�^�ϐ�a�ƌ���\��num�ϐ�������

			class Num{
			public:
				int *a;
				int num;
				Num(int num){
					a = new int[num];
					this->num = num;
				}
				Num(const Num &dst){
					a = new int[num]
				}
				~Num(){
					delete[] a;
				}
			};
		*/
		Vector3(const Vector3 &obj);

		virtual ~Vector3(){};

		//	�Q�b�^�[�ƃZ�b�^�[
		//	�N���X�̕ϐ��͔���J�ɂ���̂���{�@���̃N���X��֐�����D�����肢�����Ă͍���̂�
		//	�����o�ϐ������J���邩����J�ɂ��邩�͕ۗ����@����ł̓e�X�g�����˂Ă���̂łƂ肠�������J�ɂ��Ă���
		inline float get_x() const;
		inline float get_y() const;
		inline float get_z() const;
		inline Vector3 get_all() const;
		void set_x(const float x);
		void set_y(const float y);
		void set_z(const float z);
		void set_all(const Vector3 &a);
		//	������Z�q�̃I�[�o�[���[�h
		Vector3& operator = (const Vector3 &v);

		//	�x�N�g���̑傫���̌v�Z
		float getMagnitude() const;

		/*�@���Z�q�̃I�[�o�[���[�h�Ƃ͉��Z�q�̏����������Œ�`���Ď������邱��
			�L�q���@�́A
			�߂�l ���O operator ���Z�q�i ���� �j{ ���� }
			�ƂȂ�B
			���ʂ̊֐��ƈႤ�Ƃ���͊֐������g�p���Ȃ��Ƃ���ɂ���B
			���L�̏ꍇ�ł�
			Vector3�^�ϐ�a = Vector3�^�ϐ�b * 3.2;
			�ƋL�q���邱�Ƃ�a��b��3,2�{�����l����������
			���������֐��̖��O���g�p�����ɉ��Z�q�ő�p������̂ƍl���Ă��炤�Ƃ킩��₷��
			
		*/
		//	�x�N�g���̃X�J���[�{�@�X�J���[�{�Ƃ͒ʏ�̊|���Z�̂���
		//	��Z���Z�q�̃I�[�o�[���[�h
		Vector3 operator * (float num) const;
		friend Vector3 operator * (float num, const Vector3 &v);

		//�@��Z������Z�q�̃I�[�o�[���[�h
		Vector3& operator *= (float num);

		//	�x�N�g���̉��Z
		//	���Z���Z�q�̃I�[�o�[���[�h
		Vector3 operator+(const Vector3 &P2)const;


		//	���Z������Z�q�̃I�[�o�[���[�h
		Vector3& operator+=(const Vector3 &P2);

		//	�x�N�g���̈����Z
		//�@���Z���Z�q�̃I�[�o�[���[�h
		Vector3 operator - (const Vector3 &v) const;

		//	���Z������Z�q�̃I�[�o�[���[�h
		Vector3& operator -= (const Vector3 &v);

		//�x�N�g���̐��K��
		void Normalize();

		//	2�̃x�N�g���̓���
		float Dot(const Vector3 &v);

		//	2�̃x�N�g���̊O��
		Vector3 Cross(const Vector3 &v);

		//�@�R���\�[���p�̊e�����o�ϐ��̕\��
		void print();
	}Point3;

	//	���ς���p�x���v�Z
	float Scalar(const Vector3 &v1, const Vector3 &v2);

	Vector3 GetVector3(float x, float y, float z);

	VECTOR Vector3ToDxVector(Vector3& a);

}

