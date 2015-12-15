#include "Func.h"

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}

// �L�[�̓��͏�ԍX�V
void Keyboard_Update(){
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++){
		if (tmpKey[i] != 0){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			m_Key[i] = 0; // 0�ɂ���
		}
	}
}

namespace km{
	Vector3 MATRIX_TO_VECTOR3(Matrix4X1 &mat){
		return GetVector3(mat.index[0], mat.index[1], mat.index[2]);
	}
	Matrix4X1 VECTOR3_TO_MATRIX(Vector3 &vec){
		Matrix4X1 ret;
		ret.index[0] = vec.get_x();
		ret.index[1] = vec.get_y();
		ret.index[2] = vec.get_z();
		ret.index[3] = 1;

		return ret;
	}
}