// тренировочная штука для проекта.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

class Cat {
public:
	// конструктор
	Cat(std::string s, int t)
		: sound(s), tail(t)
	{
	}
	// виртуальный деструктор
	virtual ~Cat() {}

	// вирутальная функция 
	// поскольку она не определена (=0)
	// значит экземпляр класса Cat создать нельзя
	// только его наследников, которые реализуют этот метод
	virtual std::string meetsAHuman() = 0;
public:
	std::string sound;
	int tail;
};

//////////////////////////////////////////////

class BigCats :public Cat {
public:
	BigCats(std::string bnc)
		: Cat("roar", 7), bigNoseColor(bnc)
	{
	}

	virtual std::string meetsAHuman()
	{
		return "roars and eats the poor bastard";
	}
public:
	std::string bigNoseColor;
};

//////////////////////////////////////////////

class SmallCats :public Cat {
public:
	SmallCats(std::string bec)
		: Cat("meow", 3), bigEyesColor(bec)
	{
	}

	virtual std::string meetsAHuman()
	{
		return "purrs and asks for food";
	}
public:
	std::string bigEyesColor;
};

std::string multiplicate(std::string string, int number) {
	for (int i = 1; i < number; i++) {
		string += string;
	}
	return string;
}

// то же самое через оператор
std::string operator*(std::string string, int number)
{
	for (int i = 1; i < number; i++) {
		string += string;
	}
	return string;
}

std::string meows(int number, std::string sound)
{
	// вызываем написанный нами оператор умножения
	return (sound + " ") * number;
}

void twoCatsMeetAHuman()
{
	// в нутри вектора лежат указатели на базовый класс
	// информация о точном типе указателя
	// известна только во время работы программы
	std::vector<Cat*> cats;

	// не знаем заранее, какие значения будут в массиве
	for (int index = 2; index-- > 0;)
	{
		if (rand() % 2)
			cats.push_back(new BigCats("brown"));
		else
			cats.push_back(new SmallCats("grey"));
	}

	std::cout
		<< "We have two felines. First of witch has tail "
		<< cats[0]->tail << " long, and the second -- "
		<< cats[1]->tail << "."
		<< std::endl;

	// вызываем вируальную функцию. Те функции, которые виртуальны
	// могут быть вызваны для указателя, точный тип которого нам не известен. 
	// для SmallCats будет вызывана SmallCats::meetsAHuman,
	// для BigCats будет вызывана BigCats::meetsAHuman,
	// Если бы это была не виртуальная 
	// функция, то компилятор мог бы вызвать функцию только по её 
	// известному типу, в данном случае Cats::meetsAHuman()  
	// (которая у нас неопределена)
	std::cout
		<< "And than first meets a human it " << cats[0]->meetsAHuman()
		<< ". But second in the same situation " << cats[1]->meetsAHuman()
		<< "." << std::endl;

	// удаляем объекты, классический вариант итерации по массиву
	// или по любой другой коллекции
	for (auto iter = cats.begin(); iter != cats.end(); ++iter)
		// здесь будет вызыван вируальный деструктор
		delete* iter;

	// ещё один вариант
	// for(auto n: cats) 
	//	  delete n; // <= по сути то же самое, что и с итератором

	// вариант, который подходит только для вектора
	// for(int index=0; index < cats.size(); ++index)
	//    delete cats[index];
}

int main()
{
	// обрати внимание, что я не задаю здесь внутренни свойства 
	// классов, такие как издаваемый звук и длина хвоста
	// они стпрятаны в конструкторе, поскольку это свойства
	// всех котов и тигров. А цвет глаз или носов различается
	// у разных тигров и котов, поэтому мы их задаем, когда вызываем
	// конструкторы

	SmallCats fluffyPaw("blue");
	BigCats angryTiger("black");

	std::cout << "The Fluffypaw's tail is only "
		<< fluffyPaw.tail
		<< ", while the tail of a big and angry tiger is almowst "
		<< angryTiger.tail
		<< " meters long."
		<< std::endl; // всегда ставится в конце вывода

	std::cout
		<< "But they still sound almost the same. Our big kitty says "
		<< meows(3, angryTiger.sound)
		<< ". And the little one goes "
		<< meows(2, fluffyPaw.sound)
		<< std::endl;

	std::cout
		<< "So, as you can see, they're both pretty qute, especially with the tiger's big and "
		<< angryTiger.bigNoseColor
		<< " nose and the kitty's gorgeous "
		<< fluffyPaw.bigEyesColor << " eyes." << std::endl;

	twoCatsMeetAHuman();
}

