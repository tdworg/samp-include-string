# samp-include-string

Many useful functions for strings.

#### Functions list:

| Function    | Parameters                                                            | Returns value             |
|-------------|-----------------------------------------------------------------------|---------------------------|
| strncat     | `dest[], const src[], n`                                              | -                         |
| memcmp      | `const s1[], const s2[], n`                                           | -                         |
| strexplode  | `dest[][], const src[], const delimiter = ' '`                        | -                         |
| strcount    | `const src[], const pattern[]`                                        | number of found fragments |
| strerase    | `dest[], const src[], pos = 0, len = sizeof src`                      | -                         |
| strltrim    | `dest[], const src[], const s = ' '`                                  | -                         |
| strrtrim    | `dest[], const src[], const s = ' '`                                  | -                         |
| strtrim     | `dest[], const src[], const s = ' ', e_TDW_STRING_TRIM_Alg:al = BOTH` | -                         |
| find_first  | `const src[], const _char`                                            | pos or -1                 |
| find_last   | `const src[], const _char, const size = sizeof src`                   | pos or -1                 |
