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
		printf("���� ������ �� �� �����ϴ�. \n");
	else
		printf("���� ������ �������ϴ�.\n");

	if (writeFile == NULL) 
		printf("�� ������ �� �� �����ϴ�.\n");
	else 
		printf("�� ������ �������ϴ�.\n");
	
	if (timeFile == NULL || velocityFile == NULL || xposFile == NULL|| yposFile == NULL|| zposFile == NULL) 
		printf("��ǥ �� �ӵ� Ȥ�� �ð� ������ �� �� �����ϴ�.\n");
	else 
		printf("��ǥ �� �ӵ� Ȥ�� �ð� ������ �������ϴ�.\n");
	
	fseek(readFile, 0, SEEK_END);		//���� �����͸� ���� ������ �̵���Ŵ
	fseek(timeFile, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
	fseek(velocityFile, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
	fseek(xposFile, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
	fseek(yposFile, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
	fseek(zposFile, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ

	readFileSize = ftell(readFile);			// ���� �������� ���� ��ġ�� ����
	timeSize = ftell(timeFile);          // ���� �������� ���� ��ġ�� ����
	velocitySize = ftell(velocityFile);          // ���� �������� ���� ��ġ�� ����
	xposSize = ftell(xposFile);          // ���� �������� ���� ��ġ�� ����
	yposSize = ftell(yposFile);          // ���� �������� ���� ��ġ�� ����
	zposSize = ftell(zposFile);          // ���� �������� ���� ��ġ�� ����

	bufferToCountCell = malloc(readFileSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountCell, 0, readFileSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToPushData = malloc(readFileSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToPushData, 0, readFileSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToCountTime = malloc(timeSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountTime, 0, timeSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToCountVelocity = malloc(velocitySize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountVelocity, 0, velocitySize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToCountXpos = malloc(xposSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountXpos, 0, xposSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToCountYpos = malloc(yposSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountYpos, 0, yposSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ
	bufferToCountZpos = malloc(zposSize + 1);    // ���� ũ�� + 1����Ʈ(���ڿ� �������� NULL)��ŭ ���� �޸� �Ҵ�
	memset(bufferToCountZpos, 0, zposSize + 1);  // ���� ũ�� + 1����Ʈ��ŭ �޸𸮸� 0���� �ʱ�ȭ

	fseek(readFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountCell, readFileSize, 1, readFile);    // csv ���� ũ�⸸ŭ ���� ����
	fseek(timeFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountTime, timeSize, 1, timeFile);    // csv ���� ũ�⸸ŭ ���� ����
	fseek(velocityFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountVelocity, velocitySize, 1, velocityFile);    // csv ���� ũ�⸸ŭ ���� ����
	fseek(xposFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountXpos, xposSize, 1, xposFile);    // csv ���� ũ�⸸ŭ ���� ����
	fseek(yposFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountYpos, yposSize, 1, yposFile);    // csv ���� ũ�⸸ŭ ���� ����
	fseek(zposFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToCountZpos, zposSize, 1, zposFile);    // csv ���� ũ�⸸ŭ ���� ����

	char* timePtr = strtok(bufferToCountTime, "\n");      // " " �� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (timePtr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		timeArray[timeCount] = atof(timePtr);
		timeCount++;
		timePtr = strtok(NULL, "\n");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	char* velocityPtr = strtok(bufferToCountVelocity, "\n");      // " " �� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (velocityPtr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		velocityArray[velocityCount] = atof(velocityPtr);
		velocityCount++;
		velocityPtr = strtok(NULL, "\n");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	char* XposPtr = strtok(bufferToCountXpos, "\n");      // " "�� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (XposPtr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		xposArray[xposCount] = atof(XposPtr);
		xposCount++;
		XposPtr = strtok(NULL, "\n");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}
	
	char* YposPtr = strtok(bufferToCountYpos, "\n");      // " " �� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (YposPtr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		yposArray[yposCount] = atof(YposPtr);
		yposCount++;
		YposPtr = strtok(NULL, "\n");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}


	char* ZposPtr = strtok(bufferToCountZpos, "\n");      // " "�� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (ZposPtr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		zposArray[zposCount] = atof(ZposPtr);
		zposCount++;
		ZposPtr = strtok(NULL, "\n");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}
	
	char* ptr = strtok(bufferToCountCell, ",");      // " "�� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (ptr != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		readCellCount++;
		ptr = strtok(NULL, ",");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
	}

	int** d_Array = malloc(sizeof(int*) * readCellCount);

	for (int i = 0; i < readCellCount; i++) {
		d_Array[i] = malloc(sizeof(int) * readCellCount);
	}
	printf("readCellCount1 : %d\n", readCellCount);

	readCellCount = 0;

	fseek(readFile, 0, SEEK_SET);                // ���� �����͸� ������ ó������ �̵���Ŵ
	fread(bufferToPushData, readFileSize, 1, readFile);    // csv ���� ũ�⸸ŭ ���� ����

	char* ptr2 = strtok(bufferToPushData, ",");      // " "�� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (ptr2 != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		d_Array[readCellCount] = ptr2;
		readCellCount++;
		ptr2 = strtok(NULL, ",");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
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
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//���͹��̶� time�� ��Ī�� ��
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
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//���͹��̶� time�� ��Ī���� ���� ��
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
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//���͹��̶� time�� ��Ī�� ��
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
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//���͹��̶� time�� ��Ī���� ���� �� 
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
				if (atof(d_Array[i + 1]) == timeArray[j]) {		//���͹��̶� time�� ��Ī�� ��
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
				else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//���͹��̶� time�� ��Ī���� ���� ��
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
					if (atof(d_Array[i + 1]) == timeArray[j]) {		//���͹��̶� time�� ��Ī�� ��
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
					else if (timeArray[j] < atof(d_Array[i + 1]) && timeArray[j + 1] > atof(d_Array[i + 1])) {				//���͹��̶� time�� ��Ī���� ���� ��
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
	fclose(readFile);     // ���� ������ �ݱ�
	printf("���� ������ �ݾҽ��ϴ�.\n");

	fclose(writeFile);     // ���� ������ �ݱ�
	printf("�� ������ �ݾҽ��ϴ�.\n");

	fclose(timeFile);     // ���� ������ �ݱ�
	fclose(velocityFile);     // ���� ������ �ݱ�
	fclose(xposFile);     // ���� ������ �ݱ�
	fclose(yposFile);     // ���� ������ �ݱ�
	fclose(zposFile);     // ���� ������ �ݱ�
	printf("��ǥ �� �ð� ������ �ݾҽ��ϴ�.\n");

	free(bufferToCountCell);   // ���� �޸� ����
	free(bufferToPushData);   // ���� �޸� ����
	free(bufferToCountTime);   // ���� �޸� ����
	free(bufferToCountVelocity);   // ���� �޸� ����
	free(bufferToCountXpos);   // ���� �޸� ����
	free(bufferToCountYpos);   // ���� �޸� ����
	free(bufferToCountZpos);   // ���� �޸� ����
	free(d_Array);			   // ���� �޸� ����
	printf("������ �������ϴ�.\n");

	return 0;
}
#endif