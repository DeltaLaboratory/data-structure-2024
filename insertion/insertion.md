# 삽입 정렬 (Insertion Sort)

삽입 정렬은 모든 요소를 앞의 요소와 비교하면서 적절한 위치에 찾아 삽입하여 정렬하는 알고리즘이다.

## 알고리즘 작동 방식

1. 두 번째 요소부터 시작하여 배열을 순회한다.
2. 현재 요소를 key로 저장한다.
3. key보다 앞에 있는 요소들 중 key보다 큰 요소들을 뒤로 한 칸씩 이동시킨다.
4. key를 적절한 위치에 삽입한다.
5. 배열의 끝에 도달할 때까지 2-4 과정을 반복한다.

## 시각화

아래는 삽입 정렬의 과정을 보여주는 시각화이다:

```
초기 배열: [5, 2, 4, 6, 1, 3]

1단계: [2, 5, 4, 6, 1, 3]
2단계: [2, 4, 5, 6, 1, 3]
3단계: [2, 4, 5, 6, 1, 3]
4단계: [1, 2, 4, 5, 6, 3]
5단계: [1, 2, 3, 4, 5, 6]

최종 정렬된 배열: [1, 2, 3, 4, 5, 6]
```

## 시간 복잡도
최악인 경우는, 모든 요소가 역순으로 정렬되어 있을 때이다. 이 때, 모든 요소를 비교하면서 삽입해야 하므로 $O(n^2)$이다.

- 비교 횟수는 $n + (n - 1) + (n - 2) + ... + 1 = n(n + 1) / 2$이다.
- 이동 횟수는 $n + (n - 1) + (n - 2) + ... + 1 = n(n + 1) / 2$이다.

평균인 경우는, 모든 요소가 랜덤하게 정렬되어 있을 때이다. 이 때, 평균적으로 $O(n^2)$이다.

- 비교 횟수는 $n + (n - 1) + (n - 2) + ... + 1 = n(n + 1) / 2$이다.
- 이동 횟수는 $n + (n - 1) + (n - 2) + ... + 1 = n(n + 1) / 2$이다.

최선인 경우는, 모든 요소가 이미 정렬되어 있을 때이다. 이 때, 모든 요소를 한번씩만 비교하면 되므로 $O(n)$이다.

- 비교 횟수는 $n - 1$이다.
- 이동 횟수는 0이다.

## 공간 복잡도
주어진 배열 안에서 교환을 통해 정렬을 수행하므로 $O(n)$이다. 추가적인 메모리 공간을 거의 사용하지 않는 in-place 알고리즘이다.

## 구현 세부
1. 현재 요소를 임시 변수(key)에 저장한다.
2. key를 적절한 위치에 삽입한다.
3. key보다 큰 요소들을 한 칸씩 뒤로 밀어넣는다.

## 안정성
삽입 정렬은 안정적인 정렬 알고리즘이다. 같은 값을 가진 요소가 있을 때, 그들의 상대적인 순서가 유지된다. 이는 key를 삽입할 때, 같은 값을 가진 요소의 뒤에 삽입하기 때문이다.

## 장단점
장점:
- 구현이 간단하고 이해하기 쉽다.
- 작은 데이터셋에 효율적이다.
- 거의 정렬된 데이터에 대해 매우 효율적이다.
- 안정적인 정렬 알고리즘이다.

단점:
- 큰 데이터셋에 대해 비효율적이다.
- 평균 및 최악의 경우 시간 복잡도가 $O(n^2)$로 높다.

## 코드
```c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define ELEMENT_RANGE 1024 * 1024

void insertion_sort(int* arr, size_t size) {
    for (int i = 1; i < size; i++) {
        const int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 배열이 정렬되어 있는지 확인
int is_sorted(int* arr, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int *arr = malloc(sizeof(int) * ARRAY_SIZE);

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % ELEMENT_RANGE;
    }

    printf("Before sorting: ");
    if (ARRAY_SIZE <= 100) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Too many elements to print");
    }
    printf("\n");

    insertion_sort(arr, ARRAY_SIZE);

    printf("After sorting: ");
    if (ARRAY_SIZE <= 100) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Too many elements to print");
    }
    printf("\n");

    if (is_sorted(arr, ARRAY_SIZE)) {
        printf("Sorting is successful\n");
    } else {
        printf("Sorting is failed\n");
    }

    free(arr);
    return 0;
}
```