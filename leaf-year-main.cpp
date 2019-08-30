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
	int m_nYear				= 0;		//�Է� ���� �⵵
	int m_nAcc				= 0;		//�� �ϼ�
	float m_nLeapYear		= 0.f;		//����
	float m_nNLYear			= 0.f;		//����ε� �����ΰ�
	float m_nNormalYear		= 0.f;		//���
	int	m_bSelectYear		= 0;		//������� �������� Ȯ��
	

	printf("Enter the year : ");
	scanf("%d", &m_nYear);
	fflush(stdin);						//���ۺ���


	m_nLeapYear				= m_nYear / 4.f;		//���� ����� �Ұ�
	m_nNormalYear			= m_nYear / 100.f;	//��� ����� �Ұ�
	m_nNLYear				= m_nYear / 400.f;		//���� ����� ����ε� �����ΰ�
	m_nAcc					= ((m_nYear*YEAR) + (int)((m_nLeapYear + m_nNLYear) - m_nNormalYear)); //�� �ϼ� ���.

	//printf("%d\n : ", m_nAcc);
	//printf("%d\n : ", m_nAcc%7);
	m_bSelectYear	= ((m_nYear % 4 == 0) && (m_nYear % 100 != 0 || m_nYear % 400 == 0)) ? LEAPYEAR : NORMALYEAR;
	//���� ��� �񱳿���


	DrawCal(m_nYear, m_nAcc, m_bSelectYear);		//�޷� �׷����� �������ϱ� ���� �Լ�

	system("pause");
	return 0;
}

void DrawCal( int nYear, int nAcc, int bSelectYear)
{
	int m_nYear				= nYear;		//���� �⵵
	int m_nStartYo			= nAcc%7;		//���� �⵵ 1���� �����ϴ� ����
	int m_nStartIl			= nAcc ;		//���ݱ��� �� �ϼ�
	int m_nbSelectYear		= bSelectYear;	//�������� ������� Ȯ���ϴ� ����
	char m_cInput			= 0;


	//printf("%d\n", m_nStartYo);

	for(int cal = 1; cal <= MONTH; cal++)
	{
		printf("���� ��������.<Enter/q> : ");
		scanf("%c", &m_cInput);
		fflush(stdin);

		if( m_cInput == 10 )
		{


			printf("%d�� %d��\n", m_nYear, cal);
			printf(" Sun Mon Tue Wen Thu Fri Sat\n");


			for( int j = 0; j < m_nStartYo; j++)		//�� ó�� ���Ϻ��� �����ϱ� ���� ������ �ֱ� ���� �ݺ���
			{
				printf("    ");		//���� ����
			}


			for(int i = 1+m_nStartYo; i <= JudgeMoon(cal, m_nbSelectYear)+m_nStartYo; i++)
			{
				//JudgeMoon�Լ� = 31�� 30�� 28�� 29������ �Ǻ��Ͽ� �����ϱ� ���� �Լ�
				printf("%4d", i-m_nStartYo);

				if( i % 7 == 0)		//�������� �Ǹ� ������ ����.
					printf("\n");

			}
			printf("\n");

			m_nStartIl			+= JudgeMoon(cal, m_nbSelectYear);		//���� ����� ���� �ϼ��� �� �ϼ��� �� ���Ѵ�
			m_nStartYo			= m_nStartIl%7;					//�׸��� �������� �����ϴ��� �ٽ� �ʱ�ȭ�� �Ѵ�.


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
		if( m_nbSelectYear == LEAPYEAR )		//�����̸� 29���� ��ȯ�Ѵ�.
			return 29;
		else
			return 28;
		break;
	}
}