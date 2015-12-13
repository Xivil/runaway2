#pragma once
#define MILE_TO_KM 1.609
#define KM_TO_METER 1000
#define WEEK_TO_DAY 7
#define DAY_TO_HOUR 24
#define HOUR_TO_MIN 60
#define MIN_TO_SEC 60

//	日付を秒に変換する関数
float convertDaysToSeconds(float days){
	float seconds;
	seconds = days * DAY_TO_HOUR * HOUR_TO_MIN * MIN_TO_SEC;
	return seconds;
}

//	マイル(距離)をメートルに変換
float convertMilesToMeters(float miles){
	float meters;
	meters = miles * MILE_TO_KM * KM_TO_METER;
	return meters;
}

//	時速マイルを秒速メートルに変換
float convertMilesHourToMeterSecond(float miles){
	return miles * MILE_TO_KM * KM_TO_METER / HOUR_TO_MIN / MIN_TO_SEC;
}