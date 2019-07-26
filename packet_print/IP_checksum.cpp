#include<iostream>
#include<cmath>
using namespace std;
// 4500 0054 e5a6 0000 4001 (1388) c0a8 0029
// c0a8 0001
int checksum(int a[]);
int main() {
	int a[9] = { 0x4500,  0x0054, 0xe5a6, 0x0000, 0x4001, 0xc0a8, 0x0029, 0xc0a8, 0x0001 };
	//checksum: 1388
}
int checksum(int a[]) {
	int temp = 0x0000;
	int leftover;
	for (int i = 0;i<9;i++) {
		temp += a[i];
	}
	printf("sum: %x \n", temp);
	leftover = temp/pow(16,4);
	temp=temp - leftover * pow(16, 4) + leftover;
	printf("leftover: %x %x \n", leftover, temp);
	temp = ~temp;
	printf("checksum: %4.x \n",temp);
	return temp;
}