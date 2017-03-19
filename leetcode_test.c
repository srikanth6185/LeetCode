/*
 * leetcode_test.c
 *
 *  Created on: Mar 17, 2017
 *      Author: srikanth
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ns {
	int val;
	int idx;
}nt;

struct ListNode {
	int val;
	struct ListNode *next;
};


typedef struct ListNode ListNode_t;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


#define MAX_CHARS 255
/**
 * Length of the longest substring of
 * non-repeating characters.
 */
int lengthOfLongestSubstring(char* s) {
	int hs[MAX_CHARS];
	int max = 0, i, start = -1;


	for(i = 0; i < MAX_CHARS; i++){
		hs[i] = -1;
	}

	for(i = 0; s[i] != '\0'; i++) {
		if (hs[(int)s[i]] > start) {
			start = hs[(int)s[i]];
		}

		hs[(int)s[i]] = i;
		if (max < (i -  start)) {
			max = i - start;
		}
	}

	return max;
}



struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	ListNode_t *curr;
	ListNode_t dummy;
	int sum = 0;

	curr = &dummy;


	while (l1 || l2) {
		curr->next = (ListNode_t*)calloc(1, sizeof(ListNode_t));
		curr = curr->next;
        sum /= 10;

        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }

		curr->val = sum % 10;
	}

	if (sum / 10) {
		curr->next = (ListNode_t*)calloc(1, sizeof(ListNode_t));
		curr->next->val = sum/10;
	}

	return dummy.next;
}

void quick_sort_nums(nt* nums, int l, int h)
{
	int i, j, pivot;
	nt temp;

	if ((l >= h) || (l < 0) || (h < 0)) {
		return;
	}

	pivot = h;
	i = j = l;


	while (j < pivot) {
		if (nums[j].val < nums[pivot].val) {
			temp = nums[j];
			nums[j] = nums[i];
			nums[i] = temp;
			i++;
		}
		j++;
	}

	temp = nums[pivot];
	nums[pivot] = nums[i];
	nums[i] = temp;

	quick_sort_nums(nums, l, i -1);
	quick_sort_nums(nums, i + 1, h);

	return;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {

	int *result_nums;
	int i, j;
	nt *sorted_nums;


	if (!nums || (numsSize < 0) ) {
		return NULL;
	}

	sorted_nums = (nt *)malloc(sizeof(nt) * numsSize);
	if (!sorted_nums) {
		return NULL;
	}

	for(i = 0; i < numsSize; i++) {
		sorted_nums[i].val = nums[i];
		sorted_nums[i].idx = i;
	}

#if 0
	for (i = 1; i < numsSize; i++) {
		for (j = 0; j < (numsSize - i); j++) {
			if (sorted_nums[j].val > sorted_nums[j+1].val) {
				nt temp = sorted_nums[j];
				sorted_nums[j] = sorted_nums[j+1];
				sorted_nums[j+1] = temp;
			}
		}
	}
#endif
	quick_sort_nums(sorted_nums, 0, (numsSize-1));

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
	int arr[4] = {2, 7, 11, 4};
	int numsSize = 4;
	int *result;

	result = twoSum(arr, numsSize, 26);

	if (result) {
		printf("[ %d, %d ]\n", result[0], result[1]);
		free(result);
	}

	return;
}

void test_LongestSubstring(void)
{
	char string[512] = "dvdf";
	int len;

	len = lengthOfLongestSubstring(string);

	printf("Len : %d\n", len);

	return;
}



int main(void)
{
	//test_twoSum();
	test_LongestSubstring();
	printf("Done\n");
	return 0;
}
