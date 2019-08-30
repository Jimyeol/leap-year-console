#include <stdio.h>
#include "Windows.h"

#define YEAR 365
#define LEAPYEAR 0
#define NORMALYEAR 1
#define MONTH 12
enum
{
	MON = 1,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN,
};
enum
{
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC,
};

void DrawCal( int nYear, int nAcc, int bSelectYear);
int JudgeMoon( int nMoon, int bSelectYear);

int main()
{
	int m_nYear				= 0;		//입력 받은 년도
	int m_nAcc				= 0;		//총 일수
	float m_nLeapYear		= 0.f;		//윤년
	float m_nNLYear			= 0.f;		//평년인데 윤년인거
	float m_nNormalYear		= 0.f;		//평년
	int	m_bSelectYear		= 0;		//평년인지 윤년인지 확인
	

	printf("Enter the year : ");
	scanf("%d", &m_nYear);
	fflush(stdin);						//버퍼비우기


	m_nLeapYear				= m_nYear / 4.f;		//윤년 빼줘야 할것
	m_nNormalYear			= m_nYear / 100.f;	//평년 뺴줘야 할것
	m_nNLYear				= m_nYear / 400.f;		//더해 줘야할 평년인데 윤년인거
	m_nAcc					= ((m_nYear*YEAR) + (int)((m_nLeapYear + m_nNLYear) - m_nNormalYear)); //총 일수 계산.

	//printf("%d\n : ", m_nAcc);
	//printf("%d\n : ", m_nAcc%7);
	m_bSelectYear	= ((m_nYear % 4 == 0) && (m_nYear % 100 != 0 || m_nYear % 400 == 0)) ? LEAPYEAR : NORMALYEAR;
	//윤년 평년 비교연산


	DrawCal(m_nYear, m_nAcc, m_bSelectYear);		//달력 그래픽을 디자인하기 위한 함수

	system("pause");
	return 0;
}

void DrawCal( int nYear, int nAcc, int bSelectYear)
{
	int m_nYear				= nYear;		//현재 년도
	int m_nStartYo			= nAcc%7;		//현재 년도 1월달 시작하는 요일
	int m_nStartIl			= nAcc ;		//지금까지 총 일수
	int m_nbSelectYear		= bSelectYear;	//윤년인지 평년인지 확인하는 변수
	char m_cInput			= 0;


	//printf("%d\n", m_nStartYo);

	for(int cal = 1; cal <= MONTH; cal++)
	{
		printf("엔터 누르세요.<Enter/q> : ");
		scanf("%c", &m_cInput);
		fflush(stdin);

		if( m_cInput == 10 )
		{


			printf("%d년 %d월\n", m_nYear, cal);
			printf(" Sun Mon Tue Wen Thu Fri Sat\n");


			for( int j = 0; j < m_nStartYo; j++)		//맨 처음 요일부터 시작하기 위해 공백을 넣기 위한 반복문
			{
				printf("    ");		//공백 삽입
			}


			for(int i = 1+m_nStartYo; i <= JudgeMoon(cal, m_nbSelectYear)+m_nStartYo; i++)
			{
				//JudgeMoon함수 = 31일 30일 28일 29일인지 판별하여 대입하기 위한 함수
				printf("%4d", i-m_nStartYo);

				if( i % 7 == 0)		//일주일이 되면 라인을 띄운다.
					printf("\n");

			}
			printf("\n");

			m_nStartIl			+= JudgeMoon(cal, m_nbSelectYear);		//현재 출력한 달의 일수를 총 일수에 더 더한다
			m_nStartYo			= m_nStartIl%7;					//그리고 언제부터 시작하는지 다시 초기화를 한다.


		}
		else if( m_cInput == 113 )
			return;
	}

}

int JudgeMoon( int nMoon, int bSelectYear)
{
	int m_nMoon				= nMoon;
	int m_nbSelectYear		= bSelectYear;

	switch( m_nMoon )
	{
	case JAN:
	case MAR:
	case MAY:
	case JUL:
	case AUG:
	case OCT:
	case DEC:
		return 31;
		break;
	case APR:
	case JUN:
	case SEP:
	case NOV:
		return 30;
		break;
	case FEB:
		if( m_nbSelectYear == LEAPYEAR )		//윤년이면 29일을 반환한다.
			return 29;
		else
			return 28;
		break;
	}
}