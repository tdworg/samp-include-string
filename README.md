# samp-include-string

Many useful functions for strings.

#### Functions list:

| Function | Parameters                                                            | Returns value             |
|----------|-----------------------------------------------------------------------|---------------------------|
| strncat  | `dest[], const src[], n`                                              | -                         |
| memcmp   | `const s1[], const s2[], n`                                           | -                         |
| strexpl  | `dest[][], const src[], const delimiter = ' '`                        | -                         |
| strcnt   | `const src[], const pattern[]`                                        | number of found fragments |
| strerase | `dest[], const src[], pos = 0, len = sizeof src`                      | -                         |
| strltrm  | `dest[], const src[], const s = ' '`                                  | -                         |
| strrtrm  | `dest[], const src[], const s = ' '`                                  | -                         |
| strtrm   | `dest[], const src[], const s = ' ', e_TDW_STRING_TRIM_Alg:al = BOTH` | -                         |
