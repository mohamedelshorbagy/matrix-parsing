#include "CMatrix.h"
#include "CMatrix.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include "stdarg.h"
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iterator>

//using namespace std;

void getString(string s) {
        cout << s << endl;
}


int isInsideMatrix(vector<CMatrix> matricesArray,string target) {
        bool found = false;
        int index = -1;
        for(int i =0;i < matricesArray.size();i++) {
                if(matricesArray[i].getName() == target) {
                        found = true;
                        index = i;

                }
        }

        
        return index;

}

CMatrix addOperation(vector<CMatrix> matricesArray,int a,int b,string target) {
        CMatrix returnedResult = matricesArray[a] + matricesArray[b];
        returnedResult.setName(target);
        return returnedResult;

}

CMatrix subOperation(vector<CMatrix> matricesArray,int a,int b,string target) {
        CMatrix returnedResult = matricesArray[a] - matricesArray[b];
        returnedResult.setName(target);
        return returnedResult;

}

CMatrix multiplyOperation(vector<CMatrix> matricesArray,int a,int b,string target) {
        CMatrix returnedResult = matricesArray[a] * matricesArray[b];
        returnedResult.setName(target);
        return returnedResult;

}
CMatrix divideOperation(vector<CMatrix> matricesArray,int a,int b,string target) {
        CMatrix aMatrix = matricesArray[a];
        CMatrix bMatrix = matricesArray[b].getInverse();
        CMatrix returnedResult = aMatrix * bMatrix;
        returnedResult.setName(target);
        return returnedResult;

}


CMatrix transposeOperation(vector<CMatrix> &matricesArray,int a,string target) {
        CMatrix returnedResult = matricesArray[a].getTranspose();
        returnedResult.setName(target);
        return returnedResult;

}

CMatrix elmentWiseDivOperationNumber(vector<CMatrix> &matricesArray,int a,string number,string target) {

        int num = atof(number.c_str());
        CMatrix aMatrix = matricesArray[a];
        CMatrix dMatrix(aMatrix.getnR(),aMatrix.getnC(),CMatrix::MI_VALUE,num);
        CMatrix returnedResult = dMatrix.elementWiseDiv(aMatrix);
        returnedResult.setName(target);
        return returnedResult;

} 

CMatrix elmentWiseDivOperationNormal(vector<CMatrix> &matricesArray,int a,int b,string target) {

        CMatrix aMatrix = matricesArray[a];
        CMatrix bMatrix = matricesArray[b];
        CMatrix returnedResult = bMatrix.elementWiseDiv(aMatrix);
        returnedResult.setName(target);
        return returnedResult;

} 






bool checkAlpha(const string &str) {
	for (int i = 0; i < str.size(); i++)
		if (!isalpha(str[i]) || !isspace(str[i]))
			return true;
	return false;
}

bool checkNumeric(const string &str) {
	bool allDigits = true;
	for (int i = 0; i < str.size(); i++)
		if (!isdigit(str[i]) && str[i] != '.')
				allDigits = false;
	return allDigits;
}

bool getIndexAndCheckIfExist(vector<string> &matrixNames,
	vector<CMatrix> &matrix,
	string &firstParameter, int &firstIndex, bool &found1,
	string &secondParameter, int &secondIndex, bool &found2) {

	found1 = false;
	for (int i = 0; i < matrixNames.size(); i++) {
		if (firstParameter == matrixNames[i]) {
			firstIndex = i;
			if (firstIndex >= matrix.size())
				found1 = false;
			else
				found1 = true;

			break;
		}
	}
	found2 = false;
	for (int i = 0; i < matrixNames.size(); i++) {
		if (secondParameter == matrixNames[i]) {
			secondIndex = i;
			if (secondIndex >= matrix.size())
				found2 = false;
			else
				found2 = true;

			break;
		}
	}

	bool doBreak = false;

	if(!found1){
		if(checkAlpha(firstParameter)){
			found1 = true;
			doBreak = false;
		}
	}

	if (!found1 && !found2) {
		cout << firstParameter << " and "
			<< secondParameter << " aren't Intiallized" << endl;
		doBreak = true;
	}

	if (!found1 && !doBreak) {
		cout << firstParameter << " is not Intiallized" << endl;
		doBreak = true;
	}
	if (!found2 && !doBreak) {
		cout << secondParameter << " is not Intiallized" << endl;
		doBreak = true;
	}

	return doBreak;
}


