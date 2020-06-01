/* ======================================================================
카지노 슬롯머신 
6월 1일 기준 :: up 버튼을 누르면 슬롯머신이 동작하고 화면에 과일들이 나타난다. 과일 세개가 일치하면 돈을 획득한다.

가격표
게임 플레이 비용 -1원
사과 x 3 이면 +5원
포도 x 3 이면 +10원
오렌지 x 3 이면 +20원

향후 필요한 것: 
1. 키보드 입력을 스페이스로 교체
2. money를 모든 씬과 연동해야함
3. 이미지 필요: 슬롯 머신 뒷 배경/ 가격표
4. 배경음악 및 효과음 삽입하기
5. 필요하다면? 애니메이션 넣기
6. 필요하다면? 카지노 게임 더 추가하기 (ex. 주사위 게임 )
=========================================================================*/

													
#include <stdio.h>
#include <bangtal.h>
#include <time.h>
#include <stdlib.h>

#define ANIMATION_TIME		2

ObjectID fruit[9];
SceneID scene1;
ObjectID machine;

TimerID timer;

int num1, num2, num3;


void Gameinit() {

	scene1 = createScene("바탕화면", "고쳐야 됨!.png"); // 카지노 바탕화면 필요할듯
	machine = createObject("machine.png");
	locateObject(machine, scene1, 350, 250);
	showObject(machine);

	//object를 배열화
	char fruitImage[30];
	for (int i = 0; i < 9; i++) {
		sprintf_s(fruitImage, "fruit%d.png", i);
		fruit[i] = createObject(fruitImage);
	}

}

void timerCallback(TimerID timer)
{
	setTimer(timer, ANIMATION_TIME);
	startTimer(timer);
}


int slot1() {
	
	num1 = rand() % 3;
	return num1;
}

int slot2() {

	num2 = rand() % 3 + 3;
	return num2;
}

int slot3() {

	num3 = rand() % 3 + 6;
	return num3;
}


void Roulette() {

	for (int i = 0; i < 9; i++) { // 카지노 슬롯 초기화
		hideObject(fruit[i]);
	}

	int xLocate[3] = { 380, 540, 700 };

	locateObject(fruit[slot1()], scene1, xLocate[0], 300); // slot1
	showObject(fruit[num1]);
	
	locateObject(fruit[slot2()], scene1, xLocate[1], 300); // slot2
	showObject(fruit[num2]);

	locateObject(fruit[slot3()], scene1, xLocate[2], 300); // slot3
	showObject(fruit[num3]);

	}

void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == 84 && state == KeyState::KEYBOARD_PRESSED) {		//up 버튼 클릭시
		Roulette();
		if ((num1 + 3) == num2 && num2 == (num3 - 3) && num2 == 3) { // 사과 세개가 나올 경우
			showMessage("+5원");
		}

		else if ((num1 + 3) == num2 && num2 == (num3 - 3) && num2 == 4 ) { // 포도 세개가 나올 경우
			showMessage("+10원");
		}

		else if ((num1 + 3) == num2 && num2 == (num3 - 3) && num2 == 5) { // 오렌지 세개가 나올 경우
			showMessage("+20원");
		}

		else { 
			showMessage("-1원"); 
		}

	}
		
}

int main() {

	setKeyboardCallback(keyboardCallback);
	setTimerCallback(timerCallback);
	srand((unsigned int)time(NULL));
	Gameinit();
	
	TimerID timer = createTimer(ANIMATION_TIME);
	startTimer(timer);


	startGame(scene1);


}