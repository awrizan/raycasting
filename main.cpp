
// everything above the dashed line is the game setup


//game rules
#define SENSITIVITY 6
#define SPEED 0 //speed will be faster the smaller the number
#define PI 3.14159265
#define RAY_COUNT 60
//#define RAY_COUNT 90

//make a Loc map[100][100] and have your x and y points put in like map[y][x]



//------------------------------------------------------------------------------------------------------------------------------------//


//includes
#include <iostream>
#include <Windows.h>


struct Loc
{
	double x;
	double y;
};


//------------------------------------------------------------------------------------------------------------------------------------//


int main()
{

	HWND cmd = GetConsoleWindow();
	HDC dc = GetDC(cmd);

	Loc pos = { 5, 5 };

	bool map[1000][1000];

	//starting angle
	int angle = 90;


	double rad;

	double split = (RAY_COUNT / 2) * (PI / 180);

	
	//wall setup
	for (int i = 0; i < 20; i++) {
		map[50 + i][50] = true;
		map[50][50 + i] = false;
		map[50 + i][69] = true;
		map[69][50 + i] = false;
	}

	for (int i = 0; i < 20; i++) {
		map[20 + i][20] = true;
		map[20][20 + i] = false;
		map[20 + i][39] = true;
		map[39][20 + i] = false;
	}

	//starts game loop
	while (!(GetAsyncKeyState(0x51) & 0x8000)) {

		//left
		if ((GetAsyncKeyState(0x44) & 0x8000)) {
			if (angle >= 360) {
				angle = 1;
			}
			else {
				angle += 1*SENSITIVITY;
			}
			
			
		}

		//right
		if (GetAsyncKeyState(0x41) & 0x8000) {
			if (angle <= 1) {
				angle = 360;
			}
			else {
				angle -= 1*SENSITIVITY;
			}

			
		}

		rad = angle * (PI / 180);

		//backwards
		if (GetAsyncKeyState(0x57) & 0x8000) {
			pos.x += (cos(rad));
			pos.y += (sin(rad));

		}

		//forward
		if (GetAsyncKeyState(0x53) & 0x8000) {
			pos.x -= (cos(rad));
			pos.y -= (sin(rad));
			
		}

		//draws player + direction facing - debugging
		SetPixel(dc, static_cast<int>(pos.x), static_cast<int>(pos.y), RGB(0, 255, 0));


		

		int r = 0;
		for (int j = 0; j < RAY_COUNT; j++) {
			int dist = -1;
			

			for (int i = 0; i < 100 /*range*/; i++) {
				//SetPixel(dc, static_cast<int>(pos.x+(i*(cos(rad + ((j * (PI/180)) - split))))), static_cast<int>(pos.y+(i*(sin(rad + ((j * (PI / 180)) - split))))), RGB(0, 255, 0));
	
				if (map[static_cast<int>(pos.y + (i * (sin(rad + ((j * (PI / 180)) - split)))))][static_cast<int>(pos.x + (i * (cos(rad + ((j * (PI / 180)) - split)))))] == true) {
					//SetPixel(dc, static_cast<int>(pos.x + (i * (cos(rad + ((j * (PI / 180)) - split))))), static_cast<int>(pos.y + (i * (sin(rad + ((j * (PI / 180)) - split))))), RGB(255, 0, 0));
					r = 200;
					dist = i;
					break;
				}

				else if (map[static_cast<int>(pos.y + (i * (sin(rad + ((j * (PI / 180)) - split)))))][static_cast<int>(pos.x + (i * (cos(rad + ((j * (PI / 180)) - split)))))] == false) {
					r = 80;
					dist = i;
					break;
				}
				
			}

			//mitigate fisheye effect
			//100 - dist = wall size actual

			if (dist > -1) {
				//double dist2 = dist;
				
				double dist2 = dist *cos(rad/(j+8) );
					
				
				

				for (int i = 0; i < 100 -dist2; i++) {


					// i - (100 - dist) / 2
					SetPixel(dc, 600 + j * 2, 200 + (i-(100-dist2)/2) , RGB(int(r-(dist/10)), int(r-(dist/10)),int(r-(dist/10))));
					

				}
			}
			if(dist == 0){
				pos.x -= (cos(rad));
				pos.y -= (sin(rad));
			}
		}
		


		
		std::cout << pos.x << " " << pos.y << std::endl;

		std::cout << angle << std::endl;

		Sleep(SPEED);

		//refreshes frame
		system("cls");
		


	}


	ReleaseDC(cmd, dc);

	system("pause");
	return 0;
}
