#include <iostream>
#include <fstream>

const unsigned MAX_SIZE = 25;

struct Pair
{
	int first = 0;
	int second= 0;
};

struct Relation
{
	Pair relations[MAX_SIZE];
	size_t size = 0;
};

void writeRelationToFile(std::ofstream& writePath, const Relation& relat)
{
	if (!writePath.is_open())
		return;

	for (int i = 0; i < relat.size; i++)
	{
		writePath << relat.relations[i].first << ' ' 
			<< relat.relations[i].second << std::endl;
	}
}

Pair createPair()
{
	Pair toReturn;
	return toReturn;
}

void initPair(Pair& pair, int first, int second)
{
	pair.first = first;
	pair.second = second;
}

Pair readPairFromFile(std::ifstream& readPath)
{
	if (!readPath.is_open())
		return createPair();

	Pair a = createPair();
	readPath >> a.first >> a.second;
	return a;
}

void writePairToFile(std::ofstream& outFile,const Pair& pair)
{
	if (!outFile.is_open())
		return;

	outFile << pair.first << ' ' << pair.second << std::endl;
}

void addPairToRelation(const Pair& pair, Relation& rel)
{
	if (rel.size >= MAX_SIZE)
		return;

	rel.relations[rel.size++] = pair;
}

Relation createRelation()
{
	Relation toReturn;
	return toReturn;
}

Relation readRelationToFile(std::ifstream& readPath)
{
	if (!readPath.is_open())
		return createRelation();

	Relation toReturn;

	while (true)
	{
		if (readPath.eof())
			break;
		addPairToRelation(readPairFromFile(readPath), toReturn);
	}

	return toReturn;
}

int main()
{
	Relation r;

	std::ifstream outFile("fileName.txt");

	r = readRelationToFile(outFile);
	std::cout << r.relations[0].first << " " << r.relations[0].second << std::endl <<
		r.relations[1].first << " " << r.relations[1].second;
	outFile.close();

}