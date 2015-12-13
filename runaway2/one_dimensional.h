#pragma once

//	���x�����̏ꍇ�̕ψʂ����߂�
float calcDisplacement(float vel, float time){
	return vel * time;
}

//	���x�����̎��̐V�����ʒu�̋��ߕ�
float calcPosition(float oldPosition, float vel, float time){
	return oldPosition + (vel * time);
}

// �t���[���Ԃł̕��ϑ��x
float calcAvgVel(float start, float end, float time){
	return (end - start) / time;
}

