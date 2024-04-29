#ifndef __STR_DEAL_H__
#define __STR_DEAL_H__

int stringCompare(const char *str1, const char *str2);// �ַ����ȽϺ���������0��ʾ�����ַ������
void stringReplace(char *str, const char *old, const char *new); // �ַ����滻�������������ҵ���old���ַ����滻Ϊnew���ַ���
int stringFind(const char *haystack, const char *needle) ;// �ַ������Һ����������ҵ������ַ�����������δ�ҵ��򷵻�-1
void stringCopy(char *dest, const char *src) ;// �ַ������ƺ�������src�ַ������Ƶ�dest�ַ�����
void stringConcatenate(char *dest, const char *src); // �ַ������Ӻ�������src�ַ������ӵ�dest�ַ�����ĩβ



//ʹ������
// int main() {
//     char str[] = "Hello World, world!";
//     char old[] = "world";
//     char new[] = "WORLD";
    
//     // �滻���е�"world"Ϊ"WORLD"
//     stringReplace(str, old, new);
    
//     // ��ӡ�滻����ַ���
//     printf("Replaced string: %s\n", str);
    
//     return 0;
// }

// int main() {
//     char src[] = "Hello World";
//     char dest[50]; // ȷ��dest���㹻�Ŀռ����洢���Ƶ��ַ���
    
//     // ����src��dest
//     stringCopy(dest, src);
    
//     // ��ӡ���ƺ���ַ���
//     printf("Copied string: %s\n", dest);
    
//     return 0;
// }

// int main() {
//     char haystack[] = "Hello World";
//     char needle[] = "World";
    
//     // ����needle��haystack�е�λ��
//     int index = stringFind(haystack, needle);
    
//     // ��ӡ���ҽ��
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
    
//     // �Ƚ�str1��str2
//     if (stringCompare(str1, str2) == 0) {
//         printf("str1 and str2 are equal.\n");
//     }
    
//     // �Ƚ�str1��str3
//     if (stringCompare(str1, str3) != 0) {
//         printf("str1 and str3 are not equal.\n");
//     }
    
//     return 0;
// }

// int main() {
//     char dest[50] = "Hello";
//     char src[] = " World";
    
//     // ����src��dest
//     stringConcatenate(dest, src);
    
//     // ��ӡ���Ӻ���ַ���
//     printf("Concatenated string: %s\n", dest);
    
//     return 0;
// }
#endif