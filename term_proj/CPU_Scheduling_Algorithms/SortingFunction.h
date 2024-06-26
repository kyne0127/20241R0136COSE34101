#ifndef __COMPARE__FUNCTION__
#define __COMPARE__FUNCTION__

// Sorting Function

#include "./Process.h"

/**
 * [compare_by_end_time 종료 시간 기준 비교 함수]
 * @param  a [process 구조체 1]
 * @param  b [process 구조체 2]
 * @return   [비교 결과]
 */
int compare_by_end_time(const void *a, const void *b)
{
    /* const void 형 변수 형 변환 */
    Process *ptA = (Process *)a;
    Process *ptB = (Process *)b;

    /* ptA의 end 시간이 작을 경우 */
    if (ptA->end_time < ptB->end_time)
        return -1;
        // -1 반환

    /* ptA의 end 시간이 클 경우 */
    else if (ptA->end_time > ptB->end_time)
        return 1;
        // 1 반환

    /* end 시간이 같을 경우 */
    else
        return 0;
        // 0 반환
}

/**
 * [quick_sort_by_end_time 종료 시간 기준 퀵 정렬 함수]
 * @param p   [process 구조체 배열]
 * @param len [process 수]
 */
void quick_sort_by_end_time(Process p[], int len)
{
    qsort(p, len, sizeof(Process), compare_by_end_time);
    // 내장 함수인 qsort 함수 호출 compare_by_end_time 함수로 종료 시간으로 비교
}


int compare_by_turnaround_time(const void *a, const void *b)
{
    /* const void 형 변수 형 변환 */
    Process *ptA = (Process *)a;
    Process *ptB = (Process *)b;

    /* ptA의 end 시간이 작을 경우 */
    if (ptA->end_time < ptB->end_time)
        return -1;
        // -1 반환

    /* ptA의 end 시간이 클 경우 */
    else if (ptA->end_time > ptB->end_time)
        return 1;
        // 1 반환

    /* end 시간이 같을 경우 */
    else
        return 0;
        // 0 반환
}

void quick_sort_by_turnaround_time(Process p[], int len)
{
    qsort(p, len, sizeof(Process), compare_by_turnaround_time);
    // 내장 함수인 qsort 함수 호출 compare_by_turnaround_time 함수로 종료 시간으로 비교
}

/**
 * [merge 분할된 배열 합병 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 index]
 * @param mid   [배열의 가운데 index]
 * @param right [배열의 가장 오른쪽 index]
 */
void merge(Process arr[], int left, int mid, int right)
{
    int fIdx = left;
    // 왼쪽 배열의 시작 index를 저장할 변수 선언 및 초기화
    int rIdx = mid + 1;
    // 오른쪽 배열의 시작 index를 저장할 변수 선언 및 초기화
    int i;
    // 반복문에서 사용할 변수 선언

    Process *sortArr = (Process *)malloc(sizeof(Process) * (right + 1));
    // 정렬된 배열을 저장할 배열 동작 할당
    int sIdx = left;

    /* left부터 mid까지의 블록과 mid + 1부터
       right까지의 블록을 비교하는 부분 */
    while (fIdx <= mid && rIdx <= right)
    {
        /* left의 도착 시간이 right보다 작을 경우 */
        if (arr[fIdx].arrive_time <= arr[rIdx].arrive_time)
            sortArr[sIdx] = arr[fIdx++];
            // left의 데이터를 결과 배열에 복사

        /* 그렇지 않을 경우 */
        else
            sortArr[sIdx] = arr[rIdx++];
            // right의 데이터를 결과 배열에 복사

        sIdx++;
        // 결과 배열의 index 증가
    }

    /* 오른쪽 배열의 데이터가 남아있는 경우 */
    if (fIdx > mid)
    {
        /* 오른쪽 배열의 남은 데이터 만큼 반복 */
        for (i = rIdx; i <= right; i++, sIdx++)
            sortArr[sIdx] = arr[i];
            // 오른쪽 배열의 데이터를 결과 배열에 복사
    }

    /* 왼쪽 배열의 데이터가 남아있는 경우 */
    else
    {
        /* 왼쪽 배열의 남은 데이터 만큼 반복 */
        for (i = fIdx; i <= mid; i++, sIdx++)
            sortArr[sIdx] = arr[i];
            // 왼쪽 배열의 데이터를 결과 배열에 복사
    }

    /* 배열의 데이터 개수만큼 반복 */
    for (i = left; i <= right; i++)
        arr[i] = sortArr[i];
        // 원본 배열에 복사

    free(sortArr);
    // 배열 메모리 할당 해제
}

/**
 * [merge_sort_by_arrive_time 도착 시간을 기준 합병 정렬 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 index]
 * @param right [배열의 가장 오른쪽 index]
 */
void merge_sort_by_arrive_time(Process arr[], int left, int right)
{
    int mid;
    // 중간 지점 index

    /* left가 right보다 작으면 실행 */
    if (left < right)
    {
        /* 중간 지점을 계산한다 */
        mid = (left + right) / 2;

        /* 둘로 나눠서 각각을 정렬 */
        merge_sort_by_arrive_time(arr, left, mid);
        merge_sort_by_arrive_time(arr, mid + 1, right);

        /* 정렬된 두 배열을 병합 */
        merge(arr, left, mid, right);
    }
}

#endif
