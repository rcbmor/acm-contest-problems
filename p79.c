/* Problem 7.9 (Number Base Conversion)
[Greater New York ACM/ICPC 2002] Write a program to convert numbers in one base
to numbers in a second base. There are 62 diﬀerent digits: { 0-9,A-Z,a-z }.

Input:
The ﬁrst line of input contains a single positive integer. This is the number
of lines that follow.Each of the following lines will have a (decimal) input
base followed by a (decimal) output base followed by a number expressed in the
input base. Both the input base and the output base will be in the range from
2 to 62. That is (in decimal) A = 10, B = 11, ..., Z = 35, a = 36, b = 37,
..., z = 61 (0-9 have their usualmeanings).

Sample Input:
3
62 2 abcdefghiz 10 16 1234567890123456789012345678901234567890 16
35 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2

Sample Output:
62 abcdefghiz
2 1011100000100010111110010010110011111001001100011010010001

10 1234567890123456789012345678901234567890
16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2

16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
35 333YMHOUE8JPLT7OX6K9FYCQ8A
*/

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int a, b;
char sa[10000];
char sb[10000];
void rev(char s[])
{
    int l = strlen(s);
    for (int i = 0; i < l - 1 - i; i++)
	swap(s[i], s[l - 1 - i]);
} void

 multi(char s[], int k)
{
    int i, c = 0, d;
    for (i = 0; s[i]; i++) {
	d = (s[i] - '0') * k + c;
	c = d / b;
	d %= b;
	s[i] = '0' + d;
    }
    while (c) {
	s[i] = '0' + (c % b);
	i++;
	c /= b;
    }
    s[i] = '\0';
}

void add(char s[], int k)
{
    int i, c = k, d;
    for (i = 0; s[i]; i++) {
	d = (s[i] - '0') + c;
	c = d / b;
	d %= b;

	s[i] = '0' + d;
    }
    while (c) {
	s[i] = '0' + (c % b);
	i++;
	c /= b;
    }
    s[i] = '\0';
}

void trans(char s[])
{
    int i;
    for (i = 0; s[i]; i++) {
	char &c = s[i];
	if (c >= 'A' &&c <= 'Z')
	    c = '0'+10 + (c - 'A');
	if (c >= 'a' && c <= 'z')
	    c = '0' + 36 + (c - 'a');
    }
}

void itrans(char s[])
{
    int i;
    for (i = 0; s[i]; i++) {
	char &c = s[i];
	int d = c - '0';
	if (d >= 10 && d <= 35)
	    c = 'A'+(d - 10);
	if (d >= 36)
	    c = 'a'+(d - 36);
    }
}

int main()
{
    int q;
    cin >> q;
    int i, j;
    while (q) {
	q--;
	cin >> a >> b >> sa;
	sb[0] = '0';
	sb[1] = '\0';
	cout << a << " " << sa << endl;
	trans(sa);
	for (i = 0; sa[i]; i++) {
	    multi(sb, a);
	    add(sb, sa[i] - '0');
	}
	rev(sb);
	itrans(sb);
	cout << b << " " << sb << endl;
	cout << endl;
    }
    return 0;
}

