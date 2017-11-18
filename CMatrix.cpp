#include "CMatrix.h"
#include "stdarg.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>

using namespace std;

	CMatrix::CMatrix() {
		nR = nC = 0;
		values = NULL;
		this -> name = "none";
	}
	CMatrix::~CMatrix() {
			 reset();
		 }

		 CMatrix::CMatrix(string name,int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0) {
								 this -> nR = nR;
								 this -> nC = nC;
								 this -> name = name;
								 if((nR * nC) == 0) {
									 values = NULL;
									 return;
								 }
								 values = new double *[nR];
								 for (int iR = 0; iR < nR; iR++) {
									 values[iR] = new double[nC];
									 for (int iC = 0; iC < nC; iC++) {
										 switch (initialization) {
										 case MI_ZEROS :
					 values[iR][iC] = 0;
					 break;
										 case MI_ONES :
					 values[iR][iC] = 1;
					 break;
										 case MI_EYE :
					 values[iR][iC] = (iR == iC) ? 1 : 0;
					 break;
										 case MI_RAND :
					 values[iR][iC] = (rand() % 1000000) / 1000000.0;
					 break;
										 case MI_VALUE :
					 values[iR][iC] = initializationValue;
					 break;
										 }
									 }
								 }



		 }


	CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue) {
				  this -> nR = nR;
				  this -> nC = nC;
					this -> name = "none";
				  if((nR * nC) == 0) {
					  values = NULL;
					  return;
				  }
				  values = new double *[nR];
				  for (int iR = 0; iR < nR; iR++) {
					  values[iR] = new double[nC];
					  for (int iC = 0; iC < nC; iC++) {
						  switch (initialization) {
						  case MI_ZEROS :
	  values[iR][iC] = 0;
	  break;
						  case MI_ONES :
	  values[iR][iC] = 1;
	  break;
						  case MI_EYE :
	  values[iR][iC] = (iR == iC) ? 1 : 0;
	  break;
						  case MI_RAND :
	  values[iR][iC] = (rand() % 1000000) / 1000000.0;
	  break;
						  case MI_VALUE :
	  values[iR][iC] = initializationValue;
	  break;
						  }
					  }
				  }
			  }
	CMatrix ::CMatrix(int nR, int nC, double first, ...) {
		this -> nR = nR;
	   this -> nC = nC;
		 this -> name = "none";
	   if((nR * nC) == 0) {
		   values = NULL;
		   return;
	   }
	   values = new double *[nR];
		   va_list va;

		   va_start(va, first);
   for (int iR = 0; iR < nR; iR++) {
	   values[iR] = new double[nC];
	   for (int iC = 0; iC < nC; iC++) {
		   values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
	   }
	}
	va_end(va);
		}
		CMatrix ::CMatrix(string name,int nR, int nC, double first, ...) {
			this -> nR = nR;
			 this -> nC = nC;
			 this -> name = name;
			 if((nR * nC) == 0) {
				 values = NULL;
				 return;
			 }
			 values = new double *[nR];
				 va_list va;

				 va_start(va, first);
		 for (int iR = 0; iR < nR; iR++) {
			 values[iR] = new double[nC];
			 for (int iC = 0; iC < nC; iC++) {
				 values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
			 }
		}
		va_end(va);
			}

	CMatrix ::CMatrix(const CMatrix & m) {
		nR = nC = 0;
		values = NULL;
		this -> name = "none";
		copy(m);
		}
	CMatrix::CMatrix(string s) {
		 nR = nC = 0;
		 values = NULL;
		 this -> name = "none";
	    	 copy(s);
		 }
	CMatrix::CMatrix(string data,string s) {
		nR = nC = 0;
		values = NULL;
		name = data;
		copy(s);
	}

	void CMatrix ::copy(const CMatrix & m) {
		reset();
		this -> nR = m.nR;
		this -> nC = m.nC;
		this -> name = m.name;
		if((nR * nC) == 0) {
			values = NULL;
			return;
		}
		values = new double *[nR];
		for (int iR = 0; iR < nR; iR++) {
			values[iR] = new double[nC];
			for (int iC = 0; iC < nC; iC++) {
				values[iR][iC] = m.values[iR][iC];
			}
		}
	}

	string CMatrix:: getName() {
		string data = this -> name;
			return data;
		}
	void CMatrix:: setName(string s) {
			this->name = s;
		}

	CMatrix::CMatrix(double d) {
		nR = nC = 0;
		values = NULL;
		this -> name = "none";
		copy(d);
	}
	void CMatrix::copy(double d) {
		reset();
		this -> nR = 1;
		this -> nC = 1;
		this -> name = "none";
		values = new double *[1];
		values[0] = new double[1];
		values[0][0] = d;
	}
