#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define EASY_SIZE 3
#define NORMAL_SIZE 4
#define HARD_SIZE 5
#define VERY_HARD_SIZE 7
#define TIME_SIZE 15

#define INFINITY_MAX_NUMBER 6
#define TIME_MAX_NUMBER 10
#define TIME_LIMIT 5

void intro_game(void);

int select_mode(void);

void time_intro(void);
void time_game_control(void);
void time_print_number(int n, int cnt[]);

void Infinity_intro(void);
int Infinity_select_difficulty(void);
void Infinity_game_control(int matrixSize, int* score);
void infinity_print_number(int n, int cnt[]);

int find_num(int cnt[]);

int main(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x00 | 0x70);
    
    srand(time(NULL));
    int score = 0; // 정답 횟수를 저장할 변수 추가
    intro_game();
    select_mode();

    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void intro_game(void) {
    system("cls");
    gotoxy(10, 5); // 텍스트를 원하는 위치로 이동
    printf("=== 숫자 맞추기 게임 ===\n");
    gotoxy(10, 7);
    printf("정방행렬에 나타난 숫자 중에서\n");
    gotoxy(10, 8);
    printf("가장 많이 출현한 숫자를 찾아라!\n\n");
    gotoxy(10, 10);
    printf("아무 키나 누르면 시작합니다. \n");
    getch();
}

int select_mode(void) {
   	int choice;
    int matrixSize;
    int score = 0;

    system("cls");
    gotoxy(10, 5); // 텍스트를 원하는 위치로 이동
    printf("=== 모드 선택 ===\n");
    gotoxy(10, 7);
    printf("1. Time Attack Mode\n");
    gotoxy(10, 8);
    printf("2. Infinity Mode\n");
    gotoxy(10, 10);
    printf("=== 1,2 이외의 키는 게임이 종료됩니다 ===");
    gotoxy(10, 13); 
    printf("모드를 선택하세요 (1-2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Time Attack 모드 선택
            time_intro();
            time_game_control();
            break;
        case 2:
            // Infinity 모드 선택
            matrixSize = Infinity_select_difficulty();
            Infinity_intro();
            while (1) // 무한 루프를 사용하여 게임을 반복 실행
            {
                Infinity_game_control(matrixSize, &score);
            }
            break;
        default:
        	printf("게임을 종료합니다.");
        	Beep(0,500); 
            // 기본값으로 게임 종료
            exit(0);
    }
}

void time_intro(void) {
    system("cls");
    gotoxy(10, 5); // 텍스트를 원하는 위치로 이동
    printf("=== Time Attack Mode ===\n");
    gotoxy(10, 7);
    printf("15 * 15 행렬에서\n");
    gotoxy(10, 8);
    printf("가장 많이 출현한 숫자를 찾아라!\n\n");
    gotoxy(10, 10);
    printf("제한시간은 없고 숫자는 0 ~ 9 까지 있습니다.\n\n");
    gotoxy(10, 12);
    printf("아무 키나 누르면 시작합니다. \n");
    getch();
}

void time_game_control(void)
{
	double C4 = 261.63;  // 도
    double E4 = 329.63;  // 미
    double G4 = 392.00;  // 솔
    int cnt[TIME_MAX_NUMBER], answer, user, chances = 2;
    clock_t start, end;
    double pst;
    int correct = 0; // 정답 여부를 나타내는 변수 추가

    system("cls");
    time_print_number(TIME_SIZE, cnt);
    answer = find_num(cnt);
    printf("\n\n");
    printf("출현횟수가 가장 많은 숫자 입력>");
    start = clock();
    while (!kbhit())
    {
        end = clock();
        pst = (double)(end - start) / CLOCKS_PER_SEC;
    }

    user = getch() - '0';
    
    // 정답을 입력받을 때까지 기회를 주며, 기회가 남아있을 경우 계속 반복합니다.
    while (chances > 0)
    {
        if (user == answer)
        {
    		Beep((int)C4, 500);
    		Beep((int)E4, 500);
    		Beep((int)G4, 500);
            printf("\n\n맞았습니다 ^.^ \n");
            printf("입력한 숫자 : %d \n", user);
            printf("정답 숫자: %d\n", answer);
            printf("정답 숫자의 출현 횟수: %d\n", cnt[answer]);
            printf("정답을 입력받는데 걸린 시간: %.2f 초\n", pst);
            correct = 1;
            break;
        }
        else
        {
            chances--;
            if (chances > 0)
            {
            	printf("입력한 숫자 : %d \n", user);
                printf("\n틀렸습니다 T_T. 다시 입력하세요. 남은 기회: %d\n", chances);
                Beep((int)C4, 500);
                user = getch() - '0';
            }
            else
            {
            	printf("입력한 숫자 : %d \n", user);
                printf("\n틀렸습니다 T_T. 기회를 모두 사용하셨습니다. Game Over\n");
                Beep((int)C4, 500);
                printf("아무 키나 누르면 모드 선택화면으로 돌아갑니다. \n");
                getch();
                select_mode();
            }
        }
    }

    if (correct)
    {
        printf("아무 키나 누르면 모드 선택화면으로 돌아갑니다. \n");
        getch();
        select_mode();
    }
}

void Infinity_intro(void) {
    system("cls");
    gotoxy(10, 5); // 텍스트를 원하는 위치로 이동
    printf("=== Infinity Mode ===\n");
    gotoxy(10, 7);
    printf("선택한 난이도에서\n");
    gotoxy(10, 8);
    printf("가장 많이 출현한 숫자를 찾아라!\n\n");
    gotoxy(10, 10);
    printf("각 행렬당 제한시간은 5초이고, 숫자는0 ~ 5까지 있습니다.\n\n");
    gotoxy(10, 12);
    printf("아무 키나 누르면 시작합니다. \n");
    getch();
}

