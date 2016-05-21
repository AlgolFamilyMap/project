#pragma once
#include <string>
#include "FamilyMap_LJH.h"
void swapInAry(treeNode ary[], int i, int j) {
	treeNode temp = ary[i];
	ary[i] = ary[j];
	ary[j] = temp;
}

int partition(treeNode ary[], int left, int right) {
	treeNode pivot = ary[left];
	int l = left;
	int r = right + 1;

	while (l < r) {
		while (ary[++l].level < pivot.level);
		while (ary[--r].level > pivot.level);

		if (l >= r)
			break;
		swapInAry(ary, l, r);
	}

	swapInAry(ary, left, r);

	return r;
}

void quickSort(treeNode ary[], int left, int right) {
	if (left < right) {
		int pivot = partition(ary, left, right);
		quickSort(ary, left, pivot - 1);
		quickSort(ary, pivot + 1, right);
	}
}