class Text {

string text;

public:

Text() {}

Text(const string& fname) {

    ifstream ifs(fname.c_str());

    string line;

    while (getline(ifs, line))

        text += line + '\n';

    }

    string contents() {

        return text;

    }

};
void implemetation(){

    vector<string> matrixNames;
    vector<CMatrix> matrix;
    vector<long> existingIndex;
    vector<bool> existingFlag;

    string line = "";
    int numlines = 0;
    while (1) {
            getline(cin, line);
            if (line == "end" || line == "end;") {
                    cout << "thanks, good bye..." << endl;
                    break;
            }
            if (line.empty()) {
                    continue;
            }
            /*
            if (line.find(";") == string::npos) {
                    cout << "missing ending semi colone" << endl;
                    continue;
            }
            */
            //line = line.substr(0, line.length() - 1);
            size_t n = std::count(line.begin(), line.end(), '=');
            int x = 0;
            if (n == 0) {
                    if (matrixNames.size() == 0) {
                            cout << "unintiallized matrix" << endl;
                    }
                    for (int i = 0; i < matrixNames.size(); i++) {
                            if (matrixNames[i] == line && i < matrix.size()) {
                                    cout << matrix[i];
                                    break;
                            }
                            if (i == matrixNames.size() - 1) {
                                    cout << "unintiallized matrix" << endl;
                            }
                    }
            }

            for (int i = 0; i < n; i++) {
                    string l = (line.substr(0, line.find('=')));
                    string::iterator end_pos = remove(l.begin(), l.end(), ' ');
                    l.erase(end_pos, l.end());
                    if (!matrixNames.size()) {
                            existingFlag.push_back(false);
                    }
                    for (int i = 0; i < matrixNames.size(); i++) {
                            if (l == matrixNames[i]) {
                                    existingFlag.push_back(true);
                                    existingIndex.push_back(i);
                                    break;
                            }
                            if (i == matrixNames.size() - 1) {
                                    existingFlag.push_back(false);
                            }
                    }

                    if (!existingFlag[numlines + i]) {
                            matrixNames.push_back(l);
                            existingIndex.push_back(i);
                    }
                    else {
                            matrixNames.push_back(l);
                    }
                    line = line.substr(line.find('=') + 1);
            }

            for (int i = 0; i < n; i++) {
                    int a = line.find("[");
                    if (line.find('[') != string::npos) {
                            /*
                            cout <<line;
                            CMatrix a(line);
                            matrix.push_back(a);
                            matrixNames.push_back("B");
                            */
                            if (line[0] == ' ')
                                    line =line.substr(1, line.length());
                            if (!existingFlag[numlines + i]) {
                                    CMatrix b(line);
                                    matrix.push_back(b);
                            }
                            else {
                                    CMatrix b(line);
                                    matrix.push_back(NULL);
                                    matrix[existingIndex[numlines + i]] = b;
                            }

                    }
                    else if (line.find('[') == string::npos) {
                            //removing spaces
                            string::iterator end_pos = remove(line.begin(), line.end(), ' ');
                            line.erase(end_pos, line.end());

                            if (line.find('+') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('+'));
                                    string secondParameter = line.substr(line.find('+') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                            break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] + matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] + matrix[secondIndex];
                                    }
                            }
                            else if (line.find('-') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('-'));
                                    string secondParameter = line.substr(line.find('-') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                            break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] - matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] - matrix[secondIndex];
                                    }

                            }
                            else if (line.find('*') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('*'));
                                    string secondParameter = line.substr(line.find('*') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                            break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] * matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] * matrix[secondIndex];
                                    }
                            }
                            else if (line.find('/') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('/'));
                                    string secondParameter = line.substr(line.find('/') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                            break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] * matrix[secondIndex].getInverse());
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] * matrix[secondIndex].getInverse();
                                    }
                            }
                            else if (line.find("'") != string::npos) {
                                    string firstParameter = line.substr(0, line.find("'"));
                                    int firstIndex;
                                    bool found1;

                                    found1 = false;
                                    for (int i = 0; i < matrixNames.size(); i++) {
                                            if (firstParameter == matrixNames[i]) {
                                                    firstIndex = i;
                                                    if (firstIndex >= matrix.size())
                                                            found1 = false;
                                                    else
                                                            found1 = true;

                                                    break;
                                            }
                                    }

                                    if (!found1) {
                                            cout << firstParameter << " is not Intiallized" << endl;
                                            break;
                                    }

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex].getTranspose());
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex].getTranspose();
                                    }
                            }
                            else if (checkAlpha(line)) {

                                    bool found = false; int index;
                                    for (int i = 0; i < matrixNames.size(); i++) {
                                            if (line == matrixNames[i]) {
                                                    index = i;
                                                    if (index >= matrix.size())
                                                            found = false;
                                                    else
                                                            found = true;
                                                    break;
                                            }
                                    }

                                    if (!found) {
                                            cout << line << " is not Intiallized" << endl;
                                            break;
                                    }

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[index] + 0);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[index];
                                    }

                            }
                            else {
                                    cout << "operation not found" << endl;
                            }
                    }
            }

            numlines += n;
    }
}
void implemetation(string xt){

    vector<string> matrixNames;
    vector<CMatrix> matrix;
    vector<long> existingIndex;
    vector<bool> existingFlag;

    string line = "";
    int numlines = 0;
   // while (1) {
           // getline(cin, line);
    line=xt;
            if (line == "end" || line == "end;") {
                    cout << "thanks, good bye..." << endl;
                   // break;
            }
            if (line.empty()) {
                  //  continue;
            }
            /*
            if (line.find(";") == string::npos) {
                    cout << "missing ending semi colone" << endl;
                    continue;
            }
            */
            //line = line.substr(0, line.length() - 1);
            size_t n = std::count(line.begin(), line.end(), '=');
            int x = 0;
            if (n == 0) {
                    if (matrixNames.size() == 0) {
                            cout << "unintiallized matrix" << endl;
                    }
                    for (int i = 0; i < matrixNames.size(); i++) {
                            if (matrixNames[i] == line && i < matrix.size()) {
                                    cout << matrix[i];
                                  //  break;
                            }
                            if (i == matrixNames.size() - 1) {
                                    cout << "unintiallized matrix" << endl;
                            }
                    }
            }

            for (int i = 0; i < n; i++) {
                    string l = (line.substr(0, line.find('=')));
                    string::iterator end_pos = remove(l.begin(), l.end(), ' ');
                    l.erase(end_pos, l.end());
                    if (!matrixNames.size()) {
                            existingFlag.push_back(false);
                    }
                    for (int i = 0; i < matrixNames.size(); i++) {
                            if (l == matrixNames[i]) {
                                    existingFlag.push_back(true);
                                    existingIndex.push_back(i);
                              //      break;
                            }
                            if (i == matrixNames.size() - 1) {
                                    existingFlag.push_back(false);
                            }
                    }

                    if (!existingFlag[numlines + i]) {
                            matrixNames.push_back(l);
                            existingIndex.push_back(i);
                    }
                    else {
                            matrixNames.push_back(l);
                    }
                    line = line.substr(line.find('=') + 1);
            }

            for (int i = 0; i < n; i++) {
                    int a = line.find("[");
                    if (line.find('[') != string::npos) {
                            /*
                            cout <<line;
                            CMatrix a(line);
                            matrix.push_back(a);
                            matrixNames.push_back("B");
                            */
                            if (line[0] == ' ')
                                    line =line.substr(1, line.length());
                            if (!existingFlag[numlines + i]) {
                                    CMatrix b(line);
                                    matrix.push_back(b);
                            }
                            else {
                                    CMatrix b(line);
                                    matrix.push_back(NULL);
                                    matrix[existingIndex[numlines + i]] = b;
                            }

                    }
                    else if (line.find('[') == string::npos) {
                            //removing spaces
                            string::iterator end_pos = remove(line.begin(), line.end(), ' ');
                            line.erase(end_pos, line.end());

                            if (line.find('+') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('+'));
                                    string secondParameter = line.substr(line.find('+') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                           // break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] + matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] + matrix[secondIndex];
                                    }
                            }
                            else if (line.find('-') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('-'));
                                    string secondParameter = line.substr(line.find('-') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                //            break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] - matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] - matrix[secondIndex];
                                    }

                            }
                            else if (line.find('*') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('*'));
                                    string secondParameter = line.substr(line.find('*') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                  //          break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] * matrix[secondIndex]);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] * matrix[secondIndex];
                                    }
                            }
                            else if (line.find('/') != string::npos) {
                                    string firstParameter = line.substr(0, line.find('/'));
                                    string secondParameter = line.substr(line.find('/') + 1);
                                    int firstIndex, secondIndex;
                                    bool found1, found2;

                                    if (getIndexAndCheckIfExist(matrixNames, matrix,
                                            firstParameter, firstIndex, found1,
                                            secondParameter, secondIndex, found2))
                                    //        break;

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex] * matrix[secondIndex].getInverse());
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex] * matrix[secondIndex].getInverse();
                                    }
                            }
                            else if (line.find("'") != string::npos) {
                                    string firstParameter = line.substr(0, line.find("'"));
                                    int firstIndex;
                                    bool found1;

                                    found1 = false;
                                    for (int i = 0; i < matrixNames.size(); i++) {
                                            if (firstParameter == matrixNames[i]) {
                                                    firstIndex = i;
                                                    if (firstIndex >= matrix.size())
                                                            found1 = false;
                                                    else
                                                            found1 = true;

                                      //              break;
                                            }
                                    }

                                    if (!found1) {
                                            cout << firstParameter << " is not Intiallized" << endl;
                                        //    break;
                                    }

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[firstIndex].getTranspose());
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[firstIndex].getTranspose();
                                    }
                            }
                            else if (checkAlpha(line)) {

                                    bool found = false; int index;
                                    for (int i = 0; i < matrixNames.size(); i++) {
                                            if (line == matrixNames[i]) {
                                                    index = i;
                                                    if (index >= matrix.size())
                                                            found = false;
                                                    else
                                                            found = true;
                                          //          break;
                                            }
                                    }

                                    if (!found) {
                                            cout << line << " is not Intiallized" << endl;
                                            //break;
                                    }

                                    if (!existingFlag[numlines + i]) {
                                            matrix.push_back(matrix[index] + 0);
                                    }
                                    else {
                                            matrix.push_back(NULL);
                                            matrix[existingIndex[numlines + i]] = matrix[index];
                                    }

                            }
                            else {
                                    cout << "operation not found" << endl;
                            }
                    }
            }

            numlines += n;
    }



