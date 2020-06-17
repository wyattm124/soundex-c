#include <stdio.h>
#include <string.h>

/* lose_repeated will replace consecutive occurances of a charachter in a string
 * with one occurance of the character. for instance aabbc will become abc.
 */

void lose_repeated(char *word, char *res) {
	char curr = word[0];
	char next = word[0];
	int c_ind = 0;
	int n_ind = 0;
	while(next != '\0') {
		res[c_ind] = curr;
		c_ind++;
		while(next == curr) {
			n_ind++;
			next = word[n_ind];
		}
		curr = next;
	}
	res[c_ind] = '\0';
}

/* lose_char_except_first will drop all occurances of c in word and put
 * the result in res. It will not drop the character if it is the first
 * character in the string
 */

void lose_char_except_first(char *word, char *res, char c) {
	int ind = 1;
	int i = 1;
	res[0] = word[0];
	while(word[ind] != '\0') {
		if(word[ind] == c) {
			ind++;
		} else {
			res[i] = word[ind];
			i++;
			ind++;
		}
	}
	res[i] = '\0';
}

/* parse replaces each character with its Soundex value, 'c' if
 * the character is a vowel with out a soundex value, and 'v' if
 * the character is a vowel
 */

char parse(char c) {
	switch(c) {
		case 'a':
		case 'A':
		case 'e':
		case 'E':
		case 'i':
	        case 'I':
		case 'o':
	        case 'O':
		case 'u':
		case 'U':
		case 'y':
		case 'Y':
			return 'v';
		case 'h':
		case 'H':
		case 'w':
		case 'W':
			return 'c';
		case 'b':
		case 'B':
		case 'f':
		case 'F':
		case 'p':
		case 'P':
		case 'v':
		case 'V':
			return '1';
		case 'c':
		case 'C':
		case 'g':
		case 'G':
		case 'j':
		case 'J':
		case 'k':
		case 'K':
		case 'q':
		case 'Q':
		case 's':
		case 'S':
		case 'x':
		case 'X':
		case 'z':
		case 'Z':
			return '2';
		case 'd':
		case 'D':
		case 't':
		case 'T':
			return '3';
		case 'l':
		case 'L':
			return '4';
		case 'm':
		case 'M':
		case 'n':
		case 'N':
			return '5';
		case 'r':
		case 'R':
			return '6';
		default :
			return 'X';
	}
}

/* Sndx computest the Soundex value of word and PUTS THE RESULT
 * BACK INTO WORD (not res, although res is used). I used a slightly
 * different algorithim than what is what outlined on the wiki page
 * but I believe it is more succinct and is accurate :
 *    1. drop all consanants that do not have a Soundex value except if they are the first character
 *    2. replace all consecutive occurances of a character with one occurance of that character
 *    3. drop all the vowels of the string
 *    4. replace the first character with its original value instead of its soundex value
 */

void Sndx(char *word, int len, char *res) {
	char first;
	if(len < 1) {
		res[0] = '0';
		res[1] = '0';
		res[2] = '0';
		res[3] = '\0';
		return;
	} else {
		first = word[0];
	}
	int ind = 0;
	for(; ind < len; ind++) {
		res[ind] = parse(word[ind]);
	}
	res[ind] = '\0';
	lose_char_except_first(res, word, 'c');
	lose_repeated(word, res);
	lose_char_except_first(res, word, 'v');
	word[0] = first;
	int k = 0;
	while((k = strlen(word)) < 4) {
		word[k] = '0';
		word[k+1] = '\0';
	}
	word[4] = '\0';
}

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("Must put in a word to convert to Soundex\n");
		return 1;
	}
	int l = strlen(argv[0]);
	char res[256];
	for(int i = argc - 1; i > 0; i--) {
		Sndx(argv[i], strlen(argv[i]), res);
		printf("%s\n", argv[i]);
	}
	return 0;
}
