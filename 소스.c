#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 1
int main(void) {
	char readFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\10.csv";
	char writeFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\coordinateTransformedData\\Transed_10.csv";
	char timeFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\time.txt";
	char velocityFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\velocity.txt";
	char xposFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\xpos.txt";
	char yposFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\ypos.txt";
	char zposFileName[200] = "C:\\Users\\nic6\\Desktop\\coordinate_transform\\realRun\\10\\zpos.txt";
	char* bufferToCountCell;
	char* bufferToPushData;
	char *bufferToCountTime;
	char* bufferToCountVelocity;
	char* bufferToCountXpos;
	char* bufferToCountYpos;
	char* bufferToCountZpos;
	char buffer[10];
	int readFileSize;
	int timeSize;
	int velocitySize;
	int xposSize;
	int yposSize;
	int zposSize;
	int readCellCount = 0;
	int timeCount = 0;
	int velocityCount = 0;
	int xposCount = 0;
	int yposCount = 0;
	int zposCount = 0;
	int trash = 0;
	float timeArray[25000] = { 0, };
	float velocityArray[25000] = { 0, };
	float xposArray[25000] = { 0, };
	float yposArray[25000] = { 0, };
	float zposArray[25000] = { 0, };

	FILE* readFile = NULL;
	FILE* writeFile = NULL;
	FILE* timeFile = NULL;
	FILE* velocityFile = NULL;
	FILE* xposFile = NULL;
	FILE* yposFile = NULL;
	FILE* zposFile = NULL;

	readFile = fopen(readFileName, "r");
	writeFile = fopen(writeFileName, "w");
	timeFile = fopen(timeFileName, "r");
	velocityFile = fopen(velocityFileName, "r");
	xposFile = fopen(xposFileName, "r");
	yposFile = fopen(yposFileName, "r");
	zposFile = fopen(zposFileName, "r");

	if (readFile == NULL)
		printf("읽을 파일을 열 수 없습니다. \n");
	else
		printf("읽을 파일을 열었습니다.\n");

	if (writeFile == NULL) 
		printf("쓸 파일을 열 수 없습니다.\n");
	else 
		printf("쓸 파일을 열었습니다.\n");
	
	if (timeFile == NULL || velocityFile == NULL || xposFile == NULL|| yposFile == NULL|| zposFile == NULL) 
		printf("좌표 및 속도 혹은 시간 파일을 열 수 없습니다.\n");
	else 
		printf("좌표 및 속도 혹은 시간 파일을 열었습니다.\n");
	
	fseek(readFile, 0, SEEK_END);		//파일 포인터를 파일 끝으로 이동시킴
	fseek(timeFile, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	fseek(velocityFile, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	fseek(xposFile, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	fseek(yposFile, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
	fseek(zposFile, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴

	readFileSize = ftell(readFile);			// 파일 포인터의 현재 위치를 얻음
	timeSize = ftell(timeFile);          // 파일 포인터의 현재 위치를 얻음
	velocitySize = ftell(velocityFile);          // 파일 포인터의 현재 위치를 얻음
	xposSize = ftell(xposFile);          // 파일 포인터의 현재 위치를 얻음
	yposSize = ftell(yposFile);          // 파일 포인터의 현재 위치를 얻음
	zposSize = ftell(zposFile);          // 파일 포인터의 현재 위치를 얻음

	bufferToCountCell = malloc(readFileSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountCell, 0, readFileSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToPushData = malloc(readFileSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToPushData, 0, readFileSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToCountTime = malloc(timeSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountTime, 0, timeSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToCountVelocity = malloc(velocitySize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountVelocity, 0, velocitySize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToCountXpos = malloc(xposSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountXpos, 0, xposSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToCountYpos = malloc(yposSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountYpos, 0, yposSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	bufferToCountZpos = malloc(zposSize + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
	memset(bufferToCountZpos, 0, zposSize + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화

	fseek(readFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountCell, readFileSize, 1, readFile);    // csv 파일 크기만큼 값을 읽음
	fseek(timeFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountTime, timeSize, 1, timeFile);    // csv 파일 크기만큼 값을 읽음
	fseek(velocityFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountVelocity, velocitySize, 1, velocityFile);    // csv 파일 크기만큼 값을 읽음
	fseek(xposFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountXpos, xposSize, 1, xposFile);    // csv 파일 크기만큼 값을 읽음
	fseek(yposFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountYpos, yposSize, 1, yposFile);    // csv 파일 크기만큼 값을 읽음
	fseek(zposFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToCountZpos, zposSize, 1, zposFile);    // csv 파일 크기만큼 값을 읽음

	char* timePtr = strtok(bufferToCountTime, "\n");      // " " 를 기준으로 문자열을 자름, 포인터 반환

	while (timePtr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		timeArray[timeCount] = atof(timePtr);
		timeCount++;
		timePtr = strtok(NULL, "\n");      // 다음 문자열을 잘라서 포인터를 반환
	}

	char* velocityPtr = strtok(bufferToCountVelocity, "\n");      // " " 를 기준으로 문자열을 자름, 포인터 반환

	while (velocityPtr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		velocityArray[velocityCount] = atof(velocityPtr);
		velocityCount++;
		velocityPtr = strtok(NULL, "\n");      // 다음 문자열을 잘라서 포인터를 반환
	}

	char* XposPtr = strtok(bufferToCountXpos, "\n");      // " "를 기준으로 문자열을 자름, 포인터 반환

	while (XposPtr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		xposArray[xposCount] = atof(XposPtr);
		xposCount++;
		XposPtr = strtok(NULL, "\n");      // 다음 문자열을 잘라서 포인터를 반환
	}
	
	char* YposPtr = strtok(bufferToCountYpos, "\n");      // " " 를 기준으로 문자열을 자름, 포인터 반환

	while (YposPtr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		yposArray[yposCount] = atof(YposPtr);
		yposCount++;
		YposPtr = strtok(NULL, "\n");      // 다음 문자열을 잘라서 포인터를 반환
	}


	char* ZposPtr = strtok(bufferToCountZpos, "\n");      // " "를 기준으로 문자열을 자름, 포인터 반환

	while (ZposPtr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		zposArray[zposCount] = atof(ZposPtr);
		zposCount++;
		ZposPtr = strtok(NULL, "\n");      // 다음 문자열을 잘라서 포인터를 반환
	}
	
	char* ptr = strtok(bufferToCountCell, ",");      // " "를 기준으로 문자열을 자름, 포인터 반환

	while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		readCellCount++;
		ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
	}

	int** d_Array = malloc(sizeof(int*) * readCellCount);

	for (int i = 0; i < readCellCount; i++) {
		d_Array[i] = malloc(sizeof(int) * readCellCount);
	}
	printf("readCellCount1 : %d\n", readCellCount);

	readCellCount = 0;

	fseek(readFile, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	fread(bufferToPushData, readFileSize, 1, readFile);    // csv 파일 크기만큼 값을 읽음

	char* ptr2 = strtok(bufferToPushData, ",");      // " "를 기준으로 문자열을 자름, 포인터 반환

	while (ptr2 != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		d_Array[readCellCount] = ptr2;
		readCellCount++;
		ptr2 = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
	}
	
	fputs("Position X,Position Y,Position Z,Velocity,AccX,AccY,AccZ,GyroX,GyroY,GyroZ,MagX,MagY,MagZ,Minor201,Minor202,Minor203,Minor204,Minor205,Minor206,Minor207,Minor208,Minor209,Minor210,Minor211,Minor212,Minor213,Minor214,Minor215,Minor216,Minor217,Minor218,Minor219,Minor220,Minor221,Minor222,Minor223,Minor224,Minor225,Minor226,Minor227,Minor228,Minor229,Minor230,Minor231,Minor232,Minor233,Minor234,Minor235,Minor236,Minor237,Minor238,Minor239,Minor240,Minor241,Minor242,Minor243,Minor244,Minor245,Minor246,Minor247,Minor248,Minor249,Minor250,Minor251,Minor252,Minor253,Minor254,Minor255,Minor256,Minor257,Minor258,Minor259,Minor260\n", writeFile);

	for (int i = 0; i < readCellCount; i++) {
		char* accInterval = "accInterval\0";
		char* accXyz = "accXyz\0";
		char* magInterval = "magInterval\0";
		char* magXyz = "magXyz\0";
		char* gyroInterval = "gyroInterval\0";
		char* gyroXyz = "gyroXyz\0";
		char* beaconInterval = "beaconInterval\0";
		char* minor = "minor\0";
		char* rssi = "rssi\0";
		//     acc     /////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (strcmp(d_Array[i], accInterval) == 0) {
			for (int j = 0; j < timeCount; j++) {
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//인터벌이랑 time이 매칭될 때
					sprintf(buffer, "%f", xposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", yposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", zposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", velocityArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					trash = 0;
					break;
				}
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//인터벌이랑 time이 매칭되지 않을 때
					if (timeArray[j + 1] - atof(d_Array[i + 1]) > atof(d_Array[i + 1]) - timeArray[j]) {
						sprintf(buffer, "%f", xposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
					else {
						sprintf(buffer, "%f", xposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
				}
				else if (timeArray[j + 1] < timeArray[j]) {
					trash = 1;
					break;
				}
			}
		}
		if (trash == 0) {
			if (strcmp(d_Array[i], accXyz) == 0) {
				fputs(d_Array[i + 3], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 5], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 7], writeFile);
				fputs("\n", writeFile);
			}
		}

		//     mag     /////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (strcmp(d_Array[i], magInterval) == 0) {
			for (int j = 0; j < timeCount; j++) {
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//인터벌이랑 time이 매칭될 때
					sprintf(buffer, "%f", xposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", yposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", zposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", velocityArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					trash = 0;
					break;
				}
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//인터벌이랑 time이 매칭되지 않을 때 
					if (timeArray[j + 1] - atof(d_Array[i + 1]) > atof(d_Array[i + 1]) - timeArray[j]) {
						sprintf(buffer, "%f", xposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
					else {
						sprintf(buffer, "%f", xposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
				}
				else if (timeArray[j + 1] < timeArray[j]) {
					trash = 1;
					break;
				}
			}
		}
		if (trash == 0) {
			if (strcmp(d_Array[i], magXyz) == 0) {
				fputs(",,,,,,", writeFile);
				fputs(d_Array[i + 3], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 5], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 7], writeFile);
				fputs("\n", writeFile);
			}
		}
		

		//     gyro     /////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (strcmp(d_Array[i], gyroInterval) == 0) {
			for (int j = 0; j < timeCount; j++) {
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//인터벌이랑 time이 매칭될 때
					sprintf(buffer, "%f", xposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", yposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", zposArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					sprintf(buffer, "%f", velocityArray[j]);
					fputs(buffer, writeFile);
					memset(buffer, 0, sizeof(buffer));
					fputs(",", writeFile);
					trash = 0;
					break;
				}
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//인터벌이랑 time이 매칭되지 않을 때
					if (timeArray[j + 1] - atof(d_Array[i + 1]) > atof(d_Array[i + 1]) - timeArray[j]) {
						sprintf(buffer, "%f", xposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
					else {
						sprintf(buffer, "%f", xposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j + 1]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
				}
				else if (timeArray[j + 1] < timeArray[j]) {
					trash = 1;
					break;
				}
			}
		}
		if (trash == 0) {
			if (strcmp(d_Array[i], gyroXyz) == 0) {
				fputs(",,,", writeFile);
				fputs(d_Array[i + 3], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 5], writeFile);
				fputs(",", writeFile);
				fputs(d_Array[i + 7], writeFile);
				fputs("\n", writeFile);
			}
		}

		//     beacon     /////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (strcmp(d_Array[i], beaconInterval) == 0) {
			if (atoi(d_Array[i + 7]) == 1 && (atoi(d_Array[i + 9]) - 200 > 0 && atoi(d_Array[i + 9]) - 200 < 61)) {
				for (int j = 0; j < timeCount; j++) {
					if (atof(d_Array[i + 1]) == timeArray[j]) {		//인터벌이랑 time이 매칭될 때
						sprintf(buffer, "%f", xposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", yposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", zposArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						sprintf(buffer, "%f", velocityArray[j]);
						fputs(buffer, writeFile);
						memset(buffer, 0, sizeof(buffer));
						fputs(",", writeFile);
						trash = 0;
						break;
					}
					else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//인터벌이랑 time이 매칭되지 않을 때
						if (timeArray[j + 1] - atof(d_Array[i + 1]) > atof(d_Array[i + 1]) - timeArray[j]) {
							sprintf(buffer, "%f", xposArray[j]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", yposArray[j]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", zposArray[j]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", velocityArray[j]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							trash = 0;
							break;
						}
						else {
							sprintf(buffer, "%f", xposArray[j + 1]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", yposArray[j + 1]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", zposArray[j + 1]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							sprintf(buffer, "%f", velocityArray[j + 1]);
							fputs(buffer, writeFile);
							memset(buffer, 0, sizeof(buffer));
							fputs(",", writeFile);
							trash = 0;
							break;
						}
					}
					else if (timeArray[j + 1] < timeArray[j]) {
						trash = 1;
						break;
					}
				}
			}
		}
		if (trash == 0) {
			if (strcmp(d_Array[i], minor) == 0) {
				int minorDiff = atoi(d_Array[i + 1]) - 200;
				if (minorDiff > 0 && minorDiff < 61) {
					fputs(",,,,,,,,", writeFile);

					for(int i=1;i<=minorDiff;i++)
						fputs(",", writeFile);
				}
			}
			if (strcmp(d_Array[i], rssi) == 0) {
				if (atoi(d_Array[i - 3]) - 200 > 0 && atoi(d_Array[i - 3]) - 200 < 61) {
					fputs(d_Array[i + 1], writeFile);
					fputs("\n", writeFile);
				}
			}
		}
	}

	printf("readCellCount2 : %d\n", readCellCount);
	fclose(readFile);     // 파일 포인터 닫기
	printf("읽은 파일을 닫았습니다.\n");

	fclose(writeFile);     // 파일 포인터 닫기
	printf("쓴 파일을 닫았습니다.\n");

	fclose(timeFile);     // 파일 포인터 닫기
	fclose(velocityFile);     // 파일 포인터 닫기
	fclose(xposFile);     // 파일 포인터 닫기
	fclose(yposFile);     // 파일 포인터 닫기
	fclose(zposFile);     // 파일 포인터 닫기
	printf("좌표 및 시간 파일을 닫았습니다.\n");

	free(bufferToCountCell);   // 동적 메모리 해제
	free(bufferToPushData);   // 동적 메모리 해제
	free(bufferToCountTime);   // 동적 메모리 해제
	free(bufferToCountVelocity);   // 동적 메모리 해제
	free(bufferToCountXpos);   // 동적 메모리 해제
	free(bufferToCountYpos);   // 동적 메모리 해제
	free(bufferToCountZpos);   // 동적 메모리 해제
	free(d_Array);			   // 동적 메모리 해제
	printf("해제가 끝났습니다.\n");

	return 0;
}
#endif