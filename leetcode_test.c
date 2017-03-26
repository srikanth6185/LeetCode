/*
 * leetcode_test.c
 *
 *  Created on: Mar 17, 2017
 *      Author: srikanth
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)

double m2(int a , int b)
{
    return (a + b) / 2.0;
}

double m3(int a , int b, int c)
{
    int ma = MAX(a, MAX(b, c));
    int mi = MIN(a, MIN(b, c));

    return (a + b + c - ma - mi);
}

double m4(int a , int b, int c, int d)
{
    int ma = MAX(a, MAX(b, MAX(c,d)));
    int mi = MIN(a, MIN(b, MIN(c,d)));

    return (a + b + c + d - ma -mi) / 2.0;
}

double findMedianArray(int* nums, int n)
{
    if (n % 2) {
        return nums[(n - 1)/2];
    } else {
        return (nums[(n - 1)/2] + nums[n/2])/2.0;
    }
}

double findMedianSortedArraysImpl(int* A, int n, int* B, int m)
{
    int midA, midB;
    printf("A[0]:%d n:%d B[0]:%d m:%d\n", A[0], n, B[0], m);
    if (n == 0) {
        if (m == 0) {
            return 0;
        }
        return findMedianArray(B, m);
    } else if (n == 1) {
        if (m == 1) {
            return (A[0] + B[0])/2.0;
        }
        /* B is odd sized
         * Ex {1} {2,3,4,5,7}
         */
        if (m & 1) {
            return m2(B[m/2],
                      m3(A[0],
                         B[m/2 - 1],
                         B[m/2 + 1]));
        }
        /* B is even sized
         * Ex {1} {2,3,4,5}
         */
        return m3(B[m/2],
                  B[(m - 1)/2] ,
                  A[0]);
    } else if (n == 2) {
        if (m == 2) {
            return m4(A[0], A[1], B[0], B[1]);
        }

        /* B is odd sized*/
        if (m & 1) {
            return m3(B[m/2],
                      MAX(A[0], /*B[(m - 1)/2]*/ B[m/2 -1]),
                      MIN(A[1], /*B[(m + 1)/2]*/ B[m/2 + 1]));
        }

        /*B is even sized*/
        return m4(B[m/2],
                  B[(m - 1)/2],
                  MAX(A[0], B[m/2 - 2]),
                  MIN(A[1], B[m/2 + 1]));
    }

    midA = (n - 1)/2;
    midB = (m - 1)/2;

    if (A[midA] <= B[midB]) {
    	return findMedianSortedArraysImpl(A + midA, n/2 + 1, B, m - midA);
    } else {
        return findMedianSortedArraysImpl(A, n/2 + 1, B + midA, m - midA);
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (!nums1 || !nums2 || (nums1Size < 0) || (nums2Size < 0)) {
        return -1;
    }

    if (nums1Size <= nums2Size) {
        return findMedianSortedArraysImpl(nums1, nums1Size, nums2, nums2Size);
    }

    return findMedianSortedArraysImpl(nums2, nums2Size, nums1, nums1Size);
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

void test_MedianOfSortedArrays()
{
	int arr2[] = {9,28,245,307,461,561,680,683,688,711,728,755,789,880,937,962,1154,1166,1179,1259,1315,1331,1459,1545,1638,1642,1652,1658,1670,1877,2002,2015,2046,2109,2159,2162,2180,2197,2316,2338,2372,2419,2423,2529,2628,2636,2745,2793,2818,2833,2962,3009,3016,3080,3170,3258,3270,3337,3362,3452,3693,3788,3802,3979,4044,4070,4074,4074,4353,4355,4439,4586,4626,4716,4719,4790,4887,4924,4925,4929,4992,5034,5051,5121,5121,5320,5336,5518,5615,5700,5700,5716,5751,5905,5911,5947,5997,6015,6045,6153,6180,6226,6256,6321,6321,6340,6588,6726,6735,6886,6955,6964,6980,6998,7007,7058,7150,7274,7293,7294,7341,7354,7359,7427,7433,7511,7593,7887,7943,8033,8217,8246,8248,8260,8270,8288,8307,8370,8398,8435,8446,8460,8505,8526,8565,8806,8824,8872,8904,8992,9035,9037,9048,9113,9115,9274,9316,9336,9432,9445,9466,9562,9582,9592,9803,9897,9924,9999,10015,10043,10149,10214,10260,10309,10320,10323,10350,10415,10510,10613,10671,10712,10726,10769,10824,10832,11015,11056,11059,11067,11082,11221,11268,11271,11299,11325,11327,11339,11377,11390,11440,11560,11656,11740,11756,11830,11839,11843,11882,11932,11934,11960,11962,12075,12141,12163,12190,12314,12327,12379,12420,12477,12511,12512,12724,12802,12843,12914,12952,12968,13006,13049,13073,13239,13298,13428,13471,13496,13592,13641,13659,13795,13812,13841,13885,13949,14043,14120,14150,14173,14230,14250,14278,14298,14441,14455,14456,14584,14671,14735,14889,14914,14946,14949,14978,14993,15175,15239,15280,15565,15577,15582,15637,15652,15699,15701,15772,15841,15844,15854,15936,16060,16141,16175,16182,16195,16241,16287,16370,16397,16461,16516,16718,16739,16752,16795,16859,16911,16943,17054,17062,17064,17065,17065,17091,17093,17101,17147,17186,17240,17265,17326,17473,17499,17518,17552,17610,17628,17655,17774,17821,17847,17854,17949,18012,18070,18086,18103,18122,18130,18249,18260,18442,18541,18569,18735,18778,18910,18976,18986,19023,19116,19140,19156,19183,19194,19217,19227,19252,19290,19311,19344,19414,19479,19524,19571,19633,19648,19651,19723,19728,19733,19756,19815,19853,19944,20042,20155,20208,20238,20246,20255,20382,20413,20438,20470,20583,20590,20611,20642,20715,20755,20919,20948,20958,21120,21210,21271,21351,21356,21380,21436,21496,21544,21640,21709,21721,21724,21733,21860,21879,21948,21953,21955,21992,21994,22028,22124,22128,22131,22191,22221,22225,22487,22548,22560,22640,22640,22643,22656,22691,22769,22928,22935,23001,23007,23011,23053,23080,23159,23165,23236,23243,23297,23425,23449,23480,23553,23565,23646,23673,23711,23816,23882,23882,24009,24020,24036,24175,24236,24262,24288,24322,24372,24416,24429,24668,24785,24828,24883,25008,25079,25107,25205,25470,25539,25569,25633,25709,25719,25817,25873,25953,26026,26049,26132,26139,26229,26338,26385,26473,26511,26536,26538,26635,26678,26754,26846,26884,26994,27015,27336,27424,27510,27536,27589,27701,27749,27810,27950,27989,27989,27991,28006,28028,28089,28137,28174,28193,28198,28257,28261,28363,28434,28466,28479,28531,28547,28586,28650,28696,28780,28816,28839,28855,29005,29108,29162,29240,29282,29335,29381,29384,29491,29573,29673,29677,29710,29938,29984,30051,30089,30108,30141,30177,30358,30396,30560,30584,30674,30675,30678,30828,30954,30994,31132,31193,31279,31346,31355,31466,31514,31595,31690,31843,31923,32060,32175,32230,32233,32241,32338,32370,32410,32456,32460,32601,32689,32761};
	int arr1[] = {20,481,516,770,1063,1247,1275,1469,1681,1974,2093,2324,2440,2548,2553,2759,2990,3032,3578,3813,3869,4019,4713,4741,4744,4771,4777,4863,5009,5266,5307,5476,5549,5673,5740,5925,6049,6364,6455,6565,6706,7094,7129,7259,7347,7364,7578,7635,7791,7793,7837,7863,8046,8046,8346,8535,8655,8946,9079,9594,10638,10991,11110,11167,11603,11718,11857,11960,12057,12109,12240,12287,12412,12565,12610,12680,12701,12814,12907,13128,13170,13385,13493,13572,13640,13947,13986,14139,14173,14319,14382,14407,14473,14497,14949,15038,15056,15416,15523,15649,15921,16451,16542,16579,16723,16894,17010,17410,17452,17725,17925,18070,18298,18329,18438,18741,18808,19247,19330,19778,19875,20595,20631,20765,20782,20998,21135,21525,21576,21622,21755,21891,21920,22097,22196,22770,22791,22841,23024,23066,23074,23094,23509,23863,24014,24101,24194,24360,24426,24499,24523,26026,26036,26237,26282,26380,26399,26883,27276,27304,27464,27482,27531,27571,27693,27736,27948,27950,28015,28029,28034,28369,28484,28538,28610,28845,29019,29122,29142,29173,29251,29304,29342,29517,29595,29731,29750,29830,29961,29987,30053,30374,30398,30510,30633,30661,30748,31278,31310,31850,31919,32175,32239,32261,32433,32457,32504,32761};
	//int arr1[4] = {1,2,3,4};
    //int arr2[6] = {5,6,7,8,9,10};
    double median;

    median = findMedianSortedArrays(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
    printf("Median:%f\n", median);

    return;
}

int main(void)
{
    //test_twoSum();
    //test_LongestSubstring();
	test_MedianOfSortedArrays();
    printf("Done\n");
    return 0;
}
