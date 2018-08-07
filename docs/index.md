# jregex



*Huang Jiahua*

The jregex library provides four ways to handle problems with regular expression including matching and searching. And the users are provided with four function. 

## Matching

The first function provided is to return wheter a string matches the given regular expression.

```c++
#include "jregex/jregex.h"
#include <string>
#include <iostream>

const std::string seq = "AGGGCT";
jregex::jreg pat("AG*C?T{1,}");
if (jregex::jregex_match(seq, pat))
    std::cout << "Positive!" << std::endl;
```

## Searching
The second function provided is to return wheter there is a sub-string that matches the given regular expression.

```c++
#include "jregex/jregex.h"
#include <string>
#include <iostream>

const std::string seq = "GTCCAGGGCTACTG";
jregex::jreg pat("AG*C?T{1,}");
if (jregex::jregex_search(seq, pat))
    std::cout << "Positive!" << std::endl;
```

## Finding the First

The third function provided is to return the position and length of the sub-string that matches the regular expression. The returned value is a class named `jregex::result`. It has three member function: `position()`, `length()` and `str()` returning the matching **position**, the **length** of the matching sub-string and the **sub-string** respectively. The `str()` returns a copy of the sub-string.

```c++
#include "jregex/jregex.h"
#include <string>
#include <iostream>

const std::string seq = "GTCCAGGGCTACTG";
jregex::jreg pat("AG*C?T{1,}");
jregex::result re =
	jregex::jreg_find(seq, pat);
if (re.position() != seq.size()) // suggesting matching sucessfully
	std::cout << "It suggests positive from No."
	          << seq.position()
	          << " with " << seq.length()
	          << "characters: " << seq.str()
	          << std::endl;	
```

## Finding All

The final function provided return an array of `result`s mentioned above, and the array is stored in a `std::vector<result>` or `jregex::results`. Mind that it doesn't matches recursively, for example, the matching position of `"AAAA"` by the `jreg("AA")` is 0 and 2, not 0, 1 and 2.

```c++
const std::string seq = "GTCACCTTCCA";
jregex::jreg pat("[^AG]CA");
jregex::results arr; // empty
jregex::jregex_find(seq,
                    arr, // reference of the array
                    pat);
for (jregex::result re : arr)
    std::cout << re.str() << std::endl;  
```                  

## Supported Regular Expression Grammer 

| name | notation | example |
| :------: | :------: | :------: |
| concatenation | characters | abcd |
| parentheses | enclosed in ( ) | a(bc)d |
| or | separated by \| | (ab\|c)d |
| closure | * | (ab)*c\* |
| at least 1 | + | (ab)+c+ |
| 0 or 1| ? | (ab)?c? |
| specific times | count in { } | m{2}d |
| range of times | range in { } | m{1,2}d{3,} |
| wildcard | . | .+\\.cpp |
| specified set| enclosed in [ ] | [AEIOU]\* |
| set with range | [ ] with - | [A-Z][0-9] |
| complement | [ ] with ^ | [^AEIOU]\* |
| escape | \\ | \\\* \\+ |
| space | \s \S \t | \s \S \t ... |
| digit | \d \D | \d \D |
| alpha and digit | \w \W | \w \W |


## Not Yet Supported 

- Anchors: ^ and $
- \b \B representing the boundaries
- \1 \2 \<foo\> referencing the clusters
- ?= ?<= ?! ?<!
- <.+?>
- Whatever not mentioned above





