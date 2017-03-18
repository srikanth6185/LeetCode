/*
 * leetcode_test.c
 *
 *  Created on: Mar 17, 2017
 *      Author: srikanth
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
	struct ns {
		int val;
		int idx;
	};

	int *result_nums;
	int i, j;
	struct ns *sorted_nums;


	if (!nums || (numsSize < 0) ) {
		return NULL;
	}

	sorted_nums = (struct ns *)malloc(sizeof(struct ns) * numsSize);
	if (!sorted_nums) {
		return NULL;
	}

	for(i = 0; i < numsSize; i++) {
		sorted_nums[i].val = nums[i];
		sorted_nums[i].idx = i;
	}

	for (i = 1; i < numsSize; i++) {
		for (j = 0; j < (numsSize - i); j++) {
			if (sorted_nums[j].val > sorted_nums[j+1].val) {
				struct ns temp = sorted_nums[j];
				sorted_nums[j] = sorted_nums[j+1];
				sorted_nums[j+1] = temp;
			}
		}
	}

	printf("Sorted [");
	for(i = 0; i < numsSize; i++) {
		printf(" %d,%d ", sorted_nums[i].val, sorted_nums[i].idx);
	}
	printf("]\n");

	result_nums = (int *)malloc(sizeof(int) * 2);
	if (!result_nums) {
		goto error;
	}
	memset(result_nums, 0, sizeof(int) * 2);

	i = 0;
	j = numsSize - 1;

	while (i < j) {
		int sum = sorted_nums[i].val + sorted_nums[j].val;
		if (sum == target) {
			result_nums[0] = sorted_nums[i].idx;
			result_nums[1] = sorted_nums[j].idx;
			goto success;
		} else if (sum < target) {
			i++;
		} else {
			j--;
		}
	}

success:
	free(sorted_nums);
	return result_nums;

error:
	if (sorted_nums) {
		free(sorted_nums);
	}

	if (result_nums) {
		free(result_nums);
	}
	return NULL;
}

void test_twoSum(void)
{
	int arr[4] = {15, 7, 11, 2};
	int numsSize = 4;
	int *result;

	result = twoSum(arr, numsSize, 26);

	if (result) {
		printf("[ %d, %d ]\n", result[0], result[1]);
		free(result);
	}

	return;
}

int main(void)
{
	test_twoSum();
	return 0;
}
