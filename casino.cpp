/* ======================================================================
카지노 슬롯머신 

가격표
게임 플레이 비용 -1원
사과 x 3 이면 +5원
포도 x 3 이면 +10원
오렌지 x 3 이면 +20원

향후 필요한 것: 
1. 키보드 입력을 스페이스로 교체
2. money를 모든 씬과 연동해야함
//3. 이미지 필요: 슬롯 머신 옆에 가격표
5. 과일별 출현 확률 수정? 이를테면 사과>포도>오렌지 순으로 출현하게
=========================================================================*/

													
#include <stdio.h>
#include <bangtal.h>
#include <time.h>
#include <stdlib.h>

#define APPLE 0
#define GRAPE 1 
#define ORANGE 2

const Second animationTime = 0.05f; // 물음표가 화면에 출력되는 시간 간격

ObjectID fruitA[3], fruitB[3], fruitC[3];
int num1, num2, num3;

SceneID scene1;
ObjectID questionMark, machine;

TimerID timer;

SoundID bgm, coin, win;

int spin = 0;

bool game = 0; // 0은 스핀이 멈춘 상태, 1은 스핀이 돌아가고 있는 상태 

int xLocate[3] = { 430, 580, 730 }; // 카지노 A B C 슬롯의 x좌표값

void Gameinit() { 

	scene1 = createScene("카지노", "background.png"); 
	machine = createObject("machine.png");
	locateObject(machine, scene1, 260, 25);
	scaleObject(machine, 2.5f);
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

	coin = createSound("coinEffect.wav"); // 동전 투입 효과음

	questionMark = createObject("questionMark.png"); 

	win = createSound("win.mp3"); // 과일 세개가 일치할 때의 효과음

	timer = createTimer(600.0f);
	
}

int slotA() {  //slotA에 무작위 과일에 해당하는 난수를 생성한다
	num1 = rand() % 3;
	return num1;
}

int slotB() { //slotB에 무작위 과일에 해당하는 난수를 생성한다
	num2 = rand() % 3;
	return num2;
}

int slotC() { //slotC에 무작위 과일에 해당하는 난수를 생성한다
	num3 = rand() % 3;
	return num3;
}



void Roulette() {

	game = 0; // 스핀이 멈췄음

	locateObject(fruitA[slotA()], scene1, xLocate[0], 310); // 난수를 이어 받아 A 슬롯에 과일 이미지를 출력한다
	showObject(fruitA[num1]);						   
													  
	locateObject(fruitB[slotB()], scene1, xLocate[1], 310); // 난수를 이어 받아 B 슬롯에 과일 이미지를 출력한다 
	showObject(fruitB[num2]);						  
													  
	locateObject(fruitC[slotC()], scene1, xLocate[2], 310); // 난수를 이어 받아  C 슬롯에 과일 이미지를 출력한다
	showObject(fruitC[num3]);

	if (num1 == num2 && num2 == num3 && num3 == APPLE) { // 사과 세개가 나올 경우 효과음 재생
		showMessage("+5원");
		playSound(win);
	}

	else if (num1 == num2 && num2 == num3 && num3 == GRAPE) { // 포도 세개가 나올 경우 효과음 재생
		showMessage("+10원");
		playSound(win);
	}

	else if (num1 == num2 && num2 == num3 && num3 == ORANGE) { // 오렌지 세개가 나올 경우 효과음 재생
		showMessage("+20원");
		playSound(win);
	}

	else { // 게임 비용
		showMessage("-1원");
	}

}
	 
void Spin() { // 물음표가 슬롯 A B C에 시간 간격을 두고 차례대로 생성됨 (룰렛 스핀)

	game = 1; // 스핀이 돌아가는 중

		for (int i = 0; i < 3; i++) { // 화면에 보이는 카지노 슬롯 초기화
			hideObject(fruitA[i]);
			hideObject(fruitB[i]);
			hideObject(fruitC[i]);
		}

		spin = spin + 30; // 물음표 애니메이션 시간 간격 조정

		//애니메이션
		if (spin < 100) {
			hideObject(questionMark);
			showObject(questionMark);
			locateObject(questionMark, scene1, xLocate[0], 300);
			setTimer(timer, animationTime);
			startTimer(timer);


		}
		else if (spin > 100 && spin < 200) {
			hideObject(questionMark);
			locateObject(questionMark, scene1, xLocate[1], 300);
			showObject(questionMark);
			setTimer(timer, animationTime);
			startTimer(timer);
		}

		else if (spin > 200 && spin <= 300) {
			hideObject(questionMark);
			locateObject(questionMark, scene1, xLocate[2], 300);
			showObject(questionMark);
			setTimer(timer, animationTime);
			startTimer(timer);
		}

		else {
			hideObject(questionMark);
			Roulette(); // 슬롯 C에 물음표가 출력 된 후에 무작위 과일들이 화면에 나타남
		}
}
	

void timerCallback(TimerID timer)
{
	if (timer == timer) { 
		Spin();
	}

}
	

void keyboardCallback(KeyCode code, KeyState state)
{

	if (game == 0 && code == 84 && state == KeyState::KEYBOARD_PRESSED) { // 스핀이 멈췄을때 up 버튼을 누르면 룰렛이 스핀한다.
		
		spin = 0; 
		Spin();
		playSound(coin);
	}
	
}


int main() {
	
	setKeyboardCallback(keyboardCallback);
	setTimerCallback(timerCallback);
	srand((unsigned int)time(NULL));
	Gameinit();
	
	startGame(scene1);

}