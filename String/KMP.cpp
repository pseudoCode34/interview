#include <iostream>
#include <vector>

// Fills lps[] for given patttern pat[0..pat.size()-1]
void computeLPSArray(std::string &pat, std::vector<size_t> &lps) {
	// length of the previous longest prefix suffix
	size_t len = 0;
	lps[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to pat.size()-1
	size_t i = 1;
	while (i < pat.size()) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
			continue;
		}
		// This is tricky. Consider the example. AAACAAAA and i = 7. The idea is
		// similar to search step.
		if (len != 0) {
			len = lps[len - 1];
			continue;
			// Also, note that we do not increment i here
		}
		lps[i] = 0;
		i++;
	}
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(std::string &pat, std::string &txt) {
	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	std::vector<size_t> lps(pat.size());

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, lps);

	size_t i = 0; // index for txt[]
	size_t j = 0; // index for pat[]
	while (i < txt.size()) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == pat.size()) {
			std::cout << "Found pattern at index " << i - j << std::endl;
			j = lps[j - 1];
		}

		if ((i >= txt.size()) || (pat[j] == txt[i])) continue;

		// mismatch after j matches
		// Do not match lps[0..lps[j-1]] characters, they will match anyway
		if (j != 0) j = lps[j - 1];
		else
			++i;
	}
}

// Driver program to test above function
int main() {
	std::string txt("ABABDABACDABABCABAB");
	std::string pat("ABABCABAB");
	KMPSearch(pat, txt);
	return 0;
}
