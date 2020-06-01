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
4. 배경음악이 끝날때 callback으로 다시 실행시키고 싶은데 방법을 모르겠다
5. 과일별 출현 확률 수정
=========================================================================*/

													
#include <stdio.h>
#include <bangtal.h>
#include <time.h>
#include <stdlib.h>

#define APPLE 0
#define GRAPE 1 
#define ORANGE 2

#define ANIMATION_TIME		2

ObjectID fruitA[3], fruitB[3], fruitC[3];
int num1, num2, num3;

SceneID scene1;
ObjectID machine;

TimerID timer;

SoundID bgm, coin, win;

void Gameinit() { 

	scene1 = createScene("바탕화면", "고쳐야 됨!.png"); // 카지노 바탕화면 필요할듯
	machine = createObject("machine.png");
	locateObject(machine, scene1, 350, 250);
	showObject(machine);

	//슬롯머신에 사용되는 과일들 생성 후 배열에 넣어 사용
	char fruitImage[20];
	for (int i = 0; i < 3; i++) {
		sprintf_s(fruitImage, "fruitA%d.png", i);
		sprintf_s(fruitImage, "fruitB%d.png", i);
		sprintf_s(fruitImage, "fruitC%d.png", i);
		fruitA[i] = createObject(fruitImage);
		fruitB[i] = createObject(fruitImage);
		fruitC[i] = createObject(fruitImage);
	}

	bgm = createSound("casinoBackground.wav");
	playSound(bgm);

	coin = createSound("coinEffect.wav");

	win = createSound("win.mp3");
}

void timerCallback(TimerID timer)
{
	setTimer(timer, ANIMATION_TIME);
	startTimer(timer);
}

int slotA() {  //slotB에 무작위 과일에 해당하는 난수를 생성한다
	num1 = rand() % 3;
	return num1;
}

int slotB() { //slotB에 무작위 과일에 해당하는 난수를 생성한다
	num2 = rand() % 3;
	return num2;
}

int slotC() { //slotB에 무작위 과일에 해당하는 난수를 생성한다
	num3 = rand() % 3;
	return num3;
}

void Roulette() {
	for (int i = 0; i < 3; i++) { // 화면에 보이는 카지노 슬롯 초기화
		hideObject(fruitA[i]);
		hideObject(fruitB[i]);
		hideObject(fruitC[i]);
	}

	int xLocate[3] = { 380, 540, 700 };

	locateObject(fruitA[slotA()], scene1, xLocate[0], 300); // A 슬롯에 무작위 과일 이미지를 화면에 출력한다
	showObject(fruitA[num1]);
	
	locateObject(fruitB[slotB()], scene1, xLocate[1], 300); // B 슬롯에 무작위 과일 이미지를 출력한다 
	showObject(fruitB[num2]);

	locateObject(fruitC[slotC()], scene1, xLocate[2], 300); // C 슬롯에 무작위 과일 이미지를 출력한다
	showObject(fruitC[num3]);

	}
 

void keyboardCallback(KeyCode code, KeyState state)
{

	if (code == 84 && state == KeyState::KEYBOARD_PRESSED) { // up 버튼을 누를 때 코인 효과음이 나온다.
		playSound(coin);

	}

	if (code == 84 && state == KeyState::KEYBOARD_RELEASED) { //up 버튼을 땔 때 룰렛이 작동한다.
		Roulette();
		if (num1 == num2 && num2 == num3 && num3 == APPLE) { // 사과 세개가 나올 경우
			showMessage("+5원");
			playSound(win);
		}

		else if (num1 == num2 && num2 == num3 && num3 == GRAPE ) { // 포도 세개가 나올 경우
			showMessage("+10원");
			playSound(win);
		}

		else if (num1 == num2 && num2 == num3 && num3 == ORANGE) { // 오렌지 세개가 나올 경우
			showMessage("+20원");
			playSound(win);
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