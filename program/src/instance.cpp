#include <instance.h>
#include <algorithm>
#include <functional>

int Instance::evaluate(const Individual * ind) const
{
  return 0;
}

char Instance::randomNucleotide(){
	int r = randint(0,4);
	if(r == 0) return 'A';
	if(r == 1) return 'C';
	if(r == 2) return 'G';
	else return 'T';
}

void Instance::randomize(const int numWords, const int superstringLength, const float avgCommonPartPercent){
	std::string superString;
	superString.resize(superstringLength);
	for(int i = 0; i < superstringLength; i++){
		superString[i] = randomNucleotide();
	}
	std::vector<std::string> tempWords;
	tempWords.resize(numWords);
	int baseWordLength = superstringLength/numWords;
	int randScope = int(0.25 * float(baseWordLength) * avgCommonPartPercent);
	int sidewordLength = int(float(baseWordLength) * (1.0 + (avgCommonPartPercent)/2.0));
	int midwordLength = int(float(baseWordLength) * (1.0 + avgCommonPartPercent));

	tempWords[0].resize(sidewordLength + randint(-randScope, randScope+1));
	for(int i = 0, n = tempWords[0].size(); i < n; i++) {
		tempWords[0][i] = superString[i];
	}
	tempWords[numWords-1].resize(sidewordLength + randint(-randScope, randScope+1));
	for(int i = 0, n = tempWords[numWords-1].size(); i < n; i++) {
		tempWords[numWords-1][i] = superString[superstringLength - n + i];	
	}

	for(int j = 1; j < numWords-1; j++){
		int n = midwordLength + randint(-randScope, randScope+1);
		tempWords[j].resize(n);
		for(int i = 0, I = (n - baseWordLength)/2 + baseWordLength*j; i < n; i++){
			tempWords[j][i] = superString[I];
		}
	}

	std::random_shuffle(tempWords.begin(), tempWords.end());

	for(int i = 0; i < numWords; i++){
		add_word(tempWords[i]);
	}

}





