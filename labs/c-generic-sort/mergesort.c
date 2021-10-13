
void mergesort(void *lineptr[], int left, int right, int (*comp)(void *, void *)) {

	if(left < right){
		int middle = left + (right - left) / 2;
		mergesort(lineptr, left, middle, comp);
		mergesort(lineptr, middle + 1, right, comp);
		merge(lineptr, left ,middle, right, comp);
	}
}


void merge(void *lineptr[], int left, int middle, int right, int (*comp)(void *, void *)) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	void *L[n1];
	void *M[n2];

	for (int i = 0; i < n1; i++)
    	L[i] = lineptr[left + i];
  	for (int j = 0; j < n2; j++)
    	M[j] = lineptr[middle + 1 + j];

	int i, j, k;
	i = 0;
	j = 0;
	k = left;

	while (i < n1 && j < n2) {
		if ((*comp)(L[i], M[j]) < 0) {
			lineptr[k] = L[i];
			i++;
		} else {
			lineptr[k] = M[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		lineptr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		lineptr[k] = M[j];
		j++;
		k++;
	}	
}

