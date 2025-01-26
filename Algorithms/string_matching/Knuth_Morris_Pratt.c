/*
computeLPSArray 函數：
    計算部分匹配表 (LPS)。
    使用動態規劃的方式找到 pattern 自身的前綴與後綴相同的長度。
    這部分的運行時間為 𝑂(𝑚)，其中 𝑚 是 pattern 的長度。

KMP_Search 函數：
    使用 LPS 表進行字串比對。
    當發生失配時，根據 LPS 表快速跳過已知的匹配部分，避免重複檢查。
    這部分的運行時間為 𝑂(𝑛)，其中 𝑛 是 text 的長度。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 函數宣告
void computeLPSArray(const char *pattern, int patternLength, int *lps);
void KMP_Search(const char *text, const char *pattern);

int main() {
    const char *text = "ababcabcabababd";
    const char *pattern = "ababd";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    
    KMP_Search(text, pattern);

    return 0;
}

// 計算部分匹配表 (LPS: Longest Prefix which is also Suffix)
void computeLPSArray(const char *pattern, int patternLength, int *lps) {
    int length = 0; // 當前的前綴長度
    lps[0] = 0;     // 第一個元素永遠為 0
    int i = 1;

    while (i < patternLength) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP 搜索演算法
void KMP_Search(const char *text, const char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    // 準備部分匹配表
    int *lps = (int *)malloc(patternLength * sizeof(int));
    computeLPSArray(pattern, patternLength, lps);

    int i = 0; // text 的索引
    int j = 0; // pattern 的索引

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps); // 釋放動態記憶體
}
