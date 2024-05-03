#include "iostream"
#include "fstream"
using namespace std;
const int maxDinh = 20;

struct node {
	int dinhKe;
	int trongSo;
	node* link;
};

struct danhSachKe {
	node* dsk[maxDinh];
	int soDinh; // số đỉnh của graph
};

void readFile(danhSachKe& list) {
	ifstream inFile("Text.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep.";
		return;
	}
	// cho danh sách = null hết
	for (int i = 0; i < maxDinh; i++)
		list.dsk[i] = NULL;	
	// Nhap số đỉnh tổng
	inFile >> list.soDinh;
	for (int i = 0; i < list.soDinh; i++) {
		int soDinhKe;
		inFile >> soDinhKe;
		for (int j = 0; j < soDinhKe; j++) {
			node* newNode = new node();
			inFile >> newNode->dinhKe;
			inFile >> newNode->trongSo;
			newNode->link = NULL;
			// Thêm vào single list theo đỉnh tương ứng 
			if (list.dsk[i] == NULL)  // chưa có đỉnh kề nào hết 
				list.dsk[i] = newNode;
			else { // đã có đỉnh kề trước đó thêm vào cuối single list 
				node* temp = list.dsk[i];
				while (temp->link != NULL)
					temp = temp->link;
				temp->link = newNode;
			}
		}
	}
}

void xuatDanhSachKe(danhSachKe list) {
	cout << "GRAPH";
	for (int i = 0; i < list.soDinh; i++) {
		cout << "\n(" << i << "): ";
		node* pointer = list.dsk[i];
		while (pointer) {
			cout << "(" << pointer->dinhKe << "," << pointer->trongSo << ") ";
			pointer = pointer->link;
		}
	}
}

int demSoCanh(danhSachKe list) {
	int count = 0;
	for (int i = 0; i < list.soDinh; i++) {
		node* pointer = list.dsk[i];
		while (pointer) {
			count++;
			pointer = pointer->link;
		}
	}
	return count;
}

int tinhBacRa(danhSachKe list, int u) {
	int count = 0;
	node* pointer = list.dsk[u];
	while (pointer)
	{
		count++;
		pointer = pointer->link;
	}
	return count;
}

int tinhBacVao(danhSachKe list, int u) {
	int count = 0;
	for (int i = 0; i < list.soDinh; i++) {
		node* pointer = list.dsk[i];
		while (pointer) {
			if (pointer->dinhKe == u) {
				count++;
				break;
			}
			pointer = pointer->link;
		}
	}
	return count;
}

bool canhCoTrongSoLonNhat(danhSachKe list, int& u, int& v) {
	node* max = NULL;
	for (int i = 0; i < list.soDinh; i++) {
		node* pointer = list.dsk[i];
		while (pointer) {
			if (max == NULL) {
				u = i;
				max = pointer;
			}
			else if (pointer->trongSo > max->trongSo) {
				u = i;
				max = pointer;
			}
			pointer = pointer->link;
		}
	}

	if (max == NULL)
		return false;
	else {
		v = max->dinhKe;
		return true;
	}
}

int main() {
	danhSachKe list;
	readFile(list);
	xuatDanhSachKe(list);
	cout << "\nTong so canh: " << demSoCanh(list);
	cout << "\nBac ra cua 5: " << tinhBacRa(list, 5);
	cout << "\nBac vao cua 5: " << tinhBacVao(list, 5);
	int u, v;
	if (canhCoTrongSoLonNhat(list, u, v))
		cout << "\nCanh co trong so lon nhat: (" << u << "," << v << ")";
	else
		cout << "\nKhong co canh";
}