int main(int argc, char* argv[]){

        vector<CMatrix> matrices;

                        std::ifstream ifs("example.m");
                        std::string content( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );

                        size_t countSqaures = std::count(content.begin(),content.end() , ']');

                        for(int i = 0 ;i < countSqaures + 1;i++) {

                        size_t found = content.find('[');
                        if(found != std::string::npos) {
                        string matrixData,matrixName;
                        matrixData = content.substr(0,content.find(']') + 1);
                        matrixName = matrixData.substr(0,content.find('='));
                        matrixName.erase(std::remove(matrixName.begin(),matrixName.end(),' '),matrixName.end());
                        matrixData.erase(0,matrixData.find('['));
                        matrixData.erase(std::remove(matrixData.begin(), matrixData.end(), '\n'), matrixData.end());
                        

                        CMatrix temp(matrixName,matrixData);
                        matrices.push_back(temp);
                        content.erase(0,content.find('=',content.find(']')) - 2);

                                cout << "End Of Matrcies" << endl;
                        } else {
                        }




                        }


                        std::istringstream f(content);
                        std::string operationLine;
                        int countMe = 0;
                        while(getline(f,operationLine)) {
                                cout << operationLine << endl;
                                cout << "***************" << endl;
                                if(operationLine.find('+') != std::string::npos) {
                                    operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());                                        
                                    string firstParameter = operationLine.substr(operationLine.find('=') + 1, operationLine.find('+') - (operationLine.find('=') + 1));
                                    string secondParameter = operationLine.substr(operationLine.find('+') + 1);
                                    string result = operationLine.substr(0,operationLine.find('='));

                                    CMatrix resultMatrix = addOperation(matrices,isInsideMatrix(matrices,firstParameter),isInsideMatrix(matrices,secondParameter),result);
                                    matrices.push_back(resultMatrix);

                                }
                                else if(operationLine.find('-') != std::string::npos) {
                                operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());
                                    
                                    string firstParameter = operationLine.substr(operationLine.find('=') + 1, operationLine.find('-') - (operationLine.find('=') + 1));
                                    string secondParameter = operationLine.substr(operationLine.find('-') + 1);
                                    string result = operationLine.substr(0,operationLine.find('='));

                                    CMatrix resultMatrix = subOperation(matrices,isInsideMatrix(matrices,firstParameter),isInsideMatrix(matrices,secondParameter),result);
                                    matrices.push_back(resultMatrix);

                                }
                                else if(operationLine.find('*') != std::string::npos) {
                                operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());

                                    string firstParameter = operationLine.substr(operationLine.find('=') + 1, operationLine.find('*') - (operationLine.find('=') + 1));
                                    string secondParameter = operationLine.substr(operationLine.find('*') + 1);
                                    string result = operationLine.substr(0,operationLine.find('='));

                                    CMatrix resultMatrix = multiplyOperation(matrices,isInsideMatrix(matrices,firstParameter),isInsideMatrix(matrices,secondParameter),result);
                                    matrices.push_back(resultMatrix);

                                }
                                else if(operationLine.find('/') != std::string::npos && operationLine.find('.') == std::string::npos) {
                                operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());

                                    string firstParameter = operationLine.substr(operationLine.find('=') + 1, operationLine.find('/') - (operationLine.find('=') + 1));
                                    string secondParameter = operationLine.substr(operationLine.find('/') + 1);
                                    string result = operationLine.substr(0,operationLine.find('='));


                                    CMatrix resultMatrix = divideOperation(matrices,isInsideMatrix(matrices,firstParameter),isInsideMatrix(matrices,secondParameter),result);
                                    matrices.push_back(resultMatrix);

                                }
                                else if(operationLine.find("'") != std::string::npos) {
                                        operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());
                                        string firstParameter = operationLine.substr(operationLine.find('=') + 1,1);
                                        string result = operationLine.substr(0,operationLine.find('='));
                
                                        CMatrix resultMatrix = transposeOperation(matrices,isInsideMatrix(matrices,firstParameter),result);
                                        matrices.push_back(resultMatrix);

                                } 
                                else if(operationLine.find("./") != std::string::npos) {
                                   operationLine.erase(std::remove(operationLine.begin(), operationLine.end(), ' '), operationLine.end());

                                    string firstParameter = operationLine.substr(operationLine.find('=') + 1, operationLine.find("./") - (operationLine.find('=') + 1));
                                    string secondParameter = operationLine.substr(operationLine.find("./") + 2);
                                    string result = operationLine.substr(0,operationLine.find('='));

                                    if(checkNumeric(firstParameter)) {

                                            CMatrix resultMatrix = elmentWiseDivOperationNumber(matrices,isInsideMatrix(matrices,secondParameter),firstParameter,result);
                                            matrices.push_back(resultMatrix);

                                    } else {
                                            CMatrix resultMatrix = elmentWiseDivOperationNormal(matrices,isInsideMatrix(matrices,secondParameter),isInsideMatrix(matrices,firstParameter),result);
                                            matrices.push_back(resultMatrix);

                                    }


                                }

                        }


                        for(int i = 0 ;i < matrices.size();i++) {
                                cout << "matrices["  << i << "] Name is : "<< matrices[i].getName() << endl;
                                cout << "Data Inside matrices[" << i << "] is : "<< endl;
                                cout << matrices[i] << endl;
                        }


        




				return 0;
}

