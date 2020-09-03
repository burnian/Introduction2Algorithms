#pragma once
#include <string>
using namespace std;


namespace Bur {
	void BinaryStringSum() {
		string a = "1";
		string b = "11";

		int carry = 0;
		int idxLong = a.length() - 1;
		int idxShort = b.length() - 1;
		int gap = idxLong - idxShort;
		if (idxLong < idxShort) {
			gap = idxShort - idxLong;
			idxLong = idxShort;
			string temp = a;
			a = b;
			b = temp;
		}

		while (idxLong >= 0 && (idxLong - gap >= 0 || carry > 0)) {
			a[idxLong] += (idxLong - gap >= 0 ? b[idxLong - gap] - '0' : 0) + carry;
			carry = 0;
			if (a[idxLong] > '1') {
				carry = 1;
				a[idxLong] -= 2;
			}
			idxLong--;
		}
		if (carry > 0)
			a.insert(0, "1");
	}
}