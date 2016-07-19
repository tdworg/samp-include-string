# samp-include-string

Many useful functions for strings.

#### Functions list:

| Function       | Parameters                                                                              | Returns value             |
|----------------|-----------------------------------------------------------------------------------------|---------------------------|
| strncat        | `dest[], const src[], n`                                                                | -                         |
| memcmp         | `const s1[], const s2[], n`                                                             | -                         |
| strexplode     | `dest[][], const src[], const delimiter = ' '`                                          | -                         |
| strcount       | `const src[], const pattern[]`                                                          | number of found fragments |
| strerase       | `dest[], const src[], pos = 0, len = sizeof src`                                        | -                         |
| strltrim\_c    | `dest[], const src[], const s = ' '`                                                    | -                         |
| strltrim\_s    | `dest[], const src[], const s[] = " "`                                                  | -                         |
| strrtrim\_c    | `dest[], const src[], const s = ' '`                                                    | -                         |
| strrtrim\_s    | `dest[], const src[], const s[] = " "`                                                  | -                         |
| strtrim\_c     | `dest[], const src[], const s = ' ', e_TDW_STRING_TRIM_Alg:al = BOTH`                   | -                         |
| strtrim\_s     | `dest[], const src[], const s[] = " ", e_TDW_STRING_TRIM_Alg:al = BOTH`                 | -                         |
| find_first\_c  | `const src[], const _char`                                                              | pos or -1                 |
| find_first\_s  | `const src[], const _chars[]`                                                           | pos or -1                 |
| find_last\_c   | `const src[], const _char, const size = sizeof src`                                     | pos or -1                 |
| find_last\_s   | `const src[], const _chars[], const size = sizeof src`                                  | pos or -1                 |
| strreplace     | `dest[], const src[], const replace[], const replacment[], start = 0, len = 0xFFFFFFFF` |                           |
| strtok\_c      | `dest[], const src[], &index, const delim = ' '`                                        |                           |
| strtok\_s      | `dest[], const src[], &index, const delim[] = " "`                                      |                           |
| stoi           | `const src[]`                                                                           | result                    |
| stof           | `const src[]`                                                                           | Float:result              |