/*
	void CMatrix ::copy(string s) {
		reset();
		char * buffer = new char[s.length() + 1];
		strcpy(buffer, s.c_str());
		const char * lineSeparators = ";\r\n";
		char * line = strtok(buffer, lineSeparators);
		while (line) {
			CMatrix row;
			string s;
			for(int i = 1 ; i < strlen(line);i++) {
				if(line[i] == ' ' || line[i] == ']') {
					CMatrix item = atof(s.c_str());
					row.addColumn(item);
					s = "";
				} else {
					s += line[i];
				}
			}

			if(row.nC > 0 && (row.nC == nC || nR == 0))
				addRow(row);
			line = strtok(NULL, lineSeparators);
		}
		// this -> name = "none"; // Parsing First Charactars for Initialization for the Contructor
		delete[] buffer;
	}
*/
void CMatrix ::copy(string s) {
	reset();
	char * buffer = new char[s.length() + 1];
	strcpy(buffer, s.c_str());
	const char * lineSeparators = ";";
	char * line = strtok(buffer, lineSeparators);
	while (line) {
			CMatrix row;
			string s;
			for(int i = 0 ; i < strlen(line) + 1;i++) {
				if(line[i] == ' ' || i == strlen(line)) {
					if(s == "") {
						s = "";
					} else {
					CMatrix item = atof(s.c_str());
					row.addColumn(item);
					s = "";
					}
				} else if(line[i] == '[' || line[i] == ']') {
					continue;
				} else {
					s += line[i];
				}
			}

			if(row.nC > 0 && (row.nC == nC || nR == 0))
				addRow(row);
			line = strtok(NULL, lineSeparators);
		}
	delete[] buffer;
}

	void CMatrix ::reset() {
		if(values) {
			for (int i = 0; i < nR; i++)
				delete[] values[i];
			delete[] values;
		}
		nR = nC = 0;
		values = NULL;
	}
	string CMatrix ::getString() {
		string s;
		for (int iR = 0; iR < nR; iR++) {
			for (int iC = 0; iC < nC; iC++) {
				char buffer[50];
				double n = values[iR][iC];
				//sprintf(buffer, 50, " %g\t", values[iR][iC]);
				sprintf(buffer, "%g\t", n);
				s += buffer;
			}
			s += "\r\n";
		}
		return s;
	}

	void CMatrix::getValues() {

		int lengthValues = sizeof(this->values) / sizeof(double);
		for(int i = 0 ; i < nR;i++) {
			for(int j = 0;j< nC ;j++) {

				printf("%g\t",values[i][j]);

			}
			printf("\n");
		}
		cout << endl;
		cout << "Number of Rows : " << nR << endl;
		cout << "Number of Columns : " << nC << endl;


	}

	CMatrix CMatrix ::operator = (const CMatrix & m) {
		copy(m);
		return *this;
	}
	CMatrix CMatrix ::operator = (double d) {
		copy(d);
		return *this;
	}
	CMatrix CMatrix ::operator = (string s) {
		copy(s);
		return *this;
	}

	void CMatrix ::add(const CMatrix & m) {
		if(nR!= m.nR || nC!= m.nC)
			throw ("Invalid matrix dimension");
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				values[iR][iC] += m.values[iR][iC];
	}
	void CMatrix ::operator += (const CMatrix & m) {
		add(m);
	}
	void CMatrix ::operator += (double d) {
		add(CMatrix(nR, nC, MI_VALUE, d));
	}
	CMatrix CMatrix ::operator + (const CMatrix & m) {
		CMatrix r = *this;
		r += m;
		return r;
	}
	CMatrix CMatrix ::operator + (double d) {
		CMatrix r = *this;
		r += d;
		return r;
	}

	void CMatrix ::sub(const CMatrix & m) {
		if(nR!= m.nR || nC!= m.nC)
			throw ("Invalid matrix dimension");
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				values[iR][iC] -= m.values[iR][iC];
	}
	void CMatrix ::operator -= (const CMatrix & m) {
		sub(m);
	}
	void CMatrix ::operator -= (double d) {
		sub(CMatrix(nR, nC, MI_VALUE, d));
	}
	CMatrix CMatrix ::operator - (const CMatrix & m) {
		CMatrix r = *this;
		r -= m;
		return r;
	}
	CMatrix CMatrix ::operator - (double d) {
		CMatrix r = *this;
		r -= d;
		return r;
	}

	CMatrix CMatrix ::elementWiseDiv(const CMatrix & m){

		if(nR != m.nR && nC != m.nC)
			throw("Invalid matrix dimension");
		CMatrix r(nR, nC);
		for (int iR = 0; iR < r.nR; iR++) {
			for (int iC = 0; iC < r.nC; iC++) {
				r.values[iR][iC] = values[iR][iC] / m.values[iR][iC];
			}
		}
		copy(r);

		return *this;
	}

	void CMatrix ::mul(const CMatrix & m) {
		if(nC!= m.nR)
			throw ("Invalid matrix dimension");
		CMatrix r(nR, m.nC);
		for (int iR = 0; iR < r.nR; iR++) {
			for (int iC = 0; iC < r.nC; iC++) {
				r.values[iR][iC] = 0;
				for (int k = 0; k < m.nR; k++) {
					r.values[iR][iC] += values[iR][k] * m.values[k][iC];
				}
			}
		}
		copy(r);
	}
	void CMatrix ::operator *= (const CMatrix & m) {
		mul(m);
	}
	void CMatrix ::operator *= (double d) {
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				values[iR][iC] *= d;
	}
	CMatrix CMatrix ::operator * (const CMatrix & m) {
		CMatrix r = *this;
		r *= m;
		return r;
	}
	CMatrix CMatrix ::operator * (double d) {
		CMatrix r = *this;
		r *= d;
		return r;
	}

	CMatrix CMatrix ::operator++() {
		add(CMatrix(nR, nC, MI_VALUE, 1.0));
		return *this;
	}
	CMatrix CMatrix ::operator++(int) {
		CMatrix C = *this;
		add(CMatrix(nR, nC, MI_VALUE, 1.0));
		return C;
	}
	CMatrix CMatrix ::operator --() {
		add(CMatrix(nR, nC, MI_VALUE, -1.0));
		return *this;
	}
	CMatrix CMatrix ::operator --(int) {
		CMatrix r = *this;
		add(CMatrix(nR, nC, MI_VALUE, -1.0));
		return r;
	}
	CMatrix CMatrix ::operator - () {
		for (int iR = 0; iR < nR; iR++)
			for (int iC = 0; iC < nC; iC++)
				values[iR][iC] = -values[iR][iC];
		return *this;
	}
	CMatrix CMatrix ::operator + () {
		return *this;
	}

	void CMatrix ::setSubMatrix(int r, int c,const CMatrix & m) {
		if((r + m.nR) > nR || (c + m.nC) > nC) throw ("Invalid matrix dimension");
		for (int iR = 0; iR < m.nR; iR++)
			for (int iC = 0; iC < m.nC; iC++)
				values[r + iR][c + iC] = m.values[iR][iC];
	}
	CMatrix CMatrix ::getSubMatrix(int r, int c, int nR, int nC) {
		if((r + nR) > nR || (c + nC) > nC) throw ("Invalid matrix dimension");
		CMatrix m(nR, nC);
		for (int iR = 0; iR < m.nR; iR++)
			for (int iC = 0; iC < m.nC; iC++)
				m.values[iR][iC] = values[r + iR][c + iC];
		return m;
	}

	void CMatrix ::addColumn(const CMatrix & m) {
		CMatrix n(max(nR, m.nR), nC + m.nC);
		n.setSubMatrix(0, 0, *this);
		n.setSubMatrix(0, nC, m);
		*this = n;
	}
	void CMatrix ::addRow(const CMatrix & m) {
		CMatrix n(name,nR + m.nR, max(nC, m.nC));
		n.setSubMatrix(0, 0, *this);
		n.setSubMatrix(nR, 0, m);
		*this = n;
	}

	CMatrix CMatrix ::getCofactor(int r, int c) {
		if(nR <= 1 && nC <= 1) throw ("Invalid matrix dimension");
		CMatrix m(nR - 1, nC - 1);
		for (int iR = 0; iR < m.nR; iR++)
			for (int iC = 0; iC < m.nC; iC++) {
				int sR = (iR < r) ? iR : iR + 1;
				int sC = (iC < c) ? iC : iC + 1;
				m.values[iR][iC] = values[sR][sC];
			}
		return m;
	}
	double CMatrix ::getDeterminant() {
		if(nR!= nC) throw ("Invalid matrix dimension");
		if(nR == 1 && nC == 1) return values[0][0];
		double value = 0, m = 1;
		for (int iR = 0; iR < nR; iR++) {
			value += m * values[0][iR] * getCofactor(0, iR).getDeterminant();
			m *= -1;
		}
		return value;
	}

	CMatrix CMatrix::getTranspose()
	{
		CMatrix a(nC, nR);
		for (int iR = 0; iR < a.nR; iR++)
			for (int iC = 0; iC < a.nC; iC++)
				a.values[iR][iC] = values[iC][iR];

		return a;
	}

	CMatrix CMatrix::getInverse()
	{
		if (nR != nC) throw ("Invalid matrix dimension");
		CMatrix m(nR, nC);
		for (int iR = 0; iR < m.nR; iR++)
			for (int iC = 0; iC < m.nC; iC++)
			{
				if (iR % 2 == 0) {
					m.values[iR][iC] = (iC % 2 == 0) ? getCofactor(iR, iC).getDeterminant() : -getCofactor(iR, iC).getDeterminant();
				}
				else
					m.values[iR][iC] = (iC % 2 == 0) ? -getCofactor(iR, iC).getDeterminant() : getCofactor(iR, iC).getDeterminant();
			}
		m = m.getTranspose();
		m = m * (1 / getDeterminant());
		return m;
}

	istream & operator >> (istream &is, CMatrix & m) {
		string s;
		getline(is, s, ']');
		s += "]";
		m = CMatrix(s);
		return is;
	}
	ostream & operator << (ostream & os, CMatrix & m) {
		os << m.getString();
		return os;
	}
