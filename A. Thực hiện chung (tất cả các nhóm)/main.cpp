#include <cstdio>
#include <iostream>
#include <omp.h>
using namespace std;
// Ham in ma tran
void InMatran(double* pMatrix, int rowCount, int colCount) {
	cout << "Ma tran: " << endl;
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			cout << pMatrix[i * colCount + j] << "\t";
		}
		cout << endl;
	}
}
// Ham in vector
void InVecto(double *pVector, int size) {
	cout << "Vector: " << endl;
	for (int i = 0; i < size; i++) {
		cout << pVector[i] << "\t";
	}
	cout << endl;
}
// Ham random data
void LayNgauNhienDuLieu(double* pMatrix, double* pVector, int row, int col) {
	srand(unsigned(clock())); // Ham random 1 so bat ki
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			pMatrix[i * col + j] = rand() / double(1000);
		}
	}
	for (int i = 0; i < col; i++) {
		pVector[i] = rand() / double(1000);
	}
}
// Ham giai phong bo nho
void GiaiPhongBoNho(double* pMatrix, double* pVector, double* pResult) {
	delete[] pMatrix;
	delete[] pVector;
	delete[] pResult;
}
// Ham nhan tuan tu ma tran voi vecto
void NhanTuanTu(double* pMatrix, double* pVector, double* pResult, int row, int col) {
	for (int i = 0; i < row; i++) {
		pResult[i] = 0;
		for (int j = 0; j < col; j++) {
			pResult[i] += pMatrix[i * col + j] * pVector[j];
		}
	}
}
void KhoiTaoGiaTri(double*& pMatrix, double*& pVector, double*& pResult, int& row, int& col) {
	// Nhap vao kich co cua ma tran (so hang, so cot) (so cot cua ma tran = so hang cua vector)
	do {
		cout << "Nhap vao so hang cua ma tran: ";
		cin >> row;
		cout << "Nhap vao so cot cua ma tran: ";
		cin >> col;
		if (row <= 0) cout << "So hang cua ma tran phai lon hon 0" << endl;
		if (col <= 0) cout << "So cot cua ma tran phai lon hon 0" << endl;
	} while (row <= 0 || col <= 0);
	// Phan chia bo nho
	pMatrix = new double[row * col];
	pVector = new double[col];
	pResult = new double[row];
	// Random gia tri cua ma tran va vecto
	LayNgauNhienDuLieu(pMatrix, pVector, row, col);
}

void NhanSongSong(double* pMatrix, double* pVector,
	double* pResult, int row, int col) {
	int i, j;  // Loop variables 
	#pragma omp parallel for private (j)   
	for (i = 0; i < row; i++) {
		pResult[i] = 0;
		for (j = 0; j < col; j++)
			pResult[i] += pMatrix[i * col + j] * pVector[j];
	}
}

int main() {
	double* pMatrix;
	double* pVector;
	double* pResult;
	int row;
	int col;
	cout << "Nhan ma tran voi vecto tuan tu: " << endl;
	KhoiTaoGiaTri(pMatrix, pVector, pResult, row, col);
	InMatran(pMatrix, row, col);
	InVecto(pVector, col);
	double start_time = omp_get_wtime();
	NhanTuanTu(pMatrix, pVector, pResult, row, col);
	double end_time = omp_get_wtime();
	cout << "Ket qua tinh toan tuan tu: " << endl;
	InVecto(pResult, row);
	double start_time1 = omp_get_wtime();
	NhanSongSong(pMatrix, pVector, pResult, row, col);
	double end_time1 = omp_get_wtime();
	cout << "Ket qua tinh toan song song: " << endl;
	InVecto(pResult, row);
	double time_tuan_tu = end_time - start_time;
	double time_song_song = end_time1 - start_time1;
	cout << "Thoi gian tuan tu va song song la: " << time_tuan_tu << "(s), " << time_song_song << "(s)" << endl;
	if (time_tuan_tu < time_song_song) {
		cout << "Tuan tu nhanh hon";
	}
	else if(time_tuan_tu > time_song_song) {
		cout << "Song song nhanh hon";
	}
	else {
		cout << "Tuan tu bang song song";
	}
	GiaiPhongBoNho(pMatrix, pVector, pResult);
	return 0;
}
