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




int main(int argc, char* argv[]){

        vector<CMatrix> matrices;

                        std::ifstream ifs("example.m");
                        std::string content( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );

                        size_t countSqaures = std::count(content.begin(),content.end() , ']');
                        bool flag = false;
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

                                } else {
                                        flag = true;
                                }




                        }


                        std::istringstream f(content);
                        std::string operationLine;
                        int countMe = 0;
                        while(getline(f,operationLine)) {
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

