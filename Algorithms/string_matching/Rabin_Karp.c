/*
calculateHash 函數：

計算初始哈希值，使用 CHARSET（假設為 ASCII）作為進制，並使用質數進行取模以避免溢出。
recalculateHash 函數：

使用滾動哈希公式，避免重新計算整個子字串的哈希值，提升效率。
通過減去第一個字符的影響，並加入新字符來更新哈希值。
RabinKarp_Search 函數：

遍歷文本的每個可能的子字串，逐一比較哈希值。
如果哈希值匹配，再進一步進行逐字符比較以確認是否真匹配（避免哈希碰撞）。

*/

#include <stdio.h>
#include <string.h>

#define PRIME 101 // 質數作為哈希基數
#define CHARSET 256 // 字元集大小，假設為 ASCII

// 計算初始哈希值
int calculateHash(const char *str, int length, int prime) {
    int hash = 0;
    for (int i = 0; i < length; i++) {
        hash = (hash * CHARSET + str[i]) % prime;
    }
    return hash;
}

// 滾動哈希值的重新計算
int recalculateHash(const char *str, int oldIndex, int newIndex, int currentHash, int patternLength, int prime) {
    currentHash = (currentHash - str[oldIndex] * ((int)pow(CHARSET, patternLength - 1)) % prime + prime) % prime;
    currentHash = (currentHash * CHARSET + str[newIndex]) % prime;
    return currentHash;
}

// Rabin-Karp 搜索演算法
void RabinKarp_Search(const char *text, const char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    if (patternLength > textLength) {
        printf("Pattern length is greater than text length. No match possible.\n");
        return;
    }

    // 計算初始的哈希值
    int patternHash = calculateHash(pattern, patternLength, PRIME);
    int textHash = calculateHash(text, patternLength, PRIME);

    // 滾動哈希搜索
    for (int i = 0; i <= textLength - patternLength; i++) {
        // 如果哈希值匹配，逐字符確認是否真的匹配
        if (patternHash == textHash) {
            int match = 1;
            for (int j = 0; j < patternLength; j++) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // 計算下一個子字串的哈希值
        if (i < textLength - patternLength) {
            textHash = recalculateHash(text, i, i + patternLength, textHash, patternLength, PRIME);
        }
    }
}

int main() {
    const char *text = "ababcabcabababd";
    const char *pattern = "ababd";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    RabinKarp_Search(text, pattern);

    return 0;
}
