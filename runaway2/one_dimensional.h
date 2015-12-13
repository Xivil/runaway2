#pragma once

//	速度が一定の場合の変位を求める
float calcDisplacement(float vel, float time){
	return vel * time;
}

//	速度が一定の時の新しい位置の求め方
float calcPosition(float oldPosition, float vel, float time){
	return oldPosition + (vel * time);
}

// フレーム間での平均速度
float calcAvgVel(float start, float end, float time){
	return (end - start) / time;
}

