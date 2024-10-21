#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3 , MaxLevel = 4};

enum enOperationType {Add = 1, Sub = 2, Mult = 3, Div = 4 , MixOp = 5};

string GetOpTypeSymbol(enOperationType opType)
{
	switch (opType)
	{
		case enOperationType::Add:
		{
			return"+";
			break;
		}
		case enOperationType::Sub:
		{
			return"-";
			break;
		}
		case enOperationType::Mult:
		{
			return"*";
			break;
		}
		case enOperationType::Div:
		{
			return"/";
			break;
		}
		case enOperationType::MixOp:
		{
			return "Mix";
			break;
		}
	}
}

struct stQuestion
{
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int Number1 = 0;
	int Number2 = 0;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerRight = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfQuestion;
	short NumberRightAnswer = 0;
	short NumberWrongAnswer = 0;
	bool isPass = false;  
};

int RandomNumber(int Form, int To)
{
	int Random = rand() % (To - Form + 1) + Form;
	return Random;

}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
	{
		system("color 2F"); // turn screen to Green
	}
	else
	{
		system("color 4F");// turn screen to Red
		cout << "\a";
	}
}

int ReadHowManyQuestion()
{
	int NumberQuestion = 0;
	do
	{
		cout << "How many Questions do you want [1 to 10]: ";
		cin >> NumberQuestion;

	} while (NumberQuestion < 1 || NumberQuestion > 10);

	return NumberQuestion;
}

enOperationType ReadOpType()
{
	int OperationType;
	do
	{
		cout << "Enter Question Level [1] Add, [2] Sub, [3] Mult, [4] Div, [5] MixOp ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

enQuestionLevel ReadQuestionLevel()
{
	int QuestionLevel;
	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

int SimpleCalculator (int Number1 , int Number2,enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
	{
		return (Number1 + Number2);
		break;
	}
	case enOperationType::Sub:
	{
		return (Number1 - Number2);
		break;
	}
	case enOperationType::Mult:
	{
		return (Number1 * Number2);
		break;
	}
	case enOperationType::Div:
	{
		return (Number1 / Number2);
		break;
	}
	}

}

enQuestionLevel GetRandomOperationLevel()
{
	int Op = RandomNumber(1, 3);
	return (enQuestionLevel)Op;
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	
	if (QuestionLevel == enQuestionLevel::MaxLevel)
	{
		QuestionLevel = GetRandomOperationLevel();
	}

	Question.QuestionLevel = QuestionLevel;

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
		case enQuestionLevel::EasyLevel:
		{
			Question.Number1 = RandomNumber(1, 10);
			Question.Number2 = RandomNumber(1, 10);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

			return Question;
		}
		case enQuestionLevel::MedLevel:
		{
			Question.Number1 = RandomNumber(10, 50);
			Question.Number2 = RandomNumber(10, 50);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

			return Question;
		}
		case enQuestionLevel::HardLevel:
		{
			Question.Number1 = RandomNumber(50, 100);
			Question.Number2 = RandomNumber(50, 100);

			Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

			return Question;
		}
	}

	// to ignore warning from Complier as this Function is not return value
	return Question;

}

void GenerateQuizzQuistion(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
	{
		Quizz.QuestionList[Question] =
			GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, int QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout <<GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz & Quizz , int QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz. QuestionList[QuestionNumber].AnswerRight = false;
		Quizz.NumberWrongAnswer++;

		cout << "Worng Answer :-( \n";
		cout << "The Right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerRight = true;
		Quizz.NumberRightAnswer++;
		cout << "Right answer :-) \n";
	}

	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerRight);

}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short i = 0; i < Quizz.NumberOfQuestion; i++)
	{
		PrintTheQuestion(Quizz, i);

		Quizz.QuestionList[i].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, i);

	}

	Quizz.isPass = (Quizz.NumberRightAnswer >= Quizz.NumberWrongAnswer);


}

string GetFinalResult(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "\t\t\t_________________________________________________\n\n";
	cout << "\t\t\t\tFinal Resilt is " << GetFinalResult(Quizz.isPass);
	cout << "\n\t\t\t_________________________________________________\n\n";
	cout << "\t\t\tNumber of Question     : " << Quizz.NumberOfQuestion << endl;
	cout << "\t\t\tQuestion Level         : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "\t\t\tOpTyhpe                : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "\t\t\tNumber of Right Answer : " << Quizz.NumberRightAnswer << endl;
	cout << "\t\t\tNumber of Worng Answer : " << Quizz.NumberWrongAnswer << endl;
	cout << "\t\t\t_________________________________________________\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuistion(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResult(Quizz);
}

void StartGame()
{
	char PLayAgain = 'Y';
	do
	{
		ResetScreen();

		PlayMathGame();
		
		cout << "\n\t\t\tDo you want to play again? Y/N? ";
		cin >> PLayAgain;

	} while (toupper(PLayAgain) == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	system("pause>0");
	return 0;
}