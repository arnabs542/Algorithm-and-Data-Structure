//http://www.lintcode.com/submission/4326475/
/**
* @param m: An integer m denotes the size of a backpack
* @param A: Given n items with size A[i]
* @return: The maximum size
*/
//method 1: two dimension
int backPack(int m, vector<int> A) {
	//bp[i+1][j] means choosing from first i items and their max value <=j 

	int len = A.size();
	vector<vector<int>> bp(len + 1, vector<int>(m + 1, 0));

	for (int i = 0; i<len; i++) {
		for (int j = 0; j <= m; j++) {
			if (A[i]>j) {
				bp[i + 1][j] = bp[i][j];
			}
			else {
				bp[i + 1][j] = bp[i][j - A[i]] + A[i]>bp[i][j] ? bp[i][j - A[i]] + A[i] : bp[i][j];
			}
		}
	}

	return bp[len][m];
}

//method2: less memory usage

int backPack(int m, vector<int> A) {
	//res[j]: bool value,0<j<=m res[j]==true means current backpack size j
	//can be filled by items from A.

	int len = A.size();
	vector<bool> res(m + 1, false);
	res[0] = true;
	for (int i = 0; i<len; i++) {
		for (int j = m; j >= 0; j--) {
			if (A[i] <= j&&res[j - A[i]])
				res[j] = true;
		}
	}

	for (int j = m; j >= 0; j--) {
		if (res[j])
			return j;
	}

	return 0;
}
