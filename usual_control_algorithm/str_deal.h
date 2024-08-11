/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       str_deal.c/h
  * @brief      字符串处理算法
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Aug-11-2024     ZSB              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
 
#ifndef __STR_DEAL_H__
#define __STR_DEAL_H__

int stringCompare(const char *str1, const char *str2);// 字符串比较函数，返回0表示两个字符串相等
void stringReplace(char *str, const char *old, const char *new); // 字符串替换函数，将所有找到的old子字符串替换为new子字符串
int stringFind(const char *haystack, const char *needle) ;// 字符串查找函数，返回找到的子字符串的索引，未找到则返回-1
void stringCopy(char *dest, const char *src) ;// 字符串复制函数，将src字符串复制到dest字符串中
void stringConcatenate(char *dest, const char *src); // 字符串连接函数，将src字符串连接到dest字符串的末尾



//使用例程
// int main() {
//     char str[] = "Hello World, world!";
//     char old[] = "world";
//     char new[] = "WORLD";
    
//     // 替换所有的"world"为"WORLD"
//     stringReplace(str, old, new);
    
//     // 打印替换后的字符串
//     printf("Replaced string: %s\n", str);
    
//     return 0;
// }

// int main() {
//     char src[] = "Hello World";
//     char dest[50]; // 确保dest有足够的空间来存储复制的字符串
    
//     // 复制src到dest
//     stringCopy(dest, src);
    
//     // 打印复制后的字符串
//     printf("Copied string: %s\n", dest);
    
//     return 0;
// }

// int main() {
//     char haystack[] = "Hello World";
//     char needle[] = "World";
    
//     // 查找needle在haystack中的位置
//     int index = stringFind(haystack, needle);
    
//     // 打印查找结果
//     if (index != -1) {
//         printf("Found '%s' at index %d.\n", needle, index);
//     } else {
//         printf("'%s' not found in '%s'.\n", needle, haystack);
//     }
    
//     return 0;
// }

// int main() {
//     char *str1 = "Hello";
//     char *str2 = "Hello";
//     char *str3 = "World";
    
//     // 比较str1和str2
//     if (stringCompare(str1, str2) == 0) {
//         printf("str1 and str2 are equal.\n");
//     }
    
//     // 比较str1和str3
//     if (stringCompare(str1, str3) != 0) {
//         printf("str1 and str3 are not equal.\n");
//     }
    
//     return 0;
// }

// int main() {
//     char dest[50] = "Hello";
//     char src[] = " World";
    
//     // 连接src到dest
//     stringConcatenate(dest, src);
    
//     // 打印连接后的字符串
//     printf("Concatenated string: %s\n", dest);
    
//     return 0;
// }
#endif