int Infinity_select_difficulty(void)
{
    int choice;
    system("cls");
    gotoxy(10, 4);
    printf("=== Infinity Mode ===\n");
    gotoxy(10, 5);
    printf("=== 난이도 선택 ===\n");
    gotoxy(10, 7);
    printf("1. Easy (3x3)\n");
    gotoxy(10, 8);
    printf("2. Normal (4x4)\n");
    gotoxy(10, 9);
    printf("3. Hard (5x5)\n");
    gotoxy(10, 10);
    printf("4. Very Hard (7x7)\n");
    gotoxy(10, 11);
    printf("1~4 의외의 값은 Normal로 선택됩니다\n");
    gotoxy(10, 12);
    printf("난이도를 선택하세요 (1-4): ");
    scanf("%d", &choice);

    int matrixSize; // 선택한 난이도에 따른 행렬 크기
    switch (choice)
    {
    case 1:
        matrixSize = EASY_SIZE;
        break;
    case 2:
        matrixSize = NORMAL_SIZE;
        break;
    case 3:
        matrixSize = HARD_SIZE;
        break;
    case 4:
        matrixSize = VERY_HARD_SIZE;
        break;
    default:
        matrixSize = NORMAL_SIZE; // 기본은 Normal 난이도로 설정
        break;
    }

    return matrixSize;
}

void Infinity_game_control(int matrixSize, int* score)
{
	double C4 = 261.63;  // 도
    double E4 = 329.63;  // 미
    double G4 = 392.00;  // 솔

    int cnt[INFINITY_MAX_NUMBER], answer[INFINITY_MAX_NUMBER], user;
    int num_of_answers = 0; // 정답 숫자의 개수
    clock_t start, end;
    double pst;
    int correct = 0; // 정답 여부를 나타내는 변수 추가

    system("cls");
    infinity_print_number(matrixSize, cnt);
    printf("\n\n");
    printf("출현횟수가 가장 많은 숫자 입력>");

    // 정답 숫자들을 찾아 배열에 저장
    int max_num = 0;
    for (int i = 0; i < INFINITY_MAX_NUMBER; i++) {
        if (cnt[i] > max_num) {
            max_num = cnt[i];
            num_of_answers = 0;
            answer[num_of_answers++] = i;
        } else if (cnt[i] == max_num) {
            answer[num_of_answers++] = i;
        }
    }

    start = clock();
    while (!kbhit()) {
        end = clock();
        pst = (double)(end - start) / CLOCKS_PER_SEC;
        if (TIME_LIMIT < pst) {
            printf("\n제한시간을 넘었습니다. Game Over\n");
            printf("\n================================\n\n");
            Beep((int)C4, 500);
            printf("정답 횟수: %d\n", *score);
            exit(0);
        }
    }
    user = getch() - '0';

    // 모든 일치하는 숫자를 검사
    for (int i = 0; i < num_of_answers; i++) {
        if (user == answer[i]) { 	
		    Beep((int)C4, 500);
		    Beep((int)E4, 500);
		    Beep((int)G4, 500);
            printf("\n\n맞았습니다 ^.^ \n");
            printf("\n================================\n");
            printf("입력한 숫자 : %d \n", user);
            printf("번호: ");
            for (int j = 0; j < num_of_answers; j++) {
                printf("%d ", answer[j]);
            }
            printf("\n================================\n");
            printf("\n횟수 : %d\n", cnt[answer[0]]);
            printf("아무 키나 누르면 다음 문제로 이동합니다. \n");
            getch();
            (*score)++; // 정답 횟수 증가
            correct = 1;
            break; // 정답을 찾았으므로 루프 종료
        }
    }

    if (!correct) {
        printf("\n\n틀렸습니다 T_T \n");
        printf("\n================================\n");
        printf("Game Result 정답 횟수: %d\n", *score);
        printf("\n================================\n");
        printf("입력한 숫자 : %d \n", user);
        printf("번호: ");
        for (int i = 0; i < num_of_answers; i++) {
            printf("%d ", answer[i]);
        }
        printf("\n횟수 : %d\n", cnt[answer[0]]);
        printf("================================\n");
        Beep((int)C4, 1000);
        printf("아무 키나 누르면 모드 선택화면으로 돌아갑니다. \n");
        getch();
        select_mode();
    }
}

void infinity_print_number(int n, int cnt[])
{
    int i, j, r_num;
    for (i = 0; i < INFINITY_MAX_NUMBER; i += 1)
        cnt[i] = 0;
    for (i = 1; i <= n; i += 1)
    {
        for (j = 1; j <= n; j += 1)
        {
            r_num = rand() % INFINITY_MAX_NUMBER;
            cnt[r_num] += 1;
            printf("%d  ", r_num);
        }
        printf("\n");
    }
}

void time_print_number(int n, int cnt[])
{
    int i, j, r_num;
    for (i = 0; i < TIME_MAX_NUMBER; i += 1)
        cnt[i] = 0;
    for (i = 1; i <= n; i += 1)
    {
        for (j = 1; j <= n; j += 1)
        {
            r_num = rand() % TIME_MAX_NUMBER;
            cnt[r_num] += 1;
            printf("%d  ", r_num);
        }
        printf("\n");
    }
}

int find_num(int cnt[])
{
    int i, check, max_num = 0;
    for (i = 0; i < INFINITY_MAX_NUMBER; i += 1)
    {
        if (max_num <= cnt[i])
        {
            max_num = cnt[i];
            check = i;
        }
    }
    return check;
}
