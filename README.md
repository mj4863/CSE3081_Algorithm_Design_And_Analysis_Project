# CSE3081_Algorithm_Design_And_Analysis_Project
2024-2 알고리즘설계와분석

```
AlgorithmDesignAnalysis/
├── HW1_BrightestArea/        # Maximum‐Sum Subarray/Subrectangle & Brightest Area Detection
├── HW2_PriorityQueue/        # Min-Heap 기반 Priority Queue 구현 및 테스트
├── HW3_SortingMethods/       # 여섯 가지 정렬 알고리즘 구현 및 최적화 실험
├── HW4_DynamicProgramming/   # Convex Polygon Triangulation & Longest Palindromic Subsequence
└── HW5_MST/                  # Kruskal MST 구현 및 대용량 그래프 성능 분석

```

---

## HW1: Detection of Brightest Area in 2D Image

**핵심 요구사항**

* **1D Maximum Sum Subarray**

  * O(n log n) 분할정복법 (Algorithm 1)
  * O(n) Kadane’s algorithm (Algorithm 2)
  * 각 알고리즘마다 최대합, 시작/끝 인덱스 출력
* **2D Maximum Sum Subrectangle**

  * O(n⁴) Summed-Area Table (Algorithm 3)
  * O(n³ log n) Algorithm 1 재사용 (Algorithm 4)
  * O(n³) Algorithm 2 재사용 (Algorithm 5)
  * 각 알고리즘마다 최대합, 좌상/우하 코너 인덱스 출력
* **입출력 방식**

  * `HW1 config.txt` 에 테스트케이스 수 및
    `<알고리즘번호> <.pgm 파일> <평균값 파일> <출력 파일>` 순으로 기술
  * 밝기 편차 영상 생성: 원본 픽셀 값에서 평균값 파일의 정수 평균 빼기
  * 출력 파일에 `s k i l j` (sum, top-left (k,i), bottom-right (l,j))
* **실험 및 보고**

  * 다양한 n (예: 64,128,256)에 대해 ms 단위 수행 시간 측정 (Release/x64)
  * 평균값 취한 반복 실험 후 이론적 복잡도와 실제 시간 관계 분석
  * 실험 환경(OS, CPU, RAM, 컴파일러 등) 명시

---

## HW2: Min-Heap 기반 Priority Queue

**핵심 요구사항**

1. **PQ24**: 기본 배열 기반 Min-Heap 구현
2. **adjust\_client\_priority(clientID, inc)**: client의 priority 증가 후 힙 업데이트
3. **min\_heap\_adjust\_priority(index, inc)**: 내부 힙 노드 우선순위 조정
4. 제공된 `example1()`\~`example5()` 테스트 함수에서 올바른 동작 확인
5. 테스트 명령어(`commands.txt`)로

   * 입력 파일 경로 읽기
   * `result_cl_ex_i.txt` & `result_mh_ex_i.txt` 생성

---

## HW3: Sorting Methods

**핵심 요구사항**

* `sort.cpp` 파일에 다음 6가지 함수 구현

  1. `insertion` (기본 삽입정렬)
  2. `heap` (교과서적 힙정렬)
  3. `weird` (min-heap 후 삽입정렬)
  4. `quick_classic` (기본 퀵정렬)
  5. `intro` (IntroSort)
  6. `merge_with_insertion` (병합정렬 + 삽입정렬 최적화)
* **실험 및 최적화 평가**

  * 입력 크기 범위 선정 → 시간 측정 → 테이블 및 그래프/수식 분석
  * 이론적 시간복잡도와 실제 성능 비교
* **제출**

  * `SortingMethods/` 디렉토리 전체를 Visual Studio 압축 제출

---

## HW4: Dynamic Programming 연습

### Problem 1: Minimal Triangulation

* Convex 다각형 n ≤ 200
* `HW4/Problem 1/command.txt` 로
  `<입력파일> <출력파일>` 쌍 읽기
* 입력:

  ```
  n
  x₀ y₀
  …
  xₙ₋₁ yₙ₋₁
  ```
* 출력:

  ```
  total_length (소수점 둘째 자리 반올림)
  i₁ j₁
  …
  iₙ₋₃ jₙ₋₃
  ```
* 인덱스 정렬 규칙: (i,j)쌍을 i 오름차순, 같으면 j 오름차순

### Problem 2: Longest Palindromic Subsequence

* `HW4/Problem 2/LPS command.txt` 로
  `<입력파일> <출력파일>` 쌍 읽기
* 입력:

  ```
  T
  L
  문자열₁
  L
  문자열₂
  …
  ```
* 출력:

  ```
  T
  len₁
  LPS₁
  len₂
  LPS₂
  …
  ```
* 대소문자 구분, subsequence 기반 DP 구현

---

## HW5: Kruskal Minimum Spanning Tree

**핵심 요구사항**

* 가중치 비연결 그래프 (n vertices, m edges, 최대 weight)
* `commands.txt` 첫 줄에 그래프 디렉토리, 둘째 줄에
  `<파일명>`으로 입력, 셋째 줄에
  `<출력파일>`로 저장 경로 지정
* **Kruskal + Disjoint Set + Min-Heap**

  * O(|E| log |V|) 복잡도 달성
* 출력 파일:

  ```
  C                    # connected component 개수
  v₁ w₁
  …
  v_C w_C
  ```

  – vᵢ: 컴포넌트의 정점 수, wᵢ: MST 총 weight
* **실험 및 보고**

  * 6개 대용량 그래프에 대해 수행 시간(ms), scanned edges 수 등 측정
  * 이론적 복잡도와 실제 시간 관계 분석

---

### 공통 실행 방법 예시

```bash
# 각 과제 디렉토리로 이동하여 빌드/실행
cd HWX_.../
# (Visual Studio 프로젝트이거나 Java/C++ 등 언어별 컴파일 & 실행)
```

