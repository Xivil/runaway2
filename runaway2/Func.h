#include "DxLib.h"
#include "MATRIX.h"
#include "VECTOR.h"
static int m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�


// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard_Get(int KeyCode);
// �L�[�̓��͏�ԍX�V
void Keyboard_Update();

namespace km{
	//	Matrix4X1�^��Vector3�^�ɕϊ�
	Vector3 MATRIX_TO_VECTOR3(Matrix4X1 &mat);

	//�@Vector3�^��Matrix4X1�^�ɕϊ�
	Matrix4X1 VECTOR3_TO_MATRIX(Vector3 &vec);
}